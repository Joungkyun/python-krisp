# $Id: Makefile,v 1.3 2010-09-10 19:11:45 oops Exp $

PYTHON=/usr/bin/python

all: krisp.c
	$(PYTHON) setup.py build

intall:
	$(PYTHON) setup.py install
