#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

start_color
init_pair 1 COLOR_RED COLOR_BLUE
color_set 1

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

getch

endwin
