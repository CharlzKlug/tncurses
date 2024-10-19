#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::noecho
tncurses::keypad stdscr TRUE
tncurses::mousemask [tncurses::ALL_MOUSE_EVENTS] NULL
tncurses::mvaddstr 10 0 "Click with mouse or Press \[Enter\] to exit..."
while {true} {
    set ch [tncurses::getch]
    if {$ch == [tncurses::KEY_MOUSE]} {
	tncurses::clear
	tncurses::mvaddstr 10 0 "Click with mouse or Press \[Enter\] to exit..."
	set mort [tncurses::getmouse]
	switch -- [lindex $mort 4] \
	    [tncurses::BUTTON1_PRESSED] {
		tncurses::mvaddstr 0 0 "Button 1 Pressed!"
	    } \
	    [tncurses::BUTTON1_RELEASED] {
		tncurses::mvaddstr 1 0 "Button 1 Released!"
	    } \
	    [tncurses::BUTTON1_CLICKED] {
		tncurses::mvaddstr 2 0 "Button 1 Clicked!"
	    } \
	    [tncurses::BUTTON1_DOUBLE_CLICKED] {
		tncurses::mvaddstr 3 0 "Button 1 Dbl-Clicked!"
	    } \
	    [tncurses::BUTTON2_PRESSED] {
		tncurses::mvaddstr 0 20 "Button 2 Pressed!"
	    } \
	    [tncurses::BUTTON2_RELEASED] {
		tncurses::mvaddstr 1 20 "Button 2 Released!"
	    } \
	    [tncurses::BUTTON2_CLICKED] {
		tncurses::mvaddstr 2 20 "Button 2 Clicked!"
	    } \
	    [tncurses::BUTTON2_DOUBLE_CLICKED] {
		tncurses::mvaddstr 3 20 "Button 2 Dbl-Clicked!"
	    } \
	    [tncurses::BUTTON3_PRESSED] {
		tncurses::mvaddstr 0 40 "Button 3 Pressed!"
	    } \
	    [tncurses::BUTTON3_RELEASED] {
		tncurses::mvaddstr 1 40 "Button 3 Released!"
	    } \
	    [tncurses::BUTTON3_CLICKED] {
		tncurses::mvaddstr 2 40 "Button 3 Clicked!"
	    } \
	    [tncurses::BUTTON3_DOUBLE_CLICKED] {
		tncurses::mvaddstr 3 40 "Button 3 Dbl-Clicked!"
	    }
	tncurses::refresh
	continue
    }
    if {[format "%c" $ch] eq "\n"} break
}
tncurses::endwin
