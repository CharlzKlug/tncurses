#!/usr/bin/env tclsh

load ./libtncurses.so

set LMAX 12
set CENTER 1

set label_text {
    "I" "AM" "SAM" "DO"
    "NOT" "LIKE" "THAT" "SAY"
    "WOULD" "COULD" "YOU"
    "GREEN EGGS AND HAM"
}

slk_init 2
initscr
noecho
keypad stdscr TRUE

for {set label 0} {$label < $LMAX} {incr label} {
    slk_set [expr {$label + 1}] [lindex $label_text $label] $CENTER
}
slk_refresh
addstr "Use the Function Keys to type\n"
addstr "Press '?' or '!' or '.' to end a line\n"
addstr "Press Enter to quit\n\n"
refresh

set ch [getch]
while {[format "%c" $ch] ne "\n"} {
    switch -- $ch \
	[scan ? %c] - \
	[scan ! %c] - \
	[scan . %c] {
	    addch [format "%c" $ch]
	    addch \n
	} \
	[KEY_F 1] {
	    printw "[lindex $label_text 0] "
	} \
	[KEY_F 2] {
	    printw "[lindex $label_text 1] "
	} \
	[KEY_F 3] {
	    printw "[lindex $label_text 2] "
	} \
	[KEY_F 4] {
	    printw "[lindex $label_text 3] "
	} \
	[KEY_F 5] {
	    printw "[lindex $label_text 4] "
	} \
	[KEY_F 6] {
	    printw "[lindex $label_text 5] "
	} \
	[KEY_F 7] {
	    printw "[lindex $label_text 6] "
	} \
	[KEY_F 8] {
	    printw "[lindex $label_text 7] "
	} \
	[KEY_F 9] {
	    printw "[lindex $label_text 8] "
	} \
	[KEY_F 10] {
	    printw "[lindex $label_text 9] "
	} \
	[KEY_F 11] {
	    printw "[lindex $label_text 10] "
	} \
	[KEY_F 12] {
	    printw "[lindex $label_text 11] "
	} \
	default {}
    refresh
    set ch [getch]
}

endwin
