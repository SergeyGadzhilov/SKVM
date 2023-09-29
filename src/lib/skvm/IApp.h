/*
 * InputLeap -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2012 Nick Bolton
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Fwd.h"
#include "base/Fwd.h"
#include <memory>

namespace skvm {

typedef int (*StartupFunc)(int, char**);

class IArchTaskBarReceiver;

class IApp {
public:
    virtual ~IApp() {}

    virtual void setByeFunc(void(*bye)(int)) = 0;
    virtual ArgsBase& argsBase() const = 0;
    virtual int standardStartup(int argc, char** argv) = 0;
    virtual int runInner(int argc, char** argv, ILogOutputter* outputter, StartupFunc startup) = 0;
    virtual void startNode() = 0;
    virtual IArchTaskBarReceiver* taskBarReceiver() const = 0;
    virtual void bye(int error) = 0;
    virtual int mainLoop() = 0;
    virtual void initApp(int argc, const char** argv) = 0;
    virtual const char* daemonName() const = 0;
    virtual int foregroundStartup(int argc, char** argv) = 0;
    virtual std::unique_ptr<Screen> create_screen() = 0;
    virtual IEventQueue* getEvents() const = 0;
};

} // namespace skvm
