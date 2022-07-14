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
}  // namespace cunumeric
