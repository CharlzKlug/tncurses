#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvaddchstr 0 5 {*}[string-to-chtypes-lst "hello there!"]
refresh
getch

endwin
