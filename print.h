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
  CHECK_ARGUMENTS(4, "wrong # args: should be \"mvprintw x y string\"");

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

#endif /* PRINT_H */
