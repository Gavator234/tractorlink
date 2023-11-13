
# tractorlink - A program replicating the Fallout series's terminal hacking minigame.
# Copyright (C) 2023  Gavin Mitchell

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.27)

project(tractorlink CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

if (WIN32)
  add_compile_definitions(WINCOMPAT)
elseif (UNIX)
  add_compile_definitions(UNIXCOMPAT)
endif()

include_directories(include)
add_subdirectory(src)

# terminal.cc settings
target_link_libraries(terminal os)
target_link_libraries(terminal ${CURSES_LIBRARIES})

# tractorlink settings
add_executable(tractorlink main.cc)
target_link_libraries(tractorlink terminal os)

# make sure the build number is incremented before building
add_custom_command(TARGET tractorlink PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/increment_build.cmake
)