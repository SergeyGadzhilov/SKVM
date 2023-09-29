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

#include "config.h"

#include "base/Fwd.h"
#include "inputleap/KeyState.h"
#include "XWindowsImpl.h"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#    include <X11/extensions/XKBstr.h>

#include <map>
#include <vector>

namespace skvm {

//! X Windows key state
/*!
A key state for X Windows.
*/
class XWindowsKeyState : public KeyState {
public:
    typedef std::vector<int> KeycodeList;
    enum {
        kGroupPoll       = -1,
        kGroupPollAndSet = -2
    };

    XWindowsKeyState(IXWindowsImpl* impl, Display*, bool useXKB,
                     IEventQueue* events);
    XWindowsKeyState(IXWindowsImpl* impl, Display*, bool useXKB,
                     IEventQueue* events, skvm::KeyMap& keyMap);
    ~XWindowsKeyState();

    //! @name modifiers
    //@{

    //! Set active group
    /*!
    Sets the active group to \p group.  This is the group returned by
    \c pollActiveGroup().  If \p group is \c kGroupPoll then
    \c pollActiveGroup() will really poll, but that's a slow operation
    on X11.  If \p group is \c kGroupPollAndSet then this will poll the
    active group now and use it for future calls to \c pollActiveGroup().
    */
    void setActiveGroup(std::int32_t group);

    //! Set the auto-repeat state
    /*!
    Sets the auto-repeat state.
    */
    void setAutoRepeat(const XKeyboardState&);

    //@}
    //! @name accessors
    //@{

    //! Convert X modifier mask to SKVM mask
    /*!
    Returns the SKVM modifier mask corresponding to the X modifier
    mask in \p state.
    */
    KeyModifierMask mapModifiersFromX(unsigned int state) const;

    //! Convert SKVM modifier mask to X mask
    /*!
    Converts the SKVM modifier mask to the corresponding X modifier
    mask.  Returns \c true if successful and \c false if any modifier
    could not be converted.
    */
    bool mapModifiersToX(KeyModifierMask, unsigned int&) const;

    //! Convert SKVM key to all corresponding X keycodes
    /*!
    Converts the SKVM key \p key to all of the keycodes that map to
    that key.
    */
    void mapKeyToKeycodes(KeyID key,
                            KeycodeList& keycodes) const;

    //@}

    // IKeyState overrides
    bool fakeCtrlAltDel() override;
    KeyModifierMask pollActiveModifiers() const override;
    std::int32_t pollActiveGroup() const override;
    void pollPressedKeys(KeyButtonSet& pressedKeys) const override;

protected:
    // KeyState overrides
    void getKeyMap(skvm::KeyMap& keyMap) override;
    void fakeKey(const Keystroke& keystroke) override;

private:
    void init(Display* display, bool useXKB);
    void updateKeysymMap(skvm::KeyMap&);
    void updateKeysymMapXKB(skvm::KeyMap&);
    bool hasModifiersXKB() const;
    int getEffectiveGroup(KeyCode, int group) const;
    std::uint32_t getGroupFromState(unsigned int state) const;

    static void remapKeyModifiers(KeyID, std::int32_t, skvm::KeyMap::KeyItem&, void*);

private:
    struct XKBModifierInfo {
    public:
        unsigned char m_level;
        std::uint32_t m_mask;
        bool m_lock;
    };

#ifdef SKVM_TEST_ENV
public: // yuck
#endif
    typedef std::vector<KeyModifierMask> KeyModifierMaskList;

private:
    typedef std::map<KeyModifierMask, unsigned int> KeyModifierToXMask;
    typedef std::multimap<KeyID, KeyCode> KeyToKeyCodeMap;
    typedef std::map<KeyCode, unsigned int> NonXKBModifierMap;
    typedef std::map<std::uint32_t, XKBModifierInfo> XKBModifierMap;

    IXWindowsImpl* m_impl;

    Display* m_display;
    XkbDescPtr m_xkb;
    std::int32_t m_group;
    XKBModifierMap m_lastGoodXKBModifiers;
    NonXKBModifierMap m_lastGoodNonXKBModifiers;

    // X modifier (bit number) to SKVM modifier (mask) mapping
    KeyModifierMaskList m_modifierFromX;

    // SKVM modifier (mask) to X modifier (mask)
    KeyModifierToXMask m_modifierToX;

    // map KeyID to all keycodes that can synthesize that KeyID
    KeyToKeyCodeMap m_keyCodeFromKey;

    // autorepeat state
    XKeyboardState m_keyboardState;

#ifdef SKVM_TEST_ENV
public:
    std::int32_t group() const { return m_group; }
    void group(const std::int32_t& group) { m_group = group; }
    KeyModifierMaskList& modifierFromX() { return m_modifierFromX; }
#endif
};

} // namespace skvm
