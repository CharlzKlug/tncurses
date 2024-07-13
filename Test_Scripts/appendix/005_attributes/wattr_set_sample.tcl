#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
start_color
init_pair 1 COLOR_RED COLOR_BLUE
wattr_set stdscr [expr [A_BOLD] | [A_REVERSE] | [A_BLINK]] 1 NULL
set attrList [attr_get]
set attributes [lindex $attrList 0]
set cpair [lindex $attrList 1]

addstr "Attributes active in this window:\n"
if {[expr $attributes & [A_COLOR]]} {printw "Color w/pair $cpair\n"}
if {[expr $attributes & [A_STANDOUT]]} {addstr "Standout\n"}
if {[expr $attributes & [A_REVERSE]]} {addstr "Reverse\n"}
if {[expr $attributes & [A_BLINK]]} {addstr "Blink\n"}
if {[expr $attributes & [A_DIM]]} {addstr "Dim\n"}
if {[expr $attributes & [A_BOLD]]} {addstr "Bold\n"}
refresh
getch

set win [newwin 10 30 4 26]
wattr_set $win [A_BOLD] 1 NULL
waddstr $win "---==Test==---"
wrefresh $win
getch

delwin $win

endwin
