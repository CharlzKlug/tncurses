#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

waddchnstr stdscr [chtype H [A_UNDERLINE] [A_BOLD] [A_BLINK]] {*}[string-to-chtypes-lst "ello there!"] 5
refresh
set somewindow [newwin 10 30 4 26]
waddchstr $somewindow {*}[string-to-chtypes-lst "** TEST **"]
wrefresh $somewindow
refresh
getch

endwin
