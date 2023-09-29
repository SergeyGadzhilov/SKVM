/*
 * InputLeap -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2002 Chris Schoeneman
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

#include "skvm/DragInformation.h"
#include "skvm/clipboard_types.h"
#include "skvm/IScreen.h"
#include "skvm/IPrimaryScreen.h"
#include "skvm/ISecondaryScreen.h"
#include "skvm/IKeyState.h"
#include "skvm/option_types.h"

namespace skvm {

//! Screen interface
/*!
This interface defines the methods common to all platform dependent
screen implementations that are used by both primary and secondary
screens.
*/
class IPlatformScreen : public IScreen,
                public IPrimaryScreen, public ISecondaryScreen,
                public IKeyState {
public:
    //! @name manipulators
    //@{

    //! Enable screen
    /*!
    Enable the screen, preparing it to report system and user events.
    For a secondary screen it also means preparing to synthesize events
    and hiding the cursor.
    */
    virtual void enable() = 0;

    //! Disable screen
    /*!
    Undoes the operations in enable() and events should no longer
    be reported.
    */
    virtual void disable() = 0;

    //! Enter screen
    /*!
    Called when the user navigates to this screen.
    */
    virtual void enter() = 0;

    //! Leave screen
    /*!
    Called when the user navigates off the screen.  Returns true on
    success, false on failure.  A typical reason for failure is being
    unable to install the keyboard and mouse snoopers on a primary
    screen.  Secondary screens should not fail.
    */
    virtual bool leave() = 0;

    //! Set clipboard
    /*!
    Set the contents of the system clipboard indicated by \c id.
    */
    virtual bool setClipboard(ClipboardID id, const IClipboard*) = 0;

    //! Check clipboard owner
    /*!
    Check ownership of all clipboards and post grab events for any that
    have changed.  This is used as a backup in case the system doesn't
    reliably report clipboard ownership changes.
    */
    virtual void checkClipboards() = 0;

    //! Open screen saver
    /*!
    Open the screen saver.  If \c notify is true then this object must
    send events when the screen saver activates or deactivates until
    \c closeScreensaver() is called.  If \c notify is false then the
    screen saver is disabled and restored on \c closeScreensaver().
    */
    virtual void openScreensaver(bool notify) = 0;

    //! Close screen saver
    /*!
    // Close the screen saver.  Stop reporting screen saver activation
    and deactivation and, if the screen saver was disabled by
    openScreensaver(), enable the screen saver.
    */
    virtual void closeScreensaver() = 0;

    //! Activate/deactivate screen saver
    /*!
    Forcibly activate the screen saver if \c activate is true otherwise
    forcibly deactivate it.
    */
    virtual void screensaver(bool activate) = 0;

    //! Notify of options changes
    /*!
    Reset all options to their default values.
    */
    virtual void resetOptions() = 0;

    //! Notify of options changes
    /*!
    Set options to given values.  Ignore unknown options and don't
    modify options that aren't given in \c options.
    */
    virtual void setOptions(const OptionsList& options) = 0;

    //! Set clipboard sequence number
    /*!
    Sets the sequence number to use in subsequent clipboard events.
    */
    virtual void setSequenceNumber(std::uint32_t) = 0;

    //! Change dragging status
    virtual void setDraggingStarted(bool started) = 0;

    //@}
    //! @name accessors
    //@{

    //! Test if is primary screen
    /*!
    Return true iff this screen is a primary screen.
    */
    virtual bool isPrimary() const = 0;

    //@}

    virtual std::string& getDraggingFilename() = 0;
    virtual void clearDraggingFilename() = 0;
    virtual bool isDraggingStarted() = 0;
    virtual bool isFakeDraggingStarted() = 0;

    virtual void fakeDraggingFiles(DragFileList fileList) = 0;
    virtual const std::string& getDropTarget() const = 0;
    virtual void setDropTarget(const std::string&) = 0;

    //! Handle system event
    /*!
    A platform screen is expected to install a handler for system
    events in its c'tor like so:
    \code
    m_events->add_handler(EventType::SYSTEM, m_events->getSystemTarget(),
                          [this](const auto& e){ handle_system_event(e); });
    \endcode
    It should remove the handler in its d'tor.  Override the
    \c handle_system_event() method to process system events.
    It should post the events \c IScreen as appropriate.

    A primary screen has further responsibilities.  It should post
    the events in \c IPrimaryScreen as appropriate.  It should also
    call \c onKey() on its \c KeyState whenever a key is pressed
    or released (but not for key repeats).  And it should call
    \c updateKeyMap() on its \c KeyState if necessary when the keyboard
    mapping changes.

    The target of all events should be the value returned by
    \c get_event_target().
    */
    virtual void handle_system_event(const Event& event) = 0;
};

} // namespace skvm
