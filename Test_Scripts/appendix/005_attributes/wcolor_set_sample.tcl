#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

start_color
init_pair 1 COLOR_RED COLOR_BLUE
wcolor_set stdscr 1

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

set newWindow [newwin 10 30 4 26]
init_pair 2 COLOR_WHITE COLOR_YELLOW
wcolor_set $newWindow 2
waddstr $newWindow "Sample string."
wrefresh $newWindow
getch

endwin
