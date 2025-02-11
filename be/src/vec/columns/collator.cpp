// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "vec/columns/collator.h"

//#include "config_core.h"

#if USE_ICU
#include <unicode/ucol.h>
#else
#ifdef __clang__
#pragma clang diagnostic ignored "-Wunused-private-field"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
#endif

#include <boost/algorithm/string/case_conv.hpp>

#include "vec/common/exception.h"
//#include <IO/WriteHelpers.h>
//#include <Poco/String.h>

namespace doris::vectorized::ErrorCodes {
extern const int UNSUPPORTED_COLLATION_LOCALE;
extern const int COLLATION_COMPARISON_FAILED;
extern const int SUPPORT_IS_DISABLED;
} // namespace doris::vectorized::ErrorCodes

Collator::Collator(const std::string& locale_) : locale(boost::algorithm::to_lower_copy(locale_)) {
#if USE_ICU
    UErrorCode status = U_ZERO_ERROR;

    collator = ucol_open(locale.c_str(), &status);
    if (status != U_ZERO_ERROR) {
        ucol_close(collator);
        throw doris::vectorized::Exception(
                "Unsupported collation locale: " + locale,
                doris::vectorized::ErrorCodes::UNSUPPORTED_COLLATION_LOCALE);
    }
#else
    throw doris::vectorized::Exception(
            "Collations support is disabled, because ClickHouse was built without ICU library",
            doris::vectorized::ErrorCodes::SUPPORT_IS_DISABLED);
#endif
}

Collator::~Collator() {
#if USE_ICU
    ucol_close(collator);
#endif
}

int Collator::compare(const char* str1, size_t length1, const char* str2, size_t length2) const {
#if USE_ICU
    UCharIterator iter1, iter2;
    uiter_setUTF8(&iter1, str1, length1);
    uiter_setUTF8(&iter2, str2, length2);

    UErrorCode status = U_ZERO_ERROR;
    UCollationResult compare_result = ucol_strcollIter(collator, &iter1, &iter2, &status);

    if (status != U_ZERO_ERROR)
        throw doris::vectorized::Exception(
                "ICU collation comparison failed with error code: " +
                        doris::vectorized::toString<int>(status),
                doris::vectorized::ErrorCodes::COLLATION_COMPARISON_FAILED);

    /** Values of enum UCollationResult are equals to what exactly we need:
     *     UCOL_EQUAL = 0
     *     UCOL_GREATER = 1
     *     UCOL_LESS = -1
     */
    return compare_result;
#else
    (void)str1;
    (void)length1;
    (void)str2;
    (void)length2;
    return 0;
#endif
}

const std::string& Collator::getLocale() const {
    return locale;
}

std::vector<std::string> Collator::getAvailableCollations() {
    std::vector<std::string> result;
#if USE_ICU
    size_t available_locales_count = ucol_countAvailable();
    for (size_t i = 0; i < available_locales_count; ++i) result.push_back(ucol_getAvailable(i));
#endif
    return result;
}
