#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::scrollok stdscr TRUE
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]
tncurses::init_pair 2 [tncurses::COLOR_WHITE] [tncurses::COLOR_RED]

set half [expr [tncurses::COLS] >> 1]
set size [expr $half * [tncurses::COLS]]
set size [expr $size >> 1]
set alpha [tncurses::newwin [tncurses::LINES] [expr $half - 1] 0 0]
tncurses::scrollok $alpha TRUE
tncurses::wbkgd $alpha [tncurses::COLOR_PAIR 1]
set beta [tncurses::newwin [tncurses::LINES] [expr $half - 1] 0 $half]
tncurses::scrollok $beta TRUE
tncurses::wbkgd $beta [tncurses::COLOR_PAIR 2]

for {set x 0} {$x < [expr $size - 1]} {incr x} {
    tncurses::wprintw $alpha "O "
    tncurses::wprintw $beta " X"
}

tncurses::refresh
tncurses::wrefresh $alpha
tncurses::wrefresh $beta
tncurses::wgetch $beta
tncurses::copywin $beta $alpha 10 5 10 5 15 30 TRUE
tncurses::refresh
tncurses::wrefresh $alpha
tncurses::wrefresh $beta
tncurses::wgetch $beta
tncurses::endwin
