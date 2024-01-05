grammar PL0;

start : program EOF;

program : programHead block;

programHead : 'PROGRAM' identifier;

block : (constantSpecification)? (varSpecification)? statement;

constantSpecification : 'CONST' constantDefinition (',' constantDefinition)* ';';

constantDefinition : identifier ':=' uint;

uint : NUMBER (NUMBER)*;

varSpecification : 'VAR' identifier (',' identifier)* ';';

identifier : LETTER (LETTER | NUMBER)* ;

compoundStatement : 'BEGIN' statement (';' statement)* 'END';

statement : assignmentStatement
          | ifStatement
          | whileStatement
          | compoundStatement
          | nullStatement
          ;

nullStatement : ;

assignmentStatement : identifier ':=' expression;

expression : ('+' | '-')? item | expression addOperator item;

item : factor | item mulOperator factor;

factor : identifier | uint | '(' expression ')';

addOperator : '+' | '-';

mulOperator : '*' | '/';

ifStatement : 'IF' condition 'THEN' statement;

whileStatement : 'WHILE' condition 'DO' statement;

condition : expression relationOperator expression;

relationOperator : '=' | '<>' | '<' | '<=' | '>' | '>=';

NUMBER : [0-9];

LETTER : [a-z];

WS : [ \t\r\n]+ -> skip;

/*
PROGRAM add
VAR x,y;
BEGIN
    x:=1;
    y:=2;
    WHILE x<5 DO x:=x+1;
    IF y>0 THEN y:=y-1;
    y:=y+x
END
*/