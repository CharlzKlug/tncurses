#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::box stdscr 42 43
tncurses::refresh
tncurses::getch

tncurses::endwin
