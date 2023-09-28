/*
 * InputLeap -- mouse and keyboard sharing utility
 * Copyright (C) 2013-2016 Symless Ltd.
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

#define INPUTLEAP_TEST_ENV

#include "base/EventTarget.h"
#include "skvm/Screen.h"

#include <gmock/gmock.h>

namespace inputleap {

class MockScreen : public Screen, public EventTarget
{
public:
    const EventTarget* get_event_target() const override { return this; }
    MockScreen() : inputleap::Screen() { }
    MOCK_METHOD0(disable, void());
    MOCK_CONST_METHOD4(getShape, void(std::int32_t&, std::int32_t&, std::int32_t&, std::int32_t&));
    MOCK_CONST_METHOD2(getCursorPos, void(std::int32_t&, std::int32_t&));
    MOCK_METHOD0(resetOptions, void());
    MOCK_METHOD1(setOptions, void(const OptionsList&));
    MOCK_METHOD0(enable, void());
};

} // namespace inputleap
