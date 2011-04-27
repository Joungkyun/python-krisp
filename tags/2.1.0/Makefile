# $Id: Makefile,v 1.6 2010-09-10 19:15:24 oops Exp $

PYTHON = /usr/bin/python

all: build

build: krisp.c version.h
	$(PYTHON) setup.py build

intall:
	$(PYTHON) setup.py install

clean:
	-rm -rf build *.pyc

test:
	$(PYTHON) test.py
