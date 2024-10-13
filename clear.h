#ifndef CLEAR_H
#define CLEAR_H

static int Erase_Cmd(ClientData cdata, Tcl_Interp *interp,
		     int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"erase\"");

  int result= erase();

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while erase", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* CLEAR_H */
