#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
noecho
keypad stdscr TRUE
mousemask [ALL_MOUSE_EVENTS] NULL
while {true} {
    set ch [getch]
    if {$ch == [KEY_MOUSE]} {
	clear
	set mort [getmouse]
	switch -- [lindex $mort 4] \
	    [BUTTON1_PRESSED] {
		mvaddstr 0 0 "Button 1 Pressed!"
	    } \
	    [BUTTON1_RELEASED] {
		mvaddstr 1 0 "Button 1 Released!"
	    } \
	    [BUTTON1_CLICKED] {
		mvaddstr 2 0 "Button 1 Clicked!"
	    } \
	    [BUTTON1_DOUBLE_CLICKED] {
		mvaddstr 3 0 "Button 1 Dbl-Clicked!"
	    } \
	    [BUTTON2_PRESSED] {
		mvaddstr 0 20 "Button 2 Pressed!"
	    } \
	    [BUTTON2_RELEASED] {
		mvaddstr 1 20 "Button 2 Released!"
	    } \
	    [BUTTON2_CLICKED] {
		mvaddstr 2 20 "Button 2 Clicked!"
	    } \
	    [BUTTON2_DOUBLE_CLICKED] {
		mvaddstr 3 20 "Button 2 Dbl-Clicked!"
	    } \
	    [BUTTON3_PRESSED] {
		mvaddstr 0 40 "Button 3 Pressed!"
	    } \
	    [BUTTON3_RELEASED] {
		mvaddstr 1 40 "Button 3 Released!"
	    } \
	    [BUTTON3_CLICKED] {
		mvaddstr 2 40 "Button 3 Clicked!"
	    } \
	    [BUTTON3_DOUBLE_CLICKED] {
		mvaddstr 3 40 "Button 3 Dbl-Clicked!"
	    }
	refresh
	continue
    }
    if {[format "%c" $ch] eq "\n"} break
}
endwin
