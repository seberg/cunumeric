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

// Useful for IDEs
#include "cunumeric/quantile/quantile.h"

#include "cunumeric/quantile/quantile_op_util.h"
#include "cunumeric/pitches.h"

namespace cunumeric {

using namespace Legion;
using namespace legate;

template <VariantKind KIND, QuantileOpCode OP_CODE, LegateTypeCode CODE, int DIM>
struct QuantileOpImplBody;

template <VariantKind KIND, QuantileOpCode OP_CODE>
struct QuantileOpImpl {
  template <LegateTypeCode CODE,
            int DIM,
            std::enable_if_t<QuantileOp<OP_CODE, CODE>::valid>* = nullptr>
  void operator()(QuantileOpArgs& args) const
  {
    using OP  = QuantileOp<OP_CODE, CODE>;
    using RHS = legate_type_of<CODE>;

    using RET = typename OP::RetT;

    auto rect = args.out.shape<DIM>();

    Pitches<DIM - 1> pitches;
    size_t volume = pitches.flatten(rect);

    if (volume == 0) return;

    auto out = args.out.write_accessor<RET, DIM>(rect);
    auto in  = args.in.read_accessor<RHS, DIM>(rect);

#ifndef LEGION_BOUNDS_CHECKS
    // Check to see if this is dense or not
    bool dense = out.accessor.is_dense_row_major(rect) && in.accessor.is_dense_row_major(rect);
#else
    // No dense execution if we're doing bounds checks
    bool dense = false;
#endif

    OP func{args.args};
    QuantileOpImplBody<KIND, OP_CODE, CODE, DIM>()(func, out, in, pitches, rect, dense);
  }

  template <LegateTypeCode CODE,
            int DIM,
            std::enable_if_t<!QuantileOp<OP_CODE, CODE>::valid>* = nullptr>
  void operator()(QuantileOpArgs& args) const
  {
    assert(false);
  }
};

template <VariantKind KIND>
struct QuantileOpDispatch {
  template <QuantileOpCode OP_CODE>
  void operator()(QuantileOpArgs& args) const
  {
    auto dim = std::max(1, args.out.dim());
    double_dispatch(dim, args.in.code(), QuantileOpImpl<KIND, OP_CODE>{}, args);
  }
};

template <VariantKind KIND>
static void quantile_op_template(TaskContext& context)
{
  auto& inputs  = context.inputs();
  auto& outputs = context.outputs();
  auto& scalars = context.scalars();

  auto op_code = scalars[0].value<QuantileOpCode>();

  std::vector<Store> extra_args;
  for (size_t idx = 2; idx < inputs.size(); ++idx) extra_args.push_back(std::move(inputs[idx]));

  QuantileOpArgs args{inputs[0], outputs[0], op_code, std::move(extra_args)};
  op_dispatch(args.op_code, QuantileOpDispatch<KIND>{}, args);
}

}  // namespace cunumeric
