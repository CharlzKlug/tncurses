#ifndef OUTPUT_H
#define OUTPUT_H
/* curses output options */

static int ClearOk_Cmd(ClientData cdata, Tcl_Interp *interp,
		       int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(3, "wrong # args: should be \"clearok window bool\"");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);

  bool bf;
  STRING_TO_BOOL(Tcl_GetString(objv[2]), bf);

  int result= clearok(win, bf);

  char str[16]= "";
  sprintf(str, "%d", result);

  Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1));
  return TCL_OK;
}

#endif /* OUTPUT_H */
