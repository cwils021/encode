encode

basic caesar cipher encoding with a user defined shift value

A make file is included, simply type:

$ make

sample run output:

$ ./encode -F filename -O outputname ShiftValue

i.e. ./encode -F testfile.txt -O copy.txt 1

will encrypt the contents of testfile.txt to copy.txt by shifting all alpha characters by 1

