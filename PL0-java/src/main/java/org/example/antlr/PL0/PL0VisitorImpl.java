package org.example.antlr.PL0;

import PL0.PL0Parser;

import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.*;

public class PL0VisitorImpl extends PL0.PL0BaseVisitor<String> {
    private Integer nextquad=100;//初始指令地址
    private Integer tempVarCounter = 0;
    private List<Comtab> table=new ArrayList<>();
    private Map<Integer,Quadruple> quadruple=new HashMap<>();

    private List<Integer> trueList=new ArrayList<>();
    private List<Integer> falseList=new ArrayList<>();
    private List<Integer> nextList=new ArrayList<>();

    private String newTempVar() {
        return "t" + tempVarCounter++;
    }
    public Comtab findComtab(String condition) {
        for (Comtab item : table) {
            if (item.getName().equals(condition)) {//名字一致返回对应引用
                return item;
            }
        }
        return null; // 如果找不到匹配的对象，返回null
    }
    public Boolean setComtab(String name,Integer num){
        for (Comtab item : table) {
            if (item.getName().equals(name)) {//名字一致返回对应引用
                item.setValue(num);
                return true;
            }
        }
        return false;
    }

    public void printQuadruple(){
        int quad=100;
        for (int i=0;i<quadruple.size();i++){
            System.out.println(quad+": "+quadruple.get(quad).getInsType()+" "+
                                    quadruple.get(quad).getArg1()+" "+
                                    quadruple.get(quad).getArg2()+" "+
                                    quadruple.get(quad).getResult());
            quad++;
        }


    }
    public void printTable(){
        System.out.println("符号表如下：");
        for (int i=0;i<table.size();i++){
            System.out.println(
                    table.get(i).getName()+" "+
                    table.get(i).getValue()+" "+
                    table.get(i).getKind());

        }
    }
    public void generateTarget(){

        try {
            FileOutputStream fos = new FileOutputStream("target.txt");
            PrintStream ps = new PrintStream(fos);
            System.setOut(ps);

            // 执行程序的其他操作
            printQuadruple();

            // 关闭输出流
            ps.close();
            fos.close();
        }
        catch (Exception e){
            e.printStackTrace();
        }


    }

    //@Override public String visitStart(PL0.PL0Parser.StartContext ctx) { return visitChildren(ctx); }

    //@Override public String  visitProgram(PL0.PL0Parser.ProgramContext ctx) { return visitChildren(ctx); }

    //@Override public String visitProgramHead(PL0.PL0Parser.ProgramHeadContext ctx) { return visitChildren(ctx); }

    //@Override public String visitBlock(PL0.PL0Parser.BlockContext ctx) { return visitChildren(ctx); }

    //@Override public String visitConstantSpecification(PL0.PL0Parser.ConstantSpecificationContext ctx) {return visitChildren(ctx); }

    @Override public String visitConstantDefinition(PL0.PL0Parser.ConstantDefinitionContext ctx) {
        String leftOperand = visit(ctx.identifier());
        // 获取右操作数
        String rightOperand = visit(ctx.uint());

        Comtab temp=findComtab(leftOperand);
        if(temp!=null){
            return null;//直接结束
        }
        //加入符号表
        Comtab comtab=new Comtab();
        comtab.setKind(0);//0表示常量
        comtab.setName(leftOperand);
        comtab.setValue(Integer.valueOf(rightOperand));
        table.add(comtab);

        //生成指令
        Quadruple ins=new Quadruple();
        ins.setInsType(":=");
        ins.setResult(leftOperand);
        ins.setArg1(rightOperand);
        quadruple.put(nextquad,ins);
        nextquad++;//地址自增一
        return null;
    }

    @Override
    public String visitUint(PL0.PL0Parser.UintContext ctx) {
        //System.out.println(ctx.getText());
        return ctx.getText();
    }

    @Override public String visitVarSpecification(PL0.PL0Parser.VarSpecificationContext ctx) {
        List<PL0Parser.IdentifierContext> identifierList = ctx.identifier();
        for(int i=0;i<identifierList.size();i++){
            String variableName = identifierList.get(i).getText();
            // 检查是否已经存在于符号表中，如果存在则表示已经重复定义了，可以进行相应的处理
            Comtab existingVariable = findComtab(variableName);
            if (existingVariable != null) {

                //System.out.println("var变量"+existingVariable.getName()+"重复定义");
                return null;
            }
            // 创建新的 Comtab 对象，并设置其成员变量
            Comtab newVariable = new Comtab();
            newVariable.setKind(1); // 1 表示变量
            newVariable.setName(variableName);
            // 将新的 Comtab 对象添加到符号表中
            table.add(newVariable);
        }


        return null;
    }

    @Override
    public String visitIdentifier(PL0.PL0Parser.IdentifierContext ctx) {
        //System.out.println(ctx.getText());
        return ctx.getText();
    }


    @Override public String visitCompoundStatement(PL0.PL0Parser.CompoundStatementContext ctx) {
        List<Integer> nextList=new ArrayList<>();
        int quad;
        List<PL0Parser.StatementContext> statementList = ctx.statement();
        for(int i=0;i<statementList.size();i++){
            visitStatement(statementList.get(i));
            nextList=new ArrayList<>( this.nextList);
            this.nextList.clear();//情况，防止影响后续代码
            quad=nextquad;
            for (Integer entry : nextList) {
                quadruple.get(entry).setResult(String.valueOf(quad));
            }
        }
        return null;
    }

    @Override public String visitStatement(PL0.PL0Parser.StatementContext ctx) {
        List<Integer> nextList=new ArrayList<>();
        if(ctx.ifStatement()!=null) {
            visitIfStatement(ctx.ifStatement());
            nextList = new ArrayList<>(this.nextList);//创建新的对象而不是引用
            this.nextList.clear();
        }
        else if(ctx.whileStatement()!=null){
            visitWhileStatement(ctx.whileStatement());
            nextList=new ArrayList<>(this.nextList);
            this.nextList.clear();

        }
        else if(ctx.assignmentStatement()!=null){
            visitAssignmentStatement(ctx.assignmentStatement());
            nextList=new ArrayList<>(this.nextList);
            this.nextList.clear();

        }
        else if(ctx.compoundStatement()!=null){
            visitCompoundStatement(ctx.compoundStatement());
            nextList=new ArrayList<>(this.nextList);
            this.nextList.clear();

        }
        this.nextList=nextList;
        return null;

    }

    //@Override public String visitNullStatement(PL0.PL0Parser.NullStatementContext ctx) { return visitChildren(ctx); }

    @Override public String visitAssignmentStatement(PL0.PL0Parser.AssignmentStatementContext ctx) {
        String variableName = visit(ctx.identifier());
        Comtab temp=findComtab(variableName);
        if(temp==null){
            //System.out.println("没有定义");
            return  null;
        }

        // 获取表达式的临时变量名称
        //赋值给相应符号
        String tempVariableName = visit(ctx.expression());

        Comtab tempVar=findComtab(tempVariableName);
        if(tempVar==null) {//如果此时找不到中间变量，说明直接就是立即数
            tempVar=new Comtab();
            tempVar.setValue(Integer.valueOf(tempVariableName));
            tempVar.setName(tempVariableName);
        }



        setComtab(temp.getName(),tempVar.getValue());

        //生成指令
        Quadruple ins=new Quadruple();
        ins.setInsType(":=");
        ins.setResult(tempVar.getName());
        ins.setArg1(temp.getName());
        quadruple.put(nextquad,ins);
        nextquad++;//地址自增一
        return null;

    }

    @Override public String visitExpression(PL0.PL0Parser.ExpressionContext ctx) {

        int childCount = ctx.getChildCount();//获取子节点的数量

        // 如果子节点数量为 1，表示只有一个项，没有加法运算符
        if (childCount == 1) {
            return visit(ctx.item());
        }
        else if(childCount==2){
            String operator=ctx.getChild(0).getText();
            String item=visit(ctx.item());
            if(operator.equals("-")){
                String tempVar = newTempVar();//生成新符号
                //加入符号表
                Comtab t=findComtab(item);
                Comtab temp=new Comtab();
                temp.setName(tempVar);
                temp.setKind(1);
                temp.setValue(-t.getValue());
                table.add(temp);
                return tempVar;//返回临时变量名字
            }
            return item;
        }
        else if(childCount==3){
            String expression=visit(ctx.expression());
            String item=visit(ctx.item());

            String operator=ctx.addOperator().getText();
            String tempVar=newTempVar();
            Comtab temp=new Comtab();

            Comtab arg1=findComtab(expression);
            if(arg1==null) {//如果此时找不到中间变量，说明直接就是立即数
                arg1=new Comtab();
                arg1.setValue(Integer.valueOf(expression));
                arg1.setName(expression);
            }
            Comtab arg2=findComtab(item);
            if(arg2==null) {//如果此时找不到中间变量，说明直接就是立即数
                arg2=new Comtab();
                arg2.setValue(Integer.valueOf(item));
                arg2.setName(item);
            }
            if(operator.equals("+")){
                temp.setValue(arg1.getValue()+arg2.getValue());
            }
            else if(operator.equals("-")){
                temp.setValue(arg1.getValue()-arg2.getValue());
            }
            else {
                return null;
            }
            temp.setName(tempVar);
            temp.setKind(1);
            table.add(temp);//加入符号表

            //生成指令
            Quadruple ins=new Quadruple();
            ins.setInsType(operator);
            ins.setResult(tempVar);
            ins.setArg1(arg1.getName());
            ins.setArg2(arg2.getName());
            quadruple.put(nextquad,ins);
            nextquad++;//地址自增一

            return tempVar;
        }
        else
            return null;

    }

    @Override public String visitItem(PL0.PL0Parser.ItemContext ctx) {

        int childCount = ctx.getChildCount();//获取子节点的数量

        // 如果子节点数量为 1，表示只有一个因子，没有乘法运算符
        if (childCount == 1) {
            return visit(ctx.factor());
        }
        else if(childCount==3){
            String item=visit(ctx.item());
            String factor=visit(ctx.factor());
            String operator=ctx.mulOperator().getText();
            String tempVar=newTempVar();//临时变量
            Comtab temp=new Comtab();

            Comtab arg1=findComtab(item);
            if(arg1==null) {//如果此时找不到中间变量，说明直接就是立即数
                arg1=new Comtab();
                arg1.setValue(Integer.valueOf(item));
                arg1.setName(item);
            }
            Comtab arg2=findComtab(factor);
            if(arg2==null) {//如果此时找不到中间变量，说明直接就是立即数
                arg2=new Comtab();
                arg2.setValue(Integer.valueOf(factor));
                arg2.setName(factor);
            }
            if(operator.equals("*")){
                temp.setValue(arg1.getValue()*arg2.getValue());
            }
            else if(operator.equals( "/")){
                temp.setValue(arg1.getValue()/arg2.getValue());
            }
            else
                return null;
            temp.setName(tempVar);
            temp.setKind(1);
            table.add(temp);//加入符号表


            //生成指令
            Quadruple ins=new Quadruple();
            ins.setInsType(operator);
            ins.setResult(tempVar);
            ins.setArg1(arg1.getName());
            ins.setArg2(arg2.getName());
            quadruple.put(nextquad,ins);
            nextquad++;//地址自增一


            return tempVar;

        }
        else
            return null;
    }

    @Override public String visitFactor(PL0.PL0Parser.FactorContext ctx) {
        if(ctx.identifier()!=null){
            return visit(ctx.identifier());
        }
        else if(ctx.uint()!=null){
            return visit( ctx.uint());
        }
        else if(ctx.getChild(0).getText().equals("(")){
            //此时为（表达式）
            return visit(ctx.expression());
        }
        else
            return null;
    }

    @Override public String visitAddOperator(PL0.PL0Parser.AddOperatorContext ctx) {
        return ctx.getText();
    }

    @Override public String visitMulOperator(PL0.PL0Parser.MulOperatorContext ctx) {
        return ctx.getText();
    }

    @Override public String visitIfStatement(PL0.PL0Parser.IfStatementContext ctx) {


        List<Integer> nextList;
        Integer quad;

        visitCondition(ctx.condition());
        List<Integer> trueList=this.trueList;
        List<Integer> falseList=this.falseList;

        quad=nextquad;
        visitStatement(ctx.statement());
        nextList=new ArrayList<>(this.nextList);
        this.nextList.clear();
        for (Integer entry : trueList) {
            quadruple.get(entry).setResult( String.valueOf(quad));//回填部分
        }

        Set<Integer> uniqueValues = new HashSet<>();
        List<Integer> mergedList = new ArrayList<>();
        // 将两个列表合并并去重
        uniqueValues.addAll(falseList);
        uniqueValues.addAll(nextList);

        // 将无重复元素的集合转为列表
        mergedList.addAll(uniqueValues);
        this.nextList=mergedList;
        return null;
    }

    @Override public String visitWhileStatement(PL0.PL0Parser.WhileStatementContext ctx) {
        List<Integer> nextList;
        Integer quad1;
        Integer quad2;

        quad1=nextquad;//记录位置,方便回填
        visitCondition(ctx.condition());
        List<Integer> trueList=this.trueList;
        List<Integer> falseList=this.falseList;

        quad2=nextquad;
        visitStatement(ctx.statement());
        nextList=new ArrayList<> (this.nextList);
        this.nextList.clear();
        for (Integer entry : nextList) {//回填
            quadruple.get(entry).setResult(String.valueOf(quad1));
        }
        for (Integer entry : trueList) {
            quadruple.get(entry).setResult(String.valueOf(quad2));
        }
        Quadruple ins=new Quadruple();

        ins.setInsType("j");//无条件跳转语句
        ins.setResult(String.valueOf(quad1));
        quadruple.put(nextquad,ins);
        nextquad++;
        this.nextList=falseList;
        //System.out.println(falseList);
        return null;
    }

    @Override
    public String visitCondition(PL0.PL0Parser.ConditionContext ctx) {
        String arg1=visit(ctx.expression(0));//避免报错，检验所用
        String oper=visit(ctx.relationOperator());
        String arg2=visit(ctx.expression(1));
        //获取各个值
        List<Integer> trueList=new ArrayList<>();
        List<Integer> falseList=new ArrayList<>();
        trueList.add(nextquad);
        falseList.add(nextquad+1);

        //中间代码生成部分。
        Quadruple ins1=new Quadruple();
        ins1.setInsType("j"+ oper);
        ins1.setArg1(arg1);
        ins1.setArg2(arg2);
        quadruple.put(nextquad,ins1);
        nextquad++;

        Quadruple ins2=new Quadruple();
        ins2.setInsType("j");
        ins2.setResult("0");
        quadruple.put(nextquad,ins2);
        nextquad++;

        //Map<String,List<Integer>> r=new HashMap<>();
        this.trueList=trueList;
        this.falseList=falseList;
        return null;
    }

    @Override
    public String visitRelationOperator(PL0.PL0Parser.RelationOperatorContext ctx) {
        return ctx.getText();
    }

}
