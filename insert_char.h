#ifndef INSERT_CHAR_H
#define INSERT_CHAR_H

static int MVInsCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"mvinsch y x char\"");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);
  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);
  int input_chtype;
  Tcl_GetIntFromObj(interp, objv[3], &input_chtype);

  int result= mvinsch(y, x, input_chtype);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while mvinsch", NULL);
  return TCL_ERROR;
}

static int InsCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"insch char\"");

  int input_chtype;
  Tcl_GetIntFromObj(interp, objv[1], &input_chtype);

  int result= insch(input_chtype);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while insch", NULL);
  return TCL_ERROR;
}

static int WInsCh_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"winsch window chtype\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int input_chtype;
  Tcl_GetIntFromObj(interp, objv[2], &input_chtype);

  int result= winsch(win, input_chtype);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while winsch", NULL);
  return TCL_ERROR;
}

#endif /* INSERT_CHAR_H */
