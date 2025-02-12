#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
set text "A quick brown fox jumps over the lazy dog."

while {[set x [string index $text 0]] != ""} {
    tncurses::winsch stdscr [scan $x %c]
    tncurses::refresh
    tncurses::napms 500
    set text [string replace $text 0 0]

}

tncurses::endwin
