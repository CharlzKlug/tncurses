#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
set bdrt [baudrate]
addstr "Current baudrate is $bdrt. Press any key to continue."
getch
endwin
