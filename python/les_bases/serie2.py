#!/usr/bin/env python
# -*- coding: utf-8 -*-
def t_or_f():
    user_data = input("Enter t or f: >>> ")
    if user_data == "t":
        print("True")
    elif user_data == "f":
        print("False")
    else:
        print("Invalid input", user_data)

def quadrant(x, y):
    if x > 0:
        if y > 0:
            print("North east")
        elif y < 0:
            print("South east")
        else:
            print("East")
    elif x < 0:
        if y > 0:
            print("North west")
        elif y < 0:
            print("South west")
        else:
            print("West")
    else:
        if y > 0:
            print("North")
        elif y < 0:
            print("South")
        else:
            print("Center")

def time_in_1s(h, m, s):
    if s < 59:
        s += 1
    elif m < 59:
        s = 0
        m += 1
    elif h < 23:
        s = 0
        m = 0
        h += 1
    else:
        s = 0
        m = 0
        h = 0
    print(f"In one second it'll be {h}:{m}:{s}")

def average():
    grades = []
    user_data = 0
    while 0 <= float(user_data) <= 20:
        user_data = input("Enter a grade: >>> ")
        try:
            grades.append(float(user_data))
        except ValueError:
            break
    mean = 0
    for grade in grades:
        mean += grade
    mean = mean / len(grades)
    print("Average grade:", mean)

def disp_range(a, b):
    for i in range(a, b+1):
        print(i, end=", ")
    for i in range(b, a-1, -1):
        print(i, end=", ")
    print("")

if __name__ == "__main__":
    print("Test t_or_f... ")
    t_or_f()
    t_or_f()
    t_or_f()
    t_or_f()
    
    print("Test quadrant... ")
    quadrant(2, -5)

    print("Test time_in_1s... ")
    time_in_1s(22, 8, 59)

    print("Test average... ")
    average()

    print("Test disp_range... ")
    disp_range(3, 9)