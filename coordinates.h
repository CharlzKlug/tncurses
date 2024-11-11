#ifndef COORDINATES_H
#define COORDINATES_H

static int COLS_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"COLS\"");

  int result= COLS;

  char str[16];
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

#endif /* COORDINATES_H */
