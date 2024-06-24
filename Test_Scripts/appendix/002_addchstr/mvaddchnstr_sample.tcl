#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvaddchnstr 10 10 {*}[string-to-chtypes-lst "hello there!"] 5
refresh
getch

mvaddchnstr 5 10 {*}[string-to-chtypes-lst "hello there!"] 12
refresh
getch

endwin
