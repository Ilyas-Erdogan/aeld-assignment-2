#!/bin/bash

if [ -z $1 ] || [ -z $2 ]
then
	echo "Not enough arguments supplied."
	exit 1
fi

if ! [ -d $1 ]
then
	echo "$1 is not a directory. Please specify a directory as the first argument."
	exit 1
fi

file_count=$( ls $1 | grep -c . )
matching_count=$( grep -r $2 $1 | grep -c $2 )

echo "The number of files are $file_count and the number of matching lines are $matching_count" 
