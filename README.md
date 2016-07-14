KRISP python extension v2
===


## DESCRIPTION

This is python extension that is libkrisp python frontend.
This modules is thread safe.


## INSTALLATION

To install this extension type the following:

```bash
[root@host python-krisp]$ make install
```

***Build options:***

```bash
[root@host python-krisp]$ # only build
[root@host python-krisp]$ make build
[root@host python-krisp]$ # test module
[root@host python-krisp]$ make test
[root@host python-krisp]$ # clean built objects
[root@host python-krisp]$ make clean
[root@host python-krisp]$ # package this source
[root@host python-krisp]$ make dist
```

If your python path is not /usr/bin/python:

```bash
[root@host python-krisp]$ make install PYTHON=/opt/python3/bin/python3
```

## DEPENDENCIES

This module requires these libraries:

[libkrisp](https://github.com/Joungkyun/libkrisp) 3.1 or after.

If you use libkrisp 3.0 or before, use v1 branch. Head branch is
required 3.1 or after.


## COPYRIGHT AND LICENCE

Copyright (C) 2016 by JoungKyun.Kim &lt;http://oops.org&gt;

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as published by
the Free Software Foundation; either version 2 of the License.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE. See the GNU LESSER GENERAL PUBLIC
LICENSE for more details.

You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
