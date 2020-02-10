#/usr/bin/bash
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "Testing my_wc: "

###################################
########## failure tests ##########
###################################

# test bad args
output=`./bin/my_wc 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

output=`./bin/my_wc ./exemples/exemple1 ./exemples/exemple2 ./exemples/exemple3 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

# test bad source
output=`./bin/my_wc ./exemples/doesntExit.jpg 2>&1`
if [ $? -ne 2 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 2
fi

# test bad mode
output=`./bin/my_wc a ./exemples/test.txt 2>&1`
if [ $? -ne 3 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 3
fi

###################################
########## Passing tests ##########
###################################

# test number of words
output=`./bin/my_wc w ./exemples/test.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of words: 4" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi
output=`./bin/my_wc w ./exemples/lorem.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of words: 394" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 11
fi

# test number of characters
output=`./bin/my_wc c ./exemples/test.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of characters: 20" ]
then
    printf "${RED}FAIL${NC}\n"
    echo $output
    exit 20
fi
output=`./bin/my_wc c ./exemples/lorem.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of characters: 2729" ]
then
    printf "${RED}FAIL${NC}\n"
    echo $output
    exit 21
fi

# test number of lines
output=`./bin/my_wc l ./exemples/test.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of lines: 1" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 30
fi
output=`./bin/my_wc l ./exemples/lorem.txt 2>&1`
if [ $? -ne 0 ] || [ "$output" != "Number of lines: 34" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 31
fi

printf "${GREEN}PASS${NC}\n"