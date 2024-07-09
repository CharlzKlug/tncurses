#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
attrset [expr [A_BOLD] | [A_REVERSE] | [A_BLINK]]
set attrList [wattr_get stdscr]
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

set someWindow [newwin 10 30 4 26]
wattroff $someWindow [A_BOLD]
waddstr $someWindow "12345 qwerty\n"
set attrList [wattr_get $someWindow]
set attributes [lindex $attrList 0]
set cpair [lindex $attrList 1]
waddstr $someWindow "$attributes\n"
waddstr $someWindow "$cpair\n"
wrefresh $someWindow

getch
delwin $someWindow

endwin
