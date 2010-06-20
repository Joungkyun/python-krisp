# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _krisp
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


class KRNET_API(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KRNET_API, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KRNET_API, name)
    __repr__ = _swig_repr
    __swig_setmethods__["verbose"] = _krisp.KRNET_API_verbose_set
    __swig_getmethods__["verbose"] = _krisp.KRNET_API_verbose_get
    if _newclass:verbose = property(_krisp.KRNET_API_verbose_get, _krisp.KRNET_API_verbose_set)
    __swig_setmethods__["ip"] = _krisp.KRNET_API_ip_set
    __swig_getmethods__["ip"] = _krisp.KRNET_API_ip_get
    if _newclass:ip = property(_krisp.KRNET_API_ip_get, _krisp.KRNET_API_ip_set)
    __swig_setmethods__["netmask"] = _krisp.KRNET_API_netmask_set
    __swig_getmethods__["netmask"] = _krisp.KRNET_API_netmask_get
    if _newclass:netmask = property(_krisp.KRNET_API_netmask_get, _krisp.KRNET_API_netmask_set)
    __swig_setmethods__["start"] = _krisp.KRNET_API_start_set
    __swig_getmethods__["start"] = _krisp.KRNET_API_start_get
    if _newclass:start = property(_krisp.KRNET_API_start_get, _krisp.KRNET_API_start_set)
    __swig_setmethods__["end"] = _krisp.KRNET_API_end_set
    __swig_getmethods__["end"] = _krisp.KRNET_API_end_get
    if _newclass:end = property(_krisp.KRNET_API_end_get, _krisp.KRNET_API_end_set)
    __swig_setmethods__["icode"] = _krisp.KRNET_API_icode_set
    __swig_getmethods__["icode"] = _krisp.KRNET_API_icode_get
    if _newclass:icode = property(_krisp.KRNET_API_icode_get, _krisp.KRNET_API_icode_set)
    __swig_setmethods__["iname"] = _krisp.KRNET_API_iname_set
    __swig_getmethods__["iname"] = _krisp.KRNET_API_iname_get
    if _newclass:iname = property(_krisp.KRNET_API_iname_get, _krisp.KRNET_API_iname_set)
    __swig_setmethods__["ccode"] = _krisp.KRNET_API_ccode_set
    __swig_getmethods__["ccode"] = _krisp.KRNET_API_ccode_get
    if _newclass:ccode = property(_krisp.KRNET_API_ccode_get, _krisp.KRNET_API_ccode_set)
    __swig_setmethods__["cname"] = _krisp.KRNET_API_cname_set
    __swig_getmethods__["cname"] = _krisp.KRNET_API_cname_get
    if _newclass:cname = property(_krisp.KRNET_API_cname_get, _krisp.KRNET_API_cname_set)
    def __init__(self, *args): 
        this = _krisp.new_KRNET_API(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _krisp.delete_KRNET_API
    __del__ = lambda self : None;
KRNET_API_swigregister = _krisp.KRNET_API_swigregister
KRNET_API_swigregister(KRNET_API)

class KRNET_API_EX(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KRNET_API_EX, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KRNET_API_EX, name)
    __repr__ = _swig_repr
    __swig_setmethods__["verbose"] = _krisp.KRNET_API_EX_verbose_set
    __swig_getmethods__["verbose"] = _krisp.KRNET_API_EX_verbose_get
    if _newclass:verbose = property(_krisp.KRNET_API_EX_verbose_get, _krisp.KRNET_API_EX_verbose_set)
    __swig_setmethods__["ip"] = _krisp.KRNET_API_EX_ip_set
    __swig_getmethods__["ip"] = _krisp.KRNET_API_EX_ip_get
    if _newclass:ip = property(_krisp.KRNET_API_EX_ip_get, _krisp.KRNET_API_EX_ip_set)
    __swig_setmethods__["start"] = _krisp.KRNET_API_EX_start_set
    __swig_getmethods__["start"] = _krisp.KRNET_API_EX_start_get
    if _newclass:start = property(_krisp.KRNET_API_EX_start_get, _krisp.KRNET_API_EX_start_set)
    __swig_setmethods__["end"] = _krisp.KRNET_API_EX_end_set
    __swig_getmethods__["end"] = _krisp.KRNET_API_EX_end_get
    if _newclass:end = property(_krisp.KRNET_API_EX_end_get, _krisp.KRNET_API_EX_end_set)
    __swig_setmethods__["size"] = _krisp.KRNET_API_EX_size_set
    __swig_getmethods__["size"] = _krisp.KRNET_API_EX_size_get
    if _newclass:size = property(_krisp.KRNET_API_EX_size_get, _krisp.KRNET_API_EX_size_set)
    __swig_setmethods__["dummy"] = _krisp.KRNET_API_EX_dummy_set
    __swig_getmethods__["dummy"] = _krisp.KRNET_API_EX_dummy_get
    if _newclass:dummy = property(_krisp.KRNET_API_EX_dummy_get, _krisp.KRNET_API_EX_dummy_set)
    __swig_setmethods__["dummydata"] = _krisp.KRNET_API_EX_dummydata_set
    __swig_getmethods__["dummydata"] = _krisp.KRNET_API_EX_dummydata_get
    if _newclass:dummydata = property(_krisp.KRNET_API_EX_dummydata_get, _krisp.KRNET_API_EX_dummydata_set)
    def __init__(self, *args): 
        this = _krisp.new_KRNET_API_EX(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _krisp.delete_KRNET_API_EX
    __del__ = lambda self : None;
KRNET_API_EX_swigregister = _krisp.KRNET_API_EX_swigregister
KRNET_API_EX_swigregister(KRNET_API_EX)

version = _krisp.version
uversion = _krisp.uversion
open = _krisp.open
close = _krisp.kclose
ip2long = _krisp.kip2long
netmask = _krisp.knetmask
network = _krisp.knetwork
broadcast = _krisp.kbroadcast
prefix2long = _krisp.kprefix2long
long2prefix = _krisp.klong2prefix


def modversion () :
	return '2.0.0'

def moduversion () :
	return '002000000'

def long2ip (longip) :
    ip = [ 0, 0, 0, 0]
    for i in xrange (0, 4) :
        ip[i] = longip % 256
        longip /= 256

    ip.reverse ()
    return '.'.join (map (str, ip))

from copy import deepcopy

class search_skelton :
	pass

keys = [
		'verbose', 'ip', 'netmask', 'start', 'end', 'icode',
		'iname', 'ccode', 'cname'
]

keys_ex = [
		'ip', 'start', 'end', 'size', 'dummydata',
]

def search (db, host, err = []) :
	r = _krisp.search (db, host)
	if ( r == None ) :
		err[0] = deepcopy (r.err)
		return None

	v = search_skelton ()

	for key in keys :
		if key == 'netmask' :
			setattr (v, 'netmask', deepcopy (long2ip (r.netmask)))
			setattr (v, 'network', deepcopy (long2ip (network (r.start, r.netmask))))
			setattr (v, 'broadcast', deepcopy (long2ip (broadcast(r.start, r.netmask))))
		elif key == 'start' :
			setattr (v, key, deepcopy (long2ip(r.start)))
		elif key == 'end' :
			setattr (v, key, deepcopy (long2ip(r.end)))
		else :
			setattr (v, key, deepcopy (getattr(r, key)))


	_krisp.free_search (r);
	return v

import re

def search_ex (db, host, table, err = []) :
	r = _krisp.search_ex (db, host, table)
	if ( r == None ) :
		err[0] = deepcopy (r.err)
		return None

	v = search_skelton ()

	for key in keys_ex :
		if key == 'dummy' or key == 'dummydata' :
			continue

		if key == 'start' or key == 'end' :
			setattr (v, key, long2ip (getattr (r, key)))
		else :
			setattr (v, key, deepcopy (getattr (r, key)))

	mask = netmask (r.start, r.end)
	setattr (v, 'netmask', long2ip (mask));
	setattr (v, 'network', long2ip (network (r.start, mask)));
	setattr (v, 'broadcast', long2ip (broadcast(r.start, mask)));

	ar = re.split (':', r.dummydata)
	setattr (v, 'dummy', deepcopy (ar));
	
	_krisp.free_search_ex (r)

	return v
