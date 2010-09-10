# $Id: Makefile,v 1.4 2010-09-10 19:13:50 oops Exp $

PYTHON = /usr/bin/python

all: build

build: krisp.c version.h
	$(PYTHON) setup.py build

intall:
	$(PYTHON) setup.py install

clean:
	rm -f build *.pyc
