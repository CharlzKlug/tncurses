#!/usr/bin/env tclsh

load ./libtncurses.so

set scr [tncurses::newterm a stdout stderr]
puts $scr

exit 0
