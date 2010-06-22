PYTHON = /usr/bin/python

all: build

build: krisp.c krisp_wrap.c krisp.i
	$(PYTHON) setup.py build

swig:
	swig -python krisp.i
	perl -pi -e 's/^k([^=]+)/$$1/g' krisp.py
	cat krisp.py | grep -v '^\(search\|free_search\)' > edit.py
	cat edit.py addon.py.sample > krisp.py
	rm -f edit.py

install:
	$(PYTHON) setup.py install

clean:
	rm -rf build *.pyc
