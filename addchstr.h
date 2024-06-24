#ifndef ADDCHSTR_H
#define ADDCHSTR_H
#include <stdlib.h>

#define GET_CHTYPES(array_name, array_length, data_offset) do {		\
  array_name= malloc(sizeof(chtype) * (array_length));			\
  for (int i= 0; i < ((array_length) - 1); i++) {			\
  int tmp;								\
  Tcl_GetIntFromObj(interp, objv[i+(data_offset)], &tmp);		\
  array_name[i]= tmp;							\
  }									\
  array_name[(array_length) - 1]= 0;					\
  } while (0)

static int AddChStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(2, "wrong # args");

  chtype* chstr;
  GET_CHTYPES(chstr, objc, 1);
  
  int result= addchstr(chstr);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int AddChNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(3, "wrong # args");

  chtype* chstr;
  GET_CHTYPES(chstr, objc - 1, 1);
  
  int n;
  Tcl_GetIntFromObj(interp, objv[objc - 1], &n);
  
  int result= addchnstr(chstr, n);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int WAddChStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(3, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  chtype* chstr;
  GET_CHTYPES(chstr, (objc - 1), 2);
  
  int result= waddchstr(win, chstr);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int WAddChNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(4, "wrong # args");

  WINDOW* win;
  STRING_TO_WINDOW(Tcl_GetString(objv[1]), win);
  
  chtype* chstr;
  GET_CHTYPES(chstr, (objc - 2), 2);

  int n;
  Tcl_GetIntFromObj(interp, objv[objc - 1], &n);
  
  int result= waddchnstr(win, chstr, n);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int MvAddChStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(4, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);
  
  chtype* chstr;
  GET_CHTYPES(chstr, (objc - 2), 3);
  
  int result= mvaddchstr(y, x, chstr);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

static int MvAddChNStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(5, "wrong # args");

  int y;
  Tcl_GetIntFromObj(interp, objv[1], &y);

  int x;
  Tcl_GetIntFromObj(interp, objv[2], &x);

  chtype* chstr;
  GET_CHTYPES(chstr, objc - 3, 3);
  
  int n;
  Tcl_GetIntFromObj(interp, objv[objc - 1], &n);
  
  int result= mvaddchnstr(y, x, chstr, n);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

#endif	/* ADDCHSTR_H */
