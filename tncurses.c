/* How to build: gcc -shared -o libtncurses.so -DUSE_TCL_STUBS -I /usr/include/tcl tncurses.c -ltclstub8.6 -lncurses -fPIC */
#include <tcl.h>
#include <string.h>
#include "tncurses.h"
#include "attributes.h"
#include "addch.h"
#include "addchstr.h"
#include "addstr.h"
#include "colors.h"
#include "environment.h"
#include "alarm.h"
#include "background.h"
#include "lines.h"
#include "tty_modes.h"
#include "clear.h"
#include "output.h"

#define NS "tncurses"

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
  int ch= getch();
  char str[64];
  sprintf(str, "%d", ch);
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

static int WRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"wrefresh window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  wrefresh(win);

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


static int DelWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  WINDOW* win;

  char* buffer= Tcl_GetString(objv[1]);
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

  if (delwin(win) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "Error occured with delwin", NULL);
  return TCL_ERROR;
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

  unsigned char ch;
  ch= wgetch(win);

  char str[64];
  sprintf(str, "%d", ch);
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
  Tcl_GetIntFromObj(interp, objv[2], &cols_number);

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

static int PRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(8, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int pminrow;
  Tcl_GetIntFromObj(interp, objv[2], &pminrow);

  int pmincol;
  Tcl_GetIntFromObj(interp, objv[3], &pmincol);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[4], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[5], &smincol);

  int smaxrow;
  Tcl_GetIntFromObj(interp, objv[6], &smaxrow);

  int smaxcol;
  Tcl_GetIntFromObj(interp, objv[7], &smaxcol);

  int result= prefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int SubPad_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(6, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int rows;
  Tcl_GetIntFromObj(interp, objv[2], &rows);

  int cols;
  Tcl_GetIntFromObj(interp, objv[3], &cols);

  int y;
  Tcl_GetIntFromObj(interp, objv[4], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[5], &x);

  WINDOW* sub_pad= subpad(pad, rows, cols, y, x);

  if (sub_pad != NULL) {
    char hexstr[24];
    sprintf(hexstr, "%p", (void*)sub_pad);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "can't create new subpad", NULL);
  return TCL_ERROR;
}

static int PNOutRefresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(8, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  int pminrow;
  Tcl_GetIntFromObj(interp, objv[2], &pminrow);

  int pmincol;
  Tcl_GetIntFromObj(interp, objv[3], &pmincol);

  int sminrow;
  Tcl_GetIntFromObj(interp, objv[4], &sminrow);

  int smincol;
  Tcl_GetIntFromObj(interp, objv[5], &smincol);

  int smaxrow;
  Tcl_GetIntFromObj(interp, objv[6], &smaxrow);

  int smaxcol;
  Tcl_GetIntFromObj(interp, objv[7], &smaxcol);

  int result= pnoutrefresh(pad, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int DoUpdate_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= doupdate();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while prefresh", NULL);
  return TCL_ERROR;
}

static int PEchoChar_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* pad;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), pad);

  char *buffer= Tcl_GetString(objv[2]);
  if (strlen(buffer) == 0) {
    Tcl_AppendResult(interp, "no char argument!", NULL);
    return TCL_ERROR;
  }
  char ch= buffer[0];
  int result= pechochar(pad, ch);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while pechochar", NULL);
  return TCL_ERROR;
}

static int SLK_Init_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int mode;
  Tcl_GetIntFromObj(interp, objv[1], &mode);

  int result= slk_init(mode);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while slk_init", NULL);
  return TCL_ERROR;
}

static int SLK_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args");

  int label_num;
  Tcl_GetIntFromObj(interp, objv[1], &label_num);

  char *label_text;
  label_text= Tcl_GetString(objv[2]);

  int fmt;
  Tcl_GetIntFromObj(interp, objv[3], &fmt);

  int result= slk_set(label_num, label_text, fmt);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while slk_set", NULL);
  return TCL_ERROR;
}

static int SLK_Refresh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_refresh();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while slk_refresh", NULL);
  return TCL_ERROR;
}

static int SLK_Restore_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_restore();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while slk_restore", NULL);
  return TCL_ERROR;
}

static int SLK_Clear_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= slk_clear();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while slk_clear", NULL);
  return TCL_ERROR;
}

static int KEY_F_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int number;
  Tcl_GetIntFromObj(interp, objv[1], &number);

  int result= KEY_F(number);

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int NCURSES_MOUSE_VERSION_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= NCURSES_MOUSE_VERSION;

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int ALL_MOUSE_EVENTS_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");
  char str[64];
  sprintf(str, "%ld", ALL_MOUSE_EVENTS);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int ButtonsEvents_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  char str[64];
  if (strstr(Tcl_GetString(objv[0]), "BUTTON1_RELEASED") != NULL) {
    sprintf(str, "%ld", BUTTON1_RELEASED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON1_PRESSED") != NULL) {
    sprintf(str, "%ld", BUTTON1_PRESSED);
  }
  if (strstr(Tcl_GetString(objv[0]), "tncurses::BUTTON1_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON1_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON1_DOUBLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON1_DOUBLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON1_TRIPLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON1_TRIPLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON2_RELEASED") != NULL) {
    sprintf(str, "%ld", BUTTON2_RELEASED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON2_PRESSED") != NULL) {
    sprintf(str, "%ld", BUTTON2_PRESSED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON2_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON2_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON2_DOUBLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON2_DOUBLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON2_TRIPLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON2_TRIPLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON3_RELEASED") != NULL) {
    sprintf(str, "%ld", BUTTON3_RELEASED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON3_PRESSED") != NULL) {
    sprintf(str, "%ld", BUTTON3_PRESSED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON3_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON3_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON3_DOUBLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON3_DOUBLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON3_TRIPLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON3_TRIPLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON4_RELEASED") != NULL) {
    sprintf(str, "%ld", BUTTON4_RELEASED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON4_PRESSED") != NULL) {
    sprintf(str, "%ld", BUTTON4_PRESSED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON4_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON4_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON4_DOUBLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON4_DOUBLE_CLICKED);
  }
  if (strstr(Tcl_GetString(objv[0]), "BUTTON4_TRIPLE_CLICKED") != NULL) {
    sprintf(str, "%ld", BUTTON4_TRIPLE_CLICKED);
  }
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int MouseMask_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int newmask;
  Tcl_GetIntFromObj(interp, objv[1], &newmask);

  mmask_t* oldmask;
  STRING_TO_MMASK_T(Tcl_GetString(objv[2]), oldmask);

  mmask_t result= mousemask(newmask, oldmask);

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int KEY_MOUSE_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  int result= KEY_MOUSE;

  char str[64];
  sprintf(str, "%d", result);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int GetMouse_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args");

  MEVENT mort;
  int result= getmouse(&mort);

  if(result == OK) {
    char str[64];
    sprintf(str, "%d %d %d %d %d", mort.id, mort.x, mort.y, mort.z, mort.bstate);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while getmouse", NULL);
  return TCL_ERROR;
}

static int Move_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);
  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  int result= move(y, x);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while move", NULL);
  return TCL_ERROR;
}

static int Curs_Set_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int cursor_visibility;
  Tcl_GetIntFromObj(interp, objv[1], &cursor_visibility);

  int result= curs_set(cursor_visibility);

  if(result != ERR) {
    char str[4];
    sprintf(str, "%d", result);
    Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while curs_set", NULL);
  return TCL_ERROR;
}


static int Scr_Dump_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int result= scr_dump(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while scr_dump", NULL);
  return TCL_ERROR;
}

static int Scr_Restore_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  int result= scr_restore(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while scr_restore", NULL);
  return TCL_ERROR;
}

static int PutWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  char* filename;
  filename= Tcl_GetString(objv[2]);

  FILE *wfile;
  wfile= fopen(filename, "w");
  if(wfile == NULL) {
    Tcl_AppendResult(interp, "can't open file while putwin", NULL);
    return TCL_ERROR;
  }

  int result= putwin(win, wfile);
  fclose(wfile);
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while putwin", NULL);
  return TCL_ERROR;
}

static int GetWin_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args");

  char* filename;
  filename= Tcl_GetString(objv[1]);

  FILE *wfile;
  wfile= fopen(filename, "r");
  if(wfile == NULL) {
    Tcl_AppendResult(interp, "can't open file while getwin", NULL);
    return TCL_ERROR;
  }

  WINDOW *window= getwin(wfile);
  fclose(wfile);

  if(window == NULL) {
    Tcl_AppendResult(interp, "error occured while getwin (no window pointer)", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

int DLLEXPORT Tncurses_Init(Tcl_Interp *interp) {
  if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
    return TCL_ERROR;
  }
  /* changed this to check for an error - GPS */
  if (Tcl_PkgProvide(interp, "Tncurses", "1.0") == TCL_ERROR) {
    return TCL_ERROR;
  }
  Tcl_CreateNamespace(interp, NS, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::initscr", Initscr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::printw", PrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::refresh", Refresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getch", GetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::endwin", EndWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::newwin", NewWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::addstr", AddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwaddstr", MvWAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wrefresh", WRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::touchwin", TouchWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::addchNS", AddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::waddstr", WAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::delwin", DelWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getmaxyx", GetMaxYX_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::start_color", Start_Color_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::init_pair", Init_Pair_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wbkgd", WBkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::waddch", WAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wgetch", WGetCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::subwin", SubWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::bkgd", Bkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::derwin", DerWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wclear", WClear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::overlay", Overlay_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::overwrite", OverWrite_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::copywin", CopyWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::dupwin", DupWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::scrollok", ScrollOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getmaxy", GetMaxY_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvprintw", MvPrintW_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::scroll", Scroll_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::scrl", Scrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wscrl", WScrl_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwin", MvWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::touchline", TouchLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_PAIR", COLOR_PAIR_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::newpad", NewPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::prefresh", PRefresh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::subpad", SubPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::pnoutrefresh", PNOutRefresh_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::doupdate", DoUpdate_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::pechochar", PEchoChar_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::slk_init", SLK_Init_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::slk_set", SLK_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::slk_refresh", SLK_Refresh_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::slk_restore", SLK_Restore_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::slk_clear", SLK_Clear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::keypad", KeyPad_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::KEY_F", KEY_F_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::NCURSES_MOUSE_VERSION",
		       NCURSES_MOUSE_VERSION_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::ALL_MOUSE_EVENTS", ALL_MOUSE_EVENTS_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mousemask", MouseMask_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON1_RELEASED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON1_PRESSED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON1_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON1_DOUBLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON1_TRIPLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON2_RELEASED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON2_PRESSED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON2_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON2_DOUBLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON2_TRIPLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON3_RELEASED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON3_PRESSED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON3_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON3_DOUBLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON3_TRIPLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON4_RELEASED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON4_PRESSED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON4_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON4_DOUBLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::BUTTON4_TRIPLE_CLICKED", ButtonsEvents_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::KEY_MOUSE", KEY_MOUSE_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getmouse", GetMouse_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::move", Move_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::clrtoeol", ClrToEol_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvaddch", MvAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::clear", Clear_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvaddstr", MvAddStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::curs_set", Curs_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::box", Box_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::border", Border_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::hline", HLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::vline", VLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvhline", MvHLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvvline", MvVLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::scr_dump", Scr_Dump_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::scr_restore", Scr_Restore_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::putwin", PutWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getwin", GetWin_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwaddch", MvWAddCh_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_ATTRIBUTES", Attribute_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_NORMAL", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_STANDOUT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_UNDERLINE", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_REVERSE", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_BLINK", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_DIM", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_BOLD", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_ALTCHARSET", Attribute_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_INVIS", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_PROTECT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_HORIZONTAL", Attribute_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_LEFT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_LOW", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_RIGHT", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_TOP", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_VERTICAL", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_ITALIC", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::addchstr", AddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::addchnstr", AddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::waddchstr", WAddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::waddchnstr", WAddChNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvaddchstr", MvAddChStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvaddchnstr", MvAddChNStr_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwaddchstr", MvWAddChStr_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwaddchnstr", MvWAddChNStr_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::addnstr", AddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::waddnstr", WAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvaddnstr", MvAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwaddnstr", MvWAddNStr_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::assume_default_colors",
		       Assume_Default_Colors_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_BLACK", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_RED", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_GREEN", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_YELLOW", ColorCode_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_BLUE", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_MAGENTA", ColorCode_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_CYAN", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::COLOR_WHITE", ColorCode_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attr_get", Attr_Get_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attrset", AttrSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::A_COLOR", Attribute_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attr_off", Attr_Off_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attr_on", Attr_On_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attroff", AttrOff_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattroff", WAttrOff_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attron", AttrOn_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattron", WAttrOn_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattrset", WAttrSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::color_set", Color_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wcolor_set", WColor_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::standend", Standend_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wstandend", WStandend_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::standout", StandOut_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattr_get", WAttr_Get_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattr_off", WAttr_Off_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattr_on", WAttr_On_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::attr_set", Attr_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wattr_set", WAttr_Set_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::chgat", ChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wchgat", WChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvchgat", MvChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwchgat", MvWChGAt_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::baudrate", BaudRate_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::erasechar", EraseChar_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::has_ic", Has_Ic_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::has_il", Has_Ic_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::killchar", KillChar_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::longname", LongName_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::termattrs", TermAttrs_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::termname", TermName_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::beep", Beep_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::flash", Flash_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::bkgdset", BkgdSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wbkgdset", WBkgdSet_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::getbkgd", GetBkgd_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wborder", WBorder_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::whline", WHLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wvline", WVLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwhline", MvWHLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::mvwvline", MvWVLine_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::can_change_color", Can_Change_Color_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::init_color", Init_Color_Cmd,
		       NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::has_colors", Has_Colors_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::color_content", Color_Content_Cmd, NULL,
		       NULL);
  Tcl_CreateObjCommand(interp, NS "::pair_content", Pair_Content_Cmd, NULL,
		       NULL);
  Tcl_CreateObjCommand(interp, NS "::cbreak", CBreak_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::nocbreak", NoCBreak_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::echo", Echo_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::noecho", NoEcho_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::halfdelay", HalfDelay_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::intrflush", IntrFlush_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::meta", Meta_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::nodelay", NoDelay_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::raw", Raw_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::noraw", NoRaw_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::noqiflush", NoQiFlush_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::qiflush", QiFlush_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::notimeout", NoTimeout_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::timeout", Timeout_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wtimeout", WTimeout_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::typeahead", TypeAhead_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::erase", Erase_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::werase", WErase_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::clrtobot", ClrToBot_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wclrtobot", WClrToBot_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::wclrtoeol", WClrToEol_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::clearok", ClearOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::idlok", IdlOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::idcok", IdcOk_Cmd, NULL, NULL);
  Tcl_CreateObjCommand(interp, NS "::immedok", ImmedOk_Cmd, NULL, NULL);
  return TCL_OK;
}
