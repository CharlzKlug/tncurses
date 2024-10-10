#!/usr/bin/env tclsh

proc demoFunction {input_timeout} {
    tncurses::clear
    tncurses::wtimeout stdscr ${input_timeout}
    tncurses::addstr "Timeout demo script. Now timeout is ${input_timeout}\n"
    tncurses::addstr "Press any key to view key code or press \[Enter\] to continue...\n"
    set counter 0
    while {1} {
	set ch [tncurses::wgetch stdscr]
	tncurses::move 2 0
	tncurses::addstr "Counter: $counter"
	tncurses::move 3 0
	if {$ch != "255"} {tncurses::addstr "Last pressed key code: $ch "}
	if {$ch == 10} {break}
	set counter [expr $counter + 1]
    }
}

load ./libtncurses.so

tncurses::initscr
tncurses::noecho
tncurses::notimeout stdscr true
demoFunction -1
demoFunction 0
demoFunction 1000
tncurses::endwin
