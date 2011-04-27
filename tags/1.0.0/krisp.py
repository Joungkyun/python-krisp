#!/usr/bin/python

# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _krisp
import re

keys = [ 'key', 'ip', 'netmask', 'network', 'broadcast', 'icode', 'iname', 'ccode', 'cname', 'city', 'region' ]

def krisp_search (dp, host) :
	v = _krisp.krisp_search (dp, host)
	l = re.split (':', v)
	r = {}

	i = 0
	for key in keys :
		r[key] = l[i]
		i += 1

	return r;

new_intp = _krisp.new_intp
copy_intp = _krisp.copy_intp
delete_intp = _krisp.delete_intp
intp_assign = _krisp.intp_assign
intp_value = _krisp.intp_value
version = _krisp.version
uversion = _krisp.uversion
kerror = _krisp.kerror
krisp_open = _krisp.krisp_open
krisp_close = _krisp.krisp_close

cvar = _krisp.cvar

