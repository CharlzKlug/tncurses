#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
border [expr 0xba] [expr 0xba] [expr 0xcd] \
    [expr 0xcd] [expr 0xc9] [expr 0xbb] \
    [expr 0xc8] [expr 0xbc]
refresh
getch

endwin
