/* How to build: gcc -shared -o libtncurses.so -DUSE_TCL_STUBS -I /usr/include/tcl tncurses.c -ltclstub8.6 -lncurses -fPIC */
#include <tcl.h>
#include <string.h>
#include "tncurses.h"

#define CHECK_ARGUMENTS(arg_num, err_msg) do { \
  if (objc != (arg_num)) {		       \
  Tcl_AppendResult(interp, (err_msg), NULL);   \
  return TCL_ERROR;			       \
  }					       \
  } while (0)

#define STRING_TO_WINDOW(string_buffer, window) do {			\
    if (strcmp(string_buffer, "stdscr") == 0) {				\
      window= stdscr;							\
    } else {								\
      void* pointer= NULL;						\
      if (string_buffer == NULL ||					\
	  sscanf(string_buffer, "%p", &pointer) != 1) {			\
	Tcl_AppendResult(interp, "Bad scan", NULL);			\
	return TCL_ERROR;						\
      }									\
      window= (WINDOW*)pointer;						\
    }									\
  } while (0)

#define STRING_TO_BOOL(string_buffer, bool_value) do {		\
    if (strcmp(string_buffer, "true") == 0 ||			\
	strcmp(string_buffer, "TRUE") == 0) {			\
      bool_value= TRUE;						\
    } else if (strcmp(string_buffer, "false") == 0 ||		\
	       strcmp(string_buffer, "FALSE") == 0) {		\
      bool_value= FALSE;					\
    } else {							\
      Tcl_AppendResult(interp, "Bad scan bool value", NULL);	\
      return TCL_ERROR;						\
    }								\
  } while (0)


/* Auxiliary function. Maps string to color */
int string_to_color(char *input_string,
		    NCURSES_COLOR_T *output_color) {
  for (int i = 0; i < (COLORS_COUNT); i++) {
    if (strcmp(input_string, colors_strings[i]) == 0) {
      *output_color= ncurses_colors[i];
      return i;
    }
  }
  return (-1);
}

static int Initscr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  initscr();
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int PrintW_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  printw(Tcl_GetString(objv[1]));
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Refresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  refresh();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  char ch= getch();
  char str[2];
  sprintf(str, "%c", ch);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int EndWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  endwin();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NewWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 5) {
    return TCL_ERROR;
  }
  int rows;
  Tcl_GetIntFromObj(interp, objv[1], &rows);
  int cols;
  Tcl_GetIntFromObj(interp, objv[2], &cols);
  int y_org;
  Tcl_GetIntFromObj(interp, objv[3], &y_org);
  int x_org;
  Tcl_GetIntFromObj(interp, objv[4], &x_org);
  WINDOW *window= newwin(rows, cols, y_org, x_org);

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int AddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  addstr(Tcl_GetString(objv[1]));
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int MvWAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 5) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  void* pointer= NULL;
  if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
    Tcl_AppendResult(interp, "Bad scan", NULL);
    return TCL_ERROR;
  }
  WINDOW* win= (WINDOW*)pointer;
  int y_org;
  Tcl_GetIntFromObj(interp, objv[2], &y_org);
  int x_org;
  Tcl_GetIntFromObj(interp, objv[3], &x_org);
  char* strbuf= Tcl_GetString(objv[4]);
  mvwaddstr(win, y_org, x_org, strbuf);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NoEcho_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  noecho();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  void* pointer= NULL;
  if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
    Tcl_AppendResult(interp, "Bad scan", NULL);
    return TCL_ERROR;
  }
  WINDOW* window= (WINDOW*)pointer;
  wrefresh(window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int TouchWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  char stdscr_array[]= "stdscr";
  if (strcmp(buffer, "stdscr") == 0) {
    touchwin(stdscr);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    touchwin(win);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int AddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  addch(*buffer);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WAddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 3) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  if (strcmp(buffer, "stdscr") == 0) {
    waddstr(stdscr, Tcl_GetString(objv[2]));
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    waddstr(win, Tcl_GetString(objv[2]));
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DelWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  if (strcmp(buffer, "stdscr") == 0) {
    delwin(stdscr);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    delwin(win);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetMaxYX_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }
  char* buffer= Tcl_GetString(objv[1]);
  int maxy, maxx;
  if (strcmp(buffer, "stdscr") == 0) {
    getmaxyx(stdscr, maxy, maxx);
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    WINDOW* win= (WINDOW*)pointer;
    getmaxyx(win, maxy, maxx);
  }
  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d %d", maxy, maxx));
  return TCL_OK;
}

static int Start_Color_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  start_color();
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Init_Pair_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 4) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  int pair_number;
  if (Tcl_GetIntFromObj(interp, objv[1], &pair_number) == TCL_ERROR) {
    Tcl_AppendResult(interp, "pair number must be integer", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T foreground_color;
  if (string_to_color(Tcl_GetString(objv[2]), &foreground_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong foreground color", NULL);
    return TCL_ERROR;
  }

  NCURSES_COLOR_T background_color;
  if (string_to_color(Tcl_GetString(objv[3]), &background_color) == (-1)) {
    Tcl_AppendResult(interp, "wrong background color", NULL);
    return TCL_ERROR;
  }

  init_pair(pair_number, foreground_color, background_color);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WBkgd_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 3) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  buffer= Tcl_GetString(objv[2]);
  int input_val= -1;

  if (buffer[0] >= '0' && buffer[0] <= '9') {
    Tcl_GetIntFromObj(interp, objv[2], &input_val);
  }

  if (strlen(buffer) == 3 && buffer[0] == '\'' && buffer[2] == '\'') {
    input_val= buffer[1];
  }

  if (strlen(buffer) == 1) {
    input_val= buffer[0];
  }

  if (input_val == -1) {
    Tcl_AppendResult(interp, "wrong argument", NULL);
    return TCL_ERROR;
  }
  
  if (wbkgd(win, input_val) == ERR) {
    Tcl_AppendResult(interp, "Error occured in bkgd function", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WAddCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 3) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  char ch;
  ch= Tcl_GetString(objv[2])[0];
  waddch(win, ch);
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WGetCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  char ch;
  ch= wgetch(win);

  char str[2];
  sprintf(str, "%c", ch);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int SubWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 6) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int rows;
  if (Tcl_GetIntFromObj(interp, objv[2], &rows) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int cols;
  if (Tcl_GetIntFromObj(interp, objv[3], &cols) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int y;
  if (Tcl_GetIntFromObj(interp, objv[4], &y) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int x;
  if (Tcl_GetIntFromObj(interp, objv[5], &x) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  WINDOW *window= subwin(win, rows, cols, y, x);
  if (window == NULL) {
    Tcl_AppendResult(interp, "Error in creating subwindow!", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int Bkgd_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  int input_val= -1;

  if (buffer[0] >= '0' && buffer[0] <= '9') {
    Tcl_GetIntFromObj(interp, objv[1], &input_val);
  }

  if (strlen(buffer) == 3 && buffer[0] == '\'' && buffer[2] == '\'') {
    input_val= buffer[1];
  }

  if (strlen(buffer) == 1) {
    input_val= buffer[0];
  }

  if (input_val == -1) {
    Tcl_AppendResult(interp, "wrong argument", NULL);
    return TCL_ERROR;
  }
  
  if (bkgd(input_val) == ERR) {
    Tcl_AppendResult(interp, "Error occured in bkgd function", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DerWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 6) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int rows;
  if (Tcl_GetIntFromObj(interp, objv[2], &rows) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int cols;
  if (Tcl_GetIntFromObj(interp, objv[3], &cols) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int y;
  if (Tcl_GetIntFromObj(interp, objv[4], &y) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  int x;
  if (Tcl_GetIntFromObj(interp, objv[5], &x) == TCL_ERROR) {
    Tcl_AppendResult(interp, "Not int value!", NULL);
    return TCL_ERROR;
  }

  WINDOW *window= derwin(win, rows, cols, y, x);
  if (window == NULL) {
    Tcl_AppendResult(interp, "Error in creating subwindow!", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int WClear_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  WINDOW* win;
    
  if (strcmp(buffer, "stdscr") == 0) {
    win= stdscr;
  } else {
    void* pointer= NULL;
    if (buffer == NULL || sscanf(buffer, "%p", &pointer) != 1) {
      Tcl_AppendResult(interp, "Bad scan", NULL);
      return TCL_ERROR;
    }
    win= (WINDOW*)pointer;
  }

  int result= wclear(win);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int Overlay_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);
  
  int result= overlay(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int OverWrite_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);
  
  int result= overwrite(srcwin, dstwin);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int CopyWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(10, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* dstwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[2]), dstwin);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[3], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[4], &smincol);

  int dminrow;
  Tcl_GetIntFromObj(interp, objv[5], &dminrow);

  int dmincol;
  Tcl_GetIntFromObj(interp, objv[6], &dmincol);

  int dmaxrow;
  Tcl_GetIntFromObj(interp, objv[7], &dmaxrow);

  int dmaxcol;
  Tcl_GetIntFromObj(interp, objv[8], &dmaxcol);

  int overlay;
  Tcl_GetIntFromObj(interp, objv[9], &overlay);

  
  int result= copywin(srcwin, dstwin, sminrow,
		      smincol, dminrow, dmincol,
		      dmaxrow, dmaxcol, overlay);

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int DupWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* srcwin;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), srcwin);
  
  WINDOW* result= dupwin(srcwin);

  if (result == NULL) {
    Tcl_AppendResult(interp, "Error occured", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

static int ScrollOk_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  bool is_scroll;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), is_scroll);
  
  scrollok(win, is_scroll);
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int GetMaxY_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  int maxy= getmaxy(win);
  char str[5];
  sprintf(str, "%d", maxy);
  
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int MvPrintW_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  char *string = Tcl_GetString(objv[3]);

  if (mvprintw(y, x, string) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured", NULL);
  return TCL_ERROR;
}

static int Scroll_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= scroll(win);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while scroll", NULL);
  return TCL_ERROR;
}

static int Scrl_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int lines_number;
  Tcl_GetIntFromObj(interp, objv[1], &lines_number);

  int result= scrl(lines_number);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while scrl", NULL);
  return TCL_ERROR;
}

static int WScrl_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int lines_number;
  Tcl_GetIntFromObj(interp, objv[2], &lines_number);

  int result= wscrl(win, lines_number);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while wscrl", NULL);
  return TCL_ERROR;
}

static int MvWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);
  
  int result= mvwin(win, y, x);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while mvwin", NULL);
  return TCL_ERROR;
}

static int TouchLine_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int start;
  Tcl_GetIntFromObj(interp, objv[2], &start);

  int count;
  Tcl_GetIntFromObj(interp, objv[3], &count);
  
  int result= touchline(win, start, count);
  
  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while touchline", NULL);
  return TCL_ERROR;
}

static int COLOR_PAIR_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int color_num;
  Tcl_GetIntFromObj(interp, objv[1], &color_num);

  int result= COLOR_PAIR(color_num);
  char int_str_buffer[10];
  sprintf(int_str_buffer, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(int_str_buffer, -1));
  return TCL_OK;
}

static int NewPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int rows_number;
  Tcl_GetIntFromObj(interp, objv[1], &rows_number);

  int cols_number;
  Tcl_GetIntFromObj(interp, objv[0], &cols_number);

  WINDOW *window= newpad(rows_number, cols_number);

  if (window != NULL) {
    char hexstr[24];
    sprintf(hexstr, "%p", (void*)window);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "can't create new PAD", NULL);
  return TCL_ERROR;
}

int DLLEXPORT Tncurses_Init(Tcl_Interp *interp) {
  if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
    return TCL_ERROR;
  }
  /* changed this to check for an error - GPS */
  if (Tcl_PkgProvide(interp, "Tncurses", "1.0") == TCL_ERROR) {
    return TCL_ERROR;
  }
  Tcl_CreateObjCommand(interp, "initscr", Initscr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "printw", PrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "refresh", Refresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getch", GetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "endwin", EndWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "newwin", NewWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addstr", AddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwaddstr", MvWAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "noecho", NoEcho_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wrefresh", WRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "touchwin", TouchWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "addch", AddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddstr", WAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "delwin", DelWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getmaxyx", GetMaxYX_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "start_color", Start_Color_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "init_pair", Init_Pair_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wbkgd", WBkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "waddch", WAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wgetch", WGetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "subwin", SubWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "bkgd", Bkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "derwin", DerWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wclear", WClear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "overlay", Overlay_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "overwrite", OverWrite_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "copywin", CopyWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "dupwin", DupWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scrollok", ScrollOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "getmaxy", GetMaxY_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvprintw", MvPrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scroll", Scroll_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "scrl", Scrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "wscrl", WScrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "mvwin", MvWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "touchline", TouchLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "COLOR_PAIR", COLOR_PAIR_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, "newpad", NewPad_Cmd, NULL, NULL);
  return TCL_OK;
}
