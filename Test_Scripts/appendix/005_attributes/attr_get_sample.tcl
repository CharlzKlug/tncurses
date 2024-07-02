#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
attrset 
set attrList [attr_get]

refresh
getch

endwin

puts [lindex $attrList 0]
puts [lindex $attrList 1]
