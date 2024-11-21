#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::use_env TRUE
tncurses::initscr
tncurses::addstr "Some test string"
tncurses::getch
tncurses::endwin
