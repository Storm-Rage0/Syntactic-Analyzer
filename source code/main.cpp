/*1750120 杨云霄 计算机3班 */
#include "GUI_Parser.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	GUI_Parser w;
	w.show();
	return a.exec();
}
