#!/usr/bin/python
# -*- coding: utf-8 -*-

# $Id: test.py,v 1.8 2010-09-10 20:24:16 oops Exp $

import sys
import os
import pickle

try:
	import krisp
except ImportError:
	sys.path.append (os.getcwd() + '/build/lib.linux-i686-2.5')
	import krisp

print "krisp module version  : %s" % krisp.mod_version ()
print "krisp module uversion : %s" % krisp.mod_uversion ()
print "libkrisp version      : %s" % krisp.version ()
print "libkrisp uversion     : %s" % krisp.uversion ()

err = [];
p = krisp.open ('/usr/share/krisp/krisp.dat', err)

if ( p == None ) :
	print "Error: %s" % err[0]
	sys.exit (1)

krisp.set_mtime_interval (p, 0);
#krisp.set_debug (p, 1)

print
print '** SEARCH test'
print

search_host = [ 'cnn.com', 'kornet.net', 'google.com' ]

for host in search_host :
	# init error message variable
	print '%-10s : ' % host,

	err = []
	r = krisp.search (p, host, err)
	if not r :
		print err[0]
		continue

	# return member
	# { ip, start, end, netmask, network, broadcast, icode, iname , ccode, cname }
	print '%s(%15s) [%15s - %-15s] %2s %s' % (krisp.ip2long (r.ip), r.ip, r.start, r.end, r.ccode, r.icode)

	del r
	del err


print
print '** SEARCH_EX test'
print

for host in search_host :
	print '%-10s : ' % host,

	err = []
	r = krisp.search_ex (p, host, 'krisp', err)
	if ( r == None ) :
		print err[0]
		continue

	print '%lu(%15s) [%15s - %-15s] %2s %s' % (krisp.ip2long (r.ip), r.ip, r.start, r.end, r.dummy[0], r.dummy[2])
#
#	del r
#	del err

krisp.close (p)

ip = '192.168.0.1'
long = krisp.ip2long (ip)
print
print 'IP -> LONG : %s -> %u' % (ip, long)
print 'LONG -> IP : %u -> %s' % (long, krisp.long2ip (long))

start = '192.168.10.51'
end   = '192.168.10.121'
mask  = krisp.netmask (start, end)
prefix = krisp.mask2prefix (mask)
print 'RANGE      : %s - %s => mask %s (/%d)' % (start, end, mask, prefix)
print '             network  : %s' % krisp.network (start, mask)
print '             broadcast: %s' % krisp.broadcast (start, mask)

sys.exit (0)
