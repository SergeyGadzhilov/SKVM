/*
    InputLeap -- mouse and keyboard sharing utility
    Copyright (C) InputLeap contributors

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

#ifndef INPUTLEAP_TEST_GLOBAL_TEST_UTILS_H
#define INPUTLEAP_TEST_GLOBAL_TEST_UTILS_H

#include <cstdint>
#include <vector>

namespace skvm {

std::vector<std::uint8_t> generate_pseudo_random_bytes(std::size_t seed, std::size_t size);

} // namespace skvm

#endif // INPUTLEAP_TEST_GLOBAL_TEST_UTILS_H
