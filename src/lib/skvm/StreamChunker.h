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

#include "skvm/clipboard_types.h"
#include "base/Fwd.h"

#include <string>

namespace inputleap {

class StreamChunker {
public:
    static void sendFile(const char* filename, IEventQueue* events, const EventTarget* event_target);
    static void sendClipboard(std::string& data, std::size_t size, ClipboardID id,
                              std::uint32_t sequence, IEventQueue* events,
                              const EventTarget* event_target);
    static void interruptFile();

private:
    static bool            s_isChunkingFile;
    static bool            s_interruptFile;
};

} // namespace inputleap
