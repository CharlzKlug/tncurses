#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::beep
tncurses::flash
tncurses::getch
tncurses::endwin
