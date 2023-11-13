/*
    tractorlink - A program replicating the Fallout series's terminal hacking minigame.
    Copyright (C) 2023  Gavin Mitchell

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <sstream>
#include "common.hh"
#include "os.hh"

namespace terminal
{
  void clear();
  void set_cursor_pos(int x, int y);
  void set_cursor_visibility(bool visible);
  void clear_line();
  char get_char();

  struct window
  {
    ullVector2 termsize = os::gettermsize();
    ullVector2 winsize;
    ullVector2 winpos;
    ullVector2 cursor = {0, 0};

    std::stringstream buffer;
    window(ullVector2 wsize, ullVector2 wpos);
    void win_clear();
    void set_wcursor_pos(int xin, int yin);
    void set_wcursor_pos();
    void render();
  };
}