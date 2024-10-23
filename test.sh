#!/bin/sh

cd tests

make

for d in */; do 
    cd $d
    
    for f in *.json; do 
        ./../parser ${f} > ${f}.result.txt; 

        cmp ${f}.record.txt ${f}.result.txt
    done
    
    cd ..
done;

