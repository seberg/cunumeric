/* Copyright 2021-2022 NVIDIA Corporation
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

#include "legate.h"
#include "cunumeric/cunumeric_c.h"

namespace cunumeric {
template <typename T>
class QuantileReduction {
 public:
  // follow UnaryRedCode::MIN, MinReduction blueprint;
  //
  using LHS = T;  // Argval<T>;
  using RHS = T;  // Argval<T>;

  // PROBLEM:
  //
  // static const Argval<T> identity;
  //  error: scalar_unary_red.cc:72:33: error: cannot convert ‘cunumeric::Argval<bool>’
  //  to ‘cunumeric::UnaryRedOp<cunumeric::UnaryRedCode::QUANTILE, BOOL_LT>::VAL&’ {aka
  //  ‘bool&’}

  static const T identity;
  //  error: scalar_unary_red.cc:72:52: error: no matching function for call to
  //  ‘cunumeric::UnaryRedOp<cunumeric::UnaryRedCode::QUANTILE, BOOL_LT>::convert(Realm::Point<2,
  //  long long int>&, Legion::Point<2, long long int>&, const bool&)’
  //    72 |         OP::template fold<true>(result, OP::convert(p, shape, inptr[idx]));
  //       |                                         ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~

  static const int32_t REDOP_ID = 10111;  // some rnd nbr. for now...
  //   CUNUMERIC_ARGMIN_REDOP * MAX_TYPE_NUMBER + legate::legate_type_code_of<T>;

  template <bool EXCLUSIVE>
  __CUDA_HD__ inline static void apply(LHS& lhs, RHS rhs)
  {
    // lhs.template apply<Legion::MinReduction<T>, EXCLUSIVE>(rhs);
  }
  template <bool EXCLUSIVE>
  __CUDA_HD__ inline static void fold(RHS& rhs1, RHS rhs2)
  {
    // rhs1.template apply<Legion::MinReduction<T>, EXCLUSIVE>(rhs2);
  }
};

}  // namespace cunumeric
