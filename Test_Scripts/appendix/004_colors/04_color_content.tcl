#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
tncurses::noecho
tncurses::start_color
set foregroundColor 16

tncurses::addstr "Setting color with red: 543, green: 89, blue: 101\n"
tncurses::init_color $foregroundColor 543 89 101
tncurses::addstr "Reading content for color.\n"
set colorContent [tncurses::color_content $foregroundColor]
tncurses::addstr "Red: [lindex $colorContent 0], Green: [lindex $colorContent 1], Blue: [lindex $colorContent 2]\n"
tncurses::addstr "Press any key to continue..."
tncurses::getch
tncurses::endwin
