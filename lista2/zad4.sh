#!/bin/bash

DefaultDays=7

DefaultMask='*.pdf'

DefaultTar='archiwum.tar'

while getopts ":n:m:a:" opt; do
    case "$opt" in
	n) Days="$OPTARG"
	    ;;
	m) Mask="$OPTARG"
	    ;;
	a) Tar="$OPTARG"
	   ;;
    esac
done

if [ -n "$MaskName" ]; then
    Mask=$MaskName
fi

if [ -n "$LastModifyDays" ]; then
    Days=$LastModifyDays
fi

if [ -n "$TarName" ]; then
    Tar=$TarName
fi


if [ -z "$Days" ]; then
    echo Podaj maksymalna liczbe dni, od ktorych plik byl ostatnio modyfikowany:
    read Days
    if [ -z "$Days" ]; then
	Days=$DefaultDays
	echo Nie wybrano wartosci parametru. Ustalo czas na $DefaultDays dni.
    fi
fi

if [ -z "$Mask" ]; then
    echo Podaj wyszukiwana maske lub rozszerzenie\(Nie moze znajdowac sie miedzy apostrofami\):
    read Mask
    if [ -z "$Mask" ]; then
	Mask=$DefaultMask
	echo Nie wybrano wartosci parametru. Ustalo wyszukiwanie na pliki $DefaultMask .
    fi
fi

if [ -z "$Tar" ]; then
    echo Podaj nazwe dla tworzonego archiwom
    read Tar
    if [ -z "$Tar" ]; then
	Tar=$DefaultTar
	echo Nie wybrano wartosci parametru. Ustalo nazwe archiwom na $DefaultTar
    fi
fi


find $HOME -mtime -$Days -name $Mask -print0 | tar -cvf $Tar --null -T -
