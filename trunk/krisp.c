/*
 * $Id: krisp.c,v 1.2 2010-06-20 05:59:50 oops Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <krisp.h>

char * version (void) { // {{{
	return krisp_version ();
} // }}}

char * uversion (void) { // {{{
	return krisp_uversion ();
} // }}}

KR_API * open (char *datafile) { // {{{
	KR_API *db;
	char krerr[1024];

	if ( kr_open_safe (&db, datafile, krerr) == false ) {
		fprintf (stderr, "%s\n", krerr);
		return NULL;
	}

	return db;
} // }}}

KRNET_API * search (KR_API *db, char *host) { // {{{
	KRNET_API * isp;

	isp = (KRNET_API *) malloc (sizeof (KRNET_API));
	if ( isp == NULL ) {
		fprintf (stderr, "search:: memory allocation failed\n");
		return NULL;
	}

	memset (isp, 0, sizeof (KRNET_API));
	SAFECPY_256 (isp->ip, host);
	isp->verbose = 0;

	if ( kr_search (isp, db) ) {
		SAFECPY_1024 (isp->err, db->err);
		return NULL;
	}

	return isp;
} // }}}

KRNET_API_EX * search_ex (KR_API *db, char *host, char *table) { // {{{
	KRNET_API_EX * isp;
	short i, l;

	isp = (KRNET_API_EX *) malloc (sizeof (KRNET_API_EX));
	if ( isp == NULL ) {
		fprintf (stderr, "search:: memory allocation failed\n");
		return NULL;
	}

	memset (isp, 0, sizeof (KRNET_API_EX));
	SAFECPY_256 (isp->ip, host);
	isp->verbose = 0;

	db->table = table;
	if ( kr_search_ex (isp, db) ) {
		SAFECPY_1024 (isp->err, db->err);
		return NULL;
	}

	for ( i=0; i<isp->size - 1; i++ ) {
		l = strlen (isp->dummy[0]);
		isp->dummydata[0+l] = ':';
	}

	return isp;
} // }}}

void free_search (KRNET_API * isp) { // {{{
	if ( isp != NULL )
		free (isp);
} // }}}

void free_search_ex (KRNET_API_EX * isp) { // {{{
	if ( isp != NULL ) {
		initStruct_ex (isp, true);
		free (isp);
	}
} // }}}

void kclose (KR_API * db) { // {{{
	kr_close (db);
} // }}}

ulong kip2long (char *ip) { // {{{
	return kr_ip2long (ip);
} // }}}

ulong knetmask (ulong start, ulong end) { // {{{
	return kr_netmask (start, end);
} // }}}

ulong knetwork (ulong ip, ulong mask) { // {{{
	return kr_network (ip, mask);
} // }}}

ulong kbroadcast (ulong ip, ulong mask) { // {{{
	return kr_broadcast (ip, mask);
} // }}}

ulong kprefix2long (short prefix) { // {{{
	return kr_prefix2long (prefix);
} // }}}

short klong2prefix (ulong mask) { // {{{
	return kr_long2prefix (mask);
} // }}}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
