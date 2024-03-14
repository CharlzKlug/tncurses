#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
printw "Hello!!!\n"
refresh
set my_char [getch]

endwin
puts $my_char
