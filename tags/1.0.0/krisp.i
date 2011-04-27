%module "krisp"
%{
%}

%include "cpointer.i"
%pointer_functions (int, intp);

extern char dberr[1024];

extern char * version (void);
extern char * uversion (void);
extern char * kerror (void);
extern int  * krisp_open (char *, int);
extern char * krisp_search (int *, char *);
extern void krisp_close (int *);

