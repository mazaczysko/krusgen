# krusgen 1 "23 April 2017" "v1.3"

## NAME
**krusgen** - command line maze generator.

## SYNOPSIS
**krusgen** [`OPTIONS`]

## DESCRIPTION
Generates a maze of given size, using Kruskal's algorithm.
**Krusgen** can also export the maze into text (**-t**)  or bmp (**-b**) file, if none of the options is used, maze is exported to **stdout** as text.

Supported options:

**-h**, **--help** - show help message

**-x** <`positive, odd number`> - define map width, if not used, width is set automatically to 31

**-y** <`positive, odd number`> - define map height, if not used, height is set automatically to 31

**-f**, **--frame** - add borders to maze

**-s**, **--seed** <`seed`> - set random generator's seed

**-v**, **--version** - displays krusgen version

**-t**, **--txt** <`filename`> - export maze as text to given filename

**-b**, **--bmp** <`filename`> - export maze as bitmap (BMP2 format) to given filename

**-w**, **--wall** <`hex color`> - define wall color in bitmap, if not used wall color is white

**-a**, **--air** <`hex color`> - define air color in bitmap, if not used air color is black

**-W**, **--wallchar** <`character`> - define wall character, if not used wall character is #

**-A**, **--airchar** <`character`> - define air character, if not used air character is ' '                 

## EXAMPLES
**krusgen -x 51 -y 17** - export maze of 51 characters width and 17 characters height to **stdout** as text.

**krusgen -b test.bmp** - export maze of default dimensions as image to **test.bmp** file.

**krusgen -t test.txt** - export maze of default dimensions as text to **test.txt** file.

**krusgen -y 25 -x 37 -b colors.bmp -a FF0000 -w FFFF00** - export maze of 37 characters width and 25 characters height as image with red air and yellow walls to **colors.bmp** file.

**krusgen -W o -A \(** - export maze which has 'o' as walls and '(' as air to **stdout**.

## AUTHOR
Written by Miłosz Ryguła <miloszrygula@interia.pl>.
**Krusgen** uses **libobos** library created by Jacek Wieczorek <mrjjot@gmail.com>.

## REPORTING BUGS
Bugs can be reported as issues on Krusgen's Github page: https://github.com/mazaczysko/krusgen/issues

## COPYRIGHT
**Krusgen** and **libobos** are both licensed under GNU GPLv3 license.

Copyright (C) 2017 Miłosz Ryguła <miloszrygula@interia.pl>
Free Software Foundation, Inc.  License GPLv3+: GNU
GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
This is free software: you are free  to  change  and  redistribute  it.
There is NO WARRANTY, to the extent permitted by law.
