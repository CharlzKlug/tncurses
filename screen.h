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

  Tcl_SetObjResult(interp, Tcl_ObjPrintf("%p", (void*)win));
  return TCL_OK;
}

static int EndWin_Cmd(ClientData cdata, Tcl_Interp *interp,
		      int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"endwin\"");
  int result= endwin();
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }

  Tcl_AppendResult(interp, "error occured while \"endwin\"", NULL);
  return TCL_ERROR;
}

static int IsEndWin_Cmd(ClientData cdata, Tcl_Interp *interp,
			int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS(1, "wrong # args: should be \"isendwin\"");
  bool result= isendwin();
  if(result == TRUE) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("TRUE", -1));
    return TCL_OK;
  }

  Tcl_SetObjResult(interp, Tcl_NewStringObj("FALSE", -1));
  return TCL_OK;
}

/* static int NewTerm_Cmd(ClientData cdata, Tcl_Interp *interp, */
/*		       int objc, Tcl_Obj *const objv[]) { */
/*   CHECK_ARGUMENTS(4, "wrong # args: should be \"newterm type outFd inFd\""); */

/*   SCREEN* result= newterm(NULL, stdout, stderr); */

/*   char str[32]= ""; */
/*   sprintf(str, "%p", (void*)result); */
/*   printf("%s\n", str); */
/*   Tcl_SetObjResult(interp, Tcl_NewStringObj(str, -1)); */
/*   return TCL_OK; */
/* } */

#endif /* SCREEN_H */
