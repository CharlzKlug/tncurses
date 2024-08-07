#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path /home/user/projects/tncurses/lib
package require Tncurses

tncurses::initscr
set hasIc [tncurses::has_ic]
if {$hasIc} {
    tncurses::addstr "Current terminal has insert- and delete- capabilities.\n"
} else {
    addstr "Current terminal has not insert- and delete- capabilities.\n"
}
tncurses::addstr "Press any key to continue."
tncurses::getch
tncurses::endwin
