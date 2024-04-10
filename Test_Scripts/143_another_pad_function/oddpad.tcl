#!/usr/bin/env tclsh

load ./libtncurses.so

initscr

try {
    set p [newpad 50 100]
} trap {} {} {
    addstr "Unable to create new pad"
    refresh
    endwin
    exit 1
}

set text "This is interesting"

prefresh $p 0 0 1 1 1 25

foreach char [split $text ""] {
    pechochar $p $char
}

wgetch $p
endwin
