#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::start_color;
tncurses::init_pair 1 COLOR_YELLOW COLOR_RED

set newman [tncurses::newwin 5 30 5 10]

if {$newman == "NULL"} {
    tncurses::endwin
    puts "Error creating window"
    exit 1
}

tncurses::wbkgd $newman [tncurses::COLOR_PAIR 1]
tncurses::wborder $newman 0 0 0 0 0 0 0 0
tncurses::mvwaddstr $newman 1 1 "Ta-da!"
tncurses::wrefresh $newman
tncurses::wgetch $newman

tncurses::endwin
exit 0
