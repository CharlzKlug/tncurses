#!/usr/bin/env tclsh

package require control
load ./libtncurses.so
source ./mkchtype.tcl

proc bomb {message} {
    addstr $message
    refresh
    getch
    endwin
    exit 1
}

set FILENAME "Test_Scripts/122_scroll/gettysburg.txt"
set TALL 24
set WIDE 19
set SPACER 5

initscr

try {
    set p [newpad 200 [expr {$WIDE + 1}]]
} trap {} {} {
    bomb "Unable to create new pad\n"
}

try {
    set s1 [subpad $p $TALL [expr {$WIDE + 1}] 0 0]
} trap {} {} {
    bomb "Unable to create subpad 1\n"
}

try {
    set s2 [subpad $p $TALL [expr {$WIDE + 1}] $TALL 0]
} trap {} {} {
    bomb "Unable to create subpad 2\n"
}

try {
    set s3 [subpad $p $TALL [expr {$WIDE + 1}] [expr {2 * $TALL}] 0]
} trap {} {} {
    bomb "Unable to create subpad 1\n"
}

try {
    set fp [open $FILENAME r]
} trap {} {} {
    bomb "Unable to open file\n"
}
fconfigure $fp -buffering line

while {![eof $fp]} {
    set file_char [read $fp 1]
    if {![eof $fp]} {
	waddch $p [chtype $file_char 0]
    }
}
close $fp

pnoutrefresh $s1 0 0 0 0 [expr {$TALL - 1}] $WIDE
pnoutrefresh $s2 0 0 0 [expr {$WIDE + $SPACER}] [expr {$TALL - 1}] [expr {$WIDE * 2 + $SPACER}]
pnoutrefresh $s3 0 0 0 [expr {$WIDE * 2 + $SPACER * 2}] [expr {$TALL - 1}] \
    [expr {$WIDE * 3 + $SPACER * 2}]
doupdate

wgetch $p
endwin
