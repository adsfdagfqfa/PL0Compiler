#include "header.h"

// 词法分析器

vector<string> keyVec = { "PROGRAM","BEGIN","END","CONST","VAR","WHILE","DO","IF","THEN" };
vector<string> opeVec = { "+","-","*","/",":=","=","<>",">",">=","<","<=" };
vector<string> boundVec = { "(",")",";","," };


Lexer::Lexer(string& oriCode) {
	targetCode = oriCode;
	strToken = "";
	ch = &targetCode[0];
	currentPos = 0;
}
// 获取符号表
vector<Token> Lexer::getTokenList() { return tokenList; }
// 判断ch中的字符是否为字母
bool Lexer::IsLetter() {
	if (*ch >= 'a' && *ch <= 'z')
		return true;
	else
		return false;
}
// 判断ch中的字符是否为数字
bool Lexer::IsDigit() {
	if (*ch >= '0' && *ch <= '9')
		return true;
	else
		return false;
}
// 判断ch中的字符是否为运算符的第index个
bool Lexer::ChIsOperator(int index) {
	for (int i = 0; i < opeVec.size(); i++) {
		if (*ch == opeVec[i][index])
			return true;
	}
	return false;
}
// 判断str是否为运算符
bool Lexer::StrIsOperator() {
	auto it = find(opeVec.begin(), opeVec.end(), strToken);
	if (it != opeVec.end())
		return true;
	else
		return false;
}
// 判断ch字符是否是边界符
bool Lexer::IsBound() {
	for (int i = 0; i < opeVec.size(); i++) {
		if (*ch == opeVec[i][0])
			return true;
	}
	return false;
}
// 将下一字符读取到ch当中，由于ch为指针，因此将其加一即可
void Lexer::GetChar() {
	ch++;
	currentPos++;
}
// 检查ch中的字符是否为空白，若是，则调用GetChar直至ch中进入一个非空白字符
void Lexer::GetBC() {
	while (true)
	{
		if (*ch == ' ')
			GetChar();
		else
			break;
	}
}
// 将ch中的字符连接到strToken之后
void Lexer::Concat() {
	strToken += *ch;
}
// 对strToken中的字符串查找保留字表，若它是一个保留字，则返回它的编码，否则返回-1
int Lexer::Reserve() {
	for (int i = 0; i < keyVec.size(); i++) {
		if (strToken == keyVec[i])
			return static_cast<TokenType>(i + 1);
	}
	return -1;
}
// 对strToken中的字符串查找操作符号表，若它是一个操作符号，则返回它的编码，否则返回-1
int Lexer::OpeReserve() {
	for (int i = 0; i < opeVec.size(); i++) {
		if (strToken == opeVec[i])
			return static_cast<TokenType>(i + 12);
	}
	return -1;
}
// 对strToken中的字符串查找边界符号表，若它是一个边界符号，则返回它的编码，否则返回-1
int Lexer::BoundReserve() {
	for (int i = 0; i < boundVec.size(); i++) {
		if (strToken == boundVec[i])
			return static_cast<TokenType>(i + 23);
	}
	return -1;
}
// 将搜索指示器回调一个字符位置，将ch置为空白字符
void Lexer::Retract() {
	currentPos -= 1;
	ch--;
}
// 将strToken中的标识符插入符号表
void Lexer::InsertToken(TokenType type, string value, int numValue) {
	tokenList.push_back({ type,value,numValue });
}
// 判断ch是不是关键字的字母，大写
bool Lexer::IsKeyLetter() {
	if (*ch >= 'A' && *ch <= 'Z')
		return true;
	else
		return false;
}
// 生成符号表
bool Lexer::generateTokenList() {
	int keyIndex, opeIndex, boundIndex;
	while (currentPos < targetCode.size()) {
		GetBC();
		if (IsLetter()) {
			while (IsLetter() || IsDigit()) {
				Concat();
				GetChar();
			}
			InsertToken($ID, strToken, NULL);
		}
		else if(IsKeyLetter()){
			while (IsKeyLetter() || IsDigit()) {
				Concat();
				GetChar();
			}
			keyIndex = Reserve();
			if (keyIndex == -1) {
				// 如果它不是关键字，那么报错
				return false;
			}
			else {
				InsertToken(static_cast<TokenType>(keyIndex), strToken, NULL);
			}
		}
		else if(IsDigit()){
			while (IsDigit())
			{
				Concat();
				GetChar();
			}
			InsertToken($INT, strToken, stoi(strToken));
		}
		// { "+","-","*","/",":=","=","<>",">",">=","<","<=" }
		else if (*ch == '+') {
			Concat();
			GetChar();
			InsertToken($ADD, strToken, NULL);
		}
		else if (*ch == '-') {
			Concat();
			GetChar();
			InsertToken($SUB, strToken, NULL);
		}
		else if (*ch == '*') {
			Concat();
			GetChar();
			InsertToken($MUL, strToken, NULL);
		}
		else if (*ch == '/') {
			Concat();
			GetChar();
			InsertToken($DIV, strToken, NULL);
		}
		else if (*ch == '=') {
			Concat();
			GetChar();
			InsertToken($EQUAL, strToken, NULL);
		}
		else if (*ch == '>') {
			Concat();
			GetChar();
			InsertToken($GREATER, strToken, NULL);
		}
		else if (*ch == '<') {
			Concat();
			GetChar();
			InsertToken($LESS, strToken, NULL);
		}
		else if (*ch == ':') {
			if (*(ch + 1) == '=') {
				Concat();
				GetChar();
			}
			else
				return false;
			Concat();
			GetChar();
			InsertToken($ASSIGN, strToken, NULL);
		}
		else if (*ch == '>') {
			if (*(ch + 1) == '=') {
				Concat();
				GetChar();
			}
			else
				return false;
			Concat();
			GetChar();
			InsertToken($EQUGREAT, strToken, NULL);
		}
		else if (*ch == '<') {
			if (*(ch + 1) == '=') {
				Concat();
				GetChar();
			}
			else
				return false;
			Concat();
			GetChar();
			InsertToken($EQULESS, strToken, NULL);
		}
		else if (*ch == '<') {
			if (*(ch + 1) == '>') {
				Concat();
				GetChar();
			}
			else
				return false;
			Concat();
			GetChar();
			InsertToken($NOEQUAL, strToken, NULL);
		}
		// { "(",")",";","," }
		else if (*ch == '(') {
			Concat();
			GetChar();
			InsertToken($LEFTBRACKET, strToken, NULL);
		}
		else if (*ch == ')') {
			Concat();
			GetChar();
			InsertToken($RIGHTBRACKET, strToken, NULL);
		}
		else if (*ch == ';') {
			Concat();
			GetChar();
			InsertToken($ENDSYM, strToken, NULL);
		}
		else if (*ch == ',') {
			Concat();
			GetChar();
			InsertToken($COMMA, strToken, NULL);
		}

		strToken = "";
	}
	return true;
}