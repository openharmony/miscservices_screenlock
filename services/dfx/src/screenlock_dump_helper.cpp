/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "screenlock_dump_helper.h"
#include <regex>

namespace OHOS {
namespace MiscServicesDfx {
namespace {
constexpr int32_t MAX_RECORED_ERROR = 10;
constexpr int32_t SUB_CMD_NAME = 0;
constexpr int32_t SUB_CMD_PARAM = 1;
constexpr int32_t CMD_NO_PARAM = 1;
constexpr int32_t CMD_HAS_PARAM = 2;
constexpr const char *CMD_HELP = "-h";
constexpr const char *CMD_ALL = "all";
constexpr const char *CMD_ERROR_INFO = "-errorInfo";
constexpr const char *ILLEGAL_INFOMATION = "The arguments are illegal and you can enter '-h' for help.\n";
}

void DumpHelper::AddDumpOperation(const DumpNoParamFunc &dumpAll)
{
    if ( dumpAll == nullptr ) {
        return;
    }
    dumpAll_ = dumpAll;
}

void DumpHelper::AddErrorInfo(const std::string &error)
{
    std::lock_guard<std::mutex> lock(hidumperMutex_);
    if (g_errorInfo.size() + 1 > MAX_RECORED_ERROR) {
        g_errorInfo.pop_front();
        g_errorInfo.push_back(error);
    } else {
        g_errorInfo.push_back(error);
    }
}

void DumpHelper::ShowError(int fd)
{
    dprintf(fd, "The number of recent errors recorded is %d\n", g_errorInfo.size());
    int i = 0;
    for (const auto &it : g_errorInfo) {
        dprintf(fd, "Error ID: %d        ErrorInfo: %s\n", ++i, it.c_str());
    }
}

bool DumpHelper::Dump(int fd, const std::vector<std::string> &args)
{
    std::string command = "";
    std::string param = "";

    if (args.size() == CMD_NO_PARAM) {
        command = args.at(SUB_CMD_NAME);
    } else if (args.size() == CMD_HAS_PARAM) {
        command = args.at(SUB_CMD_NAME);
        param = args.at(SUB_CMD_PARAM);
    } else {
        ShowError(fd);
        if (!dumpAll_) {
            return false;
        }
        dumpAll_(fd);
    }

    if (command == CMD_HELP) {
        ShowHelp(fd);
    } else if (command == CMD_ERROR_INFO) {
        ShowError(fd);
    } else {
        ShowIllealInfomation(fd);
    }
    return true;
}

void DumpHelper::DumpAll(int fd)
{
    dprintf(fd, "------------------------------------------------------------------------------------\n");
    std::string ret;
    ret.append("field   type    desc\n")
        .append("screenLocked   boolean    whether there is lock screen status\n")
        .append("keyguardEnabled   boolean    whether there is PIN code, gesture, password, SIM card lock\n"\n)
        .append("inputForbidden   boolean    whether disable input\n")
        .append("systemReady   boolean    Is the system in place\n")
        .append("bootCompleted   boolean    Whether the system has been started and completed\n")
        .append("screenState   int    Screen on / off status\n")
        .append("offReason   string    Screen failure reason\n")
        .append("interactiveState   int    Screen interaction status\n")
    dprintf(fd, "%s\n", result.c_str());
}

void DumpHelper::ShowHelp(int fd)
{
    std::string result;
    result.append("Usage:dump  <command> [options]\n")
          .append("Description:\n")
		  .append("             ")
          .append("--help show help\n")
    dprintf(fd, "%s\n", result.c_str());
}

void DumpHelper::ShowIllealInfomation(int fd)
{
    dprintf(fd, "%s\n", ILLEGAL_INFOMATION);
}
} // namespace MiscServicesDfx
} // namespace OHOS
