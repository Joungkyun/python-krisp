# $Id: Makefile,v 1.5 2010-09-10 19:14:16 oops Exp $

PYTHON = /usr/bin/python

all: build

build: krisp.c version.h
	$(PYTHON) setup.py build

intall:
	$(PYTHON) setup.py install

clean:
	-rm -rf build *.pyc
