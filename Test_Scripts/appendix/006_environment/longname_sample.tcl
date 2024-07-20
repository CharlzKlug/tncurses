#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
set myLongName [tncurses::longname]
tncurses::addstr "My current terminal description is \"$myLongName\". "
tncurses::addstr "Press any key to continue."
tncurses::getch
tncurses::endwin
