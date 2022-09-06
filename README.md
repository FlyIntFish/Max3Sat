# Max3Sat

## What is Max3Sat?
[definition](https://en.wikipedia.org/wiki/MAX-3SAT)

## How to run
In order to run the application you need to pass two arguments:
  1.  Path to the file with its name (e.g. dir1/dir2/input.txt)
  2.  Amount of iterations (more = better, but lasts longer)
  
## Input files

Structure of input files should be the same as in provided examplary files ( m3s_100_2.txt and  m3s_150_0.txt ):
```
([whitespace]variable[whitespace]variable[whitespace]variable[whitespace])
```
For instance:
```
( 120  130  -27  )
```

Minus (```-```) sign indicates, that this variable should have ```false``` value to fulfill given clause.

## Output
First line of the output is a number in range <0; 1> representing amount of fulfilled clauses (fraction, passed / all)
Next **n** lines represent **n** variables (number and value), e.g. (file m3s_150_0.txt, 640 clauses):
```
0.996875
0         0
1         1
2         1
3         0
4         0
5         0
6         1
7         0
8         0
9         1
10        0
11        1
12        0
13        1
...
```
99,6875% clauses were fulfilled, i.e. 638 passed, 2 failed.
