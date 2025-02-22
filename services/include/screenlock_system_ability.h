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

#ifndef SERVICES_INCLUDE_SCLOCK_SERVICES_H
#define SERVICES_INCLUDE_SCLOCK_SERVICES_H

#include <mutex>
#include <string>
#include <vector>

#include "dm_common.h"
#include "event_handler.h"
#include "iremote_object.h"
#include "screenlock_manager_stub.h"
#include "screenlock_system_ability_interface.h"
#include "system_ability.h"
#include "window_manager.h"

namespace OHOS {
namespace ScreenLock {
enum class ServiceRunningState { STATE_NOT_START, STATE_RUNNING };
class IKeyguardStateCallback;
class StateValue {
public:
    StateValue() {};
    ~StateValue() {};

    void Reset();

    void SetScreenlocked(bool isScreenlocked)
    {
        isScreenlocked_ = isScreenlocked;
    };

    void SetScreenlockEnabled(bool screenlockEnabled)
    {
        screenlockEnabled_ = screenlockEnabled;
    };

    void SetScreenState(int screenState)
    {
        screenState_ = screenState;
    };

    void SetOffReason(int offReason)
    {
        offReason_ = offReason;
    };

    void SetCurrentUser(int currentUser)
    {
        currentUser_ = currentUser;
    };

    void SetInteractiveState(int interactiveState)
    {
        interactiveState_ = interactiveState;
    };

    bool GetScreenlockedState()
    {
        return isScreenlocked_;
    };

    bool GetScreenlockEnabled()
    {
        return screenlockEnabled_;
    };

    int GetScreenState()
    {
        return screenState_;
    };

    int GetOffReason()
    {
        return offReason_;
    };

    int GetCurrentUser()
    {
        return currentUser_;
    };

    int GetInteractiveState()
    {
        return interactiveState_;
    };

private:
    bool isScreenlocked_ = false;
    bool screenlockEnabled_ = false;
    int offReason_ = 0;
    int currentUser_ = 0;
    int screenState_ = 0;
    int interactiveState_ = 0;
};

enum class ScreenState {
    SCREEN_STATE_BEGIN_OFF = 0,
    SCREEN_STATE_END_OFF = 1,
    SCREEN_STATE_BEGIN_ON = 2,
    SCREEN_STATE_END_ON = 3,
};

enum class InteractiveState {
    INTERACTIVE_STATE_END_SLEEP = 0,
    INTERACTIVE_STATE_BEGIN_WAKEUP = 1,
    INTERACTIVE_STATE_END_WAKEUP = 2,
    INTERACTIVE_STATE_BEGIN_SLEEP = 3,
};

class ScreenLockSystemAbility : public SystemAbility, public ScreenLockManagerStub {
    DECLARE_SYSTEM_ABILITY(ScreenLockSystemAbility);

public:
    DISALLOW_COPY_AND_MOVE(ScreenLockSystemAbility);
    ScreenLockSystemAbility(int32_t systemAbilityId, bool runOnCreate);
    ScreenLockSystemAbility();
    ~ScreenLockSystemAbility();
    static sptr<ScreenLockSystemAbility> GetInstance();
    bool IsScreenLocked() override;
    bool GetSecure() override;
    void RequestUnlock(const sptr<ScreenLockSystemAbilityInterface> &listener) override;
    bool On(const sptr<ScreenLockSystemAbilityInterface> &listener, const std::string &type) override;
    bool Off(const std::string &type) override;
    bool SendScreenLockEvent(const std::string &event, int param) override;
    int Dump(int fd, const std::vector<std::u16string> &args) override;
    void SetScreenlocked(bool isScreenlocked);
    StateValue &GetState()
    {
        return stateValue_;
    }
    bool Test_SetScreenLocked(const bool isScreenlocked) override;
    bool Test_RuntimeNotify(const std::string &event, int param) override;
    int Test_GetRuntimeState(const std::string &event) override;

    class ScreenLockFocusChangedListener : public Rosen::IFocusChangedListener {
    public:
        void OnFocused(const sptr<Rosen::FocusChangeInfo> &focusChangeInfo) override;
        void OnUnfocused(const sptr<Rosen::FocusChangeInfo> &focusChangeInfo) override;
    };

    class ScreenLockDisplayPowerEventListener : public Rosen::IDisplayPowerEventListener {
    public:
        void OnDisplayPowerEvent(Rosen::DisplayPowerEvent event, Rosen::EventStatus status) override;
    };

protected:
    void OnDump() override;
    void OnStart() override;
    void OnStop() override;

private:
    void OnBeginScreenOn();
    void OnEndScreenOn();
    void OnBeginScreenOff();
    void OnEndScreenOff();
    void OnBeginWakeUp();
    void OnEndWakeUp();
    void OnBeginSleep(const int why);
    void OnEndSleep(const int why, const int isTriggered);
    void OnChangeUser(const int newUserId);
    void OnScreenlockEnabled(bool enable);
    void OnExitAnimation();
    void OnSystemReady();
    void RegisterDumpCommand();
    int32_t Init();
    ServiceRunningState state_;
    void InitServiceHandler();
    static std::mutex instanceLock_;
    static sptr<ScreenLockSystemAbility> instance_;
    static std::shared_ptr<AppExecFwk::EventHandler> serviceHandler_;
    sptr<Rosen::IFocusChangedListener> focusChangedListener_;
    sptr<Rosen::IDisplayPowerEventListener> displayPowerEventListener_;
    std::map<std::string, sptr<ScreenLockSystemAbilityInterface>> registeredListeners_;
    std::vector<sptr<ScreenLockSystemAbilityInterface>> unlockVecListeners_;
    StateValue stateValue_;
    std::mutex listenerMapMutex_;
    std::mutex lock_;
    const int32_t startTime_ = 1900;
    const int32_t extraMonth_ = 1;
    bool isFoucs_ = false;
    bool flag_ = false;
};
} // namespace ScreenLock
} // namespace OHOS
#endif // SERVICES_INCLUDE_SCLOCK_SERVICES_H
