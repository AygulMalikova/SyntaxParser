# Syntax Parser for the ANSI C

## Implemented by Artyom IUrin, Elizaveta Kolchanova and Aygul Malikova, SE-01, "ALA" Team

To run the program, firsly, clone the project

`git clone https://github.com/AygulMalikova/SyntaxParser.git`

In the terminal write the commands below

`docker run -v $(pwd):/app -i -t cmbant/docker-gcc-build /bin/bash`  
`apt-get install bison flex -y`

To run the yacc and lexer

`cd app`  
`yacc -d grammar.y && flex lex.l && gcc -Wall y.tab.c lex.yy.c -lfl && cat input.txt | ./a.out`
