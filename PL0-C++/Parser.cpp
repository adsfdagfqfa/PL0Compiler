#include "header.h"
#include <set>

// 语法分析器
/*
【<表达式>→[+|-]项 | <表达式> <加法运算符> <项>】--左递归
【<项>→<因子> | <项> <乘法运算符> <因子>】--左递归

文法：
<程序>→<程序首部> <分程序>
<程序首部>→PROGRAM <标识符>
<分程序>→[<常量说明>][<变量说明>]<语句>（注：[ ]中的项表表可选）
<常量说明>→CONST <常量定义>{，<常量定义>} ; （注： { }中的项表示可重复若干次）
<常量定义>→<标识符>:=<无符号整数>
<无符号整数>→<数字>{<数字>}
<变量说明>→VAR<标识符>{，<标识符>};
<标识符>→<字母>{<字母> | <数字>}
<复合语句>→BEGIN <语句>{; <语句>} END
<语句>→<赋值语句> | <条件语句 >| <循环语句> | <复合语句> | <空语句>
<赋值语句>→<标识符>:=<表达式>
<表达式>→[+|-]项 <EXPRESSION>
<EXPRESSION>→<加法运算符> <项> <EXPRESSION> | 空
<项>→<因子> <ITEM>
<ITEM>→<乘法运算符> <因子> <ITEM> | 空
<因子>→<标识符> |<无符号整数> | (<表达式>)
<加法运算符>→ + | -
<乘法运算符>→ * | /
<条件语句>→IF <条件> THEN <语句>
<循环语句>→WHILE <条件> DO <语句>
<条件>→<表达式> <关系运算符> <表达式>
<关系运算符>→ = | <> | < | <= | > | >=
<字母>→a | b …| x | y | z
<数字>→0 | 1 | … | 8| 9
*/

/*
FIRST集合：
FIRST(常量说明) = { CONST }
FIRST(变量说明) = { VAR }
FIRST(赋值语句) = { a~z }
FIRST(条件语句) = { IF }
FIRST(循环语句) = { WHILE }
FIRST(复合语句) = { BEGIN }
FIRST(加法运算符) = { + , - }
FIRST(乘法运算符) = { * , / }
FOLLOW集合：
FOLLOW(EXPRESSION) = { ) , END , DO , THEN , 关系运算符 , ;}
FOLLOW(ITEM) = { + , -  , ) , END , DO , THEN , 关系运算符, ;}
*/

Comtab* findVariable(const std::string& name) {
	for (auto& entry : table) {
		if (entry.name == name) {
			return &entry;
		}
	}
	return nullptr;
}//在符号表中查找,存在返回指针，不存在返回空指针


vector<Token> line;
int i = 0;

Parser::Parser(vector<string> input) {
	for (int i = 0; i < input.size(); i++) {
		code.push_back(input[i]);
	}
	p = 0;
}

bool Parser::isAllBC() {
	bool isAllBC = true;
	for (int i = 0; i < code[p].size() && isAllBC; i++) {
		if (code[p][i] != ' ')
			isAllBC = false;
	}
	return isAllBC;
}

// 读取第p行的程序
bool Parser::readline() {
	// 程序已全部读过一遍
	if (p >= code.size()) {
		// 在line的最后添加一个表示程序结束的元组
		line.push_back({$ERROR,"OVER",0});
		return true;
	}
	while (true)
	{
		if (isAllBC())
			p++;
		else
			break;
	}
	// 读取下一行程序
	Lexer lex(code[p]);
	p++;
	if (lex.generateTokenList()) {
		vector<Token> result = lex.getTokenList();

		for (int j = 0; j < result.size(); j++) {
			line.push_back(result[j]);
		}
		return true;
	}
	else {
		return false;
	}
}

// <程序>→<程序首部> <分程序>
bool Parser::program() {
	// 读取第一行程序
	bool b = readline();
	if (b == true) {
		// 进入程序首部的分析
		b = head();
		if (b == true) {
			// 进入分程序的分析
			b = block();
		}
	}
	if (b == false) {
		cout << "当前分析语句：" << code[p - 1] << endl;
	}
	else {
		// 如果此时line[i].type并不是ERROR，说明语句还没有全部分析完，报错。
		if (line[i].type != 0) {
			b = false;
			cout << "当前分析语句：" << code[p - 1] << endl;
		}
	}
	return b;
}

// <程序首部>→PROGRAM <标识符>
bool Parser::head() {
	bool b = false;
	// 判断单词是否为关键字PROGRAM
	if (line[i].type == 1) {
		i++;
		// 判断是否需要读取下一行程序
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是PROGRAM，则判断下一个单词是否为标识符
		Comtab comtab;
		b = identifier(&comtab);
	}
	return b;
}

// <分程序>→[<常量说明>][<变量说明>]<语句>
// FIRST(常量说明) = { CONST }
// FIRST(变量说明) = { VAR }
bool Parser::block() {
	vector<int> NextList;
	bool b = false;
	// 判断是否有常量说明CONST
	if (line[i].type == 4) {
		// 如有CONST，则进入常量说明的分析
		b = constSpecification();
		if (b == false) {
			return b;
		}
	}
	// 判断是否有变量说明VAR
	if (line[i].type == 5) {
		// 如有VAR，则进入变量说明的分析
		b = varSpecification();
		if (b == false) {
			return b;
		}
	}
	// 进入语句的分析
	b = statement(NextList);
	return b;
}

// <标识符>→<字母>{<字母> | <数字>}
bool Parser::identifier(Comtab* p ) {//加入指针参数，返回值为识别的标识符的名字
	bool b = false;
	// 判断单词是否为标识符
	if (line[i].type == 10) {
		p->name = line[i].value;//记录标识符的名字并返回。
	    i++;
		b = true;

		if (i >= line.size()) {
			b = readline();
		}
	}
	return b;
}

// <常量说明>→CONST <常量定义>{，<常量定义>} ;
bool Parser::constSpecification() {
	bool b = false;
	// 判断单词是否为CONST
	if (line[i].type == 4) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是CONST，则进入常量定义的分析
		b = constDefination();
	}
	else 
		return false;
	// 如果遇到逗号，则进入循环，分析常量定义
	while ((b==true) && (line[i].type == 26)) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 进入常量定义的分析
		b = constDefination();
	}
	if (b == true) {
		// 判断单词是否为分号
		if (line[i].type == 25) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
	}
	return b;
}

// <变量说明>→VAR<标识符>{，<标识符>};
bool Parser::varSpecification() {
	bool b = false;
	// 判断单词是否为VAR
	if (line[i].type == 5) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是VAR，则进入标识符的分析

		Comtab comtab;
		comtab.kind = 1;//1表示变量
		b = identifier(&comtab);
		Comtab* p = findVariable(comtab.name);
		if (p != nullptr) {//一旦重名直接返回false报错
			return false;
		}
		table.push_back(comtab);
	}
	else 
		return false;
	// 如果遇到逗号，则进入循环，分析标识符
	while ((b == true) && (line[i].type == 26)) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		Comtab comtab;
		comtab.kind = 1;//1表示变量
		b = identifier(&comtab);
		Comtab* p = findVariable(comtab.name);
		if (p != nullptr) {//一旦重名直接返回false报错
			return false;
		}
		table.push_back(comtab);
	}
	if (b == true) {
		// 判断单词是否为分号
		if (line[i].type == 25) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
	}
	return b;
}

// <常量定义>→<标识符>:=<无符号整数>
bool Parser::constDefination() {
	bool b = false;
	// 进入标识符的判断

	Comtab comtab;
	comtab.kind = 0;//0表示常量
	b = identifier(&comtab);

	Comtab* p = findVariable(comtab.name);//在表种查询，一旦重名直接返回空
	if (p != nullptr) {
		return false;
	}

	if (b == true) {
		// 判断单词是否为‘:=’
		if (line[i].type == 16) {
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// 判断单词是否为无符号整数
			b = unsignedINT();
		}
		else
			return false;//否则报错
	}

	table.push_back(comtab);//填入符号表

	return b;
}

// <?符号整数>→<数字>{<数字>}
bool Parser::unsignedINT() {
	bool b = false;
	// 判断单词是否为无符号整数
	if (line[i].type == 11) {
		i++;
		b = true;
		if (i >= line.size()) {
			b = readline();
		}
	}
	return b;
}

/*
<语句>→<赋值语句> | <条件语句 >| <循环语句> | <复合语句> | <空语句>
FIRST(赋值语句) = { a~z }
FIRST(条件语句) = { IF }
FIRST(循环语句) = { WHILE }
FIRST(复合语句) = { BEGIN }
*/
bool Parser::statement(vector<int> &NextList) {
	bool b = false;
	// 判断单词是否为标识符
	if (line[i].type == 10) {
		b = assignStatement(NextList);
	}
	// 判断单词是否为IF
	else if (line[i].type == 8) {
		b = ifStatement(NextList);
	}
	// 判断单词是否为WHILE
	else if (line[i].type == 6) {
		b = whileStatement(NextList);
	}
	// 判断单词是否为BEGIN
	else if (line[i].type == 2) {
		b = compoundStatement(NextList);
	}
	// 判断是否为空语句
	else if (line[i].type == 0 || line[i].type == 25 || line[i].type == 3) {
		b = true;
	}
	return b;
}

// <赋值语句>→<标识符>:=<表达式>
bool Parser::assignStatement(vector<int>& NextList) {
	bool b = false;
	// 判断单词是否为标识符
	Comtab comtab;//标识符
	string s; //表达式
	b = identifier(&comtab);
	Comtab* p = findVariable(comtab.name);//获取符号表的指针
	if (p == nullptr || p->kind == 0)//p为空或者p为常量
		return false;
	if (b == false) {//不是标识符
		return false;
	}
	// 判断单词是否为‘:=’
	if (line[i].type == 16) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是:=，进入表达式的分析


		b = expression(&s);
	}
	else
		return false;
	NextList.clear();//赋值语句无nextlist
	//结束部分
	Quadruple quadruple;
	quadruple.insType = ":=";
	quadruple.arg1 = s;
	quadruple.result = comtab.name;//表达式的
	intermediateCode.push_back(quadruple);
	nextquad++;
	return b;
}

// <条件语句>→IF <条件> THEN <语句>
bool Parser::ifStatement(vector<int>&NextList) {
	vector<int> trueList;
	vector<int> falseList;
	vector<int> nextList;
	int quad;
	bool b = false;
	// 判断单词是否为IF
	if (line[i].type == 8) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是IF，则进入条件的分析
		b = condition(trueList,falseList);
		// 判断单词是否为THEN
		if ((b == true) && (line[i].type == 9)) {
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// 如是THEN，则进入语句的分析

			quad = nextquad;

			b = statement(nextList);
		}
		else {
			b = false;
			return b;
		}
	}

	for (auto entry : trueList) {
		int idx = entry - 100;
		intermediateCode[idx].result = to_string(quad);//回填部分
	}

	std::set<int> uniqueValues(falseList.begin(), falseList.end());
	uniqueValues.insert(nextList.begin(), nextList.end());

	std::vector<int> mergedVector(uniqueValues.begin(), uniqueValues.end());
	NextList = mergedVector;
	return b;
}

// <循环语句>→WHILE M <条件> DO M <语句>
bool Parser::whileStatement(vector<int>&NextList) {
	vector<int> nextList;
	vector<int> trueList;
	vector<int> falseList;
	int quad1;
	int quad2;
	bool b = false;
	// 判断单词是否为WHILE
	if (line[i].type == 6) {
		quad1 = nextquad;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是WHILE，则进入条件的分析
		b = condition(trueList,falseList);
		// 判断单词是否为DO
		if ((b == true) && (line[i].type == 7)) {
			quad2 = nextquad;
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// 如是DO，则进入语句的分析
			b = statement(nextList);
		}
		else {
			b = false;
			return b;
		}
	}
	for (auto entry : nextList) {
		int idx = entry - 100;
		intermediateCode[idx].result = to_string(quad1);
	}
	for (auto entry : trueList) {
		int idx = entry - 100;
		intermediateCode[idx].result = to_string(quad2);
	}
	NextList = falseList;

	Quadruple quadruple;
	quadruple.insType = "j";//无条件跳转语句
	quadruple.result = to_string(quad1);
	intermediateCode.push_back(quadruple);
	nextquad++;
	return b;
}

// <复合语句>→BEGIN <语句>{; <语句>} END
bool Parser::compoundStatement(vector<int>& NextList) {
	vector<int> nextList;
	int quad;
	bool b = false;
	// 判断单词是否为BEGIN
	if (line[i].type == 2) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		vector<int> next;
		
		// 如是BEGIN，则进入语句的分析
		b = statement(next);
		// 如果单词为分号，则进入循环，分析语句
		
		quad = nextquad;
		for (auto entry : next) {
			int idx = entry - 100;
			intermediateCode[idx].result = to_string(quad);
		}
		nextList = next;
		while ((b == true) && (line[i].type == 25)) {
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			b = statement(next);
			quad = nextquad;
			for (auto entry : next) {
				int idx = entry - 100;
				intermediateCode[idx].result = to_string(quad);
			}
			nextList = next;
		}
		// 判断单词是否为END
		if ((b == true) && (line[i].type == 3)) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
		else {
			b = false;
			return b;
		}
	}
	NextList = nextList;
	return b;
}

// <表达式>→[+|-]项 <EXPRESSION>
bool Parser::expression(string* s) {
	bool b = false;
	bool t = false;//记录是否含义符号
	// 判断是否有‘+’或 ‘-’
	if ((line[i].type == 12) || (line[i].type == 13)) {
		if (line[i].type == 13)
			t = true;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
	}
	// 进入项的分析
	string arg1;
	b = item(&arg1);
	if (t) {//如果是加法则不处理，如果是减号
		Quadruple quadruple;
		string name = "Temp";
		quadruple.result = name + to_string(tempName);;//表达式的新名字
		tempName++;//分配一个新的名字
		quadruple.insType = ":=";
		quadruple.arg1 = string("-") + arg1;
		intermediateCode.push_back(quadruple);
		nextquad++;
		arg1 = quadruple.result;
	}

	if (b == true) {
		// 进入Expression的分析

		b = Expression(arg1, s);
	}
	

	

	return b;
}

// <EXPRESSION>→<加法运算符> <项> <EXPRESSION> | 空
// FOLLOW(EXPRESSION) = { ) , END , DO , THEN , 关系运算符 , ;}
bool Parser::Expression(string arg, string* s) {
	bool b = false;
	// 判断单词是否为‘+’或‘-’
	string oper;
	if ((line[i].type == 12) || (line[i].type == 13)) {
		oper = line[i].value;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是加法运算符，则进入项的判断
		string arg1;
		b = item(&arg1);

		string name = "Temp";
		Quadruple quadruple;
		quadruple.insType = oper;
		quadruple.arg1 = arg;
		quadruple.arg2 = arg1;
		quadruple.result = name + to_string(tempName);;//表达式的
		*s = quadruple.result;
		arg1= quadruple.result;
		tempName++;//分配一个新的名字
		intermediateCode.push_back(quadruple);
		nextquad++;

		if (b == true) {
			// 进入Expression的分析
			b = Expression(arg1, s);
		}
			
		
	}
	// 空的情况：如果单词在FOLLOW集合中，直接返回
	else if ((line[i].type == 7) || (line[i].type == 3) || (line[i].type == 24)|| (line[i].type == 9) 
		|| ((line[i].type >= 17) && (line[i].type <= 22)) || (line[i].type == 25)) {
		*s = arg;
		return true;
	}
	return b;
}

// <项>→<因子> <ITEM>
bool Parser::item(string *s) {
	bool b = false;
	// 进入因子的分析

	string arg1;
	b = factor(&arg1);
	if (b == true) {
		// 进入ITEM的分析
		b = Item(arg1, s);
	}
	
	return b;
}

// <ITEM>→<乘法运算符> <因子> <ITEM> | 空
// FOLLOW(ITEM) = { + , -  , ) , END , DO , THEN , 关系运算符, ;}
bool Parser::Item(string arg,string*s) {
	bool b = false;
	string oper;
	// 判断单词是否为‘*’或‘/’
	if ((line[i].type == 14) || (line[i].type == 15)) {
		oper = line[i].value;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是乘法运算符，则进入因子的分析
		string arg1;
		b = factor(&arg1);

		string name = "Temp";
		Quadruple quadruple;
		quadruple.insType = oper;
		quadruple.arg1 = arg;
		quadruple.arg2 = arg1;
		quadruple.result = name + to_string(tempName);;//表达式的

		tempName++;//分配一个新的名字
		*s = quadruple.result;
		arg1= quadruple.result;
		intermediateCode.push_back(quadruple);
		nextquad++;
		
		if (b == true) {
			// 进入ITEM的分析
			b = Item(arg1, s);
		}
	}
	// 空的情况：如果单词在FOLLOW集合中，直接返回
	else if((line[i].type == 12) || (line[i].type == 13) || (line[i].type == 7) || (line[i].type == 3) || (line[i].type == 24) 
		|| (line[i].type == 9) || ((line[i].type >= 17) && (line[i].type <= 22)) || (line[i].type == 25)){
		*s = arg;
		return true;
	}
	return b;
}

// <因子>→<标识符> | <无符号整数> | (<表达式>)
bool Parser::factor(string* s) {
	bool b = false;
	// 判断单词是否为标识符
	if (line[i].type == 10) {
		
		Comtab* comtab = findVariable(line[i].value);//寻找是否存在标识符
		if (comtab == nullptr)
			return false;
		*s = comtab->name;//如果找到就将参数p的name赋值为name

		i++;
		b = true;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
	}
	// 判断单词是否为无符号整数
	else if (line[i].type == 11) {

		*s = to_string(line[i].numValue);//此时为无符号整数
		i++;
		b = true;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
	}
	// 判断单词是否为‘(’
	else if (line[i].type == 23) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// 如是‘(’，则进入表达式的分析
		b = expression(s);
		// 判断单词是否为‘)’
		if ((b == true) && (line[i].type == 24)) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
		else
			b = false;
	}
	return b;
}

// <条件>→<表达式> <关系运算符> <表达式>
bool Parser::condition(vector<int>& trueList,vector<int>& falseList) {

	bool b = false;
	// 进入表达式的分析
	string arg1;//避免报错，检验所用
	string oper;
	string arg2;
	b = expression(&arg1);
	if (b == true) {
		// 判断单词是否为关系运算符
		if ((line[i].type >= 17) && (line[i].type <= 22)) {
			oper = line[i].value;
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// 如是关系运算符，则进入表达式的分析
			b = expression(&arg2);
		}
	}
	trueList.push_back(nextquad);
	falseList.push_back(nextquad + 1);

	//中间代码生成部分。
	Quadruple quadruple1;
	quadruple1.insType = string("j") + oper;
	quadruple1.arg1 = arg1;
	quadruple1.arg2 = arg2;
	intermediateCode.push_back(quadruple1);
	nextquad++;


	Quadruple quadruple2;
	quadruple2.insType = "j";//无条件跳转语句
	quadruple2.result = "0";
	intermediateCode.push_back(quadruple2);
	nextquad++;
	return b;
}