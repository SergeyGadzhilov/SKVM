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

#include "Fwd.h"
#include "base/Event.h"
#include "base/EventTypes.h"
#include <functional>
#include <memory>
#include <string>

namespace skvm {

//! Event queue interface
/*!
An event queue provides a queue of Events.  Clients can block waiting
on any event becoming available at the head of the queue and can place
new events at the end of the queue.  Clients can also add and remove
timers which generate events periodically.
*/
class IEventQueue {
public:
    using EventHandler = std::function<void(const Event&)>;

    virtual ~IEventQueue() { }

    class TimerEvent {
    public:
        EventQueueTimer* m_timer; //!< The timer
        std::uint32_t m_count; //!< Number of repeats
    };

    //! @name manipulators
    //@{

    //! Loop the event queue until quit
    /*!
    Dequeues and dispatches events until the kQuit event is found.
    */
    virtual void loop() = 0;

    /** Replace the current event queue buffer.  Any queued events are discarded.
        The queue takes ownership of the buffer.
    */
    virtual void set_buffer(std::unique_ptr<IEventQueueBuffer>) = 0;

    //! Remove event from queue
    /*!
    Returns the next event on the queue into \p event.  If no event is
    available then blocks for up to \p timeout seconds, or forever if
    \p timeout is negative.  Returns true iff an event was available.
    */
    virtual bool getEvent(Event& event, double timeout = -1.0) = 0;

    //! Dispatch an event
    /*!
    Looks up the dispatcher for the event's target and invokes it.
    Returns true iff a dispatcher exists for the target.

    The caller must ensure that the target of the event is not removed by remove_handler() or
    remove_handlers().
    */
    virtual bool dispatchEvent(const Event& event) = 0;

    //! Add event to queue
    /*!
    Adds \p event to the end of the queue.
    */
    virtual void add_event(Event&& event) = 0;

    /// A helper wrapper for cases when an event is created immediately
    void add_event(EventType type, const EventTarget* target = nullptr,
                   EventDataBase* data = nullptr,
                   Event::Flags flags = Event::kNone)
    {
        add_event(Event(type, target, data, flags));
    }

    //! Create a recurring timer
    /*!
    Creates and returns a timer.  An event is returned after \p duration
    seconds and the timer is reset to countdown again.  When a timer event
    is returned the data points to a \c TimerEvent.  The client must pass
    the returned timer to \c deleteTimer() (whether or not the timer has
    expired) to release the timer.  The returned timer event uses the
    given \p target.  If \p target is nullptr it uses the returned timer as
    the target.

    Events for a single timer don't accumulate in the queue, even if the
    client reading events can't keep up.  Instead, the \c m_count member
    of the \c TimerEvent indicates how many events for the timer would
    have been put on the queue since the last event for the timer was
    removed (or since the timer was added).
    */
    virtual EventQueueTimer* newTimer(double duration, const EventTarget* target) = 0;

    //! Create a one-shot timer
    /*!
    Creates and returns a one-shot timer.  An event is returned when
    the timer expires and the timer is removed from further handling.
    When a timer event is returned the data points to a \c TimerEvent.
    The c_count member of the \c TimerEvent is always 1.  The client
    must pass the returned timer to \c deleteTimer() (whether or not the
    timer has expired) to release the timer.  The returned timer event
    uses the given \p target.  If \p target is nullptr it uses the returned
    timer as the target.
    */
    virtual EventQueueTimer* newOneShotTimer(double duration, const EventTarget* target) = 0;

    //! Destroy a timer
    /*!
    Destroys a previously created timer.  The timer is removed from the
    queue and will not generate event, even if the timer has expired.
    */
    virtual void deleteTimer(EventQueueTimer*) = 0;

    //! Register an event handler for an event type
    /*!
    Registers an event handler for \p type and \p target.  The \p handler
    is adopted.  Any existing handler for the type,target pair is deleted.
    \c dispatchEvent() will invoke \p handler for any event for \p target
    of type \p type.  If no such handler exists it will use the handler
    for \p target and type \p kUnknown if it exists.
    */
    virtual void add_handler(EventType type, const EventTarget* target,
                             const EventHandler& handler) = 0;

    //! Unregister an event handler for an event type
    /*!
    Unregisters an event handler for the \p type, \p target pair and
    deletes it.
    */
    virtual void remove_handler(EventType type, const EventTarget* target) = 0;

    /// Unregister all event handlers for an event target
    virtual void remove_handlers(const EventTarget* target) = 0;

    //! Wait for event queue to become ready
    /*!
    Blocks on the current thread until the event queue is ready for events to
    be added.
    */
    virtual void waitForReady() const = 0;

    //@}
    //! @name accessors
    //@{

    //! Get the system event type target
    /*!
    Returns the target to use for dispatching \c EventType::SYSTEM events.
    */
    virtual const EventTarget* getSystemTarget() = 0;

    //@}
};

} // namespace skvm
