# $Id: Makefile,v 1.6 2010-09-10 19:15:24 oops Exp $

PYTHON = /usr/bin/python
NAME = mod_krisp
PROG = krisp


DIST_FILES = COPYING Changes README

all: install

build: krisp.c version.h
	$(PYTHON) setup.py build

intall:
	$(PYTHON) setup.py install

clean:
	-rm -rf build *.pyc *.bz2

test:
	$(PYTHON) test.py

dist:
	version=`cat version.h | grep MOD_VERSION | awk '{print $$3}' | sed 's/"//g'`; \
	mkdir -p $(NAME)-$$version; \
	cp -af $(DIST_FILES) Makefile *.c *.h *.py $(NAME)-$$version/; \
	tar cvfpj $(NAME)-$$version.tar.bz2 $(NAME)-$$version; \
	rm -fr $(NAME)-$$version
