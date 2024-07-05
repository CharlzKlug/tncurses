#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

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

wattrset stdscr [expr [A_BLINK] | [A_BOLD]]
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

set newWindow [newwin 10 30 4 26]
wattrset $newWindow [expr [A_BLINK] | [A_BOLD] | [A_REVERSE]]
waddstr $newWindow "Sample string."
wrefresh $newWindow
getch

delwin $newWindow

endwin
