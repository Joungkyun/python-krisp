#!/usr/bin/python

from distutils.core import setup, Extension
import os
import re
import string

incdir = []
libdir = []
libs   = [ 'krisp' ]
defs   = []

krisp_env = (os.popen ('krisp-config --libs')).read () + ' ' + \
			(os.popen ('krisp-config --includes')).read ()
envlist   = krisp_env.split ()

for arg in envlist :
	if arg[1] == 'L' :
		libdir.append (arg[2:])
	elif arg[1] == 'I' :
		incdir.append (arg[2:])
	elif arg[1] == 'D' :
		defs.append ((arg[2:], None))

del envlist

setup (
		name         = 'krisp',
		version      = '2.0.2',
		description  = 'python binding for libkrisp API',
		author       = 'JoungKyun.Kim',
		author_email = 'joungkyun@gmail.com',
		url          = 'http://github.com/Joungkyun/python-krisp',
		license      = 'LGPL',
		platforms    = 'x86/x86_64',
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
