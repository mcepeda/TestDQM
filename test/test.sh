#!/bin/bash
while read line
do
    name=$line
    echo "Text read from file - $name"
    ls $name/*
    cp $name/* .  
    foldername=$name"/TestFromDigis"_$(date +_%Y%m%d_%H%M%S)
    echo $foldername  

done < $1
