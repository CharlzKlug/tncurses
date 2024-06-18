#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

addchnstr {*}[string-to-chtypes-lst "hello there!"] 3
refresh
getch

endwin
