#pragma once
/*1750120 杨云霄 计算机3班*/
#ifndef LEX_ANALYZER

#define LEX_ANALYZER

#include<iostream>
#include<fstream>
#include<set>
#include<iomanip>
#include "Tools.h" //公共函数

using namespace std;

class LexAnalyzer {
private:
	//运算符
	set<string> OPERATORS = { "+", "-", "*", "/", "=", "==", ">", ">=", "<", "<=", "!=" };

	//关键字
	set<string> KEYWORDS = { "if", "else", "return", "while","include" ,"define","using","namespace" };

	//变量类型
	set<string> TYPES = { "int", "void","double","float" };


	//界符
	set<char> Delimiters = { '(', ')', '{', '}', '[',']',',', ';','#','"','.' };

	ifstream lex_infile;
	ofstream lex_analyze_result;

	int line_count;//定位行数
	bool print_detail;//选择是否将词法分析结果输出到txt中
	int step_count;//记录步数
	bool Is_Letter(const char ch);//判断是否是字母或者下划线
	bool Is_Digital(const char ch);//判断是否是数字
	bool Is_Single_Operator(const char ch);//判断是否是单符号运算符
	bool Is_Double_Operatorpre(const char ch);//是否双符号运算符前半部分
	bool Is_Double_Operatorlater(const char ch);//是否双符号运算符后半部分
	bool Is_Blank(const char ch);//是否是空白符
	char Get_Next();//获取下一个字符，同时计算行数。
	void PrintInfo(WordInfo word);//打印词法分析信息
	WordInfo GetBasicWord();//获取词法符号

public:
	LexAnalyzer(string lexfile_name);
	~LexAnalyzer();
	bool Open_Success(bool show_detail = true, const string code_filename = "./raw_data/test.cpp");//文件是否读到
	WordInfo GetWord();//获取文法符号，并进行打印信息。

};


#endif
