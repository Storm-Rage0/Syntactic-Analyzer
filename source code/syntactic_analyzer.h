#pragma once
/*1750120 杨云霄 计算机3班*/
#ifndef SYNTACTIC_ANALYZER

#define SYNTACTIC_ANALYZER

#include "lex_analyzer.h"
#include <fstream>
#include <iostream>
#include <map>


class SyntacticAnalyzer {
private:
	bool print_detail_;

	string codefile_name;//源代码文件
	string lexcial_name;//文法产生式序列文件
	string grammarfile_name;//文法产生式文件
	string firstset_name;//first集文件
	string followset_name;//follow集文件
	string specification_name;//项目集规范族文件
	string production_name;//分隔后的文法产生式
	string itemset_name;//文法项目文件
	string action_goto_table_name;//action goto表文件
	string analyze_process_name;//分析过程文件
	string symbols_name;//文法符号文件

	vector<Grammar> SLR_grammars;//文法产生式
	vector<Grammar> SLR_productions;//将gammars_中的产生式拆开成多个产生式，方便编号。
	set<string> grammar_symbols;//语法的所有符号，包括终结符与非终结符。
	map<string, set<string>> first_set, follow_set;//First集合、Follow集合
	vector<set<LR_item>> items_set_specification_group;//LR0项目集规范族
	set<LR_item> lr_items;//SLR所有项目
	map<pair<int, string>, SLR_operation> action_goto_table;//action 与 goto 表的融合
	ofstream syntactic_analyzer_printer_;//语法分析过程打印
	vector<string> move_conclude_string_stack_;//字符串栈
	vector<int> state_sequence_stack_;//状态序列栈


	bool IsNonTerminalSymbol(const string& symbol);//判断是否为非终结符开头的串

	bool GenerateProduction();//从grammar.txt中生成产生式
	void GenerateAugmentedGrammar();//生成拓广文法
	void GenerateFirstSet();//生成First集合
	void GenerateFollowSet();//生成Follow集合
	void GenerateGrammarSymbolSet();//生成文法符号集合
	bool GenerateNormalFamilySet();//生成项目集规范族、Action与Goto表，返回false则说明文法不是SLR，带有冲突
	void GenerateLR_items();//生成LR0所有项目
	set<LR_item> GenerateItemClosureSet(const LR_item&);//生成某个项目的闭包集合
	set<LR_item> GenerateItemsClosureSet(const set<LR_item>&);//生成某个项目集的闭包集合
	set<string> GetProductionFirstSet(const vector<string>&);//获取某个串的First集合

	void ShowProductions();//打印产生式
	void ShowGrammars();//打印文法
	void ShowFirstSet();//打印First集合
	void ShowFollowSet();//打印Follow集合
	void ShowGrammarSymbolSet();//打印GrammarSymbol集合
	void ShowLR_items();//打印LR_items集合
	void ShowClosure();//打印Closure集合，debug时候使用
	void ShowSLRError(const set<LR_item>&);//打印SLR分析中存在冲突的规范族，出现错误的时候直接显示在CMD窗口上
	void ShowSpecificationGroupSet();//打印所有规范族
	void ShowActionGotoTable();//打印Action和Goto表

	void ShowAnalyzeDetail(int step, const SLR_operation& sl_op);//打印语法分析过程

public:
	SyntacticAnalyzer(bool show_detail = true);
	~SyntacticAnalyzer();
	void Initial(const string code_file, const string grammar_file, const string first_file, const string follow_file, const string specification_file, const string lexcial_file,
		const string items_file, const string action_goto_table_file, const string analyze_process_file);//初始化各个文件名
	bool StartAnalize();//开始进行语法分析


};


#endif
