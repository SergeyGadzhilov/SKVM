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

#include "net/TCPListenSocket.h"

#include "net/NetworkAddress.h"
#include "net/SocketMultiplexer.h"
#include "net/TCPSocket.h"
#include "net/TSocketMultiplexerMethodJob.h"
#include "net/XSocket.h"
#include "io/XIO.h"
#include "arch/Arch.h"
#include "arch/XArch.h"
#include "base/IEventQueue.h"

namespace skvm {

TCPListenSocket::TCPListenSocket(IEventQueue* events, SocketMultiplexer* socketMultiplexer, IArchNetwork::EAddressFamily family) :
    m_events(events),
    m_socketMultiplexer(socketMultiplexer)
{
    try {
        m_socket = ARCH->newSocket(family, IArchNetwork::kSTREAM);
    }
    catch (XArchNetwork& e) {
        throw XSocketCreate(e.what());
    }
}

TCPListenSocket::~TCPListenSocket()
{
    try {
        if (m_socket != nullptr) {
            m_socketMultiplexer->removeSocket(this);
            ARCH->closeSocket(m_socket);
        }
    }
    catch (...) {
        // ignore
    }
}

void
TCPListenSocket::bind(const NetworkAddress& addr)
{
    try {
        std::lock_guard<std::mutex> lock(mutex_);
        ARCH->setReuseAddrOnSocket(m_socket, true);
        ARCH->bindSocket(m_socket, addr.getAddress());
        ARCH->listenOnSocket(m_socket);

        auto new_job = std::make_unique<TSocketMultiplexerMethodJob>(
                    [this](auto j, auto r, auto w, auto e)
                    { return serviceListening(j, r, w, e); },
                    m_socket, true, false);

        m_socketMultiplexer->addSocket(this, std::move(new_job));
    }
    catch (XArchNetworkAddressInUse& e) {
        throw XSocketAddressInUse(e.what());
    }
    catch (XArchNetwork& e) {
        throw XSocketBind(e.what());
    }
}

void
TCPListenSocket::close()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (m_socket == nullptr) {
        throw XIOClosed();
    }
    try {
        m_socketMultiplexer->removeSocket(this);
        ARCH->closeSocket(m_socket);
        m_socket = nullptr;
    }
    catch (XArchNetwork& e) {
        throw XSocketIOClose(e.what());
    }
}

const EventTarget* TCPListenSocket::get_event_target() const
{
    return this;
}

std::unique_ptr<IDataSocket> TCPListenSocket::accept()
{
    std::unique_ptr<IDataSocket> socket;
    try {
        socket = std::make_unique<TCPSocket>(m_events, m_socketMultiplexer,
                                             ARCH->acceptSocket(m_socket, nullptr));
        setListeningJob();
        return socket;
    }
    catch (XArchNetwork&) {
        if (socket) {
            setListeningJob();
        }
        return nullptr;
    }
    catch (std::exception &ex) {
        if (socket) {
            setListeningJob();
        }
        throw ex;
    }
}

void
TCPListenSocket::setListeningJob()
{
    auto new_job = std::make_unique<TSocketMultiplexerMethodJob>(
                [this](auto j, auto r, auto w, auto e)
                { return serviceListening(j, r, w, e); },
                m_socket, true, false);
    m_socketMultiplexer->addSocket(this, std::move(new_job));
}

MultiplexerJobStatus TCPListenSocket::serviceListening(ISocketMultiplexerJob* job,
                                                       bool read, bool, bool error)
{
    (void) job;

    if (error) {
        close();
        return {false, {}};
    }
    if (read) {
        m_events->add_event(EventType::LISTEN_SOCKET_CONNECTING, this);
        // stop polling on this socket until the client accepts
        return {false, {}};
    }
    return {true, {}};
}

} // namespace skvm
