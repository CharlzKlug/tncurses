#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

addch [chtype H]
addch [chtype i]
addch [chtype !]
refresh
getch

endwin
