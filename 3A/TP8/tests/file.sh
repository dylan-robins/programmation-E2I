#/usr/bin/bash
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "Testing my_file: "

###################################
########## failure tests ##########
###################################

# test bad args
output=`./bin/my_file 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

output=`./bin/my_file ./exemples/exemple1 ./exemples/exemple2 ./exemples/exemple3 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 1
fi

# test bad source
output=`./bin/my_file ./exemples/doesntExit.jpg 2>&1`
if [ $? -ne 3 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 3
fi

# test bad filetype
output=`./bin/my_file ./exemples/exemple1 png 2>&1`
if [ $? -ne 2 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 2
fi

###################################
########## Passing tests ##########
###################################

# test filetype of exemple1
output=`./bin/my_file ./exemples/exemple1 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a JPEG" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi
output=`./bin/my_file ./exemples/exemple1 jpg 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a jpg" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 11
fi
output=`./bin/my_file ./exemples/exemple1 JPG 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a JPG" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 12
fi
output=`./bin/my_file ./exemples/exemple1 jpeg 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a jpeg" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 13
fi
output=`./bin/my_file ./exemples/exemple1 JPEG 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a JPEG" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 14
fi

# test filetype of exemple2
output=`./bin/my_file ./exemples/exemple2 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a GIF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 20
fi
output=`./bin/my_file ./exemples/exemple2 gif 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a gif" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 21
fi
output=`./bin/my_file ./exemples/exemple2 GIF 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a GIF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 22
fi

# test filetype of exemple3
output=`./bin/my_file ./exemples/exemple3 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a RTF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 30
fi
output=`./bin/my_file ./exemples/exemple3 rtf 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a rtf" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 31
fi
output=`./bin/my_file ./exemples/exemple3 RTF 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a RTF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 32
fi

# test filetype of exemple4
output=`./bin/my_file ./exemples/exemple4 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PDF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 40
fi
output=`./bin/my_file ./exemples/exemple4 pdf 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a pdf" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 41
fi
output=`./bin/my_file ./exemples/exemple4 PDF 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PDF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 42
fi

# test filetype of exemple5
output=`./bin/my_file ./exemples/exemple5 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a GIF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 50
fi
output=`./bin/my_file ./exemples/exemple5 gif 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a gif" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 51
fi
output=`./bin/my_file ./exemples/exemple5 GIF 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a GIF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 52
fi

# test filetype of exemple6
output=`./bin/my_file ./exemples/exemple6 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PS" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 60
fi
output=`./bin/my_file ./exemples/exemple6 ps 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a ps" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 61
fi
output=`./bin/my_file ./exemples/exemple6 PS 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PS" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 62
fi

# test filetype of exemple7
output=`./bin/my_file ./exemples/exemple7 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PDF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 70
fi
output=`./bin/my_file ./exemples/exemple7 pdf 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a pdf" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 71
fi
output=`./bin/my_file ./exemples/exemple7 PDF 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a PDF" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 72
fi

# test filetype of exemple8
output=`./bin/my_file ./exemples/exemple8 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a JPEG" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi
output=`./bin/my_file ./exemples/exemple8 jpeg 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a jpeg" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi
output=`./bin/my_file ./exemples/exemple8 JPEG 2>&1`
if [ $? -ne 0 ] || [ "$output" != "File is a JPEG" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 10
fi

printf "${GREEN}PASS${NC}\n"