/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * IptablesBaseTest.h - utility class for tests that use iptables
 */

#include <deque>

#include "NetdConstants.h"

class IptablesBaseTest : public ::testing::Test {
public:
    IptablesBaseTest();

    typedef std::vector<std::pair<IptablesTarget, std::string>> ExpectedIptablesCommands;

    static int fake_android_fork_exec(int argc, char* argv[], int *status, bool, bool);
    static int fake_android_fork_execvp(int argc, char* argv[], int *status, bool, bool);
    static int fakeExecIptables(IptablesTarget target, ...);
    static int fakeExecIptablesRestore(IptablesTarget target, const std::string& commands);
    static int fakeExecIptablesRestoreWithOutput(IptablesTarget target, const std::string& commands,
                                                 std::string *output);
    static FILE *fake_popen(const char *cmd, const char *type);
    void expectIptablesCommands(const std::vector<std::string>& expectedCmds);
    void expectIptablesCommands(const ExpectedIptablesCommands& expectedCmds);
    void expectIptablesCommands(const std::vector<ExpectedIptablesCommands>& snippets);
    void expectIptablesRestoreCommands(const std::vector<std::string>& expectedCmds);
    void expectIptablesRestoreCommands(const ExpectedIptablesCommands& expectedCmds);
    void setReturnValues(const std::deque<int>& returnValues);

protected:
    static std::vector<std::string> sCmds;
    static ExpectedIptablesCommands sRestoreCmds;
    static std::deque<int> sReturnValues;
    static std::deque<std::string> sPopenContents;
    static std::deque<std::string> sIptablesRestoreOutput;
    int expectIptablesCommand(IptablesTarget target, int pos, const std::string& cmd);
};
