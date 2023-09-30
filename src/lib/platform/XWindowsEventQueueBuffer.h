/*
 * SKVM -- mouse and keyboard sharing utility
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

#include "config.h"

#include "base/Fwd.h"
#include "base/IEventQueueBuffer.h"
#include "XWindowsImpl.h"

#include <X11/Xlib.h>
#include <mutex>
#include <vector>

namespace skvm {

//! Event queue buffer for X11
class XWindowsEventQueueBuffer : public IEventQueueBuffer {
public:
    XWindowsEventQueueBuffer(IXWindowsImpl* impl, Display*, Window,
                             IEventQueue* events);
    ~XWindowsEventQueueBuffer() override;

    // IEventQueueBuffer overrides
    void init()  override { }
    void waitForEvent(double timeout) override;
    Type getEvent(Event& event, std::uint32_t& dataID) override;
    bool addEvent(std::uint32_t dataID) override;
    bool isEmpty() const override;

private:
    void flush();

    int getPendingCountLocked();

private:
    typedef std::vector<XEvent> EventList;
    IXWindowsImpl* m_impl;

    mutable std::mutex  mutex_;
    Display* m_display;
    Window m_window;
    Atom m_userEvent;
    XEvent m_event;
    EventList m_postedEvents;
    bool m_waiting;
    int m_pipefd[2];
    IEventQueue* m_events;
};

} // namespace skvm
