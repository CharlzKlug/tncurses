#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

set p [newpad 50 100]

addstr "New pad created"
refresh
getch

endwin
