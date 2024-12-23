#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Napms is started for 1000 milliseconds\n"
tncurses::refresh
tncurses::napms 1000
tncurses::addstr "Napms is finished. Press any key to continue...\n"
tncurses::getch
tncurses::endwin
