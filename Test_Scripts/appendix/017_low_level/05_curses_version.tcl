#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::printw "[tncurses::curses_version]"
tncurses::refresh
tncurses::getch
tncurses::endwin
