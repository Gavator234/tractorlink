
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

project(tractorlink
  LANGUAGES CXX
  VERSION 0.1.0  
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
  add_compile_definitions(WINCOMPAT)
elseif (UNIX)
  add_compile_definitions(UNIXCOMPAT)
endif()

include_directories(include build)
add_subdirectory(src)

# terminal.cc settings
target_link_libraries(terminal os)

# tractorlink settings
add_compile_definitions(PROJECT_VERSION=${tractorlink_VERSION_MAJOR}.${tractorlink_VERSION_MINOR})
add_executable(tractorlink main.cc)
target_link_libraries(tractorlink terminal os)