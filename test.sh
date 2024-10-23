#!/bin/sh

echo 'Running snapshot tests'

cd tests/snapshot

make

for d in */; do 
    cd $d
    
    for f in *.json; do 
        ./../parser ${f} > ${f}.result.txt; 

        cmp ${f}.record.txt ${f}.result.txt
    done
    
    cd ..
done;

echo 'Running unit tests'

cd ..
cd unit

make