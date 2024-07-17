#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

static int BaudRate_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"environment\"");

  int result= baudrate();

  char str[16];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

#endif /* ENVIRONMENT_H */
