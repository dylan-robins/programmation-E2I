#!/usr/bin/env bash

for script in *.py
do
    echo "### Running $script..."
    
    testfile="input/`basename $script .py`.test"
    python3 $script test < $testfile
    
    printf '_%.0s' {1..100}
    echo ""
done