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
#include <string>

#include "terminal.hh"

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cout << std::endl <<
        "tractorlink  Copyright (c) 2023  Gavin Mitchell\n"
        "This program comes with ABSOLUTELY NO WARRANTY.\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under certain conditions. See `--license' for details.\n\n"

        "Press enter to agree to the terms of the license, or ^C to exit . . ."
        << std::flush;
        std::cin.get();
        terminal::clear();

        char input;
        std::string inputLine;
        terminal::window TerminalWindow({20, 10}, {10, 5});
        TerminalWindow.buffer << "READY.\n\n? ";

        while (inputLine != "exit\n") {
            if (input == '\n') {
                inputLine.clear();
                TerminalWindow.buffer << "? ";
            }
            TerminalWindow.render();

            input = terminal::get_char();
            TerminalWindow.buffer << input;

            inputLine += input;
        }

        int endCursorRow = TerminalWindow.winsize.y + TerminalWindow.winpos.y + 1;

        terminal::set_cursor_pos(0, endCursorRow);

        return 0;
    }

    if (argc > 1) {
        std::string arg1 = argv[1];

        if (arg1 == "--help" || arg1 == "-h") {
            std::cout << std::endl <<
            "Usage: tractorlink [OPTION]\n"
            "  -h, --help     display this help\n"
            "  -v, --version  give you the version\n"
            "  --license      output license information and exit\n\n"
            << std::flush;
            return 0;
        }

        if (arg1 == "--license") {
            std::cout << std::endl <<
            "tractorlink  Copyright (c) 2023  Gavin Mitchell\n"
            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "(at your option) any later version.\n\n"

            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n\n"

            "You should have received a copy of the GNU General Public License\n"
            "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n"
            << std::flush;
            return 0;
        }

        if (arg1 == "--version" || arg1 == "-v") {
            std::cout << std::endl <<
            "tractorlink " << PROJECT_VERSION << "\n"
            "Made with love <3\n\n"
            << std::flush;
            return 0;
        }

        if (arg1 != "") {
            std::cout << std::endl <<
            "tractorlink: invalid option -- '" << arg1 << "'\n"
            "Try 'tractorlink --help' for more information.\n\n"
            << std::flush;
            return 1;
        }
    }

    std::cout <<
    "Achievement Unlocked! \"How did we get here?\"\n" <<
    "Somehow manage to pass -1 arguments to the program.\n\n" <<
    std::flush;
    return -1;
}