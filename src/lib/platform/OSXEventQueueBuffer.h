/*
 * InputLeap -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2004 Chris Schoeneman
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

#include "base/Fwd.h"
#include "base/IEventQueueBuffer.h"

#include <Carbon/Carbon.h>

namespace skvm {

//! Event queue buffer for OS X
class OSXEventQueueBuffer : public IEventQueueBuffer {
public:
    OSXEventQueueBuffer(IEventQueue* eventQueue);
    virtual ~OSXEventQueueBuffer();

    // IEventQueueBuffer overrides
    virtual void init();
    virtual void waitForEvent(double timeout);
    virtual Type getEvent(Event& event, std::uint32_t& dataID);
    virtual bool addEvent(std::uint32_t dataID);
    virtual bool isEmpty() const;

private:
    EventRef m_event;
    IEventQueue* m_eventQueue;
    EventQueueRef m_carbonEventQueue;
};

} // namespace skvm
