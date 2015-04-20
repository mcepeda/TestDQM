#!/bin/bash 

while read line
do
     name=$line
     echo "Text read from file - $name"
     ls $name/*
     cd $name  

     source ../../miniCode.sh & 
  
     cd ../..
 
done < $1
 
