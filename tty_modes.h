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

#endif /* TTY_MODES_H */
