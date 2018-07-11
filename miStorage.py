#!/usr/local/bin/python -i

import sys,os
from ROOT import *
ROOT.gSystem.Load("./iStorage.so")

# os._exit(0)
cosa = TFile("test.root","recreate")
test = iStorage("test")
print "iStorage \"test\" created... try \"test.help()\""
test.Write()
cosa.Close()
