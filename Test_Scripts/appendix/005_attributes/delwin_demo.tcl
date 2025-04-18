#!/usr/bin/env tclsh

load ./libtncurses.so

set ALPHA_W 30
set ALPHA_H 5

tncurses::initscr
tncurses::noecho
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]

set x [expr {([tncurses::COLS] - ${ALPHA_W}) >> 1}]
set y [expr {([tncurses::LINES] - ${ALPHA_H}) >> 1}]

tncurses::addstr "Creating new window...\n"
tncurses::refresh
set alpha [tncurses::newwin ${ALPHA_H} ${ALPHA_W} $y $x]
if {$alpha == "NULL"} {
    tncurses::endwin
    puts "Problem creating window"
    exit 1
}

tncurses::addstr "Displaying window:\n"
tncurses::addstr "Press Enter to remove the window:\n"
tncurses::refresh
tncurses::wbkgd $alpha [tncurses::COLOR_PAIR 1]
tncurses::mvwaddstr $alpha 2 12 "Hello!"
tncurses::wrefresh $alpha
tncurses::wgetch $alpha

tncurses::delwin $alpha
tncurses::addstr "Window removed: press Enter to clear it:\n"
tncurses::refresh
tncurses::getch

tncurses::touchwin stdscr
tncurses::addstr "Done!\n"
tncurses::refresh
tncurses::getch

tncurses::endwin
exit 0
