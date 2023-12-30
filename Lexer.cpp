#include "header.h"

// �ʷ�������

vector<string> keyVec = { "PROGRAM","BEGIN","END","CONST","VAR","WHILE","DO","IF","THEN" };
vector<string> opeVec = { "+","-","*","/",":=","=","<>",">",">=","<","<=" };
vector<string> boundVec = { "(",")",";","," };


Lexer::Lexer(string& oriCode) {
	targetCode = oriCode;
	strToken = "";
	ch = &targetCode[0];
	currentPos = 0;
}
// ��ȡ���ű�
vector<Token> Lexer::getTokenList() { return tokenList; }
// �ж�ch�е��ַ��Ƿ�Ϊ��ĸ
bool Lexer::IsLetter() {
	if (*ch >= 'a' && *ch <= 'z')
		return true;
	else
		return false;
}
// �ж�ch�е��ַ��Ƿ�Ϊ����
bool Lexer::IsDigit() {
	if (*ch >= '0' && *ch <= '9')
		return true;
	else
		return false;
}
// �ж�ch�е��ַ��Ƿ�Ϊ������ĵ�index��
bool Lexer::ChIsOperator(int index) {
	for (int i = 0; i < opeVec.size(); i++) {
		if (*ch == opeVec[i][index])
			return true;
	}
	return false;
}
// �ж�str�Ƿ�Ϊ�����
bool Lexer::StrIsOperator() {
	auto it = find(opeVec.begin(), opeVec.end(), strToken);
	if (it != opeVec.end())
		return true;
	else
		return false;
}
// �ж�ch�ַ��Ƿ��Ǳ߽��
bool Lexer::IsBound() {
	for (int i = 0; i < opeVec.size(); i++) {
		if (*ch == opeVec[i][0])
			return true;
	}
	return false;
}
// ����һ�ַ���ȡ��ch���У�����chΪָ�룬��˽����һ����
void Lexer::GetChar() {
	ch++;
	currentPos++;
}
// ���ch�е��ַ��Ƿ�Ϊ�հף����ǣ������GetCharֱ��ch�н���һ���ǿհ��ַ�
void Lexer::GetBC() {
	while (true)
	{
		if (*ch == ' ')
			GetChar();
		else
			break;
	}
}
// ��ch�е��ַ����ӵ�strToken֮��
void Lexer::Concat() {
	strToken += *ch;
}
// ��strToken�е��ַ������ұ����ֱ�������һ�������֣��򷵻����ı��룬���򷵻�-1
int Lexer::Reserve() {
	for (int i = 0; i < keyVec.size(); i++) {
		if (strToken == keyVec[i])
			return static_cast<TokenType>(i + 1);
	}
	return -1;
}
// ��strToken�е��ַ������Ҳ������ű�������һ���������ţ��򷵻����ı��룬���򷵻�-1
int Lexer::OpeReserve() {
	for (int i = 0; i < opeVec.size(); i++) {
		if (strToken == opeVec[i])
			return static_cast<TokenType>(i + 12);
	}
	return -1;
}
// ��strToken�е��ַ������ұ߽���ű�������һ���߽���ţ��򷵻����ı��룬���򷵻�-1
int Lexer::BoundReserve() {
	for (int i = 0; i < boundVec.size(); i++) {
		if (strToken == boundVec[i])
			return static_cast<TokenType>(i + 23);
	}
	return -1;
}
// ������ָʾ���ص�һ���ַ�λ�ã���ch��Ϊ�հ��ַ�
void Lexer::Retract() {
	currentPos -= 1;
	ch--;
}
// ��strToken�еı�ʶ��������ű�
void Lexer::InsertToken(TokenType type, string value, int numValue) {
	tokenList.push_back({ type,value,numValue });
}
// �ж�ch�ǲ��ǹؼ��ֵ���ĸ����д
bool Lexer::IsKeyLetter() {
	if (*ch >= 'A' && *ch <= 'Z')
		return true;
	else
		return false;
}
// ���ɷ��ű�
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
				// ��������ǹؼ��֣���ô����
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