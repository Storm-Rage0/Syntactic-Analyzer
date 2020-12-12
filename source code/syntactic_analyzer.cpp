/*1750120 杨云霄 计算机3班*/
#include "syntactic_analyzer.h"

void SyntacticAnalyzer::Initial(const string code_file, const string grammar_file, const string first_file, const string follow_file, const string specification_file, const string lexcial_file,
	const string items_file, const string action_goto_table_file, const string analyze_process_file) {
	this->codefile_name = code_file;//源代码文件
	this->lexcial_name = lexcial_file;//文法产生式序列文件
	this->grammarfile_name = grammar_file;//文法产生式文件
	this->firstset_name = first_file;//first集文件
	// firstset_name = "ffist.txt";//first集文件

	this->followset_name = follow_file;//follow集文件
	this->specification_name = specification_file;//项目集规范族文件
	this->production_name = "productions.txt";//分隔后的文法产生式
	this->itemset_name = items_file;//文法项目文件
	this->action_goto_table_name = action_goto_table_file;//action goto表文件
	this->analyze_process_name = analyze_process_file;//分析过程文件
	this->symbols_name = "symbols.txt";//文法符号文件

	if (GenerateProduction()) {
		GenerateAugmentedGrammar();
		GenerateFirstSet();
		GenerateFollowSet();
		GenerateGrammarSymbolSet();
		GenerateLR_items();
		GenerateNormalFamilySet();
	}

	if (this->print_detail_) {

		syntactic_analyzer_printer_.open(this->analyze_process_name);
		if (!syntactic_analyzer_printer_.is_open()) {
		}
		else
			syntactic_analyzer_printer_ << "步骤, 状态栈, 符号栈, 解释说明" << endl;

		// PrintBuildGrammarDetails();//打印构建SLR分析表的详细过程以及结果。（会自动根据print_detail_来判断是否打印）
		ShowProductions();
		ShowFirstSet();
		ShowFollowSet();
		ShowGrammarSymbolSet();
		ShowLR_items();
		ShowSpecificationGroupSet();
		ShowActionGotoTable();

	}
}

set<string> SyntacticAnalyzer::GetProductionFirstSet(const vector<string>& symbol_string) {
	set<string> first;
	for (auto iter1 = symbol_string.begin(); iter1 != symbol_string.end(); ++iter1) {
		if (!IsNonTerminalSymbol(*iter1)) {//循环到终结符		
			first.insert(*iter1);
			break;//终结符需要跳出循环
		}
		//iter1为非终结符
		for (auto iter2 = first_set[*iter1].begin(); iter2 != first_set[*iter1].end(); ++iter2) {//遍历产生式右部符号对应的First集合	
			if ((*iter2) != "$" && first.find(*iter2) == first.end())//非空也不重复
				first.insert(*iter2);
		}
		//当前符号first集合中没有空$，循环结束
		if (first_set[*iter1].find("$") == first_set[*iter1].end())
			break;
		//每一个符号的first都包含空，且已经循环到最后一个符号；这个时候整个串的first集合也应该包含空
		if (iter1 + 1 == symbol_string.end() && first.find("$") == first.end())
			first.insert("$");
	}
	return first;
}

bool SyntacticAnalyzer::GenerateProduction() {
	ifstream grammar_reader;

	grammar_reader.open(grammarfile_name);
	// grammar_reader.open("grammar.txt");

	if (!grammar_reader.is_open()) {
		cout << "文法文件无法打开！" << endl;
		return false;
	}

	string grammar_str;
	while (!grammar_reader.eof()) {
		getline(grammar_reader, grammar_str);
		if (grammar_str.length() == 0)//空串
			continue;

		string left;
		vector<string> right;

		size_t left_pos = grammar_str.find_first_of("->");
		if (left_pos < 0) {
			cout << "出现不可识别的文法！" << endl;
			grammar_reader.close();
			return false;
		}
		left = grammar_str.substr(0, left_pos);

		//跳过"->"
		grammar_str = grammar_str.substr(left_pos + 2);

		while (true) { //处理产生式右部	
			size_t right_pos = grammar_str.find_first_of("|");
			string temp_production;//记录产生式右部的一个候选式
			if (right_pos == string::npos)//最后一个候选式
				temp_production = grammar_str;
			else
				temp_production = grammar_str.substr(0, right_pos);

			right.push_back(temp_production);

			vector<string> split_production = split_string(temp_production, " ");//将产生式分割
			SLR_productions.push_back({ left,  split_production });
			//添加终结符的grammar_symbols集合
			for (auto iter = split_production.begin(); iter != split_production.end(); ++iter)
				if (!IsNonTerminalSymbol(*iter) && (*iter) != "$")
					grammar_symbols.insert(*iter);

			if (right_pos == string::npos)
				break;

			grammar_str = grammar_str.substr(right_pos + 1);

		}

		SLR_grammars.push_back({ left, right });
	}

	grammar_reader.close();
	if (SLR_productions.size() == 0)
		return false;
	return true;

}

void SyntacticAnalyzer::GenerateAugmentedGrammar() {

	string left = "Start";
	vector <string> right;
	if (SLR_productions.size() == 0) //文法错误

		return;

	right.push_back(SLR_productions[0].left);
	SLR_productions.insert(SLR_productions.begin(), { left , right });
	return;
}

void SyntacticAnalyzer::GenerateFirstSet() {
	for (auto iter = SLR_productions.begin(); iter != SLR_productions.end(); ++iter) {//遍历每一个产生式	
		first_set.insert({ iter->left, set<string>{} });//创建FirstMap
		follow_set.insert({ iter->left, set<string>{} });//创建FollowMap
		if (iter->right[0] == "$")
		{
			if (first_set[iter->left].find("$") == first_set[iter->left].end())//往first集合中添加 空$
				first_set[iter->left].insert("$");
		}
	}

	while (true) {
		bool is_change = false;
		for (auto iter1 = SLR_productions.begin(); iter1 != SLR_productions.end(); ++iter1) {//遍历每一个产生式		
			for (auto iter2 = iter1->right.begin(); iter2 != iter1->right.end(); ++iter2) {//遍历产生式右部		
				if ((*iter2) == "$")
					break;
				if (!IsNonTerminalSymbol(*iter2)) {//循环到终结符				
					if (first_set[iter1->left].find(*iter2) == first_set[iter1->left].end()) {//如果没有，则添加				
						first_set[iter1->left].insert(*iter2);
						is_change = true;
					}
					break;//终结符需要跳出循环 
				}

				for (auto iter3 = first_set[*iter2].begin(); iter3 != first_set[*iter2].end(); ++iter3) {//遍历产生式右部符号对应的First集合				
					if ((*iter3) != "$" && first_set[iter1->left].find(*iter3) == first_set[iter1->left].end()) {//非空也不重复				
						first_set[iter1->left].insert(*iter3);
						is_change = true;
					}
				}
				//当前符号first集合中没有空$，退出这条产生式的循环。
				if (first_set[*iter2].find("$") == first_set[*iter2].end())
					break;
				//每一个符号的first都包含空，且已经循环到最后一个符号；这个时候产生式左部的first也包含空
				if (iter2 + 1 == iter1->right.end() && first_set[iter1->left].find("$") == first_set[iter1->left].end()) {
					first_set[iter1->left].insert("$");
					is_change = true;
				}

			}
		}

		if (!is_change)//未发生改变，生成First完成
			break;
	}
	return;
}

void SyntacticAnalyzer::GenerateFollowSet() {
	follow_set[SLR_productions[0].left].insert("#");//文法开始符号，添加#

	while (true) {
		bool is_change = false;
		for (auto iter1 = SLR_productions.begin(); iter1 != SLR_productions.end(); ++iter1) {//遍历每个产生式		
			for (auto iter2 = iter1->right.begin(); iter2 != iter1->right.end(); ++iter2) {//遍历产生式右部每个符号			
				if (!IsNonTerminalSymbol(*iter2))//当前符号为终结符，跳过
					continue;
				//非终结符的情况
				set<string> first = GetProductionFirstSet(vector<string>(iter2 + 1, iter1->right.end()));
				for (auto iter = first.begin(); iter != first.end(); ++iter) {
					if ((*iter) != "$" && follow_set[*iter2].find(*iter) == follow_set[*iter2].end()) {//非空且还没有加入					
						follow_set[*iter2].insert(*iter);
						is_change = true;
					}
				}
				if (first.empty() || first.find("$") != first.end()) {//把产生式左部的follow集合加到当前非终结符的follow集合中				
					for (auto iter = follow_set[iter1->left].begin(); iter != follow_set[iter1->left].end(); ++iter) {
						if (follow_set[*iter2].find(*iter) == follow_set[*iter2].end()) {//还没有加入过					
							follow_set[*iter2].insert(*iter);
							is_change = true;
						}
					}
				}

			}

		}
		if (!is_change)//未发生改变，生成Follow完成
			break;
	}


	return;
}

void SyntacticAnalyzer::GenerateGrammarSymbolSet() {

	for (auto iter = first_set.begin(); iter != first_set.end(); ++iter)
		grammar_symbols.insert(iter->first);

	grammar_symbols.insert("#");//终结符#一起添加进文法符号集合中
	return;
}

void SyntacticAnalyzer::GenerateLR_items() {
	for (auto iter = SLR_productions.begin(); iter != SLR_productions.end(); iter++) {
		if (iter->right[0] == "$") {//产生式右部是空串，LR0项目 只有一个 pos用0来表示	
			lr_items.insert(LR_item{ iter - SLR_productions.begin(), -1 });//插入产生式编号与 -1（表示空）A->epsilon 只生成A->·
			continue;
		}
		int production_lenth = iter->right.size();
		for (int locate = 0; locate <= production_lenth; locate++)
			lr_items.insert(LR_item{ iter - SLR_productions.begin(), locate });//插入产生式编号与小圆点位置					
	}
	return;
}

set<LR_item> SyntacticAnalyzer::GenerateItemClosureSet(const LR_item& input_item) {
	vector<LR_item> item_stack;//用来暂存item
	item_stack.push_back(input_item);
	set<LR_item> item_set;//最终返回的item

	while (!item_stack.empty()) {//暂存的栈不空，就需要一直循环	
		//从栈中取出Item
		LR_item item = item_stack[item_stack.size() - 1];
		item_stack.pop_back();
		//插入到闭包中
		item_set.insert(item);

		if (item.point_pos == -1)
			continue;

		//小圆点在最后面，表示规约； 这里先判断，防止下面对vector的越界访问
		if (item.point_pos == SLR_productions[item.production_number].right.size())
			continue;
		//终结符
		if (!IsNonTerminalSymbol(SLR_productions[item.production_number].right[item.point_pos]))
			continue;

		string current_symbol = SLR_productions[item.production_number].right[item.point_pos];
		//非终结符
		for (auto iter = lr_items.begin(); iter != lr_items.end(); ++iter) {
			//以当前非终结符为左部，并且小圆点的位置在第0位 或者 -1位（A->·）
			if (SLR_productions[iter->production_number].left == current_symbol && (iter->point_pos == 0 || iter->point_pos == -1))
				if (item_set.find(*iter) == item_set.end())//保证之前不在set中，否则会陷入死循环
					item_stack.push_back(*iter);
		}
	}

	return item_set;
}

set<LR_item> SyntacticAnalyzer::GenerateItemsClosureSet(const set<LR_item>& items) {
	vector<LR_item> item_stack;//用来暂存item
	for (auto iter = items.begin(); iter != items.end(); ++iter)
		item_stack.push_back(*iter);
	//item_stack.push_back(input_item);
	set<LR_item> item_set;//最终返回的Item

	while (!item_stack.empty()) {//暂存的栈不空，就需要一直循环	
		//从栈中取出Item
		LR_item item = item_stack[item_stack.size() - 1];
		item_stack.pop_back();
		//插入到闭包中
		item_set.insert(item);

		//A->·
		if (item.point_pos == -1)
			continue;

		//小圆点在最后面，表示规约； 这里先判断，防止下面对vector的越界访问
		if (item.point_pos == SLR_productions[item.production_number].right.size())
			continue;
		//终结符
		if (!IsNonTerminalSymbol(SLR_productions[item.production_number].right[item.point_pos]))
			continue;

		string current_symbol = SLR_productions[item.production_number].right[item.point_pos];
		//非终结符
		for (auto iter = lr_items.begin(); iter != lr_items.end(); ++iter) {
			//以当前非终结符为左部，并且小圆点的位置在第0位 或者 -1位（A->·）
			if (SLR_productions[iter->production_number].left == current_symbol && (iter->point_pos == 0 || iter->point_pos == -1))
				if (item_set.find(*iter) == item_set.end())//保证之前不在set中，否则会陷入死循环
					item_stack.push_back(*iter);

		}
	}

	return item_set;
}

bool SyntacticAnalyzer::GenerateNormalFamilySet() {
	vector<set<LR_item>> item_stack;//用来临时存放SpecificationGroupSet
	item_stack.push_back(GenerateItemClosureSet(*lr_items.begin()));//把起始字符的Closure作为第0个规范族
	items_set_specification_group.push_back(item_stack[0]);

	while (!item_stack.empty()) {
		//从栈中取出NormaliFamilySet
		set<LR_item> item = item_stack[item_stack.size() - 1];
		item_stack.pop_back();

		//找到当前规范族的序号，不存在则current_state返回size
		int current_state = find(items_set_specification_group.begin(), items_set_specification_group.end(), item) - items_set_specification_group.begin();

		for (auto iter1 = item.begin(); iter1 != item.end(); iter1++) {//对于规范族中的每个LR0项目		
			//小圆点在最后面或-1，表示是需要规约的项目
			if ((SLR_productions[iter1->production_number].right.size() == iter1->point_pos) || (iter1->point_pos == -1)) {
				//先求follow集合
				string symbol = SLR_productions[iter1->production_number].left;//产生式左部
				//对follow集合进行遍历，加入action_goto表中，同时进行错误的判断
				for (auto iter2 = follow_set[symbol].begin(); iter2 != follow_set[symbol].end(); iter2++) {
					//action_goto_table中没有，这个时候添加进去
					if (action_goto_table.find({ current_state, *iter2 }) == action_goto_table.end()) {
						//通过当前的 状态+输入字符（这里是左部的follow集合）,对应为 规约，使用第iter1->production_number产生式
						action_goto_table.insert({ { current_state, *iter2},  {REDUCE,iter1->production_number } });
					}
					else {//表示已经存在映射规则				
						//存在映射但是却不相等，说明不是SLR文法
						if (!(action_goto_table[{ current_state, * iter2 }] == SLR_operation{ REDUCE,iter1->production_number })) {
							ShowSLRError(item);
							return false;
						}
					}
				}
			}
			else {
				//产生式右部·之后的紧接的符号
				string current_right_symbol = SLR_productions[iter1->production_number].right[iter1->point_pos];
				//GO函数，求下一个规范族
				set<LR_item> items;//存储 接受相同字符的item
				for (auto iter2 = item.begin(); iter2 != item.end(); iter2++) {
					//防止越界
					if ((iter2->point_pos == SLR_productions[iter2->production_number].right.size()) || (iter2->point_pos == -1))
						continue;

					if (SLR_productions[iter1->production_number].right[iter1->point_pos] == SLR_productions[iter2->production_number].right[iter2->point_pos])
						items.insert({ iter2->production_number, iter2->point_pos + 1 });
				}
				set<LR_item> next_normal_family = GenerateItemsClosureSet(items);

				//判断当前规范族是否已经存在
				if (find(items_set_specification_group.begin(), items_set_specification_group.end(), next_normal_family) == items_set_specification_group.end()) {//不存在				
					items_set_specification_group.push_back(next_normal_family);//插入规范族集合中
					item_stack.push_back(next_normal_family);//插入待处理堆栈中
				}
				int next_state = find(items_set_specification_group.begin(), items_set_specification_group.end(), next_normal_family) - items_set_specification_group.begin();

				//action_goto_table中没有，这个时候添加进去
				if (action_goto_table.find({ current_state, current_right_symbol }) == action_goto_table.end()) {
					//通过当前的 状态+输入字符,对应为 移进，跳转到第next_state个状态
					action_goto_table.insert({ { current_state, current_right_symbol},  {SHIFT, next_state } });
				}
				else {//表示已经存在映射规则			
					//存在映射但是却不相等，说明不是SLR文法
					if (!(action_goto_table[{ current_state, current_right_symbol }] == SLR_operation{ SHIFT, next_state })) {
						ShowSLRError(item);
						return false;
					}
				}
			}

		}//end for 规范族中的项目
	}//end while

	//插入acc状态
	int current_state2 = -1;

	for (auto iter1 = items_set_specification_group.begin(); iter1 != items_set_specification_group.end(); iter1++) {
		for (auto iter2 = iter1->begin(); iter2 != iter1->end(); iter2++)
			if (LR_item(0, 1) == *iter2) {//S->Start·		
				current_state2 = iter1 - items_set_specification_group.begin();//记录S->Start·的项目集序号
				break;
			}
		if (current_state2 >= 0)
			break;
	}

	action_goto_table[{current_state2, "#"}] = { ACCEPT, current_state2 };

	return true;
}

void SyntacticAnalyzer::ShowGrammars() {
	for (auto iter1 = SLR_grammars.begin(); iter1 != SLR_grammars.end(); iter1++) {
		cout << (*iter1).left << "->";
		for (auto iter2 = (iter1->right).begin(); iter2 != (iter1->right).end(); iter2++)
			cout << (*iter2) << "|";
		cout << "\n" << endl;
	}
	return;
}

void SyntacticAnalyzer::ShowProductions() {
	ofstream printer;
	printer.open(this->production_name);

	if (!printer.is_open()) {
		return;
	}

	for (auto iter1 = SLR_productions.begin(); iter1 != SLR_productions.end(); iter1++) {
		printer << (*iter1).left << "->";
		for (auto iter2 = (iter1->right).begin(); iter2 != (iter1->right).end(); iter2++)
			printer << (*iter2) << ' ';
		printer << endl;
	}

	return;
}

void SyntacticAnalyzer::ShowFirstSet() {
	ofstream printer;
	printer.open(this->firstset_name, ios::out);

	if (!printer.is_open()) {
		return;
	}
	printer << "First Set: \n" << endl;
	for (auto iter1 = first_set.begin(); iter1 != first_set.end(); ++iter1) {
		printer << (*iter1).first << ": ";
		int count = 0;
		int size_ = (*iter1).second.size();
		for (auto iter2 = (*iter1).second.begin(); iter2 != (*iter1).second.end(); iter2++, count++) {
			printer << (*iter2);
			if (size_ > count + 1)
				printer << " ";
		}
		printer << endl;
	}
	return;
}

void SyntacticAnalyzer::ShowFollowSet() {
	ofstream printer;
	printer.open(this->followset_name);
	if (!printer.is_open()) {
		return;
	}
	printer << "Follow Set: \n" << endl;
	for (auto iter1 = follow_set.begin(); iter1 != follow_set.end(); ++iter1) {
		printer << (*iter1).first << ": ";
		int count = 0;
		int size_ = (*iter1).second.size();
		for (auto iter2 = (*iter1).second.begin(); iter2 != (*iter1).second.end(); iter2++, count++) {
			printer << (*iter2);
			if (size_ > count + 1)
				printer << " ";
		}
		printer << endl;
	}
	return;
}

void SyntacticAnalyzer::ShowGrammarSymbolSet() {
	ofstream printer;
	printer.open(symbols_name);
	if (!printer.is_open()) {
		return;
	}
	printer << "Grammar Symblos: " << endl;
	for (auto iter = grammar_symbols.begin(); iter != grammar_symbols.end(); ++iter)
		printer << *iter << endl;
	return;
}

void SyntacticAnalyzer::ShowLR_items() {
	ofstream printer;
	printer.open(this->itemset_name);
	if (!printer.is_open()) {
		return;
	}
	printer << "SLR(1) Items: \n" << endl;
	for (auto iter1 = lr_items.begin(); iter1 != lr_items.end(); ++iter1) {
		printer << SLR_productions[iter1->production_number].left << "->";

		int production_length = SLR_productions[iter1->production_number].right.size();
		if (iter1->point_pos == -1) {//空串，只有一个点	
			printer << "·" << endl;
			continue;
		}

		for (auto iter2 = SLR_productions[iter1->production_number].right.begin(); iter2 != SLR_productions[iter1->production_number].right.end(); iter2++) {
			if (iter1->point_pos == (iter2 - SLR_productions[iter1->production_number].right.begin()))
				printer << "· ";
			printer << *iter2 << " ";
		}
		//最后一个字符的情况
		if (iter1->point_pos == production_length)
			printer << "·";
		printer << endl;
	}
	return;
}

void SyntacticAnalyzer::ShowClosure() {
	cout << "Closure项目：" << endl;
	for (auto iter = lr_items.begin(); iter != lr_items.end(); iter++) {
		set<LR_item> lr = GenerateItemClosureSet(*iter);
		for (auto iter1 = lr.begin(); iter1 != lr.end(); ++iter1) {
			cout << SLR_productions[iter1->production_number].left << "->";
			if (iter1->point_pos == -1) {//空串，只有一个点		
				cout << "·" << endl;
				continue;
			}

			int production_length = SLR_productions[iter1->production_number].right.size();
			for (auto iter2 = SLR_productions[iter1->production_number].right.begin(); iter2 != SLR_productions[iter1->production_number].right.end(); iter2++) {
				if (iter1->point_pos == (iter2 - SLR_productions[iter1->production_number].right.begin()))
					cout << "· ";
				cout << *iter2 << " ";
			}
			//最后一个字符的情况
			if (iter1->point_pos == production_length)
				cout << "·";
			cout << endl;
		}
		cout << endl;
	}

}

void SyntacticAnalyzer::ShowSLRError(const set<LR_item>& normal_family) {
	ofstream printer;
	printer.open(this->specification_name);
	printer << "不是SLR文法! 项目集规范族有冲突！" << endl;
	set<LR_item> lr = normal_family;

	for (auto iter1 = lr.begin(); iter1 != lr.end(); ++iter1) {
		printer << SLR_productions[iter1->production_number].left << "->";

		if (iter1->point_pos == -1) {//空串，只有一个点		
			printer << "·" << endl;
			continue;
		}

		int production_length = SLR_productions[iter1->production_number].right.size();

		for (auto iter2 = SLR_productions[iter1->production_number].right.begin(); iter2 != SLR_productions[iter1->production_number].right.end(); iter2++) {
			if (iter1->point_pos == (iter2 - SLR_productions[iter1->production_number].right.begin()))
				printer << "· ";
			printer << *iter2 << " ";
		}
		//最后一个字符的情况
		if (iter1->point_pos == production_length)
			printer << "·";
		printer << endl;
	}
	printer << endl;
	if (printer.is_open())
		printer.close();
}

void  SyntacticAnalyzer::ShowSpecificationGroupSet() {
	ofstream printer;
	printer.open(this->specification_name);
	if (!printer.is_open()) {
		return;
	}
	printer << "Item-Set Specification Families: \n" << endl;
	for (auto iter1 = items_set_specification_group.begin(); iter1 != items_set_specification_group.end(); ++iter1) {
		printer << "Specification Family No." << iter1 - items_set_specification_group.begin() << " : " << endl;//序号
		for (auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2) {
			printer << SLR_productions[iter2->production_number].left << "->";

			if (iter2->point_pos == -1) {//空串，只有一个点	
				printer << "·" << endl;
				continue;
			}

			int production_length = SLR_productions[iter2->production_number].right.size();

			for (auto iter3 = SLR_productions[iter2->production_number].right.begin(); iter3 != SLR_productions[iter2->production_number].right.end(); iter3++) {
				if (iter2->point_pos == (iter3 - SLR_productions[iter2->production_number].right.begin()))
					printer << "· ";
				printer << *iter3 << " ";

			}
			//最后一个字符的情况
			if (iter2->point_pos == production_length)
				printer << "·";
			printer << endl;
		}
		printer << endl;
	}
}

void SyntacticAnalyzer::ShowActionGotoTable() {
	ofstream printer;
	printer.open(this->action_goto_table_name);
	if (!printer.is_open()) {
		return;
	}
	//输出标头
	printer << "  ";
	for (auto iter = grammar_symbols.begin(); iter != grammar_symbols.end(); iter++) {
		if (IsNonTerminalSymbol(*iter))
			continue;
		if ("," == (*iter))//处理由于在CSV中输出 ","导致的位移问题。
			printer << "," << "，";
		else
			printer << "," << (*iter);
	}
	for (auto iter = grammar_symbols.begin(); iter != grammar_symbols.end(); iter++) {
		if (!IsNonTerminalSymbol(*iter))
			continue;
		printer << "," << (*iter);
	}
	printer << endl;

	for (unsigned int state = 0; state < items_set_specification_group.size(); state++) {
		printer << "state " << state;
		for (auto iter = grammar_symbols.begin(); iter != grammar_symbols.end(); iter++) {
			if (IsNonTerminalSymbol(*iter))
				continue;

			//map 不存在的情况
			if (action_goto_table.find({ state, *iter }) == action_goto_table.end())
				printer << ",";
			else {
				int next_state = action_goto_table[{state, * iter}].state;
				int op = action_goto_table[{state, (*iter)}].op;
				/*cout << "  ";*/
				if (op == SHIFT)
					printer << ",S" << next_state;
				else if (op == REDUCE)
					printer << ",r" << next_state;
				else if (op == ACCEPT)
					printer << ",acc";
				else
					printer << ",unknown";
				//cout << "  ";
			}
		}
		for (auto iter = grammar_symbols.begin(); iter != grammar_symbols.end(); ++iter) {
			if (!IsNonTerminalSymbol(*iter))
				continue;

			//map 不存在的情况
			if (action_goto_table.find({ state, *iter }) == action_goto_table.end())
				printer << ",";
			else {
				int next_state = action_goto_table[{state, * iter}].state;
				int op = action_goto_table[{state, * iter}].op;
				//cout << "  ";
				if (op == SHIFT)
					printer << "," << next_state;
				else if (op == REDUCE)
					printer << ",r" << next_state;
				else if (op == ACCEPT)
					printer << ",acc";
				else
					printer << ",unknown";
			}
		}

		printer << endl;
	}
	return;
}

void SyntacticAnalyzer::ShowAnalyzeDetail(int step, const SLR_operation& sl_op) {

	syntactic_analyzer_printer_ << step << ',';
	//输出状态栈
	for (auto iter = state_sequence_stack_.begin(); iter != state_sequence_stack_.end(); iter++)
		syntactic_analyzer_printer_ << *iter << ' ';

	syntactic_analyzer_printer_ << ',';

	//输出字符串栈
	for (auto iter = move_conclude_string_stack_.begin(); iter != move_conclude_string_stack_.end(); iter++) {
		if ("," == *iter)
			syntactic_analyzer_printer_ << "，";
		else
			syntactic_analyzer_printer_ << *iter << ' ';
	}
	syntactic_analyzer_printer_ << ',';


	//输出操作
	if (sl_op.op == SHIFT)
		syntactic_analyzer_printer_ << "Shift In";
	else if (sl_op.op == ACCEPT)
		syntactic_analyzer_printer_ << "Accept";
	else if (sl_op.op == REDUCE) {
		syntactic_analyzer_printer_ << "Reduce： " << SLR_productions[sl_op.state].left << "->";
		for (auto iter = SLR_productions[sl_op.state].right.begin(); iter != SLR_productions[sl_op.state].right.end(); iter++) {
			if ("," == *iter)
				syntactic_analyzer_printer_ << "，";
			else
				syntactic_analyzer_printer_ << *iter << ' ';
		}
	}

	syntactic_analyzer_printer_ << endl;
}

bool SyntacticAnalyzer::IsNonTerminalSymbol(const string& symbol) {
	if (symbol.length() == 0)
		return false;
	if (symbol[0] >= 'A' && symbol[0] <= 'Z')
		return true;
	return false;
}


SyntacticAnalyzer::SyntacticAnalyzer(bool show_detail) {
	print_detail_ = show_detail;//选择是否在分析过程中打印语法分析的详细信息

	// BuildGrammar();//根据grammar.txt建立SLR分析表 ACTION 和  GOTO

}

SyntacticAnalyzer::~SyntacticAnalyzer() {
	if (syntactic_analyzer_printer_.is_open())
		syntactic_analyzer_printer_.close();
}


bool LR_item::operator==(const LR_item& item) const {
	return (this->production_number == item.production_number) && (this->point_pos == item.point_pos);
}

bool LR_item::operator<(const LR_item& item) const {
	return this->production_number < item.production_number || this->production_number == item.production_number && this->point_pos < item.point_pos;
}

bool SLR_operation::operator==(const SLR_operation& operation) const {
	return (this->op == operation.op) && (this->state == operation.state);
}


//构造SLR分析器
bool SyntacticAnalyzer::StartAnalize() {
	//栈的初始化
	state_sequence_stack_.push_back(0);//初始状态0压入栈中
	move_conclude_string_stack_.push_back("#");//初始的#字符串压入栈中

	//初始化词法分析器
	LexAnalyzer lexcial_analyzer(this->lexcial_name);
	if (!lexcial_analyzer.Open_Success(true, this->codefile_name))
		return false;

	int sytactic_step = 0;
	while (true) {
		WordInfo get_word = lexcial_analyzer.GetWord();
		string word_string = get_word.word_string;
		if (get_word.type == LUNKNOWN) {//错误处理
			cout << "出现UNKNOWN的词法！" << endl;
			cout << get_word.value << endl;
		}

		while (true) {
			//选择状态序列栈栈顶
			int current_state = state_sequence_stack_[state_sequence_stack_.size() - 1];
			//action_goto表中不存在对应的操作
			if (action_goto_table.find({ current_state, word_string }) == action_goto_table.end()) {
				cout << get_word.value << endl;
				cout << "当前状态state: " << current_state << "与输入字符: " << word_string << "不兼容!" << endl;
				return false;
			}

			if (action_goto_table[{ current_state, word_string }].op == SHIFT) {//移进			
				state_sequence_stack_.push_back(action_goto_table[{ current_state, word_string }].state);
				move_conclude_string_stack_.push_back(word_string);
				ShowAnalyzeDetail(sytactic_step, action_goto_table[{ current_state, word_string }]);
				sytactic_step++;
				break;
			}
			else if (action_goto_table[{ current_state, word_string }].op == REDUCE) {//规约
				//获取规约产生式的序号
				int temp_production_num = action_goto_table[{ current_state, word_string }].state;
				int production_length; //产生式右部符号数目
				if (SLR_productions[temp_production_num].right[0] == "$")
					production_length = 0;
				else
					production_length = SLR_productions[temp_production_num].right.size();

				for (int i = 0; i < production_length; i++) {//将两个栈都弹出r个元素					
					state_sequence_stack_.erase(state_sequence_stack_.end() - 1);
					move_conclude_string_stack_.erase(move_conclude_string_stack_.end() - 1);
				}

				move_conclude_string_stack_.push_back(SLR_productions[temp_production_num].left);//用于规约的产生式的左部入栈
				if (action_goto_table.find({ state_sequence_stack_[state_sequence_stack_.size() - 1], SLR_productions[temp_production_num].left }) == action_goto_table.end()) {//不存在goto			
					cout << "ConClude Error: No mached GOTO ->" << get_word.value << endl;
					return false;
				}
				state_sequence_stack_.push_back(action_goto_table[{ state_sequence_stack_[state_sequence_stack_.size() - 1], SLR_productions[temp_production_num].left }].state);//goto对应的状态压入
				ShowAnalyzeDetail(sytactic_step, action_goto_table[{ current_state, word_string }]);
				sytactic_step++;
			}
			else if (action_goto_table[{ current_state, word_string }].op == ACCEPT) {//接受	
				state_sequence_stack_.erase(state_sequence_stack_.end() - 1);
				move_conclude_string_stack_.erase(move_conclude_string_stack_.end() - 1);
				move_conclude_string_stack_.push_back("Start");
				ShowAnalyzeDetail(sytactic_step, action_goto_table[{ current_state, word_string }]);
				sytactic_step++;
				cout << "Syntactic Analyze Success End." << endl;
				return true;
			}
			else
				return false;

		}

	}

	return true;
}
