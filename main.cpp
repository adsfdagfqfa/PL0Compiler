#include "header.h"

ifstream fileRead;
istringstream wordRead;

int tempName = 0;//临时变量的后缀
int nextquad = 100;//中间代码的起始地址
vector<Comtab> table;//符号表，最大长度为500
vector<Quadruple> intermediateCode;//中间代码
int main() {
	string fileName, oriCode;
	vector<string> input;
	cout << "请输入要执行的程序文件名(相对路径/绝对路径): " << endl;
	cin >> fileName;

	fileRead.open(fileName);
	if (!fileRead.is_open()) {
		cout << "无法打开指定文件: " << fileName << endl;
		return -1;
	}
	cout << "源代码为: " << endl;
	while (getline(fileRead, oriCode)) {
		cout << oriCode << endl;
		if (oriCode.length() != 0) {
		    input.push_back(oriCode);
		}
	}
		
	fileRead.close();

	cout << "开始分析: " << endl;
	//fileRead.open(fileName);
	//oriCode = "CONST x:=1,END";
	Lexer lex(oriCode);
	
	for (auto entry : input) {
		cout << entry << endl;
	}


	Parser parser(input);
	bool result = parser.program();
	if (result == true) {
		cout << "语法分析结果：accepted！" << endl;
	}
	else {
		cout << "语法分析结果：refused！" << endl;
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
		cout << "词法分析出错" << endl;
		return -1;
	}*/
	//fileRead.close();
	return 0;
}