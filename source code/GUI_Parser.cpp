#include "GUI_Parser.h"
#include"parser_bridge.h"

GUI_Parser::GUI_Parser(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	temp_code = new QFile("./temp_code.txt");
	temp_grammar = new QFile("./temp_grammar.txt");
	temp_first = new QFile("./temp_first.txt");
	temp_follow = new QFile("./temp_follow.txt");
	temp_specification = new QFile("./temp_specification.txt");
	temp_lex = new QFile("./temp_lexcial.txt");

	itemset_file = new QFile("./items_set.txt");
	action_goto_table_file = new QFile("./action_goto_table.csv");
	analyze_process_file = new QFile("./analyze_process.csv");
}

GUI_Parser::~GUI_Parser() {
	/*释放临时文件 */
	if (temp_code->exists()) {
		if (temp_code->isOpen())
			temp_code->close();
		temp_code->remove();
	}
	if (temp_grammar->exists()) {
		if (temp_grammar->isOpen())
			temp_grammar->close();
		temp_grammar->remove();
	}
	if (temp_first->exists()) {
		if (temp_first->isOpen())
			temp_first->close();
		temp_first->remove();
	}
	if (temp_follow->exists()) {
		if (temp_follow->isOpen())
			temp_follow->close();
		temp_follow->remove();
	}
	if (temp_specification->exists()) {
		if (temp_specification->isOpen())
			temp_specification->close();
		temp_specification->remove();
	}
	if (temp_lex->exists()) {
		if (temp_lex->isOpen())
			temp_lex->close();
		temp_lex->remove();
	}

	/*关闭打开的文件 */
	if (itemset_file->isOpen())
		itemset_file->close();
	if (action_goto_table_file->isOpen())
		action_goto_table_file->close();
	if (analyze_process_file->isOpen())
		analyze_process_file->close();

}

void GUI_Parser::open_code_file() {
	codefile_name = QFileDialog::getOpenFileName(nullptr, "Open SourceCode");

	QFile file(codefile_name);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text = file.readAll();
	ui.textEdit_code->setText(QString::fromUtf8(text));
	file.close();

	ui.textBrowser_lex->setText("");//右侧文本框清空
	ui.label_code->setText(QFileInfo(codefile_name).fileName());//提示栏显示文件名

}

void GUI_Parser::open_grammar_file() {
	grammarfile_name = QFileDialog::getOpenFileName(nullptr, "Open Grammar");

	QFile file(grammarfile_name);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text = file.readAll();
	ui.textEdit_grammar->setText(QString::fromLocal8Bit(text));
	file.close();

	/*根据文法产生的内容文本框清空*/
	ui.textBrowser_item->setText("");
	ui.textBrowser_first->setText("");
	ui.textBrowser_follow->setText("");
	ui.label_grammar->setText(QFileInfo(grammarfile_name).fileName());//提示栏显示文件名

}

void GUI_Parser::auto_save_code() {
	QString text1 = ui.textEdit_code->toPlainText();//读取文本框中的文件
	temp_code->open(QIODevice::WriteOnly | QIODevice::Text);//打开临时源文件存储
	QTextStream text_stream1(temp_code);
	text_stream1 << text1;
	temp_code->close();
}

void GUI_Parser::auto_save_grammar() {
	QString text2 = ui.textEdit_grammar->toPlainText();//读取文本框中的文件
	temp_grammar->open(QIODevice::WriteOnly | QIODevice::Text);//打开临时源文件存储
	QTextStream text_stream2(temp_grammar);
	text_stream2 << text2;
	temp_grammar->close();
}

void GUI_Parser::savelex_to_file() {
	lexcial_name = QFileDialog::getSaveFileName(nullptr, "Lexcial List Save As", "./lexial_analyzer_list.txt");

	QString text = ui.textBrowser_lex->toPlainText();
	QFile file(lexcial_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();
}

void GUI_Parser::save_first_to_file() {
	firstset_name = QFileDialog::getSaveFileName(nullptr, "First Set Save As", "./first_set.txt");

	QString text = ui.textBrowser_first->toPlainText();
	QFile file(firstset_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();

}

void GUI_Parser::save_follow_to_file() {
	followset_name = QFileDialog::getSaveFileName(nullptr, "Follow Set Save As", "./follow_set.txt");

	QString text = ui.textBrowser_follow->toPlainText();
	QFile file(followset_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();

}

void GUI_Parser::save_items_to_file() {
	specification_name = QFileDialog::getSaveFileName(nullptr, "Item Set Specification Families Save As", "./item_set_specification_family.txt");

	QString text = ui.textBrowser_item->toPlainText();
	QFile file(specification_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();

}

void GUI_Parser::save_code_to_file() {
	if (codefile_name.isEmpty()) //需要“另存为”
		codefile_name = QFileDialog::getSaveFileName(nullptr, "Save Source Code As", codefile_name);

	QString text = ui.textEdit_code->toPlainText();//读取文本
	QFile file(codefile_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();

	ui.label_code->setText(QFileInfo(codefile_name).fileName());//提示栏显示文件名

}

void GUI_Parser::save_grammar_to_file() {
	if (grammarfile_name.isEmpty())
		grammarfile_name = QFileDialog::getSaveFileName(nullptr, "Save Grammar As", codefile_name);

	QString text = ui.textEdit_code->toPlainText();//读取文本
	QFile file(grammarfile_name);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream text_stream(&file);
	text_stream << text;
	file.close();

	ui.label_grammar->setText(QFileInfo(grammarfile_name).fileName());

}

void GUI_Parser::show_action_goto_table() {
	QString filename = "./action_goto_table.csv";
	QFile file(filename);
	if (file.exists())
		QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}


void GUI_Parser::show_analyze_process() {
	QString filename = "./analyze_process.csv";
	QFile file(filename);
	if (file.exists())
		QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void GUI_Parser::show_productions() {
	QString filename = "./productions.txt";
	QFile file(filename);
	if (file.exists())
		QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void GUI_Parser::show_items() {
	QString filename = "./items_set.txt";
	QFile file(filename);
	if (file.exists())
		QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void GUI_Parser::show_symbols() {
	QString filename = "./symbols.txt";
	QFile file(filename);
	if (file.exists())
		QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
}

void GUI_Parser::syntactic_analyze() {
	QTextCodec* codec = QTextCodec::codecForName("GBK");
	start_syntactic_analyze("./temp_code.txt", "./temp_grammar.txt", "./temp_first.txt", "./temp_follow.txt", "./temp_specification.txt", "./temp_lexcial.txt",
		"./items_set.txt", "./action_goto_table.csv", "./analyze_process.csv");
	//在结果文本框显示结果
	QFile file_first("./temp_first.txt");
	file_first.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text_first = file_first.readAll();
	ui.textBrowser_first->setText(QString::fromLocal8Bit(text_first));
	file_first.close();

	QFile file_follow("./temp_follow.txt");
	file_follow.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text_follow = file_follow.readAll();
	ui.textBrowser_follow->setText(QString::fromLocal8Bit(text_follow));
	file_follow.close();

	QFile file_item("./temp_specification.txt");
	file_item.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text_item = file_item.readAll();
	ui.textBrowser_item->setText(QString::fromLocal8Bit(text_item));
	file_item.close();

	QFile file_lex("./temp_lexcial.txt");
	file_lex.open(QIODevice::ReadOnly | QIODevice::Text);
	QByteArray text_lex = file_lex.readAll();
	ui.textBrowser_lex->setText(QString::fromLocal8Bit(text_lex));
	file_lex.close();

	if ((!codefile_name.isEmpty()) && (!grammarfile_name.isEmpty())) {//判断是否可以进行分析

	}
}


// temp_code = new QFile("./temp_code.txt");
// temp_grammar = new QFile("./temp_grammar.txt");
// temp_first = new QFile("./temp_first.txt");
// temp_follow = new QFile("./temp_follow.txt");
// temp_specification = new QFile("./temp_specification.txt");
// temp_lex = new QFile("./temp_lexcial.txt");

// itemset_file = new QFile("./items_set.txt");
// action_goto_table_file = new QFile("./action_goto_table.csv");
// analyze_process_file = new QFile("./analyze_process.csv");
