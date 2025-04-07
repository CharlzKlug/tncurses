#!/usr/bin/env tclsh

load ./libtncurses.so

set ALPHA_W 30
set ALPHA_H 5

tncurses::initscr
tncurses::noecho
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]

set x [expr {([tncurses::COLS] - ${ALPHA_W}) >> 1}]
set y [expr {([tncurses::LINES] - ${ALPHA_H}) >> 1}]

tncurses::addstr "Creating new window...\n"
tncurses::refresh
set alpha [tncurses::newwin ${ALPHA_H} ${ALPHA_W} $y $x]
if {$alpha == "NULL"} {
    tncurses::endwin
    puts "Problem creating window"
    exit 1
}
# attrset [expr [A_BOLD] | [A_REVERSE] | [A_BLINK]]
# set attrList [attr_get]
# set attributes [lindex $attrList 0]

# addstr "Attributes active in this window:\n"
# if {[expr $attributes & [A_COLOR]]} {printw "Color w/pair $cpair\n"}
# if {[expr $attributes & [A_STANDOUT]]} {addstr "Standout\n"}
# if {[expr $attributes & [A_REVERSE]]} {addstr "Reverse\n"}
# if {[expr $attributes & [A_BLINK]]} {addstr "Blink\n"}
# if {[expr $attributes & [A_DIM]]} {addstr "Dim\n"}
# if {[expr $attributes & [A_BOLD]]} {addstr "Bold\n"}
# refresh
# getch

# wstandend stdscr
# set attrList [attr_get]
# set attributes [lindex $attrList 0]

# addstr "Attributes active in this window:\n"
# if {[expr $attributes & [A_COLOR]]} {printw "Color w/pair $cpair\n"}
# if {[expr $attributes & [A_STANDOUT]]} {addstr "Standout\n"}
# if {[expr $attributes & [A_REVERSE]]} {addstr "Reverse\n"}
# if {[expr $attributes & [A_BLINK]]} {addstr "Blink\n"}
# if {[expr $attributes & [A_DIM]]} {addstr "Dim\n"}
# if {[expr $attributes & [A_BOLD]]} {addstr "Bold\n"}
# refresh
# getch

# set someWindow [newwin 20 40 7 26]
# wstandend $someWindow
# waddstr $someWindow "12345 qwerty"

# wrefresh $someWindow

# getch
# delwin $someWindow
tncurses::endwin
