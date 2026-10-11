#!/bin/bash

if  [ -z $1 ] || [ -z $2 ]
then
	echo "Not enough arguments specified!"
	exit 1
fi

mkdir -p $( dirname $1 )

if ! [ $? -eq 0 ]
then
	echo "BAD"
	exit 1
fi

echo $2 > $1
