#!/usr/bin/env python
# -*- coding: utf-8 -*-

def cprint(text, color):
    cols = {
        "rst": '\033[0m',
        "cyan": '\033[36m',
        "blue": '\033[34m',
        "red": '\033[91m'
    }
    print(cols[color] + str(text) + cols["rst"])