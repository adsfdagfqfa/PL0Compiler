#include "header.h"
#include <set>

// �﷨������
/*
��<���ʽ>��[+|-]�� | <���ʽ> <�ӷ������> <��>��--��ݹ�
��<��>��<����> | <��> <�˷������> <����>��--��ݹ�

�ķ���
<����>��<�����ײ�> <�ֳ���>
<�����ײ�>��PROGRAM <��ʶ��>
<�ֳ���>��[<����˵��>][<����˵��>]<���>��ע��[ ]�е������ѡ��
<����˵��>��CONST <��������>{��<��������>} ; ��ע�� { }�е����ʾ���ظ����ɴΣ�
<��������>��<��ʶ��>:=<�޷�������>
<�޷�������>��<����>{<����>}
<����˵��>��VAR<��ʶ��>{��<��ʶ��>};
<��ʶ��>��<��ĸ>{<��ĸ> | <����>}
<�������>��BEGIN <���>{; <���>} END
<���>��<��ֵ���> | <������� >| <ѭ�����> | <�������> | <�����>
<��ֵ���>��<��ʶ��>:=<���ʽ>
<���ʽ>��[+|-]�� <EXPRESSION>
<EXPRESSION>��<�ӷ������> <��> <EXPRESSION> | ��
<��>��<����> <ITEM>
<ITEM>��<�˷������> <����> <ITEM> | ��
<����>��<��ʶ��> |<�޷�������> | (<���ʽ>)
<�ӷ������>�� + | -
<�˷������>�� * | /
<�������>��IF <����> THEN <���>
<ѭ�����>��WHILE <����> DO <���>
<����>��<���ʽ> <��ϵ�����> <���ʽ>
<��ϵ�����>�� = | <> | < | <= | > | >=
<��ĸ>��a | b ��| x | y | z
<����>��0 | 1 | �� | 8| 9
*/

/*
FIRST���ϣ�
FIRST(����˵��) = { CONST }
FIRST(����˵��) = { VAR }
FIRST(��ֵ���) = { a~z }
FIRST(�������) = { IF }
FIRST(ѭ�����) = { WHILE }
FIRST(�������) = { BEGIN }
FIRST(�ӷ������) = { + , - }
FIRST(�˷������) = { * , / }
FOLLOW���ϣ�
FOLLOW(EXPRESSION) = { ) , END , DO , THEN , ��ϵ����� , ;}
FOLLOW(ITEM) = { + , -  , ) , END , DO , THEN , ��ϵ�����, ;}
*/

Comtab* findVariable(const std::string& name) {
	for (auto& entry : table) {
		if (entry.name == name) {
			return &entry;
		}
	}
	return nullptr;
}//�ڷ��ű��в���,���ڷ���ָ�룬�����ڷ��ؿ�ָ��


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

// ��ȡ��p�еĳ���
bool Parser::readline() {
	// ������ȫ������һ��
	if (p >= code.size()) {
		// ��line��������һ����ʾ���������Ԫ��
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
	// ��ȡ��һ�г���
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

// <����>��<�����ײ�> <�ֳ���>
bool Parser::program() {
	// ��ȡ��һ�г���
	bool b = readline();
	if (b == true) {
		// ��������ײ��ķ���
		b = head();
		if (b == true) {
			// ����ֳ���ķ���
			b = block();
		}
	}
	if (b == false) {
		cout << "��ǰ������䣺" << code[p - 1] << endl;
	}
	else {
		// �����ʱline[i].type������ERROR��˵����仹û��ȫ�������꣬����
		if (line[i].type != 0) {
			b = false;
			cout << "��ǰ������䣺" << code[p - 1] << endl;
		}
	}
	return b;
}

// <�����ײ�>��PROGRAM <��ʶ��>
bool Parser::head() {
	bool b = false;
	// �жϵ����Ƿ�Ϊ�ؼ���PROGRAM
	if (line[i].type == 1) {
		i++;
		// �ж��Ƿ���Ҫ��ȡ��һ�г���
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����PROGRAM�����ж���һ�������Ƿ�Ϊ��ʶ��
		Comtab comtab;
		b = identifier(&comtab);
	}
	return b;
}

// <�ֳ���>��[<����˵��>][<����˵��>]<���>
// FIRST(����˵��) = { CONST }
// FIRST(����˵��) = { VAR }
bool Parser::block() {
	vector<int> NextList;
	bool b = false;
	// �ж��Ƿ��г���˵��CONST
	if (line[i].type == 4) {
		// ����CONST������볣��˵���ķ���
		b = constSpecification();
		if (b == false) {
			return b;
		}
	}
	// �ж��Ƿ��б���˵��VAR
	if (line[i].type == 5) {
		// ����VAR����������˵���ķ���
		b = varSpecification();
		if (b == false) {
			return b;
		}
	}
	// �������ķ���
	b = statement(NextList);
	return b;
}

// <��ʶ��>��<��ĸ>{<��ĸ> | <����>}
bool Parser::identifier(Comtab* p ) {//����ָ�����������ֵΪʶ��ı�ʶ��������
	bool b = false;
	// �жϵ����Ƿ�Ϊ��ʶ��
	if (line[i].type == 10) {
		p->name = line[i].value;//��¼��ʶ�������ֲ����ء�
	    i++;
		b = true;

		if (i >= line.size()) {
			b = readline();
		}
	}
	return b;
}

// <����˵��>��CONST <��������>{��<��������>} ;
bool Parser::constSpecification() {
	bool b = false;
	// �жϵ����Ƿ�ΪCONST
	if (line[i].type == 4) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����CONST������볣������ķ���
		b = constDefination();
	}
	else 
		return false;
	// ����������ţ������ѭ����������������
	while ((b==true) && (line[i].type == 26)) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ���볣������ķ���
		b = constDefination();
	}
	if (b == true) {
		// �жϵ����Ƿ�Ϊ�ֺ�
		if (line[i].type == 25) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
	}
	return b;
}

// <����˵��>��VAR<��ʶ��>{��<��ʶ��>};
bool Parser::varSpecification() {
	bool b = false;
	// �жϵ����Ƿ�ΪVAR
	if (line[i].type == 5) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����VAR��������ʶ���ķ���

		Comtab comtab;
		comtab.kind = 1;//1��ʾ����
		b = identifier(&comtab);
		Comtab* p = findVariable(comtab.name);
		if (p != nullptr) {//һ������ֱ�ӷ���false����
			return false;
		}
		table.push_back(comtab);
	}
	else 
		return false;
	// ����������ţ������ѭ����������ʶ��
	while ((b == true) && (line[i].type == 26)) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		Comtab comtab;
		comtab.kind = 1;//1��ʾ����
		b = identifier(&comtab);
		Comtab* p = findVariable(comtab.name);
		if (p != nullptr) {//һ������ֱ�ӷ���false����
			return false;
		}
		table.push_back(comtab);
	}
	if (b == true) {
		// �жϵ����Ƿ�Ϊ�ֺ�
		if (line[i].type == 25) {
			i++;
			if (i >= line.size()) {
				b = readline();
			}
		}
	}
	return b;
}

// <��������>��<��ʶ��>:=<�޷�������>
bool Parser::constDefination() {
	bool b = false;
	// �����ʶ�����ж�

	Comtab comtab;
	comtab.kind = 0;//0��ʾ����
	b = identifier(&comtab);

	Comtab* p = findVariable(comtab.name);//�ڱ��ֲ�ѯ��һ������ֱ�ӷ��ؿ�
	if (p != nullptr) {
		return false;
	}

	if (b == true) {
		// �жϵ����Ƿ�Ϊ��:=��
		if (line[i].type == 16) {
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// �жϵ����Ƿ�Ϊ�޷�������
			b = unsignedINT();
		}
		else
			return false;//���򱨴�
	}

	table.push_back(comtab);//������ű�

	return b;
}

// <?��������>��<����>{<����>}
bool Parser::unsignedINT() {
	bool b = false;
	// �жϵ����Ƿ�Ϊ�޷�������
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
<���>��<��ֵ���> | <������� >| <ѭ�����> | <�������> | <�����>
FIRST(��ֵ���) = { a~z }
FIRST(�������) = { IF }
FIRST(ѭ�����) = { WHILE }
FIRST(�������) = { BEGIN }
*/
bool Parser::statement(vector<int> &NextList) {
	bool b = false;
	// �жϵ����Ƿ�Ϊ��ʶ��
	if (line[i].type == 10) {
		b = assignStatement(NextList);
	}
	// �жϵ����Ƿ�ΪIF
	else if (line[i].type == 8) {
		b = ifStatement(NextList);
	}
	// �жϵ����Ƿ�ΪWHILE
	else if (line[i].type == 6) {
		b = whileStatement(NextList);
	}
	// �жϵ����Ƿ�ΪBEGIN
	else if (line[i].type == 2) {
		b = compoundStatement(NextList);
	}
	// �ж��Ƿ�Ϊ�����
	else if (line[i].type == 0 || line[i].type == 25 || line[i].type == 3) {
		b = true;
	}
	return b;
}

// <��ֵ���>��<��ʶ��>:=<���ʽ>
bool Parser::assignStatement(vector<int>& NextList) {
	bool b = false;
	// �жϵ����Ƿ�Ϊ��ʶ��
	Comtab comtab;//��ʶ��
	string s; //���ʽ
	b = identifier(&comtab);
	Comtab* p = findVariable(comtab.name);//��ȡ���ű��ָ��
	if (p == nullptr || p->kind == 0)//pΪ�ջ���pΪ����
		return false;
	if (b == false) {//���Ǳ�ʶ��
		return false;
	}
	// �жϵ����Ƿ�Ϊ��:=��
	if (line[i].type == 16) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����:=��������ʽ�ķ���


		b = expression(&s);
	}
	else
		return false;
	NextList.clear();//��ֵ�����nextlist
	//��������
	Quadruple quadruple;
	quadruple.insType = ":=";
	quadruple.arg1 = s;
	quadruple.result = comtab.name;//���ʽ��
	intermediateCode.push_back(quadruple);
	nextquad++;
	return b;
}

// <�������>��IF <����> THEN <���>
bool Parser::ifStatement(vector<int>&NextList) {
	vector<int> trueList;
	vector<int> falseList;
	vector<int> nextList;
	int quad;
	bool b = false;
	// �жϵ����Ƿ�ΪIF
	if (line[i].type == 8) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����IF������������ķ���
		b = condition(trueList,falseList);
		// �жϵ����Ƿ�ΪTHEN
		if ((b == true) && (line[i].type == 9)) {
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// ����THEN����������ķ���

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
		intermediateCode[idx].result = to_string(quad);//�����
	}

	std::set<int> uniqueValues(falseList.begin(), falseList.end());
	uniqueValues.insert(nextList.begin(), nextList.end());

	std::vector<int> mergedVector(uniqueValues.begin(), uniqueValues.end());
	NextList = mergedVector;
	return b;
}

// <ѭ�����>��WHILE M <����> DO M <���>
bool Parser::whileStatement(vector<int>&NextList) {
	vector<int> nextList;
	vector<int> trueList;
	vector<int> falseList;
	int quad1;
	int quad2;
	bool b = false;
	// �жϵ����Ƿ�ΪWHILE
	if (line[i].type == 6) {
		quad1 = nextquad;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ����WHILE������������ķ���
		b = condition(trueList,falseList);
		// �жϵ����Ƿ�ΪDO
		if ((b == true) && (line[i].type == 7)) {
			quad2 = nextquad;
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// ����DO����������ķ���
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
	quadruple.insType = "j";//��������ת���
	quadruple.result = to_string(quad1);
	intermediateCode.push_back(quadruple);
	nextquad++;
	return b;
}

// <�������>��BEGIN <���>{; <���>} END
bool Parser::compoundStatement(vector<int>& NextList) {
	vector<int> nextList;
	int quad;
	bool b = false;
	// �жϵ����Ƿ�ΪBEGIN
	if (line[i].type == 2) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		vector<int> next;
		
		// ����BEGIN����������ķ���
		b = statement(next);
		// �������Ϊ�ֺţ������ѭ�����������
		
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
		// �жϵ����Ƿ�ΪEND
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

// <���ʽ>��[+|-]�� <EXPRESSION>
bool Parser::expression(string* s) {
	bool b = false;
	bool t = false;//��¼�Ƿ������
	// �ж��Ƿ��С�+���� ��-��
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
	// ������ķ���
	string arg1;
	b = item(&arg1);
	if (t) {//����Ǽӷ��򲻴�������Ǽ���
		Quadruple quadruple;
		string name = "Temp";
		quadruple.result = name + to_string(tempName);;//���ʽ��������
		tempName++;//����һ���µ�����
		quadruple.insType = ":=";
		quadruple.arg1 = string("-") + arg1;
		intermediateCode.push_back(quadruple);
		nextquad++;
		arg1 = quadruple.result;
	}

	if (b == true) {
		// ����Expression�ķ���

		b = Expression(arg1, s);
	}
	

	

	return b;
}

// <EXPRESSION>��<�ӷ������> <��> <EXPRESSION> | ��
// FOLLOW(EXPRESSION) = { ) , END , DO , THEN , ��ϵ����� , ;}
bool Parser::Expression(string arg, string* s) {
	bool b = false;
	// �жϵ����Ƿ�Ϊ��+����-��
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
		// ���Ǽӷ�����������������ж�
		string arg1;
		b = item(&arg1);

		string name = "Temp";
		Quadruple quadruple;
		quadruple.insType = oper;
		quadruple.arg1 = arg;
		quadruple.arg2 = arg1;
		quadruple.result = name + to_string(tempName);;//���ʽ��
		*s = quadruple.result;
		arg1= quadruple.result;
		tempName++;//����һ���µ�����
		intermediateCode.push_back(quadruple);
		nextquad++;

		if (b == true) {
			// ����Expression�ķ���
			b = Expression(arg1, s);
		}
			
		
	}
	// �յ���������������FOLLOW�����У�ֱ�ӷ���
	else if ((line[i].type == 7) || (line[i].type == 3) || (line[i].type == 24)|| (line[i].type == 9) 
		|| ((line[i].type >= 17) && (line[i].type <= 22)) || (line[i].type == 25)) {
		*s = arg;
		return true;
	}
	return b;
}

// <��>��<����> <ITEM>
bool Parser::item(string *s) {
	bool b = false;
	// �������ӵķ���

	string arg1;
	b = factor(&arg1);
	if (b == true) {
		// ����ITEM�ķ���
		b = Item(arg1, s);
	}
	
	return b;
}

// <ITEM>��<�˷������> <����> <ITEM> | ��
// FOLLOW(ITEM) = { + , -  , ) , END , DO , THEN , ��ϵ�����, ;}
bool Parser::Item(string arg,string*s) {
	bool b = false;
	string oper;
	// �жϵ����Ƿ�Ϊ��*����/��
	if ((line[i].type == 14) || (line[i].type == 15)) {
		oper = line[i].value;
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ���ǳ˷����������������ӵķ���
		string arg1;
		b = factor(&arg1);

		string name = "Temp";
		Quadruple quadruple;
		quadruple.insType = oper;
		quadruple.arg1 = arg;
		quadruple.arg2 = arg1;
		quadruple.result = name + to_string(tempName);;//���ʽ��

		tempName++;//����һ���µ�����
		*s = quadruple.result;
		arg1= quadruple.result;
		intermediateCode.push_back(quadruple);
		nextquad++;
		
		if (b == true) {
			// ����ITEM�ķ���
			b = Item(arg1, s);
		}
	}
	// �յ���������������FOLLOW�����У�ֱ�ӷ���
	else if((line[i].type == 12) || (line[i].type == 13) || (line[i].type == 7) || (line[i].type == 3) || (line[i].type == 24) 
		|| (line[i].type == 9) || ((line[i].type >= 17) && (line[i].type <= 22)) || (line[i].type == 25)){
		*s = arg;
		return true;
	}
	return b;
}

// <����>��<��ʶ��> | <�޷�������> | (<���ʽ>)
bool Parser::factor(string* s) {
	bool b = false;
	// �жϵ����Ƿ�Ϊ��ʶ��
	if (line[i].type == 10) {
		
		Comtab* comtab = findVariable(line[i].value);//Ѱ���Ƿ���ڱ�ʶ��
		if (comtab == nullptr)
			return false;
		*s = comtab->name;//����ҵ��ͽ�����p��name��ֵΪname

		i++;
		b = true;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
	}
	// �жϵ����Ƿ�Ϊ�޷�������
	else if (line[i].type == 11) {

		*s = to_string(line[i].numValue);//��ʱΪ�޷�������
		i++;
		b = true;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
	}
	// �жϵ����Ƿ�Ϊ��(��
	else if (line[i].type == 23) {
		i++;
		if (i >= line.size()) {
			b = readline();
			if (b == false) {
				return b;
			}
		}
		// ���ǡ�(�����������ʽ�ķ���
		b = expression(s);
		// �жϵ����Ƿ�Ϊ��)��
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

// <����>��<���ʽ> <��ϵ�����> <���ʽ>
bool Parser::condition(vector<int>& trueList,vector<int>& falseList) {

	bool b = false;
	// ������ʽ�ķ���
	string arg1;//���ⱨ����������
	string oper;
	string arg2;
	b = expression(&arg1);
	if (b == true) {
		// �жϵ����Ƿ�Ϊ��ϵ�����
		if ((line[i].type >= 17) && (line[i].type <= 22)) {
			oper = line[i].value;
			i++;
			if (i >= line.size()) {
				b = readline();
				if (b == false) {
					return b;
				}
			}
			// ���ǹ�ϵ��������������ʽ�ķ���
			b = expression(&arg2);
		}
	}
	trueList.push_back(nextquad);
	falseList.push_back(nextquad + 1);

	//�м�������ɲ��֡�
	Quadruple quadruple1;
	quadruple1.insType = string("j") + oper;
	quadruple1.arg1 = arg1;
	quadruple1.arg2 = arg2;
	intermediateCode.push_back(quadruple1);
	nextquad++;


	Quadruple quadruple2;
	quadruple2.insType = "j";//��������ת���
	quadruple2.result = "0";
	intermediateCode.push_back(quadruple2);
	nextquad++;
	return b;
}