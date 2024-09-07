#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

tncurses::initscr
set isHasColors [tncurses::has_colors]
if {$isHasColors == 1} {set message "Has colors"} \
    {set message "Doesn't has colors"}
tncurses::addstr $message
tncurses::refresh
tncurses::getch
tncurses::endwin
