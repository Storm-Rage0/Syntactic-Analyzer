#pragma once
/*1750120 杨云霄 计算机3班*/
#ifndef PARSER_BRIDGE
#define PARSER_BRIDGE
#include"syntactic_analyzer.h"
void start_syntactic_analyze(const string code_file, const string grammar_file,const string first_file,const string follow_file,const string specification_file,const string lexcial_file,
					const string items_file,const string action_goto_table_file,const string analyze_process_file) {//根据源文件和结果文件的文件名，进行分析
	SyntacticAnalyzer demo(true);
	demo.Initial(code_file, grammar_file,first_file,follow_file,specification_file,lexcial_file,items_file,action_goto_table_file,analyze_process_file);
	demo.StartAnalize();
	return;

}

#endif // !PARSER_BRIDGE
