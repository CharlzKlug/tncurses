#ifndef ALARM_H
#define ALARM_H

static int Beep_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"beep\"");

  int result= beep();

  if (result == ERR) {
    Tcl_AppendResult(interp, "error occured while beep", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* ALARM_H */
