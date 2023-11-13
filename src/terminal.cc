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

#include <iostream>
#include <ncurses.h>

#include "terminal.hh"
#include "os.hh"

using namespace terminal;

void terminal::clear()
{
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void terminal::set_cursor_pos(int x, int y)
{
    std::cout << "\033[" << y << ";" << x << "H";
}

void terminal::set_cursor_visibility(bool visible)
{
    if (visible)
        std::cout << "\033[?25h" << std::flush;
    else
        std::cout << "\033[?25l" << std::flush;
}

void terminal::clear_line()
{
    std::cout << "\033[2K" << std::flush;
}

char terminal::get_char()
{
    return getch();
}

terminal::window::window(ullVector2 winsize, ullVector2 winpos)
                          : winsize(winsize),    winpos(winpos)
{
    clear();
    //Check to see if the window is too big for the terminal
    if (winsize.y > termsize.y || winsize.x > termsize.x) {
        std::cout << "Window size is too big for the terminal!" << std::endl;
        std::cout << "Window size: " << winsize.y << "x" << winsize.x << std::endl;
        std::cout << "Terminal size: " << termsize.y << "x" << termsize.x << std::endl;
        exit(1);
    }

    //Check to see if the window isn't cut off at a given position
    if (winpos.x + winsize.x > termsize.x || winpos.y + winsize.y > termsize.y) {
        std::cout << "Window would render cut off at that position!" << std::endl;
        std::cout << "Window size: " << winsize.y << "x" << winsize.x << std::endl;
        std::cout << "Window position: " << winpos.x << "," << winpos.y << std::endl;
        exit(1);
    }

    render();
}

void terminal::window::render()
{
    std::ios_base::sync_with_stdio(false);
    win_clear();
    cursor = {0, 0};

    //print the bounding box
    for (unsigned int i = 0; i < winsize.y; i++) {
        set_cursor_pos(winpos.x - 1, winpos.y + i);
        std::cout << "|";
        set_cursor_pos(winpos.x + winsize.x, winpos.y + i);
        std::cout << "|";
    }

    for (char c : buffer.str()) {
        if (cursor.y > winsize.y) {
            //remove the first line worth of data from the buffer, and restart the render process
            std::string aftertrim = buffer.str().substr(winsize.x);
            buffer.str(aftertrim);
            return render();
        }

        if (cursor.x == winsize.x) {
            cursor.x = 0;
            cursor.y++;
        }

        if (c == '\n') {
            cursor.x = 0;
            cursor.y++;
            continue;
        }

        //translate the position in the window to a position in the terminal
        int xpos = winpos.x + cursor.x;
        int ypos = winpos.y + cursor.y;

        //move the cursor to the position and print the character
        cursor.x++;
        set_cursor_pos(xpos, ypos);
        std::cout << c;
    }

    std::cout << std::flush;
    std::ios_base::sync_with_stdio(true);
}

void terminal::window::win_clear()
{
    std::ios_base::sync_with_stdio(false);
    for (unsigned int i = 0; i < winsize.y; i++) {
        set_cursor_pos(winpos.x, winpos.y + i);
        for (unsigned int i = 0; i < winsize.x; i++) {
            std::cout << " ";
        }
    }
    std::cout << std::flush;
    std::ios_base::sync_with_stdio(true);
}

void terminal::window::set_wcursor_pos(int xin, int yin)
{
    cursor.x = xin;
    cursor.y = yin;

    int xpos = winpos.x + cursor.x;
    int ypos = winpos.y + cursor.y;

    set_cursor_pos(xpos, ypos);
}