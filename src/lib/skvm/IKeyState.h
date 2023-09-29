/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2003 Chris Schoeneman
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

#include "skvm/key_types.h"
#include "base/Event.h"
#include "base/IEventQueue.h"
#include "base/EventTypes.h"
#include <set>

namespace skvm {

//! Key state interface
/*!
This interface provides access to set and query the keyboard state and
to synthesize key events.
*/
class IKeyState {
public:
    virtual ~IKeyState() { }

    enum {
        kNumButtons = 0x200
    };

    //! Key event data
    class KeyInfo {
    public:
        KeyInfo() = default;

        KeyInfo(KeyID key, KeyModifierMask mask, KeyButton button, std::int32_t count) :
            m_key{key},
            m_mask{mask},
            m_button{button},
            m_count{count}
        {}

        static KeyInfo create(KeyID, KeyModifierMask, KeyButton, std::int32_t count,
                              const std::set<std::string>& destinations);

        static bool isDefault(const char* screens);
        static bool contains(const char* screens, const std::string& name);
        static bool equal(const KeyInfo*, const KeyInfo*);
        static std::string join(const std::set<std::string>& destinations);
        static void split(const char* screens, std::set<std::string>&);

        const char* screens_or_nullptr() const
        {
            return screens_.empty() ? nullptr : screens_.c_str();
        }

    public:
        KeyID m_key = 0;
        KeyModifierMask m_mask = 0;
        KeyButton m_button = 0;
        std::int32_t m_count = 0;
        std::string screens_;
    };

    typedef std::set<KeyButton> KeyButtonSet;

    //! @name manipulators
    //@{

    //! Update the keyboard map
    /*!
    Causes the key state to get updated to reflect the current keyboard
    mapping.
    */
    virtual void updateKeyMap() = 0;

    //! Update the key state
    /*!
    Causes the key state to get updated to reflect the physical keyboard
    state.
    */
    virtual void updateKeyState() = 0;

    //! Set half-duplex mask
    /*!
    Sets which modifier toggle keys are half-duplex.  A half-duplex
    toggle key doesn't report a key release when toggled on and
    doesn't report a key press when toggled off.
    */
    virtual void setHalfDuplexMask(KeyModifierMask) = 0;

    //! Fake a key press
    /*!
    Synthesizes a key press event and updates the key state.
    */
    virtual void fakeKeyDown(KeyID id, KeyModifierMask mask,
                            KeyButton button) = 0;

    //! Fake a key repeat
    /*!
    Synthesizes a key repeat event and updates the key state.
    */
    virtual bool fakeKeyRepeat(KeyID id, KeyModifierMask mask, std::int32_t count,
                               KeyButton button) = 0;

    //! Fake a key release
    /*!
    Synthesizes a key release event and updates the key state.
    */
    virtual bool fakeKeyUp(KeyButton button) = 0;

    //! Fake key releases for all fake pressed keys
    /*!
    Synthesizes a key release event for every key that is synthetically
    pressed and updates the key state.
    */
    virtual void fakeAllKeysUp() = 0;

    //! Fake ctrl+alt+del
    /*!
    Synthesize a press of ctrl+alt+del.  Return true if processing is
    complete and false if normal key processing should continue.
    */
    virtual bool fakeCtrlAltDel() = 0;

    //! Fake a media key
    /*!
     Synthesizes a media key down and up. Only Mac would implement this by
     use cocoa appkit framework.
     */
    virtual bool fakeMediaKey(KeyID id) = 0;

    //@}
    //! @name accessors
    //@{

    //! Test if key is pressed
    /*!
    Returns true iff the given key is down.  Half-duplex toggles
    always return false.
    */
    virtual bool isKeyDown(KeyButton) const = 0;

    //! Get the active modifiers
    /*!
    Returns the modifiers that are currently active according to our
    shadowed state.
    */
    virtual KeyModifierMask
                        getActiveModifiers() const = 0;

    //! Get the active modifiers from OS
    /*!
    Returns the modifiers that are currently active according to the
    operating system.
    */
    virtual KeyModifierMask
                        pollActiveModifiers() const = 0;

    //! Get the active keyboard layout from OS
    /*!
    Returns the active keyboard layout according to the operating system.
    */
    virtual std::int32_t pollActiveGroup() const = 0;

    //! Get the keys currently pressed from OS
    /*!
    Adds any keys that are currently pressed according to the operating
    system to \p pressedKeys.
    */
    virtual void pollPressedKeys(KeyButtonSet& pressedKeys) const = 0;

    //@}
};

} // namespace skvm
