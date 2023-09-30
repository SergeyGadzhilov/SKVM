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

#include "server/Config.h"
#include "base/EventTarget.h"
#include "base/EventTypes.h"
#include "base/Event.h"
#include "base/UniquePtrContainer.h"
#include "net/ConnectionSecurityLevel.h"
#include "net/Fwd.h"
#include <deque>
#include <memory>
#include <set>

namespace skvm {

class ClientProxy;
class ClientProxyUnknown;
class Server;

class ClientListener : public EventTarget {
public:
    // The factories are adopted.
    ClientListener(const NetworkAddress&,
                   std::unique_ptr<ISocketFactory> socket_factory, IEventQueue* events,
                   ConnectionSecurityLevel security_level);
    ~ClientListener();

    //! @name manipulators
    //@{

    void setServer(Server* server);

    //@}

    //! @name accessors
    //@{

    //! Get next connected client
    /*!
    Returns the next connected client and removes it from the internal
    list.  The client is responsible for deleting the returned client.
    Returns nullptr if no clients are available.
    */
    ClientProxy* getNextClient();

    //! Get server which owns this listener
    Server* getServer() { return m_server; }

    //@}

private:
    // client connection event handlers
    void handle_client_connecting();
    void handle_client_accepted(IDataSocket* socket_ptr);
    void handle_unknown_client(ClientProxyUnknown* client);
    void handle_client_disconnected(ClientProxy* client);

    void cleanupListenSocket();
    void cleanupClientSockets();

private:
    typedef std::set<ClientProxyUnknown*> NewClients;
    typedef std::deque<ClientProxy*> WaitingClients;

    std::unique_ptr<IListenSocket> listen_;
    std::unique_ptr<ISocketFactory> socket_factory_;
    NewClients m_newClients;
    WaitingClients m_waitingClients;
    Server* m_server;
    IEventQueue* m_events;
    ConnectionSecurityLevel security_level_;
    UniquePtrContainer<IDataSocket> client_sockets_;
};

} // namespace skvm
