#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

addchstr {*}[string-to-chtypes-lst "hello there!"]
refresh
getch

endwin
