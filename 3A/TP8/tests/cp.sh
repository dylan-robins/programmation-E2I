#/usr/bin/bash
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "Testing my_cp: "

###################################
########## failure tests ##########
###################################

# test bad args
output=`./bin/my_cp 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

output=`./bin/my_cp ./exemples/exemple1 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

# test bad source
output=`./bin/my_cp ./exemples/doesntExit.jpg ./tests 2>&1`
if [ $? -ne 3 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 3
fi
output=`./bin/my_cp ./exemples/ ./tests 2>&1`
if [ $? -ne 4 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 4
fi

# test bad target
output=`./bin/my_cp ./exemples/exemple1 ./exemples/exemple2 ./tests/doesntExist/ 2>&1`
if [ $? -ne 5 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 2
fi
output=`./bin/my_cp ./exemples/exemple1 ./exemples/exemple2 ./exemples/test.txt 2>&1`
if [ $? -ne 5 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 5
fi

###################################
########## Passing tests ##########
###################################

# test copy one file to empty directory
output=`./bin/my_cp ./exemples/exemple1 ./tests/emptyDir 2>&1`
if [ $? -ne 0  ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi
output=`cmp --silent ./exemples/exemple1 ./tests/emptyDir/exemple1`
if [ $? -ne 0 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 11
fi

# clean directory
rm -f ./tests/emptyDir/*

# test copy 8 files to empty directory
output=`./bin/my_cp ./exemples/exemple* ./tests/emptyDir 2>&1`
if [ $? -ne 0  ]
then
    printf "${RED}FAIL${NC}\n"
    exit 20
fi
for file in ./exemples/exemple*
do
    src=./exemples/`basename $file`
    target=./tests/emptyDir/`basename $file`
    output=`cmp --silent $src $target`
    if [ $? -ne 0 ]
    then
        printf "${RED}FAIL${NC}\n"
        exit 21
    fi
done
#rm -f ./tests/emptyDir/*

# test overwrite file in directory
output=`./bin/my_cp ./exemples/exemple1 ./tests/emptyDir/exemple1 2>&1`
if [ $? -ne 0  ]
then
    printf "${RED}FAIL${NC}\n"
    exit 30
fi
output=`cmp --silent ./exemples/exemple1 ./tests/emptyDir/exemple1`
if [ $? -ne 0 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 31
fi

# clean directory
rm -f ./tests/emptyDir/*



printf "${GREEN}PASS${NC}\n"