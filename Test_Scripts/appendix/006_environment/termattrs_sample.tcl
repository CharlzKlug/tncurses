#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
set chtp [tncurses::termattrs]
tncurses::addstr "My current chtype is \"$chtp\". "
tncurses::addstr "Press any key to continue."
tncurses::getch
tncurses::endwin
