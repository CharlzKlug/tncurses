#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::addstr "Enabled nocbreak:\n"
tncurses::addstr "Try to type something, and press \[Backspace\] button. For continue press \[Enter\] 10 times:\n"
tncurses::nocbreak
for {set i 0} {$i < 10} {incr i} {
    tncurses::getch
}

tncurses::cbreak
tncurses::addstr "\nEnables cbreak:\nPress any keys ten times. You can also press \[Backspace\] button\n"
for {set i 0} {$i < 10} {incr i} {
    tncurses::getch
}

tncurses::endwin
