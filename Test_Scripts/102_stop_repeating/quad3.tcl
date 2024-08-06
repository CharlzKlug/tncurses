#!/usr/bin/env tclsh

load ./libtncurses.so
source ./mkchtype.tcl

tncurses::initscr
tncurses::refresh
tncurses::start_color
tncurses::init_pair 1 COLOR_BLACK COLOR_BLUE
tncurses::init_pair 2 COLOR_BLACK COLOR_RED
tncurses::init_pair 3 COLOR_BLACK COLOR_GREEN
tncurses::init_pair 4 COLOR_BLACK COLOR_CYAN

set resolution [tncurses::getmaxyx stdscr]
set halfy [expr {[lindex $resolution 0] / 2}]
set halfx [expr {[lindex $resolution 1] / 2}]

set a [tncurses::newwin $halfy $halfx 0 0]
set b [tncurses::newwin $halfy $halfx 0 $halfx]
set c [tncurses::newwin $halfy $halfx $halfy 0]
set d [tncurses::newwin $halfy $halfx $halfy $halfx]

tncurses::wbkgd $a [tncurses::COLOR_PAIR 1]
tncurses::mvwaddstr $a 0 0 "This is window A\n"
tncurses::wrefresh $a

tncurses::wbkgd $b [tncurses::COLOR_PAIR 2]
tncurses::mvwaddstr $b 0 0 "This is window B\n"
tncurses::wrefresh $b

tncurses::wbkgd $c [tncurses::COLOR_PAIR 3]
tncurses::mvwaddstr $c 0 0 "This is window C\n"
tncurses::wrefresh $c

tncurses::wbkgd $d [tncurses::COLOR_PAIR 4]
tncurses::mvwaddstr $d 0 0 "This is window D\n"
tncurses::wrefresh $d

while true {
    set ch [tncurses::wgetch $a]
    tncurses::waddch $b [chtype $ch 0]
    tncurses::waddch $c [chtype $ch 0]
    tncurses::waddch $d [chtype $ch 0]
    tncurses::wrefresh $b
    tncurses::wrefresh $c
    tncurses::wrefresh $d
    if {$ch eq "~"} {break}
}

tncurses::endwin
