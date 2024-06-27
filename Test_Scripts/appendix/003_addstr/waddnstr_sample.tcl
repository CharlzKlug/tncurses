#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

initscr

waddnstr stdscr "*** Test ***" 4
refresh
set somewindow [newwin 10 30 4 26]
waddnstr $somewindow "12345" 5
wrefresh $somewindow
refresh
getch
delwin $somewindow
endwin
