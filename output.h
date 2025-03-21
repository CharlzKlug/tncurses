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

static int SetScrReg_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"setscrreg top bot\"");

  int top;
  Tcl_GetIntFromObj(interp, objv[1], &top);

  int bot;
  Tcl_GetIntFromObj(interp, objv[2], &bot);

  int result= setscrreg(top, bot);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("error occured while setscrreg",
					    -1));
  return TCL_ERROR;
}

static int WSetScrReg_Cmd(ClientData cdata, Tcl_Interp *interp,
			  int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(4, "wrong # args: should be \"wsetscrreg window top bot\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  int top;
  Tcl_GetIntFromObj(interp, objv[2], &top);

  int bot;
  Tcl_GetIntFromObj(interp, objv[3], &bot);

  int result= wsetscrreg(win, top, bot);

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("error occured while wsetscrreg",
					    -1));
  return TCL_ERROR;
}

static int ScrollOk_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"scrollok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool is_scroll;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), is_scroll);

  scrollok(win, is_scroll);

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

static int NL_Cmd(ClientData cdata, Tcl_Interp *interp,
		  int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"nl\"");

  int result= nl();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("error occured while nl",
					    -1));
  return TCL_ERROR;
}

static int NoNL_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"nonl\"");

  int result= nonl();

  if (result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("error occured while nonl",
					    -1));
  return TCL_ERROR;
}

#endif /* OUTPUT_H */
