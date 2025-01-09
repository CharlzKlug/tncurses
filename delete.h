#ifndef DELETE_H
#define DELETE_H

static int DelCh_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"delch\"");

  int result= delch();

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while delch", NULL);
  return TCL_ERROR;
}

#endif /* DELETE_H */
