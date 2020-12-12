#pragma once

/*1750120 杨云霄 计算机3班*/
#include <QtWidgets/QMainWindow>
#include<QtWidgets/QFileDialog.h>
#include<QtWidgets/QMessageBox.h>
#include<qtextstream.h>
#include<qtextcodec.h>
#include<qdesktopservices.h>
#include "ui_GUI_Parser.h"

class GUI_Parser : public QMainWindow
{
	Q_OBJECT

public:
	GUI_Parser(QWidget* parent = Q_NULLPTR);
	~GUI_Parser();

private:
	Ui::GUI_ParserClass ui;
	QString codefile_name;//源代码文件
	QString lexcial_name;//文法产生式序列文件
	QString grammarfile_name;//文法产生式文件
	QString firstset_name;//first集文件
	QString followset_name;//follow集文件
	QString specification_name;//项目集规范族文件
	QString itemset_name;//文法项目文件
	QString action_goto_table_name;//action goto表文件
	QString analyze_process_name;//分析过程文件

	QFile* temp_code, * temp_grammar, * temp_first, * temp_follow, * temp_specification, * temp_lex;
	QFile* itemset_file, * action_goto_table_file, * analyze_process_file;

private slots:
	void open_code_file();//打开源代码文件

	void open_grammar_file();//打开文法文件
	void syntactic_analyze();//进行语法分析
	void savelex_to_file();//保存词法分析结果到文件
	void save_first_to_file();//保存first集到文件
	void save_follow_to_file();//保存follow集到文件
	void save_items_to_file();//保存项目集规范族到文件
	void auto_save_code();//源代码更改后自动保存
	void auto_save_grammar();//文法更改后自动保存

	void save_code_to_file();//保存修改后的源代码
	void save_grammar_to_file();//保存修改后的文法

	void show_action_goto_table();//打开action goto表
	void show_analyze_process();//打开移进-归约过程
	void show_productions();//打开文法产生式
	void show_items();//打开文法的项目
	void show_symbols();//打开符号表

};
