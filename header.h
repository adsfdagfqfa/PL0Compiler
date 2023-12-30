#pragma once

#ifndef MYCLASS_H
#define MYCLASS_H



#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

extern ifstream fileRead;
extern istringstream wordRead;

extern int nextquad;//引入,当前指令地址
extern int tempName;
struct Comtab//储存标识符的结构体
{
	string name;//标识符名字
	int kind;//标识符的种类（常量或是变量）,0表示常量，1表示变量
	int value;//数值
};

struct Quadruple//储存标识符的结构体
{
	string insType;//操作类型
	string arg1 ;//操作数1
	string arg2 ;//操作数2
	string result;//结果
	Quadruple() {//构造参数
		arg1 = "_";
		arg2 = "_";
		result = "_";
	}
};

extern vector<Comtab> table;//符号表
extern vector<Quadruple> intermediateCode;//中间代码

/* ------ 词法分析 ------ */
// 单词符号以及对应种类数字保存在枚举当中
enum TokenType {
	$ERROR,
	$PROGRAM,$BEGIN,$END,$CONST,$VAR,$WHILE,$DO,$IF,$THEN, // 关键字助记符
	$ID, // 标识符
	$INT, // 整数
	$ADD,$SUB,$MUL,$DIV,$ASSIGN,$EQUAL,$NOEQUAL,$GREATER,$EQUGREAT,$LESS,$EQULESS,$LEFTBRACKET,$RIGHTBRACKET,$ENDSYM,$COMMA
	// 算符，界符
};
// 单词符号列表项
struct Token
{
	TokenType type;
	string value;
	int numValue;
};

class Lexer {
private:
	vector<Token> tokenList;
	// 存放最新读进去的源程序字符
	char* ch;
	// 存放构成单词符号的字符串
	string strToken;
	// 存放当前指针的位置
	size_t currentPos;
	// 存放输入的字符串代码
	string targetCode;
public:
	Lexer(string& oriCode);
	// 获取符号表
	vector<Token> getTokenList();
	// 判断ch中的字符是否为字母
	bool IsLetter();
	// 判断ch中的字符是否为数字
	bool IsDigit();
	// 判断ch中的字符是否为运算符的第index个
	bool ChIsOperator(int index);
	// 判断str是否为运算符
	bool StrIsOperator();
	// 判断ch字符是否是边界符
	bool IsBound();
	// 将下一字符读取到ch当中，由于ch为指针，因此将其加一即可
	void GetChar();
	// 检查ch中的字符是否为空白，若是，则调用GetChar直至ch中进入一个非空白字符
	void GetBC();
	// 将ch中的字符连接到strToken之后
	void Concat();
	// 对strToken中的字符串查找保留字表，若它是一个保留字，则返回它的编码，否则返回-1
	int Reserve();
	// 对strToken中的字符串查找操作符号表，若它是一个操作符号，则返回它的编码，否则返回-1
	int OpeReserve();
	// 对strToken中的字符串查找边界符号表，若它是一个边界符号，则返回它的编码，否则返回-1
	int BoundReserve();
	// 将搜索指示器回调一个字符位置，将ch置为空白字符
	void Retract();
	// 将strToken中的标识符插入符号表
	void InsertToken(TokenType type, string value, int numValue);
	bool IsKeyLetter();
	// 生成符号表
	bool generateTokenList();
};

class Parser {
private:
	vector<string> code;
	int p;
public:
	Parser(vector<string> input);
	bool readline();
	bool program();
	bool head();
	bool block();
	bool identifier(Comtab* p);
	bool constSpecification();
	bool varSpecification();
	bool statement(vector<int>& NextList);
	bool constDefination();
	bool unsignedINT( Comtab* p);
	bool assignStatement(vector<int>& NextList);
	bool ifStatement(vector<int>&NextList);
	bool whileStatement(vector<int>& NextList);
	bool compoundStatement(vector<int>& NextList);
	bool expression(string* p);
	bool Expression(string p1, string* p2);
	bool item(string *p);
	bool Item(string p1, string* p2);
	bool factor(string* p);
	bool condition(vector<int> &trueList, vector<int> &falseList);
	bool isAllBC();
};





// 单词符号列表项
#endif // MYCLASS_H