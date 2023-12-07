#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""

for var in -c -n -h
do
  for var2 in -c -n -h
  do
      for var3 in -c -n -h
      do
        if [ $var2 != $var3 ]
        then
          TEST1="$var $var2 $var3 for my_grep.c my_grep.h Makefile"
          ./my_grep $TEST1 > my_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi
          rm my_grep.txt grep.txt

          TEST2="$var $var2 $var3 for my_grep.c"
          ./my_grep $TEST2 > my_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi
          rm my_grep.txt grep.txt

          TEST3="$var $var2 $var3 -e for -e ^int my_grep.c my_grep.h Makefile"
          ./my_grep $TEST3 > my_grep.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi

          rm my_grep.txt grep.txt
          TEST4="$var $var2 $var3 -e for -e ^int my_grep.c"
          ./my_grep $TEST4 > my_grep.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi
          rm my_grep.txt grep.txt

          TEST5="$var $var2 $var3 -f pattern.txt my_grep.c"
          ./my_grep $TEST5 > my_grep.txt
          grep $TEST5 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi
          rm my_grep.txt grep.txt

          TEST6="$var $var2 $var3 -f pattern.txt  my_grep.c Makefile"
          ./my_grep $TEST6 > my_grep.txt
          grep $TEST6 > grep.txt
          DIFF_RES="$(diff -s my_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files my_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              (( COUNTER_FAIL++ ))
          fi
          rm my_grep.txt grep.txt

        fi
      done
  done
done

if [ "$COUNTER_FAIL" -ne 0 ];
then
  echo "Integration test failed"
  exit 1
else
  echo "Integration test successed"
fi
