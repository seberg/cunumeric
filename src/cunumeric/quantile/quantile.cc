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

#include "cunumeric/quantile/quantile.h"
#include "cunumeric/quantile/quantile_template.inl"

namespace cunumeric {

using namespace Legion;
using namespace legate;

template <QuantileOpCode OP_CODE, LegateTypeCode CODE, int DIM>
struct QuantileOpImplBody<VariantKind::CPU, OP_CODE, CODE, DIM> {
  using OP  = QuantileOp<OP_CODE, CODE>;
  using ARG = typename OP::T;
  using RES = typename OP::RetT;

  void operator()(OP func,
                  AccessorWO<RES, DIM> out,
                  AccessorRO<ARG, DIM> in,
                  // AccessorRO<ARR_T, ARR_DIM> in_arr,
                  // how do I pass the Array on which
                  // quantile input (in) acts? TODO: figure out
                  // Note: ARR_T, ARR_DIM may differ from the input index-set shape!
                  const Pitches<DIM - 1>& pitches,
                  const Rect<DIM>& rect,
                  bool dense) const
  {
    const size_t volume = rect.volume();
    if (dense) {
      auto outptr = out.ptr(rect);
      auto inptr  = in.ptr(rect);
      for (size_t idx = 0; idx < volume; ++idx)
        outptr[idx] = func(inptr[idx] /*, in_arr? TODO: figure out */);
    } else {
      for (size_t idx = 0; idx < volume; ++idx) {
        auto p = pitches.unflatten(idx, rect.lo);
        out[p] = func(in[p] /*, in_arr? TODO: figure out */);
      }
    }
  }
};

/*static*/ void QuantileOpTask::cpu_variant(TaskContext& context)
{
  quantile_op_template<VariantKind::CPU>(context);
}

namespace  // unnamed
{
static void __attribute__((constructor)) register_tasks(void)
{
  QuantileOpTask::register_variants();
}
}  // namespace

}  // namespace cunumeric
