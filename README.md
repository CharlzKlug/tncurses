# tncurses
Binded commands:
- initscr;
- printw (accept only string);
- refresh;
- getch (return int value!);
- endwin;
- newwin;
- addstr;
- mvwaddstr;
- noecho;
- wrefresh;
- touchwin;
- addch;
- waddstr;
- delwin;
- getmaxyx. Input: window pointer. Output: list with MaxY and MaxX;
- start_color;
- init_pair;
- wbkgd (no need for COLOR_PAIR). Usage: "wbkgd $window 2";
- waddch;
- wgetch;
- subwin;
- bkgd;
Use of bkgd: if you want to send a char then use "bkgd .", if you want to send "'" char then use "bkgd '''", if you want to send a number like char, then use "bkgd '1'", and if you want to send a value, then use for example "bkg 256".
- derwin;
- wclear;
- overlay;
- overwrite;
- copywin;
- dupwin;
- scrollok;
- getmaxy;
- mvprintw;
- scroll;
- scrl;
- wscrl;
- mvwin;
- touchline;
- COLOR_PAIR;
- newpad;
- prefresh;
- pnoutrefresh;
- doupdate;
- pechochar;
- slk_init;
- slk_set;
- slk_refresh;
- slk_restore;
- slk_clear;
- keypad;
- KEY_F;
- NCURSES_MOUSE_VERSION;
- ALL_MOUSE_EVENTS;
- mousemask;
- BUTTON1_RELEASED;
- BUTTON1_PRESSED;
- BUTTON1_CLICKED;
- BUTTON1_DOUBLE_CLICKED;
- BUTTON1_TRIPLE_CLICKED;
- BUTTON2_RELEASED;
- BUTTON2_PRESSED;
- BUTTON2_CLICKED;
- BUTTON2_DOUBLE_CLICKED;
- BUTTON2_TRIPLE_CLICKED;
- BUTTON3_RELEASED;
- BUTTON3_PRESSED;
- BUTTON3_CLICKED;
- BUTTON3_DOUBLE_CLICKED;
- BUTTON3_TRIPLE_CLICKED;
- BUTTON4_RELEASED;
- BUTTON4_PRESSED;
- BUTTON4_CLICKED;
- BUTTON4_DOUBLE_CLICKED;
- BUTTON4_TRIPLE_CLICKED;
- KEY_MOUSE;
- getmouse (return list with id, x, y, z, and bstate);
- move;
- clrtoeol;
- mvaddch;
- clear;
- mvaddstr;
- curs_set;
- box;
- border;
- hline;
- vline;
- mvhline;
- mvvline;
- scr_dump;
- scr_restore;
- putwin. Accept window pointer and file name. Saves the window to file name. Return error if an error occured, otherwise return ok;
- getwin. Accept file name. Return window pointer on success, otherwise return error;
- mvwaddch;
- A_ATTRIBUTES;
- A_NORMAL;
- A_STANDOUT;
- A_UNDERLINE;
- A_REVERSE;
- A_BLINK;
- A_DIM;
- A_BOLD;
- A_ALTCHARSET;
- A_INVIS;
- A_PROTECT;
- A_HORIZONTAL;
- A_LEFT;
- A_LOW;
- A_RIGHT;
- A_TOP;
- A_VERTICAL;
- A_ITALIC;
- addchstr;
- addchnstr;
- waddchstr;
- waddchnstr;
- mvaddchstr;
- mvaddchnstr;
- mvwaddchstr;
- mvwaddchnstr;
- waddnstr;
- mvaddnstr;
- mvwaddnstr;
- assume_default_colors;
- COLOR_BLACK;
- COLOR_RED;
- COLOR_GREEN;
- COLOR_YELLOW;
- COLOR_BLUE;
- COLOR_MAGENTA;
- COLOR_CYAN;
- COLOR_WHITE;
- attr_get;
- attrset;
- A_COLOR;
- attr_off;
- attr_on;
- attroff;
- attron;
- wattron;
- wattrset;
- color_set (accepts only one argument --- color pair);
- wcolor_set;
- standend
- wstandend;
- standout;
- wattr_get;
- wattr_off;
- wattr_on;
- attr_set;
- wattr_set;
- chgat;
- wchgat;
- mvchgat;
- mvwchgat;
- baudrate;
- erasechar;
- has_ic;
- has_il;
- killchar;
- longname;
- termattrs;
- termname;
- beep;
- flash;
- bkgdset;
- wbkgdset;
- getbkgd;
- wborder;
- whline;
- wvline;
- mvwhline;
- mvwvline;
- init_color (Warning: color initialization works not on every terminals!);
- has_colors;
- can_change_color;
- color_content;
- pair_content;
- cbreak;
- nocbreak;
- echo;
- halfdelay;
- intrflush;
- meta;
- nodelay;
- raw;
- noraw;
- noqiflush;
- qiflush;
- notimeout;

Not supported
- erasewchar;
- killwchar;
- term_attrs;
