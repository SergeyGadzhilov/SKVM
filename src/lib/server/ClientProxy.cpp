/*
 * SKVM -- mouse and keyboard sharing utility
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

#include "server/ClientProxy.h"
#include "IClientConnection.h"
#include "base/EventQueue.h"

namespace inputleap {

ClientProxy::ClientProxy(const std::string& name, std::unique_ptr<IClientConnection> backend) :
    BaseClientProxy(name),
    conn_{std::move(backend)}
{
}

ClientProxy::~ClientProxy() = default;

void
ClientProxy::close(const char* msg)
{
    // force the close to be sent before we return
    get_conn().flush();
}

const EventTarget* ClientProxy::get_event_target() const
{
    return this;
}

} // namespace inputleap
