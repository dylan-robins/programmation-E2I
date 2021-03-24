#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
from datetime import datetime

def search_dir(output_file, cwd, h_level=2):
    
    for i, item in enumerate(sorted(os.listdir(cwd))):
        path = os.path.join(cwd, item)
        # if item is a directory, descend into it and list it's contents
        if os.path.isdir(path):
            output_file.write('#' * h_level + f" {i+1}. {item}\n\n")
            search_dir(output_file, path, h_level + 1)
            
        elif os.path.isfile(path) and os.path.splitext(path)[-1] == ".py":
            output_file.write('#' * h_level + f" {i+1}. {item}\n\n")
            output_file.write("```python\n")
            with open(path, 'r') as py_file:
                output_file.write(py_file.read() + "\n")
            output_file.write("```\n\n")


with open("python_programs.md", "w") as md_file:
    md_file.write(
        f"# Programmes Python\n"
        f"\n"
        f"Dylan Robins - E2I4 - {datetime.now().date().isoformat()}\n"
        f"\n"
    )
    search_dir(md_file, '.')