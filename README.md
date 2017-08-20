# wmquincunx

Window Maker dockapp displaying a bean machine

From Wikipedia [1]:

The bean machine, also known as the *quincunx* or *Galton box*, is a device
invented by Sir Francis Galton to demonstrate the central limit theorem, in
particular that the normal distribution is approximate to the binomial
distribution. Among its applications, it afforded insight into regression to
the mean or "regression to mediocrity".

[1] https://en.wikipedia.org/wiki/Bean_machine

## Installation

You will need [libdockapp](http://dockapps.net/libdockapp) to build wmquincunx.

If building from git (not necessary if using a tarball):

	autoreconf -fvi

Then the usual

    ./configure
    make
    sudo make install

## Usage

    wmquincunx [OPTIONS]

### Options
    -h, --help                   show this help text and exit
    -v, --version                show program version and exit
    -w, --windowed               run the application in windowed mode

# Bugs

Please report bugs and feature requests at the
[issues page](https://github.com/d-torrance/wmquincunx/issues).

# Copyright

Copyright (C) 2017 Doug Torrance <dtorrance@piedmont.edu>

License: [GPL-2+](https://www.gnu.org/licenses/gpl-2.0.html)
