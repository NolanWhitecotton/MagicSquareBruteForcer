# MagicSquareBruteForcer

Magic Square Brute Forcer is a program that allows you to find all possible magic squares given a set of params

<h2>Feature List</h2><br/>
-Prints all possible magic squares of a given range<br/> 

<h2>Planned features</h2><br/>
-Arg support defined below<br/>
-Mapping to identical squares<br/>
-Dynamic/Optimized ordering for faster calculations<br/>
-Optional progress reports to show the progress<br/>
-Output file

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
		-p [optional int] 	Prints the progress of the search, every given seconds
		-o [Directory]		Save the found squares to an output file
