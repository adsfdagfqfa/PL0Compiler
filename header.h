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

extern int nextquad;//����,��ǰָ���ַ
extern int tempName;
struct Comtab//�����ʶ���Ľṹ��
{
	string name;//��ʶ������
	int kind;//��ʶ�������ࣨ�������Ǳ�����,0��ʾ������1��ʾ����
	int value;//��ֵ
};

struct Quadruple//�����ʶ���Ľṹ��
{
	string insType;//��������
	string arg1 ;//������1
	string arg2 ;//������2
	string result;//���
	Quadruple() {//�������
		arg1 = "_";
		arg2 = "_";
		result = "_";
	}
};

extern vector<Comtab> table;//���ű�
extern vector<Quadruple> intermediateCode;//�м����

/* ------ �ʷ����� ------ */
// ���ʷ����Լ���Ӧ�������ֱ�����ö�ٵ���
enum TokenType {
	$ERROR,
	$PROGRAM,$BEGIN,$END,$CONST,$VAR,$WHILE,$DO,$IF,$THEN, // �ؼ������Ƿ�
	$ID, // ��ʶ��
	$INT, // ����
	$ADD,$SUB,$MUL,$DIV,$ASSIGN,$EQUAL,$NOEQUAL,$GREATER,$EQUGREAT,$LESS,$EQULESS,$LEFTBRACKET,$RIGHTBRACKET,$ENDSYM,$COMMA
	// ��������
};
// ���ʷ����б���
struct Token
{
	TokenType type;
	string value;
	int numValue;
};

class Lexer {
private:
	vector<Token> tokenList;
	// ������¶���ȥ��Դ�����ַ�
	char* ch;
	// ��Ź��ɵ��ʷ��ŵ��ַ���
	string strToken;
	// ��ŵ�ǰָ���λ��
	size_t currentPos;
	// ���������ַ�������
	string targetCode;
public:
	Lexer(string& oriCode);
	// ��ȡ���ű�
	vector<Token> getTokenList();
	// �ж�ch�е��ַ��Ƿ�Ϊ��ĸ
	bool IsLetter();
	// �ж�ch�е��ַ��Ƿ�Ϊ����
	bool IsDigit();
	// �ж�ch�е��ַ��Ƿ�Ϊ������ĵ�index��
	bool ChIsOperator(int index);
	// �ж�str�Ƿ�Ϊ�����
	bool StrIsOperator();
	// �ж�ch�ַ��Ƿ��Ǳ߽��
	bool IsBound();
	// ����һ�ַ���ȡ��ch���У�����chΪָ�룬��˽����һ����
	void GetChar();
	// ���ch�е��ַ��Ƿ�Ϊ�հף����ǣ������GetCharֱ��ch�н���һ���ǿհ��ַ�
	void GetBC();
	// ��ch�е��ַ����ӵ�strToken֮��
	void Concat();
	// ��strToken�е��ַ������ұ����ֱ�������һ�������֣��򷵻����ı��룬���򷵻�-1
	int Reserve();
	// ��strToken�е��ַ������Ҳ������ű�������һ���������ţ��򷵻����ı��룬���򷵻�-1
	int OpeReserve();
	// ��strToken�е��ַ������ұ߽���ű�������һ���߽���ţ��򷵻����ı��룬���򷵻�-1
	int BoundReserve();
	// ������ָʾ���ص�һ���ַ�λ�ã���ch��Ϊ�հ��ַ�
	void Retract();
	// ��strToken�еı�ʶ��������ű�
	void InsertToken(TokenType type, string value, int numValue);
	bool IsKeyLetter();
	// ���ɷ��ű�
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





// ���ʷ����б���
#endif // MYCLASS_H