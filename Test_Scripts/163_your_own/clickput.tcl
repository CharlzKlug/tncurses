#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

tncurses::initscr
tncurses::noecho
tncurses::keypad stdscr TRUE

tncurses::mousemask [tncurses::ALL_MOUSE_EVENTS] NULL
tncurses::addstr "Click on the screen with the mouse."
while {1} {
    set ch [tncurses::getch]
    if {$ch == [tncurses::KEY_MOUSE]} {
	set mevent_list [tncurses::getmouse]
	tncurses::clrtoeol
	set y [lindex $mevent_list 2]
	set x [lindex $mevent_list 1]
	tncurses::mvaddch [lindex $mevent_list 2] [lindex $mevent_list 1] [chtype * 0]
	tncurses::move 0 0
	tncurses::printw "[lindex $mevent_list 2]\t[lindex $mevent_list 1]\tPress \[Enter\] to exit."
	tncurses::refresh
	continue
    }
    if {[format "%c" $ch] eq "\n"} {
	break
    }
}

tncurses::endwin
