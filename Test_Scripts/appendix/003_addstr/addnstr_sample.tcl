#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

addnstr "*** Test ***" 4
addnstr "12345678 Hi!" 12
refresh
getch

endwin
