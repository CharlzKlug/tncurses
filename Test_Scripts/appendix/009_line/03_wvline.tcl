#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::wvline stdscr 42 20
tncurses::refresh
tncurses::getch

set newWindow [tncurses::newwin 10 30 4 26]
# tncurses::wborder $newWindow 0 0 0 0 0 0 0 0
tncurses::wvline $newWindow 0 100
tncurses::wrefresh $newWindow
tncurses::getch

tncurses::delwin $newWindow
tncurses::endwin
