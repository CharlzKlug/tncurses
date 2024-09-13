#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::halfdelay 10
tncurses::noecho
tncurses::addstr "Press some key\n"
for {set i 0} {$i < 10} {incr i} {
    set ch [tncurses::getch]
    if {$ch < 0} {
	tncurses::addstr "Nothing has been pressed\n"
    } {
	tncurses::addstr "Pressed the $ch key\n"
    }
}

tncurses::endwin
