#ifndef OUTPUT_H
#define OUTPUT_H
/* curses output options */

static int ClearOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"clearok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= clearok(win, bf);

  char str[16]= "";
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int IdlOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"idlok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= idlok(win, bf);

  char str[16]= "";
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

static int IdcOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"idcok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  idcok(win, bf);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int ImmedOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"immedok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  immedok(win, bf);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int LeaveOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"leaveok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  leaveok(win, bf);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* OUTPUT_H */
