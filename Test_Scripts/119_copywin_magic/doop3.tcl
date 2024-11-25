#!/usr/bin/env tclsh

load ./libtncurses.so

set text1 [string cat "Lorem ipsum dolor sit amet, " \
	       "consectetuer adipiscing elit, sed diam "\
	       "nonummy nibh euismod tincidunt ut laoreet "\
	       "dolore magna aliquam erat volutpat. Ut wisi "\
	       "enim ad minim veniam, quis nostrud exerci "\
	       "tation ullamcorper suscipit lobortis nisl "\
	       "ut aliquip ex ea commodo consequat."]
set text2 [string cat "Four score and seven years ago our "\
	       "fathers brought forth on this continent, a "\
	       "new nation, conceived in Liberty, and "\
	       "dedicated to the proposition that all men are created equal."]

tncurses::initscr
tncurses::refresh

set resolution [tncurses::getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]
set halfy [expr {$maxy / 2}]
set halfx [expr {$maxx / 2}]

set top [tncurses::newwin $halfy $maxx 0 0]
set bottom [tncurses::newwin $halfy $halfx $halfy $halfx]

tncurses::waddstr $top $text1
tncurses::wrefresh $top
tncurses::waddstr $bottom $text2
tncurses::wrefresh $bottom

tncurses::getch

tncurses::copywin $top $bottom 0 0 0 0 4 12 FALSE
tncurses::wrefresh $bottom
tncurses::getch

tncurses::endwin
