/********************************************************************************
** Form generated from reading UI file 'GUI_Parser.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_PARSER_H
#define UI_GUI_PARSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI_ParserClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox_code;
    QTextEdit *textEdit_code;
    QLabel *label_code;
    QPushButton *pushButton_code;
    QPushButton *pushButton_codeopen;
    QGroupBox *groupBox_grammar;
    QTextEdit *textEdit_grammar;
    QLabel *label_grammar;
    QPushButton *pushButton_grammar;
    QPushButton *pushButton_grammaropen;
    QGroupBox *groupBox_item;
    QTextBrowser *textBrowser_item;
    QPushButton *pushButton_items;
    QGroupBox *groupBox_set;
    QGroupBox *groupBox_first;
    QTextBrowser *textBrowser_first;
    QPushButton *pushButton_first;
    QGroupBox *groupBox_follow;
    QTextBrowser *textBrowser_follow;
    QPushButton *pushButton_follow;
    QGroupBox *groupBox_lex;
    QTextBrowser *textBrowser_lex;
    QPushButton *pushButton_lex;
    QPushButton *pushButton_start;
    QPushButton *pushButton_action_goto_table;
    QPushButton *pushButton_process;
    QPushButton *pushButton_items_2;
    QPushButton *pushButton_productions;
    QPushButton *pushButton_symbols;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GUI_ParserClass)
    {
        if (GUI_ParserClass->objectName().isEmpty())
            GUI_ParserClass->setObjectName(QString::fromUtf8("GUI_ParserClass"));
        GUI_ParserClass->resize(1740, 887);
        QFont font;
        font.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font.setPointSize(20);
        GUI_ParserClass->setFont(font);
        centralWidget = new QWidget(GUI_ParserClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox_code = new QGroupBox(centralWidget);
        groupBox_code->setObjectName(QString::fromUtf8("groupBox_code"));
        groupBox_code->setGeometry(QRect(30, 20, 401, 361));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(20);
        groupBox_code->setFont(font1);
        textEdit_code = new QTextEdit(groupBox_code);
        textEdit_code->setObjectName(QString::fromUtf8("textEdit_code"));
        textEdit_code->setGeometry(QRect(10, 40, 381, 271));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Lucida Console"));
        font2.setPointSize(10);
        textEdit_code->setFont(font2);
        textEdit_code->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        label_code = new QLabel(groupBox_code);
        label_code->setObjectName(QString::fromUtf8("label_code"));
        label_code->setGeometry(QRect(131, 4, 271, 31));
        label_code->setFont(font2);
        pushButton_code = new QPushButton(groupBox_code);
        pushButton_code->setObjectName(QString::fromUtf8("pushButton_code"));
        pushButton_code->setGeometry(QRect(240, 320, 81, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font3.setPointSize(15);
        pushButton_code->setFont(font3);
        pushButton_codeopen = new QPushButton(groupBox_code);
        pushButton_codeopen->setObjectName(QString::fromUtf8("pushButton_codeopen"));
        pushButton_codeopen->setGeometry(QRect(60, 320, 81, 31));
        QFont font4;
        font4.setPointSize(14);
        pushButton_codeopen->setFont(font4);
        groupBox_grammar = new QGroupBox(centralWidget);
        groupBox_grammar->setObjectName(QString::fromUtf8("groupBox_grammar"));
        groupBox_grammar->setGeometry(QRect(10, 390, 441, 421));
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font5.setPointSize(20);
        groupBox_grammar->setFont(font5);
        textEdit_grammar = new QTextEdit(groupBox_grammar);
        textEdit_grammar->setObjectName(QString::fromUtf8("textEdit_grammar"));
        textEdit_grammar->setGeometry(QRect(13, 50, 411, 321));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Courier New"));
        font6.setPointSize(10);
        textEdit_grammar->setFont(font6);
        label_grammar = new QLabel(groupBox_grammar);
        label_grammar->setObjectName(QString::fromUtf8("label_grammar"));
        label_grammar->setGeometry(QRect(190, 0, 201, 31));
        label_grammar->setFont(font2);
        pushButton_grammar = new QPushButton(groupBox_grammar);
        pushButton_grammar->setObjectName(QString::fromUtf8("pushButton_grammar"));
        pushButton_grammar->setGeometry(QRect(260, 380, 71, 31));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font7.setPointSize(14);
        pushButton_grammar->setFont(font7);
        pushButton_grammaropen = new QPushButton(groupBox_grammar);
        pushButton_grammaropen->setObjectName(QString::fromUtf8("pushButton_grammaropen"));
        pushButton_grammaropen->setGeometry(QRect(80, 380, 81, 31));
        pushButton_grammaropen->setFont(font4);
        groupBox_item = new QGroupBox(centralWidget);
        groupBox_item->setObjectName(QString::fromUtf8("groupBox_item"));
        groupBox_item->setGeometry(QRect(1030, 20, 651, 381));
        QFont font8;
        font8.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font8.setPointSize(20);
        groupBox_item->setFont(font8);
        textBrowser_item = new QTextBrowser(groupBox_item);
        textBrowser_item->setObjectName(QString::fromUtf8("textBrowser_item"));
        textBrowser_item->setGeometry(QRect(20, 40, 611, 271));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Source Code Pro"));
        font9.setPointSize(10);
        font9.setItalic(false);
        textBrowser_item->setFont(font9);
        pushButton_items = new QPushButton(groupBox_item);
        pushButton_items->setObjectName(QString::fromUtf8("pushButton_items"));
        pushButton_items->setGeometry(QRect(280, 320, 91, 41));
        QFont font10;
        font10.setPointSize(15);
        pushButton_items->setFont(font10);
        groupBox_set = new QGroupBox(centralWidget);
        groupBox_set->setObjectName(QString::fromUtf8("groupBox_set"));
        groupBox_set->setGeometry(QRect(900, 410, 791, 411));
        QFont font11;
        font11.setFamily(QString::fromUtf8("Pristina"));
        groupBox_set->setFont(font11);
        groupBox_first = new QGroupBox(groupBox_set);
        groupBox_first->setObjectName(QString::fromUtf8("groupBox_first"));
        groupBox_first->setGeometry(QRect(20, 40, 371, 361));
        QFont font12;
        font12.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font12.setPointSize(15);
        groupBox_first->setFont(font12);
        textBrowser_first = new QTextBrowser(groupBox_first);
        textBrowser_first->setObjectName(QString::fromUtf8("textBrowser_first"));
        textBrowser_first->setGeometry(QRect(10, 40, 351, 271));
        QFont font13;
        font13.setFamily(QString::fromUtf8("Consolas"));
        font13.setPointSize(10);
        font13.setBold(false);
        font13.setWeight(50);
        textBrowser_first->setFont(font13);
        pushButton_first = new QPushButton(groupBox_first);
        pushButton_first->setObjectName(QString::fromUtf8("pushButton_first"));
        pushButton_first->setGeometry(QRect(150, 320, 71, 31));
        QFont font14;
        font14.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font14.setPointSize(14);
        pushButton_first->setFont(font14);
        groupBox_follow = new QGroupBox(groupBox_set);
        groupBox_follow->setObjectName(QString::fromUtf8("groupBox_follow"));
        groupBox_follow->setGeometry(QRect(410, 40, 361, 361));
        QFont font15;
        font15.setFamily(QString::fromUtf8("Ink Free"));
        font15.setPointSize(15);
        groupBox_follow->setFont(font15);
        textBrowser_follow = new QTextBrowser(groupBox_follow);
        textBrowser_follow->setObjectName(QString::fromUtf8("textBrowser_follow"));
        textBrowser_follow->setGeometry(QRect(10, 40, 341, 271));
        QFont font16;
        font16.setFamily(QString::fromUtf8("Source Code Pro Light"));
        font16.setPointSize(10);
        textBrowser_follow->setFont(font16);
        pushButton_follow = new QPushButton(groupBox_follow);
        pushButton_follow->setObjectName(QString::fromUtf8("pushButton_follow"));
        pushButton_follow->setGeometry(QRect(150, 320, 61, 31));
        pushButton_follow->setFont(font14);
        groupBox_lex = new QGroupBox(centralWidget);
        groupBox_lex->setObjectName(QString::fromUtf8("groupBox_lex"));
        groupBox_lex->setGeometry(QRect(510, 40, 441, 341));
        QFont font17;
        font17.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font17.setPointSize(20);
        groupBox_lex->setFont(font17);
        textBrowser_lex = new QTextBrowser(groupBox_lex);
        textBrowser_lex->setObjectName(QString::fromUtf8("textBrowser_lex"));
        textBrowser_lex->setGeometry(QRect(20, 50, 401, 231));
        QFont font18;
        font18.setFamily(QString::fromUtf8("MV Boli"));
        font18.setPointSize(10);
        textBrowser_lex->setFont(font18);
        pushButton_lex = new QPushButton(groupBox_lex);
        pushButton_lex->setObjectName(QString::fromUtf8("pushButton_lex"));
        pushButton_lex->setGeometry(QRect(170, 290, 81, 41));
        pushButton_lex->setFont(font10);
        pushButton_start = new QPushButton(centralWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(600, 440, 181, 81));
        QFont font19;
        font19.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font19.setPointSize(22);
        pushButton_start->setFont(font19);
        pushButton_start->setMouseTracking(false);
        pushButton_start->setFocusPolicy(Qt::StrongFocus);
        pushButton_start->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 127);"));
        pushButton_start->setFlat(false);
        pushButton_action_goto_table = new QPushButton(centralWidget);
        pushButton_action_goto_table->setObjectName(QString::fromUtf8("pushButton_action_goto_table"));
        pushButton_action_goto_table->setGeometry(QRect(460, 720, 211, 51));
        QFont font20;
        font20.setFamily(QString::fromUtf8("Bradley Hand ITC"));
        font20.setPointSize(16);
        pushButton_action_goto_table->setFont(font20);
        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QString::fromUtf8("pushButton_process"));
        pushButton_process->setGeometry(QRect(680, 710, 211, 61));
        QFont font21;
        font21.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font21.setPointSize(16);
        pushButton_process->setFont(font21);
        pushButton_items_2 = new QPushButton(centralWidget);
        pushButton_items_2->setObjectName(QString::fromUtf8("pushButton_items_2"));
        pushButton_items_2->setGeometry(QRect(710, 550, 151, 51));
        QFont font22;
        font22.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font22.setPointSize(16);
        pushButton_items_2->setFont(font22);
        pushButton_productions = new QPushButton(centralWidget);
        pushButton_productions->setObjectName(QString::fromUtf8("pushButton_productions"));
        pushButton_productions->setGeometry(QRect(490, 550, 181, 51));
        QFont font23;
        font23.setFamily(QString::fromUtf8("\345\215\216\346\226\207\344\273\277\345\256\213"));
        font23.setPointSize(16);
        pushButton_productions->setFont(font23);
        pushButton_symbols = new QPushButton(centralWidget);
        pushButton_symbols->setObjectName(QString::fromUtf8("pushButton_symbols"));
        pushButton_symbols->setGeometry(QRect(610, 630, 141, 51));
        QFont font24;
        font24.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font24.setPointSize(16);
        pushButton_symbols->setFont(font24);
        GUI_ParserClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GUI_ParserClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1740, 26));
        GUI_ParserClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GUI_ParserClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GUI_ParserClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GUI_ParserClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GUI_ParserClass->setStatusBar(statusBar);

        retranslateUi(GUI_ParserClass);
        QObject::connect(pushButton_code, SIGNAL(clicked()), GUI_ParserClass, SLOT(save_code_to_file()));
        QObject::connect(pushButton_grammar, SIGNAL(clicked()), GUI_ParserClass, SLOT(save_grammar_to_file()));
        QObject::connect(pushButton_lex, SIGNAL(clicked()), GUI_ParserClass, SLOT(savelex_to_file()));
        QObject::connect(pushButton_first, SIGNAL(clicked()), GUI_ParserClass, SLOT(save_first_to_file()));
        QObject::connect(pushButton_items, SIGNAL(clicked()), GUI_ParserClass, SLOT(save_items_to_file()));
        QObject::connect(pushButton_follow, SIGNAL(clicked()), GUI_ParserClass, SLOT(save_follow_to_file()));
        QObject::connect(textEdit_code, SIGNAL(textChanged()), GUI_ParserClass, SLOT(auto_save_code()));
        QObject::connect(textEdit_grammar, SIGNAL(textChanged()), GUI_ParserClass, SLOT(auto_save_grammar()));
        QObject::connect(pushButton_codeopen, SIGNAL(clicked()), GUI_ParserClass, SLOT(open_code_file()));
        QObject::connect(pushButton_grammaropen, SIGNAL(clicked()), GUI_ParserClass, SLOT(open_grammar_file()));
        QObject::connect(pushButton_start, SIGNAL(clicked()), GUI_ParserClass, SLOT(syntactic_analyze()));
        QObject::connect(pushButton_productions, SIGNAL(clicked()), GUI_ParserClass, SLOT(show_productions()));
        QObject::connect(pushButton_symbols, SIGNAL(clicked()), GUI_ParserClass, SLOT(show_symbols()));
        QObject::connect(pushButton_action_goto_table, SIGNAL(clicked()), GUI_ParserClass, SLOT(show_action_goto_table()));
        QObject::connect(pushButton_process, SIGNAL(clicked()), GUI_ParserClass, SLOT(show_analyze_process()));
        QObject::connect(pushButton_items_2, SIGNAL(clicked()), GUI_ParserClass, SLOT(show_items()));

        QMetaObject::connectSlotsByName(GUI_ParserClass);
    } // setupUi

    void retranslateUi(QMainWindow *GUI_ParserClass)
    {
        GUI_ParserClass->setWindowTitle(QCoreApplication::translate("GUI_ParserClass", "GUI_Parser", nullptr));
        groupBox_code->setTitle(QCoreApplication::translate("GUI_ParserClass", "\346\272\220\344\273\243\347\240\201", nullptr));
        label_code->setText(QString());
        pushButton_code->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        pushButton_codeopen->setText(QCoreApplication::translate("GUI_ParserClass", "\346\211\223\345\274\200", nullptr));
        groupBox_grammar->setTitle(QCoreApplication::translate("GUI_ParserClass", "\346\226\207\346\263\225\350\247\204\345\210\231", nullptr));
        label_grammar->setText(QString());
        pushButton_grammar->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        pushButton_grammaropen->setText(QCoreApplication::translate("GUI_ParserClass", "\346\211\223\345\274\200", nullptr));
        groupBox_item->setTitle(QCoreApplication::translate("GUI_ParserClass", "\351\241\271\347\233\256\351\233\206\350\247\204\350\214\203\346\227\217", nullptr));
        pushButton_items->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        groupBox_set->setTitle(QCoreApplication::translate("GUI_ParserClass", "First/Follow\351\233\206", nullptr));
        groupBox_first->setTitle(QCoreApplication::translate("GUI_ParserClass", "First Set", nullptr));
        pushButton_first->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        groupBox_follow->setTitle(QCoreApplication::translate("GUI_ParserClass", "Follow Set", nullptr));
        pushButton_follow->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        groupBox_lex->setTitle(QCoreApplication::translate("GUI_ParserClass", "\350\257\215\346\263\225\345\215\225\345\205\203\345\272\217\345\210\227", nullptr));
        pushButton_lex->setText(QCoreApplication::translate("GUI_ParserClass", "\344\277\235\345\255\230", nullptr));
        pushButton_start->setText(QCoreApplication::translate("GUI_ParserClass", "\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        pushButton_action_goto_table->setText(QCoreApplication::translate("GUI_ParserClass", "Action Goto \350\241\250", nullptr));
        pushButton_process->setText(QCoreApplication::translate("GUI_ParserClass", "\347\247\273\350\277\233-\345\275\222\347\272\246 \350\277\207\347\250\213", nullptr));
        pushButton_items_2->setText(QCoreApplication::translate("GUI_ParserClass", "\346\226\207\346\263\225\351\241\271\347\233\256", nullptr));
        pushButton_productions->setText(QCoreApplication::translate("GUI_ParserClass", "\346\226\207\346\263\225\344\272\247\347\224\237\345\274\217", nullptr));
        pushButton_symbols->setText(QCoreApplication::translate("GUI_ParserClass", "\346\226\207\346\263\225\347\254\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI_ParserClass: public Ui_GUI_ParserClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_PARSER_H
