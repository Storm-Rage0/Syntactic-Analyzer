/*1750120 ������ �����3��*/
#include"lex_analyzer.h"
using namespace std;
const char* OutputType[] = { "Int_Number", "Float_Number","Keyword", "Identifier", "Type", "Delimiter", "Unknown", "EOF", "Operator","HeaderFile","MarcoDefinition" };

bool LexAnalyzer::Open_Success(bool show_detail, const string code_filename) {
	print_detail = show_detail;

	lex_infile.open(code_filename);

	if (!lex_infile.is_open()) {
		cerr << "ERROR��Դ�����ļ���ʧ�ܣ�" << endl;
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
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')//�����»���
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

	if (ch == '\n')//����
		line_count++;
	return ch;
}

WordInfo LexAnalyzer::GetBasicWord() {
	char ch;
	string str_token;
	WordInfo word;

	while (!lex_infile.eof()) {//ѭ����ȡ�ı�	
		ch = Get_Next();
		if (ch == '/') {//����ע��		
			char next = Get_Next();
			if (next == '/') {//����ע��			
				while (Get_Next() != '\n' && !lex_infile.eof());//���س�Ϊֹ
			}
			else if ('*' == next) {// /**/ע��			
				while (!lex_infile.eof()) {
					while (Get_Next() != '*' && !lex_infile.eof());//��*Ϊֹ

					if (lex_infile.eof()) {//ע��δ�պ�				
						word.type = LUNKNOWN; //δ֪
						word.value = "ERROR��Annotation Unfull��line: " + to_string(line_count);
						return word;
					}

					//  ע�ͽ���
					if (Get_Next() == '/')
						break;
					else {
						lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
						if (next == '\n')
							line_count--;
						word.type = LUNKNOWN; //δ֪
						word.value = "ERROR��Annotation Unfull��line: " + to_string(line_count);
						return word;
					}
				}
			}
			else {//���Ǹ�����			
				lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
				if (next == '\n')
					line_count--;
				word.type = LOPERATOR; //������
				word.value = ch;
				return word;
			}
		}
		else if (ch == '#') {//�����궨��/ͷ�ļ�
			char next;
			while (true) {//�����ո�
				next = Get_Next();
				if (next == ' ')
					continue;
				else if (Is_Letter(next)) {//����Ϊ�궨��
					str_token += next;
					while (!lex_infile.eof()) {
						char nnext = Get_Next();
						if (!Is_Letter(nnext)) { //��һ��������ĸ����Ҫ�˻�	
							if (nnext == '\n')
								line_count--;
							lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next

							if (str_token == "include") { //ͷ�ļ�
								str_token.erase(0, 7);//��ȥǰ���include
								while (Is_Blank(nnext = Get_Next()));
								if (nnext == '<') {
									while ((nnext = Get_Next()) != '>') {
										if (nnext == ' ')
											continue;
										else if (nnext == -1 || Is_Blank(nnext)) {
											if (nnext == '\n') {
												lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
												line_count--;
											}
											word.type = LUNKNOWN; //δ֪
											word.value = "ERROR��Include Unfull��line: " + to_string(line_count);
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
									word.type = LUNKNOWN; //δ֪ͷ�ļ�
									word.value = "Warning��Unknown Headerfile: " + str_token + "; " + to_string(line_count);
								}

							}
							else if (str_token == "define") {//�궨��
								word.type = LDEFINE;
								word.value = str_token;
							}
							else {//#��δ�����ַ���
								word.type = LUNKNOWN; //δ֪����
								word.value = "Warning! Undefined Words After \'#\': " + str_token + "; line:" + to_string(line_count);
							}

							return word;
						}
						else  //��һ��������ĸ������ѭ��
							str_token += nnext;
					}
				}
				else {//#������

					word.type = LUNKNOWN; //δ֪
					word.value = "ERROR! Cannot Recognize After \'#\', line: " + std::to_string(line_count);
					return word;
				}
			}
		}
		else if (Is_Digital(ch)) {
			str_token += ch;
			while (!lex_infile.eof()) {
				char next = Get_Next();
				if (!Is_Digital(next)){ //��һ���������֣��ж��Ƿ��Ǹ�����				
					if (next == '.') {//�Ǹ�����
						while(!lex_infile.eof()){
							next=Get_Next();
							if(!Is_Digital(next)){//��������һ���������֣���Ҫ�˻�
								lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
						if (next == '\n')
							line_count--;
						word.type = LFLOAT; //����
						word.value = str_token;
						return word;
							}
						}
					}
					else {//���Ǹ���������Ҫ�˻�
						lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
						if (next == '\n')
							line_count--;
						word.type = LINTEGER; //����
						word.value = str_token;
						return word;
					}
				}
				else  //��һ���������֣�����ѭ��
					str_token += next;
			}
		}

		else if (Is_Letter(ch)) {
			str_token += ch;
			while (!lex_infile.eof()) {
				char next = Get_Next();
				if ((!Is_Digital(next)) && (!Is_Letter(next))) { //��һ��������ĸ�����֣���Ҫ�˻�				
					lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
					if (next == '\n')
						line_count--;
					//�ж��Ƿ�Ϊ�ؼ��֡���������
					if (KEYWORDS.find(str_token) != KEYWORDS.end()) //�ڹؼ�����
						word.type = LKEYWORD;
					else if (TYPES.find(str_token) != TYPES.end()) //�ڱ���������
						word.type = LTYPE;
					else //��ʶ��
						word.type = LIDENTIFIER;

					word.value = str_token;
					return word;
				}
				else  //��һ��������ĸ�����֣�����ѭ��
					str_token += next;
			}
		}
		else if (Delimiters.find(ch) != Delimiters.end()) {
			word.type = LDELIMITER; //���
			word.value = ch;
			return word;
		}
		else if (Is_Single_Operator(ch)) {//�����������		
			word.type = LOPERATOR; //������
			word.value = ch;
			return word;
		}
		else if (Is_Double_Operatorpre(ch)) {//�ж��Ƿ�Ϊ˫���������		
			str_token += ch;
			char next = Get_Next();

			if (next == '=') { //ȷ����˫���������			
				str_token += next;
				word.type = LOPERATOR; //������
				word.value = str_token;
				return word;
			}
			else {
				lex_infile.seekg(-1, ios::cur);//�����ļ�ָ�����,��Ϊ�����next
				if (next == '\n')
					line_count--;
				if (ch != '!')//�Ǹ������Ų�����
				{
					word.type = LOPERATOR; //������
					word.value = str_token;
					return word;
				}
				else// ! δ����ķ���
				{
					word.type = LUNKNOWN; //������
					word.value = str_token + ", line: " + std::to_string(line_count);
					return word;
				}
			}

		}
		else if (ch == -1) {//�ı�������־
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


