#!/usr/bin/env python
# -*- coding: utf-8 -*-

def longest_word(ch):
    # split le string into words
    words = ch.split()
    # sort the words by length in descending order
    words.sort(key=len, reverse=True)
    # return the longest word
    return words[0]

if __name__ == "__main__":
    ch = input("Entrez une phrase :\n>>> ")
    print("Mot le plus long:", longest_word(ch))
    print("Longueur du mot le plus long:", len(longest_word(ch)))
    