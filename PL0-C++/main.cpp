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

	Parser parser(input);
	bool result = parser.program();
	if (result == true) {
		cout << "语法分析结果：accepted！" << endl;
		cout << "词法分析单词符号序列如下：" << endl;
		for (int i = 0; i < line.size(); i++) {
			cout << line[i].type << " " << line[i].value << " " << line[i].numValue << endl;
		}

		cout << "符号表如下：" << endl;
		int addr = 100;
		for (auto& entry : table) {
			cout << entry.name << "  " << entry.kind << endl;
		}

		fstream out;
		out.open("target.txt", ios::out);
		if (!out.is_open()) {
			cerr << "无法打开文件!" << std::endl;
			return 1; // 返回错误代码
		}
		cout << "中间代码如下：" << endl;
		for (auto& entry : intermediateCode) {
			cout << addr << ": " << entry.insType << " " << entry.arg1 << " " << entry.arg2 << " " << entry.result << endl;
			out << addr << ": " << entry.insType << " " << entry.arg1 << " " << entry.arg2 << " " << entry.result << endl;
			addr++;
		}
		out.close();
		cout << "中间代码已写入文件：target.txt当中" << endl;
	}
	else {
		cout << "语法分析结果：refused！" << endl;
	}
	return 0;
}