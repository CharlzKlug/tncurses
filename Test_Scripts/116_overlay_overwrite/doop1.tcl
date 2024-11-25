#!/usr/bin/env tclsh

load ./libtncurses.so

set text1 [string cat "Lorem ipsum dolor sit amet, " \
	       "consectetuer adipiscing elit, sed diam nonummy " \
	       "nibh euismod tincidunt ut laoreet dolore magna " \
	       "aliquam erat volutpat. Ut wisi enim ad minim veniam, " \
	       "quis nostrud exerci tation ullamcorper suscipit lobortis " \
	       "nisl ut aliquip ex ea commodo consequat."]

set text2 [string cat "Four score and seven years ago our " \
	       "fathers brought forth on this continent, " \
	       "a new nation, conceived in Liberty, and " \
	       "dedicated to the proposition that all men are created equal."]

tncurses::initscr

set alpha [tncurses::newwin 0 0 0 0]

tncurses::addstr $text1
tncurses::refresh
tncurses::getch

tncurses::waddstr $alpha $text2
tncurses::wrefresh $alpha
tncurses::getch

tncurses::overlay stdscr $alpha
tncurses::wrefresh $alpha
tncurses::getch

tncurses::endwin
