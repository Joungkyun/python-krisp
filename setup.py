#!/usr/bin/python

# $Id: setup.py,v 1.5 2010-08-02 18:32:19 oops Exp $

from distutils.core import setup, Extension
import os
import re
import string

incdir = []
libdir = []
libs   = [ 'krisp' ]
defs   = []

krisp_env = (os.popen ('krisp-config --libs')).read () + ' ' + \
			(os.popen ('krisp-config --defs')).read ()
envlist   = string.split (krisp_env)

for arg in envlist :
	if arg[1] == 'L' :
		libdir.append (arg[2:])
	elif arg[1] == 'I' :
		incdir.append (arg[2:])
	elif arg[1] == 'D' :
		defs.append ((arg[2:], None))


setup (
		name         = 'krisp',
		version      = '2.0.1',
		description  = 'python binding for libkrisp API',
		author       = 'JoungKyun.Kim',
		author_email = 'admin@oops.org',
		url          = 'http://oops.org',
		license      = 'GPL v2',
		platforms    = 'x86/x86_64',
		#py_modules   = [ 'krisp' ],
		ext_modules  = [
			Extension (
						'krisp',
						['krisp.c' ],
						include_dirs  = incdir,
						library_dirs  = libdir,
						libraries     = libs,
						define_macros = defs
					)
		]
)
