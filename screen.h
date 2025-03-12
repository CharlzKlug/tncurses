#ifndef SCREEN_H
#define SCREEN_H

static int Initscr_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"initscr\"");

  WINDOW* win;
  win= initscr();

  if (win == NULL) {
    Tcl_AppendResult(interp, "Error in \"initscr\"!", NULL);
    return TCL_ERROR;
  }

  char hexstr[24];
  sprintf(hexstr, "%p", (void*)win);
  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%p", (void*)win));
  return TCL_OK;
}

#endif /* SCREEN_H */
