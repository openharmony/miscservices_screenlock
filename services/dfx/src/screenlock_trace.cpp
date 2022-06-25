/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * miscservices under the License is miscservices on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "screenlock_trace.h"
#include "hitrace_meter.h"
#include "sclock_log.h"

namespace OHOS {
namespace MiscServicesDfx {
void InitHiTrace()
{
    UpdateTraceLabel();
}

void ValueTrace(const std::string& name, int64_t count)
{
    CountTrace(HITRACE_TAG_SCREENLOCK_MANAGER, name, count);
}

ScreenlockHiTraceAsyncTrace::ScreenlockHiTraceAsyncTrace(const std::string &value)
{
    StartTrace(HITRACE_TAG_SCREENLOCK_MANAGER, value);
    startTime_ = ScreenlockHiTraceAsyncTrace::TimeConsuming();
}

ScreenlockHiTraceAsyncTrace::~ScreenlockHiTraceAsyncTrace()
{
    FinishTrace(HITRACE_TAG_SCREENLOCK_MANAGER);
    uint64_t endTime = ScreenlockHiTraceAsyncTrace::TimeConsuming();
    uint64_t result = endTime - startTime_;
    SCLOCK_HILOGE("unlockscreen time is %{public}luL", result);
}
} // MiscServicesDfx
} // OHOS
