#!/bin/sh
RESET="\e[0m"
RED="\e[31m"
GREEN="\e[32m"

RETURN_VALUE=0
SELF=`realpath $0`
CURRENT_DIR=`dirname $SELF`
MINISHELL=../../Minishell
MINISHELL_PATH="$CURRENT_DIR/$MINISHELL"
trap "echo 'SEGFAULT'; RETURN_VALUE=1" 11

rm -rf $CURRENT_DIR/results/output_*
for FILE in $CURRENT_DIR/commands/*
do
	filename=$(basename $FILE)
	command=$(cat "$FILE")
	outfile="$CURRENT_DIR/results/output_$filename"
	expected="$CURRENT_DIR/expected/$filename"
	echo -n "Testing: $filename - "
	timeout 5s $MINISHELL_PATH -c "$command" > $outfile 2>> $outfile

	if cmp --silent $expected $outfile
	then
		echo $GREEN'SUCCESS'$RESET
		rm -rf $outfile
	else
		RETURN_VALUE=$?
		echo $RED'ERROR'$RESET
		echo "> Expected ---------------------"
		cat -e $expected 2> /dev/null
		echo "> Got --------------------------"
		cat -e $outfile 2> /dev/null
		echo "--------------------------------"
	fi
done
exit $RETURN_VALUE
