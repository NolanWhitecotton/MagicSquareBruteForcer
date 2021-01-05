# MagicSquareBruteForcer

Magic Square Brute Forcer is a program that allows you to find all possible magic squares given a set of params

<h2>Feature List</h2><br/>
-Prints all possible magic squares of a given range and size<br/> 
-Multithreading

<h2>Planned features</h2><br/>
-Dynamic/Optimized ordering for faster calculations<br/>
-Proper logging/command input while executing

<h2>Usage</h2>

`msbf [OPTION]...`


<h2>Options</h2>

	Required:
		-s, size [int]		The size of the squares that you are trying to find
		-m, max [int]		The maximum number to search up to
		
	optional:
		-n, min [int]		The minimum number to search from
		-c, compact		Makes the output compact (One line for each valid square found)
		-i, indentical		Includes magic squares that are mirrors / rotations of found squares
		-o [Directory]		Save the found squares to an output file
		-t, threads [int]	The number of threads to run on, recomended is the number of logical cores your CPU has

<h2> Examples </h2>

`msbf -s 3 -m 9 -c -t 12` <br/>
`msbf -s 3 --max 9 -c -i`<br/>
`msbf --size 3 --max 10 --min 2 -c`<br/>
