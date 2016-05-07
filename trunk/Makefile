# $Id$

PYTHON = /usr/bin/python
NAME = mod_krisp
PROG = krisp


DIST_FILES = COPYING Changes README

all: build

build: krisp.c version.h
	$(PYTHON) setup.py build

install:
	$(PYTHON) setup.py install

clean:
	-rm -rf build *.pyc *.bz2

test:
	$(PYTHON) test.py

dist:
	version=`cat version.h | grep MOD_KRISP_VERSION | awk '{print $$3}' | sed 's/"//g'`; \
	mkdir -p krisp-$$version; \
	cp -af $(DIST_FILES) Makefile *.c *.h *.py krisp-$$version/; \
	tar cvfpj krisp-$$version.tar.bz2 krisp-$$version; \
	rm -fr krisp-$$version
