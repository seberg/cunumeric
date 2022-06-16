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

#include "quant_red.h"

namespace cunumeric {
#define DEFINE_QUANTILE_IDENTITY(TYPE) \
  template <>                          \
  const TYPE QuantileReduction<TYPE>::identity = TYPE{0};

DEFINE_QUANTILE_IDENTITY(__half)
DEFINE_QUANTILE_IDENTITY(float)
DEFINE_QUANTILE_IDENTITY(double)
DEFINE_QUANTILE_IDENTITY(bool)
DEFINE_QUANTILE_IDENTITY(int8_t)
DEFINE_QUANTILE_IDENTITY(int16_t)
DEFINE_QUANTILE_IDENTITY(int32_t)
DEFINE_QUANTILE_IDENTITY(int64_t)
DEFINE_QUANTILE_IDENTITY(uint8_t)
DEFINE_QUANTILE_IDENTITY(uint16_t)
DEFINE_QUANTILE_IDENTITY(uint32_t)
DEFINE_QUANTILE_IDENTITY(uint64_t)
DEFINE_QUANTILE_IDENTITY(complex<float>)

// REGISTER_REDOP ?

}  // namespace cunumeric
