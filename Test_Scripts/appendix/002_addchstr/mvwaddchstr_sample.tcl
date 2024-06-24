#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvwaddchstr stdscr 0 10 {*}[string-to-chtypes-lst "!?"]
refresh
set somewindow [newwin 10 30 4 26]
waddchstr $somewindow {*}[string-to-chtypes-lst "** TEST **"]
wrefresh $somewindow
refresh
getch

endwin
