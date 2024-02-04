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
#include <iostream>
#include <sstream>
#include "Version.h"
#include <base/String.h>

namespace skvm {
namespace updater {

Version::Version()
{
}

Version::Version(const std::string& version)
{
    parse(version);
}

bool Version::operator >(const Version& version) const
{
    if (m_major > version.m_major) return true;
    if (m_major < version.m_major) return false;
    if (m_minor > version.m_minor) return true;
    if (m_minor < version.m_minor) return false;
    if (m_patch > version.m_patch) return true;

    return false;
}

const std::string Version::GetVersion() const
{
    std::stringstream stream;
    stream <<"v" << m_major<<"."<<m_minor<<"."<<m_patch;
    return stream.str();
}

const std::string Version::GetLink() const
{
    std::stringstream stream;
    stream << "https://github.com/SergeyGadzhilov/SKVM/releases/tag/";
    stream <<m_major<<"."<<m_minor<<"."<<m_patch;
    return stream.str();
}

std::ostream& operator<<(std::ostream &stream, const Version& version)
{
    stream<<version.GetVersion();
    return stream;
}

void Version::parse(const std::string& version)
{
    try {
        if (version.empty())
        {
            std::cerr<<"fail to parse version because it's empty"<<std::endl;
            return;
        }

        auto parts = string::splitString(version, '.');
        if (parts.size() < 3)
        {
            std::cerr<<"fail to parse version: "<<version<<std::endl;
            return;
        }

        m_major = std::stoi(parts[0]);
        m_minor = std::stoi(parts[1]);
        m_patch = std::stoi(parts[2]);
    }
    catch (std::exception& ex)
    {
        std::cerr<<"fail to parse version: "<<version<<" because "<<ex.what()<<std::endl;
    }
}

} //namespace updates
} //namespace skvm
