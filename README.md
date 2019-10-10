docker run -v $(pwd):/app -i -t cmbant/docker-gcc-build /bin/bash
apt-get install bison flex -y
cd app
yacc -d grammar.y && flex lex.l && gcc -Wall y.tab.c lex.yy.c -lfl && cat input.txt | ./a.out