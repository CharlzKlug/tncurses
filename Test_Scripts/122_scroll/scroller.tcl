#!/usr/bin/env tclsh

package require control
load ./libtncurses.so
source ./mkchtype.tcl

initscr
refresh

set resolution [getmaxyx stdscr]
set maxy [lindex $resolution 0]
set maxx [lindex $resolution 1]

set lister [newwin $maxy [expr {$maxx / 2}] 0 [expr {$maxx / 4}]]
scrollok $lister TRUE
set filename "Test_Scripts/122_scroll/gettysburg.txt"
set fp [open $filename r]
fconfigure $fp -buffering line
while {![eof $fp]} {
    set file_char [read $fp 1]
    if {![eof $fp]} {
	waddch $lister [chtype $file_char 0]
	wrefresh $lister
    }
}

close $fp

getch
endwin
