#!/usr/bin/python
# -*- coding: utf-8 -*-

# $Id: test.py,v 1.3 2010-06-20 06:09:44 oops Exp $

import sys
import os
import pickle

try:
	import krisp
except ImportError:
	sys.path.append (os.getcwd() + '/build/lib.linux-i686-2.5');
	import krisp

print "krisp module version  : %s" % krisp.modversion ()
print "krisp module uversion : %s" % krisp.moduversion ()
print "libkrisp version      : %s" % krisp.version ()
print "libkrisp uversion     : %s" % krisp.uversion ()

p = krisp.open ('/usr/share/krisp/krisp.dat')

if not p :
	sys.exit (1)

print
print '** SEARCH test'
print

search_host = [ 'cnn.com', 'kornet.net', 'google.com' ]

for host in search_host :
	# init error message variable
	err = []
	print '%-10s : ' % host,

	r = krisp.search (p, host, err);
	if not r :
		print err[0]
		continue

	# return member
	# { ip, start, end, netmask, network, broadcast, icode, iname , ccode, cname }
	print '%s(%15s) [%15s - %-15s] %2s %s' % (krisp.ip2long (r.ip), r.ip, r.start, r.end, r.ccode, r.icode)

	del r


print
print '** SEARCH_EX test'
print

for host in search_host :
	err = [];
	print '%-10s : ' % host,

	r = krisp.search_ex (p, host, 'krisp', err);
	if not r :
		print err[0]
		continue

	print '%s(%15s) [%15s - %-15s] %2s %s' % (krisp.ip2long (r.ip), r.ip, r.start, r.end, r.dummy[0], r.dummy[2])

	del r

krisp.close (p)

ip = '192.168.0.1'
long = krisp.ip2long (ip)
print
print 'IP -> LONG : %s -> %u' % (ip, long)
print 'LONG -> IP : %u -> %s' % (long, krisp.long2ip (long))

start = '192.168.10.51'
end   = '192.168.10.121'
mask  = krisp.netmask (krisp.ip2long (start), krisp.ip2long (end));
prefix = krisp.long2prefix (mask);
print 'RANGE      : %s - %s => mask %s (/%d)' % (start, end, krisp.long2ip (mask), prefix)
print '             network  : %s' % krisp.long2ip (krisp.network (krisp.ip2long (start), mask));
print '             broadcast: %s' % krisp.long2ip (krisp.broadcast (krisp.ip2long (start), mask));

sys.exit (0)
