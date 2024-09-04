#!/usr/bin/env tclsh

lappend auto_path [pwd]/lib
package require Tncurses

proc gen_random_color {} {
    return [::tcl::mathfunc::int [expr [::tcl::mathfunc::rand] * 1000]]
}


tncurses::initscr
tncurses::noecho
tncurses::start_color
set foregroundColor 16
set backgroundColor 17


for {set i 0} {$i < 10} {incr i} {
    set r1 [gen_random_color]
    set g1 [gen_random_color]
    set b1 [gen_random_color]

    tncurses::init_color $foregroundColor $r1 $g1 $b1

    set r2 [gen_random_color]
    set g2 [gen_random_color]
    set b2 [gen_random_color]

    tncurses::init_color $backgroundColor $r2 $g2 $b2

    tncurses::init_pair 1 $foregroundColor $backgroundColor
    tncurses::attron [tncurses::COLOR_PAIR 1]
    tncurses::addstr "Foreground color: red - $r1, green - $g1, blue - $b1\n"
    tncurses::addstr "Background color: red - $r2, green - $g2, blue - $b2\n"
    tncurses::addstr "Press any key to continue...\n"
    tncurses::refresh
    tncurses::getch
}
tncurses::endwin
