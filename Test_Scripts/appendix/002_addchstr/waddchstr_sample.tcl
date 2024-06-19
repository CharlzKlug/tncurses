#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

waddchstr stdscr {*}[string-to-chtypes-lst "hello there!"]
refresh
set somewindow [newwin 10 30 4 26]
waddchstr $somewindow {*}[string-to-chtypes-lst "** TEST **"]
wrefresh $somewindow
refresh
getch

endwin
