#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::noecho
tncurses::start_color
set color_pairs [tncurses::COLOR_PAIRS]
tncurses::addstr "COLOR_PAIRS is $color_pairs. Press any key to exit."
tncurses::getch
tncurses::endwin
