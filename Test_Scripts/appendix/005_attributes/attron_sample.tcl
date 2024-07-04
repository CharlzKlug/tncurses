#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
# attrset [expr [A_BOLD] | [A_REVERSE] | [A_BLINK]]
set attrList [attr_get]
set attributes [lindex $attrList 0]

addstr "Attributes active in this window:\n"
if {[expr $attributes & [A_COLOR]]} {printw "Color w/pair $cpair\n"}
if {[expr $attributes & [A_STANDOUT]]} {addstr "Standout\n"}
if {[expr $attributes & [A_REVERSE]]} {addstr "Reverse\n"}
if {[expr $attributes & [A_BLINK]]} {addstr "Blink\n"}
if {[expr $attributes & [A_DIM]]} {addstr "Dim\n"}
if {[expr $attributes & [A_BOLD]]} {addstr "Bold\n"}
refresh
getch

attron [expr [A_BLINK] | [A_BOLD]]
set attrList [attr_get]
set attributes [lindex $attrList 0]

addstr "Attributes active in this window:\n"
if {[expr $attributes & [A_COLOR]]} {printw "Color w/pair $cpair\n"}
if {[expr $attributes & [A_STANDOUT]]} {addstr "Standout\n"}
if {[expr $attributes & [A_REVERSE]]} {addstr "Reverse\n"}
if {[expr $attributes & [A_BLINK]]} {addstr "Blink\n"}
if {[expr $attributes & [A_DIM]]} {addstr "Dim\n"}
if {[expr $attributes & [A_BOLD]]} {addstr "Bold\n"}
refresh
getch

endwin
