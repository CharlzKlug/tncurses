#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path /home/user/projects/tncurses/lib
package require Tncurses

tncurses::initscr
set hasIl [tncurses::has_il]
if {$hasIl} {
    tncurses::addstr "Current terminal has insert- and delete-line\
 capabilities.\n"
} else {
    addstr "Current terminal has not insert- and delete- capabilities.\n"
}
tncurses::addstr "Press any key to continue."
tncurses::getch
tncurses::endwin
