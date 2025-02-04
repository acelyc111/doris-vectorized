# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
# where to put generated libraries
set(LIBRARY_OUTPUT_PATH "${BUILD_DIR}/src/vec")
# where to put generated binaries
set(EXECUTABLE_OUTPUT_PATH "${BUILD_DIR}/src/vec")

set(VEC_FILES
  aggregate_functions/aggregate_function_count.cpp
  aggregate_functions/aggregate_function_null.cpp
  aggregate_functions/aggregate_function_sum.cpp
  columns/collator.cpp
  columns/column.cpp
  columns/column_const.cpp
  columns/column_decimal.cpp
  columns/column_nullable.cpp
  columns/column_string.cpp
  columns/column_vector.cpp
  columns/columns_common.cpp
  common/demangle.cpp
  common/error_codes.cpp
  common/exception.cpp
  common/pod_array.cpp
  common/string_utils/string_utils.cpp
  core/block.cpp
  core/block_info.cpp
  core/column_with_type_and_name.cpp
  core/field.cpp
  core/field.cpp
  data_types/data_type.cpp
  data_types/data_type_nothing.cpp
  data_types/data_type_nothing.cpp
  data_types/data_type_nullable.cpp
  data_types/data_type_nullable.cpp
  data_types/data_type_number_base.cpp
  data_types/data_type_string.cpp
  data_types/data_types_decimal.cpp
  data_types/data_types_number.cpp
  data_types/get_least_supertype.cpp
  data_types/nested_utils.cpp
  exec/aggregation_node.cpp
  exec/olap_scan_node.cpp
  exec/olap_scanner.cpp
  exprs/vectorized_agg_fn.cpp
  exprs/vectorized_fn_call.cpp
  exprs/vexpr.cpp
  exprs/vexpr_context.cpp
  exprs/vliteral.cpp
  exprs/vslot_ref.cpp
  exprs/vcast_expr.cpp
  functions/abs.cpp
  functions/comparison.cpp
  functions/function.cpp
  functions/function_helpers.cpp
  functions/functions_logical.cpp
  functions/function_cast.cpp
  sink/mysql_result_writer.cpp
  sink/result_sink.cpp
)

add_library(Vec STATIC
    ${VEC_FILES}
)
