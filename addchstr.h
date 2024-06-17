#ifndef ADDCHSTR_H
#define ADDCHSTR_H
#include <stdlib.h>

static int AddChStr_Cmd(ClientData cdata, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
  CHECK_ARGUMENTS_GE(2, "wrong # args");
  chtype* chstr= malloc(sizeof(chtype) * objc);
  
  for (int i= 1; i < objc; i++) {
    int tmp;
    Tcl_GetIntFromObj(interp, objv[i], &tmp);
    chstr[i-1]= tmp;
  }
  chstr[objc-1]= 0;
  
  int result= addchstr(chstr);
  free(chstr);
  
  if(result == OK) {
    Tcl_SetObjResult(interp, Tcl_NewStringObj("", -1));
    return TCL_OK;
  }
  
  Tcl_AppendResult(interp, "error occured while addch", NULL);
  return TCL_ERROR;
}

#endif	/* ADDCHSTR_H */
