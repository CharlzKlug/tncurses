#ifndef WINDOW_H
#define WINDOW_H

static int NewWin_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(5,
		  "wrong # args: should be \"newwin nlines \
ncols begin_y begin_x\"");
  int rows;
  Tcl_GetIntFromObj(interp, objv[1], &rows);
  int cols;
  Tcl_GetIntFromObj(interp, objv[2], &cols);
  int y_org;
  Tcl_GetIntFromObj(interp, objv[3], &y_org);
  int x_org;
  Tcl_GetIntFromObj(interp, objv[4], &x_org);
  WINDOW *window= newwin(rows, cols, y_org, x_org);

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)window);
  Tcl_SetObjResult(interp, Tcl_NewStringObj(hexstr, -1));
  return TCL_OK;
}

#endif /* WINDOW_H */
