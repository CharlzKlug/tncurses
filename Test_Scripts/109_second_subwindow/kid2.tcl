#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::start_color
tncurses::init_pair 1 [tncurses::COLOR_WHITE] [tncurses::COLOR_BLUE]
tncurses::init_pair 2 [tncurses::COLOR_RED] [tncurses::COLOR_YELLOW]
tncurses::init_pair 3 [tncurses::COLOR_CYAN] [tncurses::COLOR_WHITE]

set sonny [tncurses::subwin stdscr 5 20 10 30]
set babygirl [tncurses::derwin stdscr 5 20 1 50]
set color_pair [tncurses::COLOR_PAIR 1]
set color_pair_length [string length $color_pair]
tncurses::bkgd [tncurses::COLOR_PAIR 1]
tncurses::addstr "Hello, son, hello baby girl. My color_pair is '$color_pair'. Length is $color_pair_length"
tncurses::wbkgd $sonny [tncurses::COLOR_PAIR 2]
tncurses::waddstr $sonny "Hello, Dad."
tncurses::wbkgd $babygirl [tncurses::COLOR_PAIR 3]
tncurses::waddstr $babygirl "Hello, Papa."
tncurses::refresh
tncurses::wrefresh $sonny
tncurses::wrefresh $babygirl
tncurses::getch

tncurses::endwin
