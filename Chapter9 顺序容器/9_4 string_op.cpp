#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<string>
#include<deque>
#include<unordered_map>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_9_51

#ifdef PROBLEM_9_43_44
void exchange_str(string& s, const string old_val, const string new_val)
{
	auto it = s.begin();
	while(it != s.end())
	{
		if (*it == old_val.at(0))
		{
			auto it_record = it;
			auto old_val_it = old_val.begin();
			while (old_val_it != old_val.end() && *old_val_it == *it)
			{
				++it;
				++old_val_it;
			}

			size_t dist = it_record - s.begin();
			if (old_val_it == old_val.end())
			{
				//s.erase(dist, old_val.size());
				//s.insert(dist, new_val);
				s.replace(dist, old_val.size(), new_val);
			}
			it = s.begin() + dist + new_val.size();
		}
		else
		{
			++it;
		}
	}
}

#endif // PROBLEM_9_43_44

#ifdef PROBLEM_9_45
string add_name(string name, const string pre_add, const string post_add)
{
	name.insert(0, pre_add);
	name.append(post_add);

	return  name;
}
#endif

#ifdef PROBLEM_9_51
class Date
{
public:
	Date(string data_str)
	{
		if (data_str.find_first_of(" ") != string::npos)
		{
			string::size_type pos1 = data_str.find_first_of(" ");
			string::size_type pos2 = data_str.find_last_of(" ");

			month = monthstr2int[data_str.substr(0, pos1)];
			day = stoi(data_str.substr(pos1 + 1, pos2));
			year = stoi(data_str.substr(pos2 + 1, data_str.size()));
		}
		else if (data_str.find_first_of("/") != string::npos)
		{
			string::size_type pos1 = data_str.find_first_of("/");
			string::size_type pos2 = data_str.find_last_of("/");

			day = stoi(data_str.substr(0, pos1));
			month = stoi(data_str.substr(pos1 + 1, pos2));
			year = stoi(data_str.substr(pos2 + 1, data_str.size()));
		}

	}

	unsigned int year;
	unsigned int month;
	unsigned int day;
	unordered_map<string, int> monthstr2int = { {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Ari", 4}, {"May", 5}, \
												{"Jun", 6}, {"Jul", 7}, {"Aut", 8}, {"Sep", 9}, {"Oct", 10}, \
												{"Nov", 11}, {"Dec", 12} };



};


#endif

int main()
{
#ifdef PROBLEM_9_41
	// 从一个 vector<char> 初始化一个 string
	vector<char> char_list = {'H', 'e', 'l', 'l', 'o'};
	string str_list;
	for (auto it = char_list.begin(); it != char_list.end(); ++it)
	{
		str_list.push_back(*it);
	}
	cout << "string = " << str_list << endl;


#endif // PROBLEM_9_41

#ifdef PROBLEM_9_43_44
	// 将 s 中的所有 old_val 替换成 new_val
	string s = "Hello World tho thothe haha ni tho hao";
	exchange_str(s, "tho", "through");
	cout << "s = " << s << endl;
#endif // PROBLEM_9_43

#ifdef PROBLEM_9_45
	// 将前缀以及后缀添加到给定的名字中
	string name = "Linus";
	name = add_name(name, "Mr ", " Jr.");
	cout << "name = " << name << endl;
#endif // PROBLEM_45

#ifdef PROBLEM_9_49
	// 读入单词文件，输出最长的不包含 d f p g 字母的单词
	string file_name = "./data.txt";
	fstream file_in;
	file_in.open(file_name);
	string word_tmp;
	string word_res = "";
	while (file_in >> word_tmp)
	{
		if (word_tmp.find_first_of("dfpg") == string::npos)
		{
			word_res = (word_res > word_tmp) ? word_res : word_tmp;
		}
	}
	cout << "word_res = " << word_res << endl;
#endif // PROBLEM_49

#ifdef PROBLEM_9_50
	//vector<string> str_vec = { "123", "11", "85", "03" };
	vector<string> str_vec = { "12.3", "1.1", "0.85", "0.3" };
	//int result = 0;
	double result = 0.0;
	for (auto it = str_vec.begin(); it != str_vec.end(); ++it)
	{
		//result += stoi(*it);
		result += stod(*it);
	}
		cout << "result = " << result << endl;


#endif

#ifdef PROBLEM_9_51
		// 构造函数构造年、月、日
		//Date test("1/1/1990");
		Date test("Feb 1 1990");
		cout << "test year = " << test.year << ", test month = " << test.month << " , test day = " << test.day << endl;


#endif

	return 0;



}