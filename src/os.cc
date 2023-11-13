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

#include "os.hh"
#include "common.hh"

#ifdef UNIXCOMPAT
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>

namespace os
{
    //oldt and newt aren't functions, they are variables that are initialized once and
    //then never changed. They just need to be preprocessed since getchar() will be ran a lot.
    const struct termios oldt = [] -> termios {
        struct termios oldt;
        tcgetattr(STDIN_FILENO, &oldt);
        return oldt;
    }();

    const struct termios newt = [] -> termios {
        struct termios newt = oldt;
        newt.c_lflag &= ~(ICANON);
        return newt;
    }();

    void timer(unsigned long long ms)
    {
        usleep(ms * 1000);
    }

    ullVector2 gettermsize()
    {
        struct winsize w;
        ioctl( STDOUT_FILENO, TIOCGWINSZ, &w);
        return ullVector2{w.ws_row, w.ws_col};
    }

    char get_char()
    {
        tcsetattr( STDOUT_FILENO, TCSANOW, &newt);

        char input = '\0';
        input = getchar();

        tcsetattr( STDOUT_FILENO, TCSANOW, &oldt);
        return input;
    }
}
#endif

#ifdef WINCOMPAT
#include <windows.h>

namespace os
{
    void timer(unsigned long long ms)
    {
        Sleep(ms);
    }int

    ullVector2 gettermsize()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return ullVector2{(unsigned) csbi.srWindow.Bottom - csbi.srWindow.Top + 1,
                          (unsigned) csbi.srWindow.Right - csbi.srWindow.Left + 1};
    }

    char get_char()
    {
        //Todo: This.
        throw std::excetpion;
    }
}
#endif