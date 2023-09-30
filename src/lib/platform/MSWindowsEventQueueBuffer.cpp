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

#include "platform/MSWindowsEventQueueBuffer.h"

#include "arch/win32/ArchMiscWindows.h"
#include "mt/Thread.h"
#include "base/IEventQueue.h"
#include <VersionHelpers.h>

namespace skvm {

MSWindowsEventQueueBuffer::MSWindowsEventQueueBuffer(IEventQueue* events) :
    m_events(events)
{
    // remember thread.  we'll be posting messages to it.
    m_thread     = GetCurrentThreadId();

    // create a message type for custom events
    m_userEvent = RegisterWindowMessage("SKVM_USER_EVENT");

    // get message type for daemon quit
    m_daemonQuit = ArchMiscWindows::getDaemonQuitMessage();

    // make sure this thread has a message queue
    MSG dummy;
    PeekMessage(&dummy, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    m_os_supported_message_types = QS_ALLINPUT;
    if (!IsWindows8OrGreater())
    {
        // don't use QS_POINTER, QS_TOUCH
        // because they can cause GetQueueStatus() to always return 0 and we miss events
        // since those flags are confusing Windows 7. See QTBUG-29097 for related info
        m_os_supported_message_types &= ~(QS_TOUCH | QS_POINTER);
    }
}

MSWindowsEventQueueBuffer::~MSWindowsEventQueueBuffer()
{
    // do nothing
}

void
MSWindowsEventQueueBuffer::waitForEvent(double timeout)
{
    // check if messages are available first.  if we don't do this then
    // MsgWaitForMultipleObjects() will block even if the queue isn't
    // empty if the messages in the queue were there before the last
    // call to GetMessage()/PeekMessage().
    if (!isEmpty()) {
        return;
    }

    // convert timeout
    DWORD t;
    if (timeout < 0.0) {
        t = INFINITE;
    }
    else {
        t = (DWORD)(1000.0 * timeout);
    }

    // wait for a message.  we cannot be interrupted by thread
    // cancellation but that's okay because we're run in the main
    // thread and we never cancel that thread.
    HANDLE dummy[1];
    MsgWaitForMultipleObjects(0, dummy, FALSE, t, m_os_supported_message_types);
}

IEventQueueBuffer::Type MSWindowsEventQueueBuffer::getEvent(Event& event, std::uint32_t& dataID)
{
    // peek at messages first.  waiting for QS_ALLINPUT will return
    // if a message has been sent to our window but GetMessage will
    // dispatch that message behind our backs and block.  PeekMessage
    // will also dispatch behind our backs but won't block.
    if (!PeekMessage(&m_event, nullptr, 0, 0, PM_NOREMOVE) &&
        !PeekMessage(&m_event, (HWND)-1, 0, 0, PM_NOREMOVE)) {
        return kNone;
    }

    // BOOL.  yeah, right.
    BOOL result = GetMessage(&m_event, nullptr, 0, 0);
    if (result == -1) {
        return kNone;
    }
    else if (result == 0) {
        event = Event(EventType::QUIT);
        return kSystem;
    }
    else if (m_daemonQuit != 0 && m_event.message == m_daemonQuit) {
        event = Event(EventType::QUIT);
        return kSystem;
    }
    else if (m_event.message == m_userEvent) {
        dataID = static_cast<std::uint32_t>(m_event.wParam);
        return kUser;
    }
    else {
        event = Event(EventType::SYSTEM, m_events->getSystemTarget(),
                      create_event_data<MSG*>(&m_event));
        return kSystem;
    }
}

bool MSWindowsEventQueueBuffer::addEvent(std::uint32_t dataID)
{
    return (PostThreadMessage(m_thread, m_userEvent,
                            static_cast<WPARAM>(dataID), 0) != 0);
}

bool
MSWindowsEventQueueBuffer::isEmpty() const
{
    return (HIWORD(GetQueueStatus(m_os_supported_message_types)) == 0);
}

} // namespace skvm
