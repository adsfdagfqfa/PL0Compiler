#include "header.h"

ifstream fileRead;
istringstream wordRead;

int tempName = 0;//��ʱ�����ĺ�׺
int nextquad = 100;//�м�������ʼ��ַ
vector<Comtab> table;//���ű���󳤶�Ϊ500
vector<Quadruple> intermediateCode;//�м����
int main() {
	string fileName, oriCode;
	vector<string> input;
	cout << "������Ҫִ�еĳ����ļ���(���·��/����·��): " << endl;
	cin >> fileName;

	fileRead.open(fileName);
	if (!fileRead.is_open()) {
		cout << "�޷���ָ���ļ�: " << fileName << endl;
		return -1;
	}
	cout << "Դ����Ϊ: " << endl;
	while (getline(fileRead, oriCode)) {
		cout << oriCode << endl;
		if (oriCode.length() != 0) {
		    input.push_back(oriCode);
		}
	}
		
	fileRead.close();

	cout << "��ʼ����: " << endl;
	//fileRead.open(fileName);
	//oriCode = "CONST x:=1,END";
	Lexer lex(oriCode);
	
	for (auto entry : input) {
		cout << entry << endl;
	}


	Parser parser(input);
	bool result = parser.program();
	if (result == true) {
		cout << "�﷨���������accepted��" << endl;
	}
	else {
		cout << "�﷨���������refused��" << endl;
	}
	
	for (auto& entry : intermediateCode) {
		cout << entry.insType<<" "<<entry.arg1<<" "<<entry.arg2<<" "<<entry.result << endl;
	}
	/*if (lex.generateTokenList()) {
		vector<Token> result = lex.getTokenList();
		for (int i = 0; i < result.size(); i++) {
			cout << result[i].type << " " << result[i].value << " " << result[i].numValue << endl;
		}
	}
	else {
		cout << "�ʷ���������" << endl;
		return -1;
	}*/
	//fileRead.close();
	return 0;
}