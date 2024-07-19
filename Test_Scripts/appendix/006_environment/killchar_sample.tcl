#!/usr/bin/env tclsh

# load ./libtncurses.so
lappend auto_path /home/user/projects/tncurses/lib
package require Tncurses

tncurses::initscr
tncurses::addstr "Killchar is \"[tncurses::killchar]\". "
tncurses::addstr "Press any key to continue."
tncurses::getch
tncurses::endwin
