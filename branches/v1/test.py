#!/usr/bin/python

# $Id: test.py,v 1.1.1.1 2008-04-30 14:34:15 oops Exp $

import krisp
import sys

z = krisp.uversion();
print "libkrisp version: ", z;

p = krisp.krisp_open('/usr/share/krisp/krisp.dat', 1)

if not p :
	print krisp.kerror ()
	sys.exit (1)

print krisp.krisp_search (p, '168.126.63.1');
krisp.krisp_close (p)

sys.exit (0)
