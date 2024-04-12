#!/usr/bin/env tclsh

load ./libtncurses.so

set LMAX 12
set CENTER 1

set label_text {"Help" "File" "Edit" "Frmt" "View" "Switch" "Win" "Help"}

slk_init 3
initscr
slk_restore

for {set label 0} {$label < $LMAX} {incr label} {
    slk_set [expr {$label + 1}] [lindex $label_text $label] $CENTER
}

slk_refresh

getch

endwin
