%module "krisp"
%{
#include <sys/types.h>
#include <krisp.h>
%}

typedef unsigned long int ulong;

typedef struct {
	char    err[1024];
	char    ip[256];
	char    icode[64];
	char    iname[64];
	char    cname[64];
	char    ccode[4];
	ulong   netmask;
	ulong   start;
	ulong   end;
	bool    verbose;
} KRNET_API;

typedef struct {
	char    err[1024];
	char    ip[16];
	char ** dummy;
	char *  dummydata;
	ulong   start;
	ulong   end;
	bool    verbose;
	short   size;
} KRNET_API_EX;


extern char * version (void);
extern char * uversion (void);
extern KR_API * open (char *);
extern KRNET_API * search (KR_API *, char *);
extern KRNET_API_EX * search_ex (KR_API *, char *, char *);
extern void free_search (KRNET_API *);
extern void free_search_ex (KRNET_API_EX *);
extern void kclose (KR_API *);

extern ulong kip2long (char *);
extern ulong knetmask (ulong, ulong);
extern ulong knetwork (ulong, ulong);
extern ulong kbroadcast (ulong, ulong);
extern ulong kprefix2long (short);
extern short klong2prefix (ulong);
