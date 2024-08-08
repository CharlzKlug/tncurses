#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::wborder stdscr 42 0 0 0 0 0 0 42
tncurses::refresh
tncurses::getch

set newWindow [tncurses::newwin 10 30 4 26]
tncurses::wborder $newWindow 0 0 0 0 0 0 0 0
tncurses::wrefresh $newWindow
tncurses::getch

tncurses::delwin $newWindow
tncurses::endwin
