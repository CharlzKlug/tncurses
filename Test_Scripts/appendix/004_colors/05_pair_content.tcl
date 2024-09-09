#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::noecho
tncurses::start_color
set foregroundColor 16
set backgroundColor 17

tncurses::addstr "Pair initialized via foreground color: $foregroundColor, and background color: $backgroundColor\n"
tncurses::init_pair 1 $foregroundColor $backgroundColor

tncurses::addstr "Reading colors...\n"
set colorsList [tncurses::pair_content 1]
tncurses::addstr "Readed colors: foreground: [lindex $colorsList 0], and background: [lindex $colorsList 1]\n"
tncurses::addstr "Press any key to continue..."
tncurses::getch
tncurses::endwin
