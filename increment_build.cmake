
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

set(HEADER_FILE ${CMAKE_CURRENT_SOURCE_DIR}/include/buildnum.hh)
set(CACHE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/buildnumcache.txt)

if(EXISTS ${CACHE_FILE})
  file(READ ${CACHE_FILE} BUILDNUM)
  math(EXPR BUILDNUM "${BUILDNUM} + 1")
else()
  set(BUILDNUM "1")
endif()

file(WRITE ${CACHE_FILE} "${BUILDNUM}")

file(WRITE ${HEADER_FILE} "
  #ifndef BUILDNUM
  #define BUILDNUM \"${BUILDNUM}\"
  #endif
")
