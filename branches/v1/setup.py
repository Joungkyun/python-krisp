#!/usr/bin/python

# $Id: setup.py,v 1.1.1.1 2008-04-30 14:34:15 oops Exp $

from distutils.core import setup, Extension
import os
import re
import string

incdir = []
libdir = []
libs   = []
defs   = []

krisp_env = (os.popen ('krisp-config --libs')).read ()
envlist   = string.split (krisp_env)

for arg in envlist :
	if arg[1] == 'L' :
		libdir.append (arg[2:])
	elif arg[1] == 'l' :
		libs.append (arg[2:])

		if re.match ('^GeoIP', arg[2:]) :
			defs.append (('HAVE_LIBGEOIP', '1'))
		elif re.match ('^sqlite3', arg[2:]) :
			defs.append (('HAVE_LIBSQLITE3', '1'))
	elif arg[1] == 'I' :
		incdir.append (arg[2:])

setup (
		name         = 'krisp',
		version      = '1.0.0',
		description  = 'python binding for libkrisp API',
		author       = 'JoungKyun.Kim',
		author_email = 'admin@oops.org',
		url          = 'http://oops.org',
		license      = 'GPL v2',
		platforms    = 'x86/x86_64',
		py_modules   = [ 'krisp' ],
		ext_modules  = [
			Extension (
						'_krisp',
						['krisp.c', 'krisp_wrap.c'],
						include_dirs  = incdir,
						library_dirs  = libdir,
						libraries     = libs,
						define_macros = defs
					)
		]
)