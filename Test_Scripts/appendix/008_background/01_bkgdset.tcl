#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::start_color
tncurses::init_pair 1 COLOR_WHITE COLOR_BLUE
tncurses::init_pair 2 COLOR_RED COLOR_YELLOW
tncurses::init_pair 3 COLOR_CYAN COLOR_WHITE

set sonny [tncurses::subwin stdscr 5 20 10 30]
set babygirl [tncurses::derwin stdscr 5 20 1 50]
set color_pair [tncurses::COLOR_PAIR 1]
set color_pair_length [string length $color_pair]
tncurses::bkgdset [expr [tncurses::COLOR_PAIR 1] | [scan "*" %c]]
tncurses::addstr "Hello, son, hello baby girl. My color_pair is '$color_pair'. Length is $color_pair_length"
tncurses::wbkgd $sonny [tncurses::COLOR_PAIR 2]
tncurses::waddstr $sonny "Hello, Dad."
tncurses::wbkgd $babygirl [tncurses::COLOR_PAIR 3]
tncurses::waddstr $babygirl "Hello, Papa."
tncurses::refresh
tncurses::getch

tncurses::endwin
