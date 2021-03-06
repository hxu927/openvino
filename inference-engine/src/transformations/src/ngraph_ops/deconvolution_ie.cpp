// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <algorithm>
#include <memory>
#include <vector>

#include "ngraph_ops/deconvolution_ie.hpp"

#include "ngraph/util.hpp"
#include "ngraph/validation_util.hpp"

using namespace std;
using namespace ngraph;

constexpr NodeTypeInfo op::DeconvolutionIE::type_info;

op::DeconvolutionIE::DeconvolutionIE(const Output<Node>& data,
                                     const Output<Node>& filters,
                                     const Strides& strides,
                                     const CoordinateDiff& pads_begin,
                                     const CoordinateDiff& pads_end,
                                     const Strides& dilations,
                                     const Shape& output_shape,
                                     const size_t& group,
                                     const PadType& auto_pad)
        : Op({data, filters})
        , m_strides(strides)
        , m_dilations(dilations)
        , m_pads_begin(pads_begin)
        , m_pads_end(pads_end)
        , m_auto_pad(auto_pad)
        , m_output_shape(output_shape)
        , m_group(group) {
    constructor_validate_and_infer_types();
}

op::DeconvolutionIE::DeconvolutionIE(const Output<Node>& data,
                                     const Output<Node>& filters,
                                     const Output<Node>& bias,
                                     const Strides& strides,
                                     const CoordinateDiff& pads_begin,
                                     const CoordinateDiff& pads_end,
                                     const Strides& dilations,
                                     const Shape& output_shape,
                                     const size_t& group,
                                     const PadType& auto_pad)
        : Op({data, filters, bias})
        , m_strides(strides)
        , m_dilations(dilations)
        , m_pads_begin(pads_begin)
        , m_pads_end(pads_end)
        , m_auto_pad(auto_pad)
        , m_output_shape(output_shape)
        , m_group(group) {
    constructor_validate_and_infer_types();
}

void op::DeconvolutionIE::validate_and_infer_types() {
    set_output_type(0, get_input_element_type(0), m_output_shape);
}

shared_ptr<Node> op::DeconvolutionIE::copy_with_new_args(const NodeVector& new_args) const {
    if (new_args.size() == 2) {
        return make_shared<DeconvolutionIE>(new_args.at(0),
                                          new_args.at(1),
                                          m_strides,
                                          m_pads_begin,
                                          m_pads_end,
                                          m_dilations,
                                          m_output_shape,
                                          m_group,
                                          m_auto_pad);
    } else {
        return make_shared<DeconvolutionIE>(new_args.at(0),
                                          new_args.at(1),
                                          new_args.at(2),
                                          m_strides,
                                          m_pads_begin,
                                          m_pads_end,
                                          m_dilations,
                                          m_output_shape,
                                          m_group,
                                          m_auto_pad);
    }
}
