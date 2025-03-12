#!/usr/bin/env tclsh

load ./libtncurses.so

tncurses::initscr
tncurses::noecho
tncurses::addstr "To be, or not to be: that is the question:\n"
tncurses::addstr "Whether 'tis nobler in the mind to suffer\n"
tncurses::addstr "The slings and arrows of outrageous fortune,\n"
tncurses::addstr "Or to take arms against a sea of troubles,\n"
tncurses::addstr "And by opposing end them?\n"

tncurses::move 0 0
for {set x 0} {$x < 5} {incr x} {
    tncurses::refresh
    tncurses::getch
    tncurses::deleteln
}

tncurses::endwin
exit 0
