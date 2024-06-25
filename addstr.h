#ifndef ADDSTR_H
#define ADDSTR_H

static int AddStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    return TCL_ERROR;
  }
  int result= addstr(Tcl_GetString(objv[1]));

  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while addstr", NULL);
  return TCL_ERROR;
}

#endif /* ADDSTR_H */
