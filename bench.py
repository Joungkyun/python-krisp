#!/usr/bin/python
# -*- coding: utf-8 -*-

# $Id$

import sys
import os
import random
import time

try:
	import krisp
except ImportError:
	osinfo = os.uname ()
	sys.path.append (
		os.getcwd () +
		'/build/lib.' +
		osinfo[0].lower() + '-' +
		osinfo[4] + '-' +
		str (sys.version_info[0]) + '.' +
		str(sys.version_info[1])
	)
	import krisp

def microtime (get_as_float = 0) :
	if ( get_as_float ) :
		return time.time()
	else :
		r = re.split ('\.', repr (time.time ()))
		return r[1] + ' ' + r[0]

def random_ip () :
	return random.randrange (16777216, 4294967296)

argc = len (sys.argv)

if ( argc is not 2 or sys.argv[1] is '-h' ) :
	print "Usage: %s query_limit" % sys.argv[0]

err = [];
p = krisp.open ('', err)
print sys.argv[1]

t1 = microtime (1)
for i in range (0, int (sys.argv[1]), 1) :
	host = krisp.long2ip (random_ip ())
	err = []
	r = krisp.search (p, host, err)
	del host
	del r
t2 = microtime (1)

krisp.close (p)

print "Execute Time: %.2f sec" % (t2 - t1)

sys.exit (0)
