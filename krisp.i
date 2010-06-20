%module "krisp"
%{
#include <sys/types.h>
#include <krisp.h>
%}

typedef unsigned long int ulong;

typedef struct {
	short			verbose;
	char			ip[256];
	unsigned long	netmask;
	unsigned long	start;
	unsigned long	end;
	char			icode[64];
	char			iname[64];
	char			ccode[4];
	char			cname[64];
} KRNET_API;

typedef struct {
    short           verbose;
    char            ip[16];
    ulong           start;
    ulong           end;
    short           size;
    char **         dummy;
    char *          dummydata;
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
