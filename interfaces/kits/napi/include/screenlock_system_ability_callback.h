/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 */
#ifndef NAPI_SCREENLOCK_CALL_BACK_INSTANCE_H
#define NAPI_SCREENLOCK_CALL_BACK_INSTANCE_H

#include <cstdint>
#include <list>
#include <string>

#include "event_listener.h"
#include "screenlock_system_ability_stub.h"

namespace OHOS {
namespace ScreenLock {
class ScreenlockSystemAbilityCallback : public ScreenLockSystemAbilityStub {
public:
    ScreenlockSystemAbilityCallback(int32_t eventType, std::list<EventListener> &eventListener);
    virtual ~ScreenlockSystemAbilityCallback();
    void OnCallBack(const std::string &event, bool result) override;
    void OnCallBack(const std::string &event) override;
    void OnCallBack(const std::string &event, int result) override;
    static int32_t GetEventType(const std::string &type);
    static bool MatchEventType(const std::string &type, const std::string &goalTypeStr);

private:
    int32_t eventType_;
    std::list<EventListener> *listenerList_;
};
} // namespace ScreenLock
} // namespace OHOS
#endif //  NAPI_SCREENLOCK_CALL_BACK_INSTANCE_H