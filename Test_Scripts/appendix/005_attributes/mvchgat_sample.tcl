#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_RED COLOR_BLUE

addstr "Attributes active in this window:\n"
mvchgat 0 0 5 [expr [A_BLINK]] 1 NULL
refresh
getch

endwin
