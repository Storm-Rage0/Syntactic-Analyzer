/*1750120 杨云霄 计算机3班*/
#include"lex_analyzer.h"
using namespace std;
const char* OutputType[] = { "Int_Number", "Float_Number","Keyword", "Identifier", "Type", "Delimiter", "Unknown", "EOF", "Operator","HeaderFile","MarcoDefinition" };

bool LexAnalyzer::Open_Success(bool show_detail, const string code_filename) {
	print_detail = show_detail;

	lex_infile.open(code_filename);

	if (!lex_infile.is_open()) {
		cerr << "ERROR！源代码文件打开失败！" << endl;
		return false;
	}
	return true;
}

bool LexAnalyzer::Is_Digital(const char ch) {
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}

bool LexAnalyzer::Is_Letter(const char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')//包含下划线
		return true;
	else
		return false;
}

bool LexAnalyzer::Is_Single_Operator(const char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return true;
	else
		return false;
}

bool LexAnalyzer::Is_Double_Operatorpre(const char ch) {
	if (ch == '=' || ch == '<' || ch == '>' || ch == '!')
		return true;
	else
		return false;
}

bool LexAnalyzer::Is_Double_Operatorlater(const char ch) {
	if (ch == '=')
		return true;
	else
		return false;
}

bool LexAnalyzer::Is_Blank(const char ch) {
	if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t')
		return true;
	else
		return false;
}

char LexAnalyzer::Get_Next() {
	char ch;
	ch = lex_infile.get();

	if (ch == '\n')//换行
		line_count++;
	return ch;
}

WordInfo LexAnalyzer::GetBasicWord() {
	char ch;
	string str_token;
	WordInfo word;

	while (!lex_infile.eof()) {//循环读取文本	
		ch = Get_Next();
		if (ch == '/') {//处理注释		
			char next = Get_Next();
			if (next == '/') {//单行注释			
				while (Get_Next() != '\n' && !lex_infile.eof());//到回车为止
			}
			else if ('*' == next) {// /**/注释			
				while (!lex_infile.eof()) {
					while (Get_Next() != '*' && !lex_infile.eof());//到*为止

					if (lex_infile.eof()) {//注释未闭合				
						word.type = LUNKNOWN; //未知
						word.value = "ERROR！Annotation Unfull！line: " + to_string(line_count);
						return word;
					}

					//  注释结束
					if (Get_Next() == '/')
						break;
					else {
						lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
						if (next == '\n')
							line_count--;
						word.type = LUNKNOWN; //未知
						word.value = "ERROR！Annotation Unfull！line: " + to_string(line_count);
						return word;
					}
				}
			}
			else {//这是个除号			
				lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
				if (next == '\n')
					line_count--;
				word.type = LOPERATOR; //操作符
				word.value = ch;
				return word;
			}
		}
		else if (ch == '#') {//包含宏定义/头文件
			char next;
			while (true) {//除掉空格
				next = Get_Next();
				if (next == ' ')
					continue;
				else if (Is_Letter(next)) {//可能为宏定义
					str_token += next;
					while (!lex_infile.eof()) {
						char nnext = Get_Next();
						if (!Is_Letter(nnext)) { //下一个不是字母，需要退回	
							if (nnext == '\n')
								line_count--;
							lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next

							if (str_token == "include") { //头文件
								str_token.erase(0, 7);//除去前面的include
								while (Is_Blank(nnext = Get_Next()));
								if (nnext == '<') {
									while ((nnext = Get_Next()) != '>') {
										if (nnext == ' ')
											continue;
										else if (nnext == -1 || Is_Blank(nnext)) {
											if (nnext == '\n') {
												lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
												line_count--;
											}
											word.type = LUNKNOWN; //未知
											word.value = "ERROR！Include Unfull！line: " + to_string(line_count);
											return word;
										}
										else
											str_token += nnext;
									}
									word.type = LINCLUDE;
									word.value = str_token;
								}
								else if (nnext == '"') {
									while ((nnext = Get_Next()) != '"') {
										if (Is_Blank(nnext))
											continue;
										else
											str_token += nnext;
									}
									word.type = LINCLUDE;
									word.value = str_token;
								}
								else {
									word.type = LUNKNOWN; //未知头文件
									word.value = "Warning！Unknown Headerfile: " + str_token + "; " + to_string(line_count);
								}

							}
							else if (str_token == "define") {//宏定义
								word.type = LDEFINE;
								word.value = str_token;
							}
							else {//#后未定义字符串
								word.type = LUNKNOWN; //未知定义
								word.value = "Warning! Undefined Words After \'#\': " + str_token + "; line:" + to_string(line_count);
							}

							return word;
						}
						else  //下一个还是字母，继续循环
							str_token += nnext;
					}
				}
				else {//#后乱码

					word.type = LUNKNOWN; //未知
					word.value = "ERROR! Cannot Recognize After \'#\', line: " + std::to_string(line_count);
					return word;
				}
			}
		}
		else if (Is_Digital(ch)) {
			str_token += ch;
			while (!lex_infile.eof()) {
				char next = Get_Next();
				if (!Is_Digital(next)){ //下一个不是数字，判断是否是浮点数				
					if (next == '.') {//是浮点数
						while(!lex_infile.eof()){
							next=Get_Next();
							if(!Is_Digital(next)){//浮点数下一个不是数字，需要退回
								lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
						if (next == '\n')
							line_count--;
						word.type = LFLOAT; //整数
						word.value = str_token;
						return word;
							}
						}
					}
					else {//不是浮点数，需要退回
						lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
						if (next == '\n')
							line_count--;
						word.type = LINTEGER; //整数
						word.value = str_token;
						return word;
					}
				}
				else  //下一个还是数字，继续循环
					str_token += next;
			}
		}

		else if (Is_Letter(ch)) {
			str_token += ch;
			while (!lex_infile.eof()) {
				char next = Get_Next();
				if ((!Is_Digital(next)) && (!Is_Letter(next))) { //下一个不是字母或数字，需要退回				
					lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
					if (next == '\n')
						line_count--;
					//判断是否为关键字、变量类型
					if (KEYWORDS.find(str_token) != KEYWORDS.end()) //在关键字中
						word.type = LKEYWORD;
					else if (TYPES.find(str_token) != TYPES.end()) //在变量类型中
						word.type = LTYPE;
					else //标识符
						word.type = LIDENTIFIER;

					word.value = str_token;
					return word;
				}
				else  //下一个还是字母或数字，继续循环
					str_token += next;
			}
		}
		else if (Delimiters.find(ch) != Delimiters.end()) {
			word.type = LDELIMITER; //界符
			word.value = ch;
			return word;
		}
		else if (Is_Single_Operator(ch)) {//单符号运算符		
			word.type = LOPERATOR; //操作符
			word.value = ch;
			return word;
		}
		else if (Is_Double_Operatorpre(ch)) {//判断是否为双符号运算符		
			str_token += ch;
			char next = Get_Next();

			if (next == '=') { //确定是双符号运算符			
				str_token += next;
				word.type = LOPERATOR; //操作符
				word.value = str_token;
				return word;
			}
			else {
				lex_infile.seekg(-1, ios::cur);//输入文件指针回退,因为多读了next
				if (next == '\n')
					line_count--;
				if (ch != '!')//是个单符号操作符
				{
					word.type = LOPERATOR; //操作符
					word.value = str_token;
					return word;
				}
				else// ! 未定义的符号
				{
					word.type = LUNKNOWN; //操作符
					word.value = str_token + ", line: " + std::to_string(line_count);
					return word;
				}
			}

		}
		else if (ch == -1) {//文本结束标志
			word.type = LEOF;
			word.value = "#";
			return word;
		}
		else if (Is_Blank(ch))
			continue;

		else {
			word.type = LUNKNOWN;
			word.value = "\'";
			word.value += ch;
			word.value += "\'Unknown, line: " + std::to_string(line_count);
			return word;
		}
	}

	word.type = LEOF;
	word.value = "#";
	return word;
}

WordInfo LexAnalyzer::GetWord() {
	WordInfo getword = GetBasicWord();
	string word_string;
	if (getword.type == LEOF)
		word_string = "#";
	else if (getword.type == LINTEGER)
		word_string = "num";
	else if (getword.type == LKEYWORD || getword.type == LTYPE ||getword.type == LDELIMITER || getword.type == LOPERATOR)
		word_string = getword.value;
	else if (getword.type == LTYPE)
		word_string = getword.value;
	else if (getword.type == LIDENTIFIER)
		word_string = "identifier";
	else;

	getword.word_string = word_string;

	if (print_detail)
		PrintInfo(getword);
	return getword;
}

void LexAnalyzer::PrintInfo(WordInfo word) {
	/*if (word.type == LEOF)
		return;*/
	cout << "step:" << setw(3) << step_count << " , type: " << OutputType[word.type] << " , value: " << word.value;	
	lex_analyze_result << "step:" << setw(3) << step_count << " , type: " << OutputType[word.type] << " , value: " << word.value;
	
	cout << endl;
	lex_analyze_result<<endl;
	
	step_count++;
	return;
}

LexAnalyzer::LexAnalyzer(string lexfile_name) {
	line_count = 1;
	step_count = 1;
	print_detail = false;
	lex_analyze_result.open(lexfile_name,ios::out);
}

LexAnalyzer::~LexAnalyzer() {
	if (lex_infile.is_open())
		lex_infile.close();

	if (lex_analyze_result.is_open())
		lex_analyze_result.close();
}


