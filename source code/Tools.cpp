
#include"Tools.h"
/*将产生式右部分开装在数组里*/
vector<string> split_string(const string& str, const string& pattern) {
	vector<string> res;
	if (str == "")
		return res;
	//在字符串末尾也加入分隔符，方便截取最后一段
	string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//去掉已分割的字符串,在剩下的字符串中进行分割
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	//debug: grammar中sp检测
	//for (auto iter = res.begin(); iter != res.end(); ++iter)
	//	if ((*iter) == "")
	//		cout << "***************************";
	return res;
}
