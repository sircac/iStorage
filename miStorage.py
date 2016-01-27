#!/usr/local/bin/python -i

import sys,os
from ROOT import *
ROOT.gSystem.Load("./iStorage.so")

# os._exit(0)
test = iStorage("test")
print "iStorage \"test\" created... try \"test.help()\""
