#ifndef BACKGROUND_H
#define BACKGROUND_H

static int Bkgd_Cmd(ClientData cdata, Tcl_Interp *interp,
		    int objc, Tcl_Obj *const objv[]) {
  if (objc != 2) {
    Tcl_AppendResult(interp, "wrong # args", NULL);
    return TCL_ERROR;
  }

  char* buffer= Tcl_GetString(objv[1]);
  int input_val= -1;

  if (buffer[0] >= '0' && buffer[0] <= '9') {
    Tcl_GetIntFromObj(interp, objv[1], &input_val);
  }

  if (strlen(buffer) == 3 && buffer[0] == '\'' && buffer[2] == '\'') {
    input_val= buffer[1];
  }

  if (strlen(buffer) == 1) {
    input_val= buffer[0];
  }

  if (input_val == -1) {
    Tcl_AppendResult(interp, "wrong argument", NULL);
    return TCL_ERROR;
  }

  if (bkgd(input_val) == ERR) {
    Tcl_AppendResult(interp, "Error occured in bkgd function", NULL);
    return TCL_ERROR;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
  return TCL_OK;
}

#endif /* BACKGROUND_H */
