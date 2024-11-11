#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr

tncurses::addstr "My COLS is [tncurses::COLS]\n"
tncurses::getch
tncurses::endwin
