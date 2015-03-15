#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os
import urllib

CATCH_URL = 'https://raw.github.com/philsquared/Catch/master/single_include/catch.hpp'
CURR_PATH = os.path.abspath(os.path.dirname(__file__))
DEST_PATH = os.path.join(CURR_PATH, 'test', 'catch.hpp')

if __name__ == '__main__':
    urllib.urlretrieve(CATCH_URL, DEST_PATH)
