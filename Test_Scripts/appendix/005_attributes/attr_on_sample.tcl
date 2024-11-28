#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
# attrset [expr [A_BOLD] | [A_REVERSE] | [A_BLINK]]
set attrList [tncurses::attr_get]
set attributes [lindex $attrList 0]

tncurses::addstr "Attributes active in this window:\n"
if {[expr $attributes & [tncurses::A_COLOR]]} {tncurses::printw "Color w/pair $cpair\n"}
if {[expr $attributes & [tncurses::A_STANDOUT]]} {tncurses::addstr "Standout\n"}
if {[expr $attributes & [tncurses::A_REVERSE]]} {tncurses::addstr "Reverse\n"}
if {[expr $attributes & [tncurses::A_BLINK]]} {tncurses::addstr "Blink\n"}
if {[expr $attributes & [tncurses::A_DIM]]} {tncurses::addstr "Dim\n"}
if {[expr $attributes & [tncurses::A_BOLD]]} {tncurses::addstr "Bold\n"}
tncurses::refresh
tncurses::getch

tncurses::attr_on [tncurses::A_BLINK]
set attrList [tncurses::attr_get]
set attributes [lindex $attrList 0]

tncurses::addstr "Attributes active in this window:\n"
if {[expr $attributes & [tncurses::A_COLOR]]} {tncurses::printw "Color w/pair $cpair\n"}
if {[expr $attributes & [tncurses::A_STANDOUT]]} {tncurses::addstr "Standout\n"}
if {[expr $attributes & [tncurses::A_REVERSE]]} {tncurses::addstr "Reverse\n"}
if {[expr $attributes & [tncurses::A_BLINK]]} {tncurses::addstr "Blink\n"}
if {[expr $attributes & [tncurses::A_DIM]]} {tncurses::addstr "Dim\n"}
if {[expr $attributes & [tncurses::A_BOLD]]} {tncurses::addstr "Bold\n"}
tncurses::refresh
tncurses::getch

tncurses::endwin
