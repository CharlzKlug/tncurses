#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Enabled noecho:\n"
tncurses::addstr "Now pressed key will not be echoed. Press any key...\n"
tncurses::noecho
tncurses::getch

tncurses::addstr "Enabled echo:\n"
tncurses::addstr "Now pressed key will be echoed. Press any key...\n"
tncurses::echo
tncurses::getch
tncurses::addstr "\nPress again any key...\n"
tncurses::getch
tncurses::endwin
