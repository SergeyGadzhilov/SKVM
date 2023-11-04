# SKVM -- mouse and keyboard sharing utility
# Copyright (C) 2023 Hadzhilov Serhii
# Copyright (C) 2012-2016 Symless Ltd.
# Copyright (C) 2009 Nick Bolton
#
# This package is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# found in the file LICENSE that should have accompanied this file.
#
# This package is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

set(sources
    skvmc.cpp
)

if (BUILD_MSWINDOWS)
    file(GLOB mswin_headers "MSWindows*.h")
    file(GLOB mswin_sources "MSWindows*.cpp")
    list(APPEND sources
        skvmc.exe.manifest
        skvmc.rc
    )
    set_property(SOURCE skvmc.rc PROPERTY COMPILE_FLAGS /nologo)
endif()
if (BUILD_CARBON)
    file(GLOB carbon_headers "OSX*.h")
    file(GLOB carbon_sources "OSX*.cpp")
endif()
if (BUILD_XWINDOWS)
    file(GLOB xwin_headers "XWindows*.h")
    file(GLOB xwin_sources "XWindows*.cpp")
endif()
if (BUILD_LIBEI)
    file(GLOB ei_headers "Ei*.h")
    file(GLOB ei_sources "Ei*.cpp")
endif()

list(APPEND sources ${mswin_sources} ${carbon_sources} ${xwin_sources} ${ei_sources})
list(APPEND headers ${mswin_headers} ${carbon_headers} ${xwin_headers} ${ei_headers})

if(SKVM_ADD_HEADERS)
    list(APPEND sources ${headers})
endif()

add_executable(skvmc ${sources})
target_link_libraries(skvmc
    arch base client common io mt net ipc platform server synlib ${libs} ${OPENSSL_LIBS})
