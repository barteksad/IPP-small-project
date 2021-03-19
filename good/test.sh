#!/bin/bash


if (($# != 2))
then
    echo "You must specify program name to run and test data directory!" >&2
    exit 1
fi

PROGRAM_PATH=$1
TEST_DIR=$2


for file_name in "$TEST_DIR"/*.in
do
    TMPFILE_OUT=$(mktemp) || exit 1
    TMPFILE_ERR=$(mktemp) || exit 1

    "$PROGRAM_PATH"<"$file_name" >"$TMPFILE_OUT" 2>"$TMPFILE_ERR"
    if [ $? == "0" ]
    then
        DIFF_OUT=$(diff "$TMPFILE_OUT" "${file_name%in}out")
        DIFF_ERR=$(diff "$TMPFILE_ERR" "${file_name%in}err")
        if ["$DIFF_OUT" == ""] && ["$DIFF_ERR" == ""]
        then
            echo "$file_name OK $?"
        else
            echo "$file_name zły wynik! $?"
        fi
    else
        echo "$file_name error, program zakoczył się z kodem $?"
    fi
    rm -f "$TMPFILE_OUT $TMPFILE_ERR"
done;
