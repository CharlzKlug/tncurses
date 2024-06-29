#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvaddnstr 0 10 "Hello!" 5
mvaddnstr 1 9 "Hello!" 6
refresh
getch

endwin
