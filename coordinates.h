#ifndef COORDINATES_H
#define COORDINATES_H

static int COLS_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"COLS\"");

  int result= COLS;

  char str[16];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int LINES_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"LINES\"");

  int result= LINES;

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d", result));
  return TCL_OK;
}

static int GetYX_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"getyx window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y= 0;
  int x= 0;

  getyx(win, y, x);

  char str[16];
  sprintf(str, "%d %d", y, x);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int GetParYX_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"getparyx window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y= 0;
  int x= 0;

  getparyx(win, y, x);

  char str[16];
  sprintf(str, "%d %d", y, x);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int GetBegYX_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"getbegyx window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y= 0;
  int x= 0;

  getbegyx(win, y, x);

  char str[16];
  sprintf(str, "%d %d", y, x);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int GetMaxYX_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"getmaxyx window\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int maxy= 0;
  int maxx= 0;

  getmaxyx(win, maxy, maxx);

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%d %d", maxy, maxx));
  return TCL_OK;
}

#endif /* COORDINATES_H */
