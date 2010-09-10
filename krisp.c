/*
 * $Id: krisp.c,v 1.10 2010-09-10 19:17:46 oops Exp $
 */
#include "Python.h"

#include <krisp.h>
#include <stdlib.h>
#include "version.h"

#if defined(__GNUC__) && __GNUC__ >= 4
	#define KR_INT_API  __attribute__ ((visibility("hidden")))
#else
	#define KR_INT_API
#endif

static PyObject * ErrorObject;

KR_INT_API ulong krisp_format_convert (char * v) { // {{{
	if ( strchr (v, '.') == NULL )
		return (ulong) strtoul (v, NULL, 10);
	return ip2long (v);
} // }}}

static PyObject * py_mod_version (PyObject * self, PyObject * args) { // {{{
	return Py_BuildValue ("s", MOD_VERSION);
} // }}}

static PyObject * py_mod_uversion (PyObject * self, PyObject * args) { // {{{
	return Py_BuildValue ("s", MOD_UVERSION);
} // }}}

static PyObject * py_version (PyObject * self, PyObject * args) { // {{{
	return Py_BuildValue ("s", krisp_version ());
} // }}}

static PyObject * py_uversion (PyObject * self, PyObject * args) { // {{{

	return Py_BuildValue ("s", krisp_uversion ());
} // }}}

static PyObject * py_ip2long (PyObject * self, PyObject * args) { // {{{
	char *	addr;

	if ( ! PyArg_ParseTuple (args, "s", &addr) )
		return NULL;

	return Py_BuildValue ("k", ip2long (addr));
} // }}}

static PyObject * py_long2ip (PyObject * self, PyObject * args) { // {{{
	ulong	laddr;
	char	retval[16];

	if ( ! PyArg_ParseTuple (args, "k", &laddr) )
		return NULL;

	return Py_BuildValue ("s", long2ip_r (laddr, retval));
} // }}}

static PyObject * py_netmask (PyObject * self, PyObject * args) { // {{{
	char *	start;
	char *	end;
	char	retval[16];
	ulong	s, e;

	if ( ! PyArg_ParseTuple (args, "ss", &start, &end) )
		return NULL;

	s = krisp_format_convert (start);
	e = krisp_format_convert (end);

	return Py_BuildValue ("s", long2ip_r (guess_netmask (s, e), retval));
} // }}}

static PyObject * py_mask2prefix (PyObject * self, PyObject * args) { // {{{
	char *	mask;
	ulong	m;

	if ( ! PyArg_ParseTuple (args, "s", &mask) )
		return NULL;

	m = krisp_format_convert (mask);

	return Py_BuildValue ("i", long2prefix (m));
} // }}}

static PyObject * py_prefix2mask (PyObject * self, PyObject * args) { // {{{
	short	prefix;
	char	retval[16];

	if ( ! PyArg_ParseTuple (args, "h", &prefix) )
		return NULL;

	return Py_BuildValue ("s", long2ip_r (prefix2long (prefix), retval));
} // }}}

static PyObject * py_network (PyObject * self, PyObject * args) { // {{{
	char *	ip;
	char *	mask;
	char	retval[16];
	ulong	i, m;

	if ( ! PyArg_ParseTuple (args, "ss", &ip, &mask) )
		return NULL;

	i = krisp_format_convert (ip);
	m = krisp_format_convert (mask);

	return Py_BuildValue ("s", long2ip_r (network (i, m), retval));
} // }}}

static PyObject * py_broadcast (PyObject * self, PyObject * args) { // {{{
	char *	ip;
	char *	mask;
	char	retval[16];
	ulong	i, m;

	if ( ! PyArg_ParseTuple (args, "ss", &ip, &mask) )
		return NULL;

	i = krisp_format_convert (ip);
	m = krisp_format_convert (mask);

	return Py_BuildValue ("s", long2ip_r (broadcast (i, m), retval));
} // }}}

static PyObject * py_open (PyObject * self, PyObject * args) { // {{{
	PyObject *	err = NULL;
	char *		database = NULL;
	int			argc;

	KR_API *	db;
	char		buf[1024];

	if ( ! PyArg_ParseTuple (args, "|sO", &database, &err) )
		return NULL;

	argc = PyTuple_Size (args);

	if ( argc > 0 && ! strlen (database) )
		database = NULL;

	if ( err != NULL ) {
		if ( ! PyList_Check (err) ) {
			PyErr_SetString (ErrorObject, "2th argument is must list");
			return NULL;
		}
	}

	if ( kr_open_safe (&db, database, buf) == false ) {
		if ( argc > 1 ) {
			PyObject * value = PyString_FromString (buf);
			PyList_Append (err, value);
			Py_DECREF (value);
		}
		return Py_None;
	}

	return Py_BuildValue ("i", (int *) db);
} // }}}

static PyObject * py_search (PyObject * self, PyObject * args) { // {{{
	static PyObject *	ret = NULL;
	static PyObject *	new = NULL;
	PyObject *			class_dict;
	PyObject *			prop;
	PyObject *			err = NULL;
	char *				host;
	int *				db;
	int					argc;

	KRNET_API 			isp;
	char				buf[16];
	ulong				networkv, broadcastv;

	if ( ! PyArg_ParseTuple (args, "is|O", &db, &host, &err) )
		return NULL;

	if ( err != NULL ) {
		if ( ! PyList_Check (err) ) {
			PyErr_SetString (ErrorObject, "3th argument is must PyLis");
			return NULL;
		}
	}

	SAFECPY_256 (isp.ip, host);
	isp.verbose = 0;

	if ( kr_search (&isp, (KR_API *) db) ) {
		if ( argc > 2 ) {
			PyObject * value = PyString_FromString (isp.err);
			PyList_Append (err, value);
			Py_DECREF (value);
		}
		return Py_None;
	}

	networkv   = network (isp.start, isp.netmask);
	broadcastv = broadcast (isp.start, isp.netmask);

	class_dict = PyDict_New ();
	prop = Py_BuildValue ("s", isp.ip);
	PyDict_SetItemString (class_dict, "ip", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (isp.start, buf));
	PyDict_SetItemString (class_dict, "start", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (isp.end, buf));
	PyDict_SetItemString (class_dict, "end", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (isp.netmask, buf));
	PyDict_SetItemString (class_dict, "netmask", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (networkv, buf));
	PyDict_SetItemString (class_dict, "network", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (broadcastv, buf));
	PyDict_SetItemString (class_dict, "broadcast", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", isp.icode);
	PyDict_SetItemString (class_dict, "icode", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", isp.iname);
	PyDict_SetItemString (class_dict, "iname", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", isp.ccode);
	PyDict_SetItemString (class_dict, "ccode", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", isp.cname);
	PyDict_SetItemString (class_dict, "cname", prop);
	Py_DECREF (prop);

	if ( ret == NULL )
		ret = PyClass_New(NULL, PyDict_New(), PyString_FromString("KRNET_API"));

	new = PyInstance_NewRaw(ret, class_dict);
	Py_DECREF (class_dict);

	return new;
} // }}}

static PyObject * py_search_ex (PyObject * self, PyObject * args) { // {{{
	static PyObject *	ret = NULL;
	static PyObject *	new = NULL;
	PyObject *			class_dict;
	PyObject *			prop;
	PyObject *			err = NULL;
	char *				host;
	char *				table;
	int *				db;
	int					argc;

	KR_API *			dbh;
	KRNET_API_EX		isp;
	char				buf[16];
	ulong				netmask, networkv, broadcastv;

	if ( ! PyArg_ParseTuple (args, "iss|O", &db, &host, &table, &err) )
		return NULL;

	if ( err != NULL ) {
		if ( ! PyList_Check (err) ) {
			PyErr_SetString (ErrorObject, "3th argument is must PyList");
			return NULL;
		}
	}

	SAFECPY_256 (isp.ip, host);
	dbh = (KR_API *) db;
	dbh->table = table;
	isp.verbose = 0;

	if ( kr_search_ex (&isp, (KR_API *) db) ) {
		if ( argc > 3 ) {
			PyObject * value = PyString_FromString (isp.err);
			PyList_Append (err, value);
			Py_DECREF (value);
		}
		return Py_None;
	}

	netmask    = guess_netmask (isp.start, isp.end);
	networkv   = network (isp.start, netmask);
	broadcastv = broadcast (isp.start, netmask);

	class_dict = PyDict_New ();
	prop = Py_BuildValue ("s", isp.ip);
	PyDict_SetItemString (class_dict, "ip", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (isp.start, buf));
	PyDict_SetItemString (class_dict, "start", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (isp.end, buf));
	PyDict_SetItemString (class_dict, "end", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (netmask, buf));
	PyDict_SetItemString (class_dict, "netmask", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (networkv, buf));
	PyDict_SetItemString (class_dict, "network", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("s", long2ip_r (broadcastv, buf));
	PyDict_SetItemString (class_dict, "broadcast", prop);
	Py_DECREF (prop);
	prop = Py_BuildValue ("i", isp.size);
	PyDict_SetItemString (class_dict, "size", prop);
	Py_DECREF (prop);

	{
		short		i;

		prop = PyList_New (isp.size);
		for ( i=0; i<isp.size; i++ )
			PyList_SetItem (prop, i, PyString_FromString (isp.dummy[i]));

		PyDict_SetItemString (class_dict, "dummy", prop);
		Py_DECREF (prop);
	}

	// free memory about kr_search_ex
	initStruct_ex (&isp, true);

	if ( ret == NULL )
		ret = PyClass_New(NULL, PyDict_New(), PyString_FromString("KRNET_API"));

	new = PyInstance_NewRaw(ret, class_dict);
	Py_DECREF (class_dict);

	return new;
} // }}}

static PyObject * py_close (PyObject * self, PyObject * args) { // {{{
	int *		db;

	if ( ! PyArg_ParseTuple (args, "i", &db) )
		return NULL;

	kr_close ((KR_API **) &db);
	db = NULL;

	return Py_None;
} // }}}

static struct PyMethodDef krisp_methods[] = { // {{{
	{ "mod_version",	py_mod_version,		METH_NOARGS },
	{ "mod_uversion",	py_mod_uversion,	METH_NOARGS },
	{ "version",		py_version,			METH_NOARGS },
	{ "uversion",		py_uversion,		METH_NOARGS },
	{ "ip2long",		py_ip2long,			METH_VARARGS },
	{ "long2ip",		py_long2ip,			METH_VARARGS },
	{ "netmask",		py_netmask,			METH_VARARGS },
	{ "mask2prefix",	py_mask2prefix,		METH_VARARGS },
	{ "prefix2mask",	py_prefix2mask,		METH_VARARGS },
	{ "network",		py_network,			METH_VARARGS },
	{ "broadcast",		py_broadcast,		METH_VARARGS },
	{ "open",			py_open,			METH_VARARGS },
	{ "search",			py_search,			METH_VARARGS },
	{ "search_ex",		py_search_ex,		METH_VARARGS },
	{ "close",			py_close,			METH_VARARGS },
	{ NULL, NULL }
}; // }}}

void initkrisp () { // {{{
	PyObject *	m;

	m = Py_InitModule ("krisp", krisp_methods);
	ErrorObject = Py_BuildValue ("s", "krisp initialize error");
} // }}}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
