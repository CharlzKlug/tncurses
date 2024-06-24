#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

mvwaddchnstr stdscr 0 10 {*}[string-to-chtypes-lst "!?"] 2
mvwaddchnstr stdscr 1 10 {*}[string-to-chtypes-lst "!?"] 1
# mvaddchnstr 0 10 {*}[string-to-chtypes-lst "!?"] 1
# mvaddchnstr 1 10 {*}[string-to-chtypes-lst "!?"] 1
refresh
set somewindow [newwin 10 30 4 26]
mvwaddchnstr $somewindow 0 0 {*}[string-to-chtypes-lst "** TEST **"] 10
mvwaddchnstr $somewindow 1 0 {*}[string-to-chtypes-lst "** TEST **"] 5
wrefresh $somewindow
refresh
getch

endwin
