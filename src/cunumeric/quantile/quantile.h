/* Copyright 2022 NVIDIA Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

template <typename index_t = int32_t, typename real_t = double>
struct Quantile {
  __host__ __device__ Quantile(real_t gamma_l  = 0.0,
                               real_t gamma_r  = 1.0,
                               real_t f1       = 0.0,
                               real_t f2       = 0.0,
                               index_t j_decr  = 0,
                               real_t pos_h    = 0.0,
                               bool continuous = false,
                               bool null_0     = false,
                               bool nearest    = false)
    : gamma_l_(gamma_l),
      gamma_r_(gamma_r),
      f1_(f1),
      f2_(f2),
      pos_h_(pos_h),
      j_decr_(j_decr),
      continuous_(continuous),
      null_0_(null_0),
      nearest_(nearest)
  {
  }

  //__host__ __device__ qualified cannot be default;
  //
  //__host__ __device__ Quantile(Quantile const& ) = default;
  //__host__ __device__ Quantile& operator = (Quantile const& ) = default;

  __host__ __device__ thrust::tuple<real_t, index_t> gamma_j(real_t q, index_t n) const
  {
    if (q >= real_t{1.0}) return thrust::make_tuple(real_t{1.0}, n - 2);

    real_t pos_try  = q * (n + f1_) + f2_;
    real_t pos_test = pos_try - pos_h_;

    real_t pos = pos_test < 0 ? 0.0 : pos_try;
    real_t k =
      std::floor(pos);  // <- works on device; or, static_cast<index_t>(pos); // floor() via cast

    auto jk   = k > 0 ? k - j_decr_ : 0;
    index_t j = static_cast<index_t>(jk);

    real_t gamma = 0.0;
    if (continuous_) {
      gamma = (pos < 1 || pos > n) ? 0.0 : pos - k;
    } else {
      bool is_pos_h_0 = (std::abs(pos_h_) <= eps_);  /// pos_h_ == 0.0
      bool even       = (is_pos_h_0 ? true : (static_cast<index_t>(k) % 2 == 0));

      real_t pos_ceil =
        std::ceil(pos);  // static_cast<index_t>(pos + 0.5); // ceil() via cast: incorrect
      real_t f_k = (nearest_ == false ? k : (pos_ceil + k) / 2.0);

      /// bool condition = (not (f_k < pos)) && even;
      bool condition = (f_k >= pos - eps_) && even;

      gamma = (condition ? gamma_l_ : gamma_r_);

      if (null_0_ == true && pos == 0) gamma = 0.0;
    }

    return thrust::make_tuple(gamma, j);
  }

  // assume sorted ptr_d_array1d
  template <typename target_t>
  __host__ __device__ real_t operator()(target_t const* ptr_d_arr_1ds, real_t q, index_t n) const
  {
    auto&& tpl = gamma_j(q, n);  // structural bindings don't work with thrust::tuple, yet

    auto gamma = thrust::get<0>(tpl);
    auto j     = thrust::get<1>(tpl);

    target_t left{0};
    target_t right{0};
    if (j >= n - 1) {
      left  = ptr_d_arr_1ds[n - 1];
      right = 0;
    } else {
      left  = ptr_d_arr_1ds[j];
      right = ptr_d_arr_1ds[j + 1];
    }

    real_t quantile_val =
      (1.0 - gamma) * static_cast<real_t>(left) + gamma * static_cast<real_t>(right);

    return quantile_val;
  }

 private:
  real_t gamma_l_{0.0};
  real_t gamma_r_{1.0};
  real_t f1_{0.0};
  real_t f2_{0.0};
  real_t pos_h_{0.0};

  index_t j_decr_{0};
  bool continuous_{false};
  bool null_0_{false};
  bool nearest_{false};

  real_t eps_{1e-16};
};
