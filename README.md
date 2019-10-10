# Syntax Parser for the ANSI C

## Implemented by Artyom IUrin, Elizaveta Kolchanova and Aygul Malikova

To run the program, firsly, clone the project

`git clone https://github.com/AygulMalikova/SyntaxParser.git`

If you have macOS, write the command below

`docker run -v $(pwd):/app -i -t cmbant/docker-gcc-build /bin/bash apt-get install bison flex`

To run the yacc and lexer

`cd app`
`yacc -d grammar.y && flex lex.l && gcc -Wall y.tab.c lex.yy.c -lfl && cat input.txt | ./a.out`
