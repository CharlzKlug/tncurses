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

#endif	/* ADDCHSTR_H */
