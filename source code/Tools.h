#pragma once

#ifndef TOOLS
#define TOOLS

#include <vector>
#include <string>

using namespace std;

enum LEXICAL_TYPE {
	LINTEGER, LFLOAT, LKEYWORD, LIDENTIFIER, LTYPE, LDELIMITER, LUNKNOWN, LEOF, LOPERATOR, LINCLUDE, LDEFINE,
	LBEGIN, LCFLOAT, LCDOUBLE, LCCHAR, LCSTRING, LCERROR, LOERROR
};

struct WordInfo//词法属性
{
	LEXICAL_TYPE type;//词类型
	string value;//单词符号
	string word_string;//进行语义分析时的符号，助记符

	//仅在函数调用的产生式用到，表示函数在全局表中的序号
	//int functionIndex;//种别编码
};

struct Grammar//文法产生式
{
	string left;
	vector<string> right;
};
/*A->Ax|AAx，S->SA|x*/
/*Grammar：[{S,[SA,x]},{A,[Ax,AAX]}]
Production：[{S,[S,A]},{S,[x]},{A,[A,x]},{A,[A,A,x]}]*/

// struct Production//产生式
// {
// 	string left;
// 	vector<string> right;
// };

enum SLR_OPERATIONS { REDUCE, SHIFT, ACCEPT };//规约、移进、接受

struct SLR_operation//ACTION或者GOTO操作
{
	SLR_OPERATIONS op;//规约、移进、接受
	int state;//item中的序号，从0开始
	bool operator==(const SLR_operation& operation) const;//判断两个操作是否相同
};

//LR项目
struct LR_item {
	int production_number;//项目所对应的产生式在 SLR_productions 的序号
	int point_pos;//项目中小圆点的位置，从0开始，最大值等于产生式右部符号数目
	LR_item(int item_num, int point_num) { this->production_number = item_num, this->point_pos = point_num; };
	bool operator==(const LR_item& item) const;//判断两个item是否相同
	bool operator<(const LR_item& item) const;//没有重载<操作的时候，无法插入
};



vector<string> split_string(const string& str, const string& pattern);

#endif
