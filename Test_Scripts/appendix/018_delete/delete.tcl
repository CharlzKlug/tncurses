#!/usr/bin/env tclsh

load ./libtncurses.so

set text "Elvis found alive *** Stock market tops\
 20,000 *** Rocky XIII big box office hit *** Congressman indicted ***"
tncurses::initscr
tncurses::noecho
tncurses::nodelay stdscr TRUE

set Y 5
set X1 10
set X2 60
set DELAY 250

set t 0

while {[tncurses::getch] == -1} {
    set currentChar [string index $text $t]
    if {$currentChar == ""} {
	set t 0
	continue
    }
    tncurses::mvinsch $Y $X2 [scan $currentChar %c]
    tncurses::mvdelch $Y $X1
    tncurses::refresh
    tncurses::napms $DELAY
    incr t
}
tncurses::endwin
