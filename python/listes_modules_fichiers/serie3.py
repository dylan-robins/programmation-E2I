#!/usr/bin/env python
# -*- coding: utf-8 -*-
from sys import argv

def reverse_file(ifile):
    for line in ifile:
        line = line.rstrip('\n')
        yield line[::-1] + '\n'

def safe_int(data):
    try:
        return int(data)
    except (ValueError, TypeError):
        print(f"Error: '{data}' couldn't be parsed as an integer.")

months = [
    "janvier",
    "février",
    "mars",
    "avril",
    "mai",
    "juin",
    "juillet",
    "août",
    "septembre",
    "octobre",
    "novembre",
    "décembre"
]

def parse_flight_line(line, month):
    # Make sure that line is valid before parsing it
    split_line = [safe_int(num) for num in line.split()]
    if len(split_line) != 9:
        print("Syntax error in line")
        print("> ", line)
        raise SyntaxError

    data = {
        "flight_number" : split_line[0],
        "departure" : f"{split_line[1]:02} {months[month]:9} à {split_line[3]:02}:{split_line[4]:02}",
        "nb_seats" : split_line[7],
        "nb_passagers" : split_line[8]
    }
    # if we arrive "before" we leave, increment the month for the arrival
    if split_line[2] < split_line[1]:
        data["arrival"] = f"{split_line[2]:02} {months[(month+1)%13]:9} à {split_line[5]:02}:{split_line[6]:02}"
    else:
        data["arrival"] = f"{split_line[2]:02} {months[month]:9} à {split_line[5]:02}:{split_line[6]:02}"
    return data

def nb_passengers(flight_file):
    total_passagers = 0
    # ensure we're at the start of the file
    flight_file.seek(0, 0)
    # read the month
    month = flight_file.readline().rstrip('\n')
    try:
        month = months.index(month)
    except ValueError:
        print(f"Error: '{month}' is not a month")
        raise
    # read all following flight records from file
    for line in flight_file:
        parsed_line = parse_flight_line(line, month)
        total_passagers += parsed_line["nb_passagers"]
    return total_passagers

def humanize_flight_records(flight_file):
    # ensure we're at the start of the file
    flight_file.seek(0, 0)
    # read the month
    month = flight_file.readline().rstrip('\n')
    try:
        month = months.index(month)
    except ValueError:
        print(f"Error: '{month}' is not a month")
        raise
    # read all following flight records from file
    for line in flight_file:
        parsed_line = parse_flight_line(line, month)
        print("Numéro du vol :", parsed_line["flight_number"])
        print("Départ le     :", parsed_line["departure"])
        print("Arrivée le    :", parsed_line["arrival"])

if __name__ == "__main__":
    if len(argv) != 3:
        print(f"Usage: {argv[0]} file_to_reverse flight_file")
        exit(1)
    
    to_mirror = argv[1]
    with open(to_mirror, 'r') as ifile, open(to_mirror+".mirrored", "w") as ofile:
        ofile.writelines(reverse_file(ifile))

    flight_log = argv[2]
    with open(flight_log, "r") as ifile:
        print("Number of passengers :", nb_passengers(ifile))
        humanize_flight_records(ifile)
    