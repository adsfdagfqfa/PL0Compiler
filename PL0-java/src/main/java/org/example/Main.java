package org.example;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.example.antlr.PL0.PL0VisitorImpl;


public class Main {

    public static void main(String[] args) {
        PL0.PL0Lexer lexer = new PL0.PL0Lexer(CharStreams.fromString(
                 "PROGRAM add"+
                    "CONST a:=10;"+
                    "VAR x,y;"+
                    "BEGIN"+
                    "x:=1*9-4/5*10;"+
                    "y:=2;"+
                    "WHILE x<5 DO x:=x+1;"+
                    "IF y>0 THEN y:=y-1;"+
                    "y:=y+x"+
                    "END"));
        PL0.PL0Parser parser = new PL0.PL0Parser((new CommonTokenStream(lexer)));
        //  parser.start();
        parser.setBuildParseTree(true);
        PL0.PL0Parser.StartContext tree = parser.start();
        //PL0.PL0BaseVisitor<String> visitor = new PL0VisitorImpl();
        PL0VisitorImpl visitor = new PL0VisitorImpl();
        visitor.visit(tree);
        System.out.println("符号表");
        visitor.printTable();
        System.out.println("中间代码");
        visitor.printQuadruple();
        visitor.generateTarget();
        //System.out.println("Hello world!");

    }
}