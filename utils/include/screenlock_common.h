/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
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

#ifndef SERVICES_INCLUDE_SCREENLOCK_COMMON_H
#define SERVICES_INCLUDE_SCREENLOCK_COMMON_H

#include <string>

#include "errors.h"

namespace OHOS {
namespace ScreenLock {
#define SCREENLOCK_SERVICE_NAME "ScreenLockService"
#define PARAM_ZERO 0
#define PARAM_ONE 1
#define PARAM_TWO 2

struct AppInfo {
    std::string bundleName_;
    int userId_;
};

const std::string BEGIN_WAKEUP = "beginWakeUp";
const std::string END_WAKEUP = "endWakeUp";
const std::string BEGIN_SCREEN_ON = "beginScreenOn";
const std::string END_SCREEN_ON = "endScreenOn";
const std::string BEGIN_SLEEP = "beginSleep";
const std::string END_SLEEP = "endSleep";
const std::string BEGIN_SCREEN_OFF = "beginScreenOff";
const std::string END_SCREEN_OFF = "endScreenOff";
const std::string CHANGE_USER = "changeUser";
const std::string SCREENLOCK_ENABLED = "screenlockEnabled";
const std::string EXIT_ANIMATION = "beginExitAnimation";
const std::string UNLOCKSCREEN = "unlockScreen";
const std::string UNLOCK_SCREEN_RESULT = "unlockScreenResult";
const std::string SCREEN_DRAWDONE = "screenDrawDone";
const std::string SYSTEM_READY = "systemReady";
const std::string BUNDLE_NAME = "com.ohos.screenlock";
const int USER_NULL = -10000;
enum ScreenLockModule {
    SCREENLOCK_MODULE_SERVICE_ID = 0x04,
};
// time error offset, used only in this file.
constexpr ErrCode SCREENLOCK_ERR_OFFSET = ErrCodeOffset(SUBSYS_SMALLSERVICES, SCREENLOCK_MODULE_SERVICE_ID);

enum ScreenLockError {
    E_SCREENLOCK_OK = SCREENLOCK_ERR_OFFSET,
    E_SCREENLOCK_SA_DIED,
    E_SCREENLOCK_READ_PARCEL_ERROR,
    E_SCREENLOCK_WRITE_PARCEL_ERROR,
    E_SCREENLOCK_PUBLISH_FAIL,
    E_SCREENLOCK_TRANSACT_ERROR,
    E_SCREENLOCK_DEAL_FAILED,
    E_SCREENLOCK_PARAMETERS_INVALID,
    E_SCREENLOCK_SET_RTC_FAILED,
    E_SCREENLOCK_NOT_FOUND,
    E_SCREENLOCK_NO_PERMISSION,
};

enum TraceTaskId {
    HITRACE_UNLOCKSCREEN,
};

constexpr int BEGIN_SLEEP_DEVICE_ADMIN_REASON = 1;
constexpr int BEGIN_SLEEP_USER_REASON = 2;
constexpr int BEGIN_SLEEP_LONG_TIME_UNOPERATOR = 3;

constexpr int END_SLEEP_DEVICE_ADMIN_REASON = 1;
constexpr int END_SLEEP_USER_REASON = 2;
constexpr int END_SLEEP_LONG_TIME_UNOPERATE = 3;

constexpr int UNLOCKSCREEN_SUCC = 0;
constexpr int UNLOCKSCREEN_FAIL = 1;
constexpr int UNLOCKSCREEN_CANCEL = 2;

constexpr int SCREENLOCK_APP_CAN_USE = 1;
constexpr int SCREENLOCK_APP_CAN_NOT_USE = 0;

constexpr std::int32_t DEFAULT_ERROR = -1;
constexpr int32_t NONE_EVENT_TYPE = 0;
constexpr int ARGV_ZERO = 0;
constexpr int ARGV_ONE = 1;
constexpr int ARGV_TWO = 2;
constexpr int ARGV_THREE = 3;
constexpr int ARGV_NORMAL = -100;
constexpr std::int32_t MAX_VALUE_LEN = 4096;
constexpr const std::int32_t STR_MAX_SIZE = 256;
constexpr int RESULT_COUNT = 2;
constexpr int PARAMTWO = 2;
constexpr std::int32_t ARGS_SIZE_ZERO = 0;
constexpr std::int32_t ARGS_SIZE_ONE = 1;
constexpr std::int32_t ARGS_SIZE_TWO = 2;
constexpr std::int32_t ARGS_SIZE_THREE = 3;
constexpr std::int32_t ARGS_SIZE_FOUR = 4;
constexpr std::int32_t RESULT_ZERO = 0;
static const uint32_t SCREENLOCK_BEGIN_WAKEUP = 0x00000001;
static const uint32_t SCREENLOCK_END_WAKEUP = 0x00000004;
static const uint32_t SCREENLOCK_BEGIN_SCREEN_ON = 0x00000008;
static const uint32_t SCREENLOCK_END_SCREEN_ON = 0x00000010;
static const uint32_t SCREENLOCK_BEGIN_SCREEN_OFF = 0x00000020;
static const uint32_t SCREENLOCK_END_SCREEN_OFF = 0x00000040;
static const uint32_t SCREENLOCK_UNLOCK_SCREEN = 0x00000080;
static const uint32_t SCREENLOCK_BEGIN_SLEEP = 0x00000100;
static const uint32_t SCREENLOCK_END_SLEEP = 0x00000200;
static const uint32_t SCREENLOCK_CHANGE_USER = 0x00000400;
static const uint32_t SCREENLOCK_SCREENLOCK_ENABLED = 0x00000800;
static const uint32_t SCREENLOCK_EXIT_ANIMATION = 0x00001000;
static const uint32_t SCREENLOCK_SYSTEM_READY = 0x00002000;
} // namespace ScreenLock
} // namespace OHOS
#endif // SERVICES_INCLUDE_SCREENLOCK_COMMON_H