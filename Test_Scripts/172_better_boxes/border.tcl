#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::border 42 0 0 0 0 0 0 42
tncurses::refresh
tncurses::getch

tncurses::endwin
