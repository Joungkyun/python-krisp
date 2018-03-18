PYTHON = /usr/bin/python
NAME = mod_krisp
PROG = krisp
ARCH = $(shell uname -m)


DIST_FILES = COPYING Changes README.md

all: build

build: krisp.c version.h
	$(PYTHON) setup.py build

install:
	$(PYTHON) setup.py install

clean:
	-rm -rf build *.pyc *.bz2 MANIFEST krisp.egg-info

distclean: clean
	-rm -rf dist

test: build
	$(PYTHON) test.py

dist:
	$(PYTHON) setup.py sdist --formats=bztar
#	version=`cat version.h | grep MOD_KRISP_VERSION | awk '{print $$3}' | sed 's/"//g'`; \
#	mkdir -p krisp-$$version; \
#	cp -af $(DIST_FILES) Makefile *.c *.h *.py krisp-$$version/; \
#	tar cvfpj krisp-$$version.tar.bz2 krisp-$$version; \
#	rm -fr krisp-$$version

bdist:
	$(PYTHON) setup.py bdist_wheel --plat-name manylinux1_$(ARCH)
