#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
set tf [tncurses::can_change_color]
if {$tf} {
    tncurses::addstr "This terminal can change the standard colors.\n"
} {
    tncurses::addstr "This terminal cannot change the colors.\n"
}
tncurses::refresh
tncurses::getch

tncurses::endwin
