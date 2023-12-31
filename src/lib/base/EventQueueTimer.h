/*
    SKVM -- mouse and keyboard sharing utility
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

#ifndef SKVM_LIB_BASE_EVENT_QUEUE_TIMER_H
#define SKVM_LIB_BASE_EVENT_QUEUE_TIMER_H

#include "EventTarget.h"

namespace skvm {

class EventQueueTimer : public EventTarget {
public:
    virtual ~EventQueueTimer() = default;
};

} // namespace skvm

#endif // SKVM_LIB_BASE_EVENT_QUEUE_TIMER_H
