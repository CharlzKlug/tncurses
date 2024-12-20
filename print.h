#ifndef PRINT_H
#define PRINT_H

static int PrintW_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"printw message\"");
  int result= printw(Tcl_GetString(objv[1]));

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured while printw", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int WPrintW_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"wprintw window message\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int result= wprintw(win, "%s", Tcl_GetString(objv[2]));

  if (result == ERR) {
    Tcl_AppendResult(interp, "Error occured while wprintw", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int MvPrintW_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"mvprintw y x string\"");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  char *string = Tcl_GetString(objv[3]);

  if (mvprintw(y, x, string) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvprintw", NULL);
  return TCL_ERROR;
}

static int MvWPrintW_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5, "wrong # args: should be \"mvwprintw window y x string\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int y;
  Tcl_GetIntFromObj(interp, objv[2], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[3], &x);

  char *string = Tcl_GetString(objv[4]);

  if (mvwprintw(win, y, x, string) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvwprintw", NULL);
  return TCL_ERROR;
}

static int VW_PrintW_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"vw_printw window string\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  char *string = Tcl_GetString(objv[2]);

  va_list some_args; // Workaround for undefined behaviour of 'vw_printw'
  va_end(some_args);
  if (vw_printw(win, string, some_args) == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while vw_printw", NULL);
  return TCL_ERROR;
}

#endif /* PRINT_H */
