#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
noecho
keypad stdscr TRUE

mousemask [ALL_MOUSE_EVENTS] NULL

while {1} {
    set ch [getch]
    if {$ch == [KEY_MOUSE]} {
	set mevent_list [getmouse]
	clrtoeol
	mvaddch [lindex $mevent_list 2] [lindex $mevent_list 1] *
	move 0 0
	printw "[lindex $mevent_list 2]\t[lindex $mevent_list 1]"
	refresh
	continue
    }
    if {[format "%c" $ch] eq "\n"} {
	break
    }
}

endwin
