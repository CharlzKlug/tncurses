#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set p [newpad 50 100]

addstr "New pad created"
prefresh $p 0 0 0 0 1 15
getch

endwin
