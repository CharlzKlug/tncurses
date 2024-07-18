#!/usr/bin/env tclsh

load ./libtncurses.so

initscr
set hasIc [has_ic]
if {$hasIc} {
    addstr "Current terminal has insert- and delete- capabilities.\n"
} else {
    addstr "Current terminal has not insert- and delete- capabilities.\n"
}
addstr "Press any key to continue."
getch
endwin
