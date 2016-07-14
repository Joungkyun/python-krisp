/*
 * Copyright (C) 2016 by JoungKyun.Kim <http://oops.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU LESSER GENERAL PUBLIC
 * LICENSE for more details.
 *
 * You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "Python.h"

#include <ipcalc.h>
#include <krisp.h>
#include <stdlib.h>
#include "version.h"

#if defined(__GNUC__) && __GNUC__ >= 4
	#define KR_INT_API  __attribute__ ((visibility("hidden")))
#else
	#define KR_INT_API
#endif

#if PY_MAJOR_VERSION >= 3
	#define MOD_ERROR_VAL NULL
	#define MOD_SUCCESS_VAL(val) val
	#define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
	#define PyString_FromString PyBytes_FromString
#else
	#define MOD_ERROR_VAL
	#define MOD_SUCCESS_VAL(val)
	#define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
#endif

static PyObject * ErrorObject;

KR_INT_API ulong krisp_format_convert (char * v) { // {{{
	if ( strchr (v, '.') == NULL )
		return (ulong) strtoul (v, NULL, 10);
	return ip2long (v);
} // }}}

static PyObject * py_mod_version (PyObject * self, PyObject * args) { // {{{
	return Py_BuildValue ("s", MOD_KRISP_VERSION);
} // }}}

static PyObject * py_mod_uversion (PyObject * self, PyObject * args) { // {{{
	return Py_BuildValue ("s", MOD_KRISP_UVERSION);
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

	long2ip_r (laddr, retval);
	return Py_BuildValue ("s", retval);
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

	long2ip_r (guess_netmask (s, e), retval);
	return Py_BuildValue ("s", retval);
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

	long2ip_r (network (i, m), retval);
	return Py_BuildValue ("s", retval);
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

	long2ip_r (broadcast (i, m), retval);
	return Py_BuildValue ("s", retval);
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

	return Py_BuildValue ("l", (long *) db);
} // }}}

static PyObject * py_search (PyObject * self, PyObject * args) { // {{{
#if PY_MAJOR_VERSION < 3
	static PyObject *	ret = NULL;
#endif
	PyObject *			new = NULL;
	PyObject *			class_dict;
	PyObject *			prop;
	PyObject *			err = NULL;
	char *				host;
	int					argc;

	KR_API *			db;
	KRNET_API 			isp;
	char				buf[16];
	ulong				networkv, broadcastv;

	if ( ! PyArg_ParseTuple (args, "ls|O", (long *) &db, &host, &err) )
		return NULL;
	argc = PyTuple_Size (args);

	if ( err != NULL ) {
		if ( ! PyList_Check (err) ) {
			PyErr_SetString (ErrorObject, "3th argument is must PyLis");
			return NULL;
		}
	}

	SAFECPY_256 (isp.ip, host);
	isp.verbose = db->verbose;

	if ( kr_search (&isp, db) ) {
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
	long2ip_r (isp.start, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "start", prop);
	Py_DECREF (prop);
	long2ip_r (isp.end, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "end", prop);
	Py_DECREF (prop);
	long2ip_r (isp.netmask, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "netmask", prop);
	Py_DECREF (prop);
	long2ip_r (networkv, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "network", prop);
	Py_DECREF (prop);
	long2ip_r (broadcastv, buf);
	prop = Py_BuildValue ("s", buf);
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

#if PY_MAJOR_VERSION >= 3
	new = _PyNamespace_New (class_dict);
#else
	if ( ret == NULL )
		ret = PyClass_New(NULL, PyDict_New(), PyString_FromString("KRNET_API"));

	new = PyInstance_NewRaw(ret, class_dict);
#endif
	Py_DECREF (class_dict);

	return new;
} // }}}

static PyObject * py_search_ex (PyObject * self, PyObject * args) { // {{{
#if PY_MAJOR_VERSION < 3
	static PyObject *	ret = NULL;
#endif
	PyObject *			new = NULL;
	PyObject *			class_dict;
	PyObject *			prop;
	PyObject *			err = NULL;
	char *				host;
	char *				table;
	int					argc;

	KR_API *			dbh;
	KRNET_API_EX		isp;
	char				buf[16];
	ulong				netmask, networkv, broadcastv;

	if ( ! PyArg_ParseTuple (args, "lss|O", (long *) &dbh, &host, &table, &err) )
		return NULL;
	argc = PyTuple_Size (args);

	if ( err != NULL ) {
		if ( ! PyList_Check (err) ) {
			PyErr_SetString (ErrorObject, "3th argument is must PyList");
			return NULL;
		}
	}

	SAFECPY_256 (isp.ip, host);
	dbh->table = table;
	isp.verbose = dbh->verbose;

	if ( kr_search_ex (&isp, dbh) ) {
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
	long2ip_r (isp.start, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "start", prop);
	Py_DECREF (prop);
	long2ip_r (isp.end, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "end", prop);
	Py_DECREF (prop);
	long2ip_r (netmask, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "netmask", prop);
	Py_DECREF (prop);
	long2ip_r (networkv, buf);
	prop = Py_BuildValue ("s", buf);
	PyDict_SetItemString (class_dict, "network", prop);
	Py_DECREF (prop);
	long2ip_r (broadcastv, buf);
	prop = Py_BuildValue ("s", buf);
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

#if PY_MAJOR_VERSION >= 3
	new = _PyNamespace_New (class_dict);
#else
	if ( ret == NULL )
		ret = PyClass_New(NULL, PyDict_New(), PyString_FromString("KRNET_API"));

	new = PyInstance_NewRaw(ret, class_dict);
#endif
	Py_DECREF (class_dict);

	return new;
} // }}}

static PyObject * py_close (PyObject * self, PyObject * args) { // {{{
	KR_API *	db;

	if ( ! PyArg_ParseTuple (args, "l", (long *) &db) )
		return NULL;

	kr_close (&db);
	db = NULL;

	return Py_None;
} // }}}

static PyObject * py_set_mtime_interval (PyObject * self, PyObject * args) { // {{{
	int			interval;
	KR_API *	db;

	if ( ! PyArg_ParseTuple (args, "li", (long *) &db, &interval) )
		return (PyObject *) NULL;

	db->db_time_stamp_interval = interval;

	return Py_BuildValue ("");
} // }}}

static PyObject * py_set_debug (PyObject * self, PyObject * args) { // {{{
	int			switches;
	KR_API *	db;

	if ( ! PyArg_ParseTuple (args, "li", (long *) &db, &switches) )
		return (PyObject *) NULL;

	db->verbose = switches;
	return Py_BuildValue ("");
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
	{ "set_mtime_interval",	py_set_mtime_interval,	METH_VARARGS },
	{ "set_debug",		py_set_debug,		METH_VARARGS },
	{ NULL, NULL }
}; // }}}

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef krisp_moduledef = { // {{{
	PyModuleDef_HEAD_INIT,
	"krisp",
	"detect IPv4 Geo data",
	-1,
	krisp_methods,
	NULL,
	NULL,
	NULL,
	NULL
}; // }}}
#endif

MOD_INIT(krisp) { // {{{
	PyObject *	m;

#if PY_MAJOR_VERSION >= 3
	m = PyModule_Create (&krisp_moduledef);
#else
	m = Py_InitModule ("krisp", krisp_methods);
#endif

	if ( m == NULL )
		return MOD_ERROR_VAL;

	PyModule_AddStringConstant (m, "__version__", MOD_KRISP_VERSION);
	ErrorObject = Py_BuildValue ("s", "krisp initialize error");

	return MOD_SUCCESS_VAL(m);
} // }}}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
