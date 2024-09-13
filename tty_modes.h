#ifndef TTY_MODES_H
#define TTY_MODES_H

static int CBreak_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"cbreak\"");

  int result= cbreak();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while cbreak", NULL);
  return TCL_ERROR;
}

static int NoCBreak_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"nocbreak\"");

  int result= nocbreak();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while nocbreak", NULL);
  return TCL_ERROR;
}

static int Echo_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"echo\"");

  int result= echo();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while echo", NULL);
  return TCL_ERROR;
}

static int NoEcho_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"noecho\"");

  int result= noecho();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while noecho", NULL);
  return TCL_ERROR;
}

static int HalfDelay_Cmd(ClientData cdata, Tcl_Interp *interp,
			 int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(2, "wrong # args: should be \"halfdelay tenths\"");

  int tenths;
  Tcl_GetIntFromObj(interp, objv[1], &tenths);

  if (1 > tenths || tenths > 255) {
    Tcl_AppendResult(interp, "tenths should be in the range 1..255", NULL);
    return TCL_ERROR;
  }

  int result= halfdelay(tenths);

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while halfdelay", NULL);
  return TCL_ERROR;
}

#endif /* TTY_MODES_H */
