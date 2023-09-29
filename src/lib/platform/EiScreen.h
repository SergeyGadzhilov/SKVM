/*  SKVM -- mouse and keyboard sharing utility
    Copyright (C) SKVM contributors

    This package is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    found in the file LICENSE that should have accompanied this file.

    This package is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SKVM_LIB_PLATFORM_EI_SCREEN_H
#define SKVM_LIB_PLATFORM_EI_SCREEN_H

#include "config.h"

#include "inputleap/PlatformScreen.h"
#include "inputleap/KeyMap.h"
#include <set>
#include <mutex>
#include <vector>

struct ei;
struct ei_event;
struct ei_seat;
struct ei_device;

namespace skvm {

class EiClipboard;
class EiKeyState;
class PortalRemoteDesktop;
#if HAVE_LIBPORTAL_INPUTCAPTURE
class PortalInputCapture;
#endif

//! Implementation of IPlatformScreen for X11
class EiScreen : public PlatformScreen {
public:
    EiScreen(bool is_primary, IEventQueue* events, bool use_portal);
    ~EiScreen();

    // IScreen overrides
    const EventTarget* get_event_target() const override;
    bool getClipboard(ClipboardID id, IClipboard*) const override;
    void getShape(std::int32_t& x, std::int32_t& y,
                  std::int32_t& width, std::int32_t& height) const override;
    void getCursorPos(std::int32_t& x, std::int32_t& y) const override;

    // IPrimaryScreen overrides
    void reconfigure(std::uint32_t activeSides) override;
    void warpCursor(std::int32_t x, std::int32_t y) override;
    std::uint32_t registerHotKey(KeyID key, KeyModifierMask mask) override;
    void unregisterHotKey(std::uint32_t id) override;
    void fakeInputBegin() override;
    void fakeInputEnd() override;
    std::int32_t getJumpZoneSize() const override;
    bool isAnyMouseButtonDown(std::uint32_t& buttonID) const override;
    void getCursorCenter(std::int32_t& x, std::int32_t& y) const override;

    // ISecondaryScreen overrides
    void fakeMouseButton(ButtonID id, bool press) override;
    void fakeMouseMove(std::int32_t x, std::int32_t y) override;
    void fakeMouseRelativeMove(std::int32_t dx, std::int32_t dy) const override;
    void fakeMouseWheel(std::int32_t xDelta, std::int32_t yDelta) const override;
    void fakeKey(std::uint32_t keycode, bool is_down) const;


    // IPlatformScreen overrides
    void enable() override;
    void disable() override;
    void enter() override;
    bool leave() override;
    bool setClipboard(ClipboardID, const IClipboard*) override;
    void checkClipboards() override;
    void openScreensaver(bool notify) override;
    void closeScreensaver() override;
    void screensaver(bool activate) override;
    void resetOptions() override;
    void setOptions(const OptionsList& options) override;
    void setSequenceNumber(std::uint32_t) override;
    bool isPrimary() const override;

protected:
    // IPlatformScreen overrides
    void handle_system_event(const Event& event) override;
    void handle_connected_to_eis_event(const Event& event);
    void updateButtons() override;
    IKeyState* getKeyState() const override;

    void update_shape();
    void add_device(ei_device* device);
    void remove_device(ei_device* device);

private:
    void send_event(EventType type, EventDataBase* data);
    ButtonID map_button_from_evdev(ei_event* event) const;
    void on_key_event(ei_event *event);
    void on_button_event(ei_event *event);
    void on_pointer_scroll_event(ei_event* event);
    void on_pointer_scroll_discrete_event(ei_event* event);
    void on_motion_event(ei_event *event);
    void on_abs_motion_event(ei_event *event);

private:
    // true if screen is being used as a primary screen, false otherwise
    bool is_primary_ = false;
    IEventQueue* events_ = nullptr;

    // keyboard stuff
    EiKeyState* key_state_ = nullptr;

    std::vector<ei_device*> ei_devices_;

    ei* ei_ = nullptr;
    ei_seat* ei_seat_ = nullptr;
    ei_device* ei_pointer_ = nullptr;
    ei_device* ei_keyboard_ = nullptr;
    ei_device* ei_abs_ = nullptr;

    std::uint32_t x_ = 0;
    std::uint32_t y_ = 0;
    std::uint32_t w_ = 0;
    std::uint32_t h_ = 0;

    // true if mouse has entered the screen
    bool is_on_screen_;

    // last pointer position
    std::int32_t cursor_x_ = 0;
    std::int32_t cursor_y_ = 0;

    mutable std::mutex mutex_;

    PortalRemoteDesktop* portal_remote_desktop_;
#if HAVE_LIBPORTAL_INPUTCAPTURE
    PortalInputCapture* portal_input_capture_;
#endif
};

} // namespace skvm

#endif // SKVM_LIB_PLATFORM_EI_SCREEN_H
