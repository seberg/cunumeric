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

#include "cunumeric/cunumeric.h"

namespace cunumeric {
enum class QuantileOpCode : int {
  INVERTED_CDF       = CUNUMERIC_QUANTOP_INV_CDF,
  AVG_INVERTED_CDF   = CUNUMERIC_QUANTOP_AVG_INV_CDF,
  CLOSEST_OBS        = CUNUMERIC_QUANTOP_CLOSEST_OBS,
  INTRP_INVERTED_CDF = CUNUMERIC_QUANTOP_INTRP_INV_CDF,
  HAZEN              = CUNUMERIC_QUANTOP_HAZEN,
  WEIBULL            = CUNUMERIC_QUANTOP_WEIBULL,
  LINEAR_INTRP       = CUNUMERIC_QUANTOP_LINEAR_INTRP,
  MEDIAN_UNBIASED    = CUNUMERIC_QUANTOP_MEDIAN_UNBIASED,
  NORMAL_UNBIASED    = CUNUMERIC_QUANTOP_NORMAL_UNBIASED,
  LOWER_POINT        = CUNUMERIC_QUANTOP_LOWER_POINT,
  HIGHER_POINT       = CUNUMERIC_QUANTOP_HIGHER_POINT,
  MID_POINT          = CUNUMERIC_QUANTOP_MID_POINT,
  NEAREST_POINT      = CUNUMERIC_QUANTOP_NEAREST_POINT,
};

template <typename Functor, typename... Fnargs>
constexpr decltype(auto) op_dispatch(QuantileOpCode op_code, Functor f, Fnargs&&... args)
{
  switch (op_code) {
    case QuantileOpCode::INVERTED_CDF:
      return f.template operator()<QuantileOpCode::INVERTED_CDF>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::AVG_INVERTED_CDF:
      return f.template operator()<QuantileOpCode::AVG_INVERTED_CDF>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::CLOSEST_OBS:
      return f.template operator()<QuantileOpCode::CLOSEST_OBS>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::INTRP_INVERTED_CDF:
      return f.template operator()<QuantileOpCode::INTRP_INVERTED_CDF>(
        std::forward<Fnargs>(args)...);
    case QuantileOpCode::HAZEN:
      return f.template operator()<QuantileOpCode::HAZEN>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::WEIBULL:
      return f.template operator()<QuantileOpCode::WEIBULL>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::LINEAR_INTRP:
      return f.template operator()<QuantileOpCode::LINEAR_INTRP>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::MEDIAN_UNBIASED:
      return f.template operator()<QuantileOpCode::MEDIAN_UNBIASED>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::NORMAL_UNBIASED:
      return f.template operator()<QuantileOpCode::NORMAL_UNBIASED>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::LOWER_POINT:
      return f.template operator()<QuantileOpCode::LOWER_POINT>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::HIGHER_POINT:
      return f.template operator()<QuantileOpCode::HIGHER_POINT>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::MID_POINT:
      return f.template operator()<QuantileOpCode::MID_POINT>(std::forward<Fnargs>(args)...);
    case QuantileOpCode::NEAREST_POINT:
      return f.template operator()<QuantileOpCode::NEAREST_POINT>(std::forward<Fnargs>(args)...);
  }
  assert(false);
  // FIXME: throw ...; // instead...

  return f.template operator()<QuantileOpCode::INVERTED_CDF>(std::forward<Fnargs>(args)...);
}

template <QuantileOpCode OP_CODE, legate::LegateTypeCode CODE>
struct QuantileOp {
  static constexpr bool valid = false;
};

// this meta-function may also depend
// on Array input type (could be integral, etc.)
// TODO: double-check
//
template <typename QuantInT, typename = void>
struct floating_type_of {
  using value_type = double;
};

template <typename QuantInT>
struct floating_type_of<QuantInT, typename std::enable_if_t<sizeof(QuantInT) < 4>> {
  using value_type = float;
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::INVERTED_CDF, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::AVG_INVERTED_CDF, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::CLOSEST_OBS, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::INTRP_INVERTED_CDF, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::HAZEN, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::WEIBULL, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::LINEAR_INTRP, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::MEDIAN_UNBIASED, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};
template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::NORMAL_UNBIASED, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::LOWER_POINT, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::HIGHER_POINT, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::MID_POINT, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

template <legate::LegateTypeCode CODE>
struct QuantileOp<QuantileOpCode::NEAREST_POINT, CODE> {
  static constexpr bool valid = true;
  using T                     = legate::legate_type_of<CODE>;
  using RetT                  = floating_type_of<T>::value_type;

  QuantileOp(const std::vector<legate::Store>& args) {}

  constexpr decltype(auto) operator()(const T& q, const Array& in) const
  {
    return RetT{}; /*for now... TODO: fix */
  }
};

}  // namespace cunumeric
