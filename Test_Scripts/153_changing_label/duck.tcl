#!/usr/bin/env tclsh

load ./libtncurses.so

set LMAX 8
set CENTER 1

set label_text {
    "Duck" "Duck" "Duck" "Duck"
    "Duck" "Duck" "Duck" "Duck"
}

slk_init 1
initscr

for {set label 0} {$label < $LMAX} {incr label} {
    slk_set [expr {$label + 1}] [lindex $label_text $label] $CENTER
}
slk_refresh
getch

slk_set 7 "Goose!" $CENTER
slk_refresh
getch

endwin
