# MagicSquareBruteForcer

Magic Square Brute Forcer is a program that allows you to find all possible magic squares given a set of params

<h2>Feature List</h2>

-Prints all possible magic squares of a given size using numbers in a given range

-Output options

-Rotation and mirror handling

-Multithreading

<h2>Planned features</h2>

-Dynamic/Optimized ordering for faster calculations

-Proper logging/progress reports

-Better thread allocation

<h2>Usage</h2>

`msbf -s 3 -m 9`

`msbf -s 3 -m 9 -t 12`

`msbf -s 3 -n 1 -m 10`

`msbf -s 3 -n 1 -m 10 -c -i`

<h2>Options</h2>

	Required:
		-s --size <argument>	The size side length of the square.
		-m --max <argument>		The maximum number to search up to.
		
	Optional:
		-n --min <argument>		The minimum number to search from.
		-c --compact			Makes the output compact (One line for each valid square found).
		-i --indentical			Includes magic squares that are mirrors and/or rotations of found squares.
		-t --threads <argument>	The number of threads to run on, defaults to your CPU hardware concurency.
