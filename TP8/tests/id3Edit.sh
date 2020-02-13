#/usr/bin/bash
RED='\033[1;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

printf "Testing id3Edit: "

###################################
########## failure tests ##########
###################################

# test bad args
output=`./bin/id3Edit 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    echo "AAAAAAAAAAAAAAAA"
    exit 2
fi
output=`./bin/id3Edit exemples/musique1.mp3 truc muche 2>&1`
if [ $? -ne 1 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 3
fi


###################################
########## Passing tests ##########
###################################

expected1="File size: 2940368 bytes
Version: MPEG1
Layer: Layer III
CRC protection: no
Bitrate: 128 kbps
Sample rate: 44100 Hz
title: J't'emmene Au Vent
artist: Louise Attaque
album: Louise Attaque
year: 1997
comment: Editions Delabel
genre: Rock"

data1="J't'emmene Au Vent
Louise Attaque
Louise Attaque
1997
Editions Delabel
17"

expected2="File size: 2940368 bytes
Version: MPEG1
Layer: Layer III
CRC protection: no
Bitrate: 128 kbps
Sample rate: 44100 Hz
title: Un autre titre
artist: Un artiste
album: Je sais pas quel album
year: 95
comment: Commmmmmmmmmmentaireeeeeeeee
genre: Jazz"

data2="Un autre titre
Un artiste
Je sais pas quel album
95
Commmmmmmmmmmentaireeeeeeeee
8"

# test read
output=`./bin/id3Edit exemples/musique1.mp3 r 2>&1`
if [ $? -ne 0 ] || [ "$output" != "$expected1" ]
then
    printf "${RED}FAIL${NC}\n"
    echo "$output"
    echo "##############"
    echo "$expected1"
    exit 10
fi

# test write
output=`echo "$data2" | ./bin/id3Edit exemples/musique1.mp3 w 2>&1`
if [ $? -ne 0 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 20
fi
output=`./bin/id3Edit exemples/musique1.mp3 r 2>&1`
if [ $? -ne 0 ] || [ "$output" != "$expected2" ]
then
    printf "${RED}FAIL${NC}\n"
    exit 21
fi

# restore
output=`echo "$data1" | ./bin/id3Edit exemples/musique1.mp3 w 2>&1`
if [ $? -ne 0 ]
then
    printf "${RED}FAIL${NC}\n"
    exit 30
fi

printf "${GREEN}PASS${NC}\n"