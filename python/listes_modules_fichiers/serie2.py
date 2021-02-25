#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import os

def python_info():
    print("OS:", sys.platform)
    print("Interpreter path:", sys.executable)
    print("Python Version:", sys.version)

def listing(cwd='.', levels=0):
    # print wrapper that intents everything
    def iprint(*args):
        print("    "*levels, *args, sep="")
    
    for item in os.listdir(cwd):
        path = os.path.join(cwd, item)
        # if item is a directory, descend into it and list it's contents
        if os.path.isdir(path):
            iprint(item+"/")
            listing(path, levels+1)
        elif os.path.isfile(path):
            iprint(item)

if __name__ == "__main__":
    print("Python Info:")
    python_info()

    print("Directory listing:")
    listing('..')

