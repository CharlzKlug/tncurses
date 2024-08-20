#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::mvwhline stdscr 10 10 42 20
tncurses::refresh
tncurses::getch

set newWindow [tncurses::newwin 10 30 4 26]
tncurses::mvwhline $newWindow 0 0 0 5
tncurses::wrefresh $newWindow
tncurses::getch

tncurses::delwin $newWindow
tncurses::endwin
