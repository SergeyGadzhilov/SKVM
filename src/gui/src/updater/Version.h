/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2024 Hadzhilov Serhii
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
#ifndef VERSION_H
#define VERSION_H

#include <string>
#include <ostream>

namespace skvm {
namespace updater {

class Version
{
public:
    Version();
    explicit Version(const std::string& version);
    bool operator >(const Version& version) const;
    friend std::ostream& operator <<(std::ostream& stream, const Version& version);

private:
    void parse(const std::string& version);

    int m_major = 0;
    int m_minor = 0;
    int m_patch = 0;
};

} //namespace updater
} //namespace skvm



#endif // VERSION_H
