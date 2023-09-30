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

#pragma once

#include "Fwd.h"
#include "arch/IArchNetwork.h"
#include "net/ConnectionSecurityLevel.h"
#include <memory>

namespace skvm {

//! Socket factory
/*!
This interface defines the methods common to all factories used to
create sockets.
*/
class ISocketFactory {
public:
    virtual ~ISocketFactory() { }

    //! Create data socket
    virtual std::unique_ptr<IDataSocket>
        create(IArchNetwork::EAddressFamily family,
               ConnectionSecurityLevel security_level) const = 0;

    //! Create listen socket
    virtual std::unique_ptr<IListenSocket>
        create_listen(IArchNetwork::EAddressFamily family,
                      ConnectionSecurityLevel security_level) const = 0;
};

} // namespace skvm
