#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
set result [tncurses::isendwin]
if {$result == FALSE} {tncurses::addstr "Not isendwin\n"}
tncurses::getch
tncurses::endwin
if {[tncurses::isendwin] == TRUE} {puts "Is endwin"}
exit 0
