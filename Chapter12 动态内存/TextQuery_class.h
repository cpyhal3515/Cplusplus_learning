#ifndef TEXTQUERY
#define TEXTQUERY

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<memory>

// 注意：不加 std 可能会报错语法错误，缺少 ";" 等等

// TextQuery 用到 QueryResult，因此这里要进行声明
class QueryResult;
class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	// 构造函数
	// 注意：这里要 new 一块空间才能给 context_line 赋值，否则会报错
	TextQuery(std::ifstream& infile) : context_line(new std::vector<std::string>)
	{
		std::string lin;
		// 逐行读入数据
		while (getline(infile, lin))
		{
			context_line->push_back(lin);
			// 计算行号
			int n = context_line->size() - 1;
			std::istringstream in(lin);
			std::string wd;
			// 逐个单词读入
			while (in >> wd)
			{
				// 查找单词 wd 在 word_line_num_mp 出现的情况
				auto &word_set_idx = word_line_num_mp[wd];
				// 没有出现过就新建一个 set
				if (word_set_idx == nullptr)
				{
					word_set_idx.reset(new std::set<line_no>);
				}
				word_set_idx->insert(n);
			}

		}


	};


	// 声明查询函数
	QueryResult query(std::string&);



private:
	// 存储整个文本
	std::shared_ptr<std::vector<std::string>> context_line;
	// 存储单词->行号（set）的映射关系
	std::map<std::string, 
		std::shared_ptr<std::set<line_no>>> word_line_num_mp;


};



class QueryResult
{
	// 将打印函数声明为友元
	friend std::ostream& print(std::ostream& stream, QueryResult& qr);
	using line_no = std::vector<std::string>::size_type;
public:
	// 构造函数
	QueryResult(std::string wd, std::shared_ptr<std::set<line_no>> wdln, std::shared_ptr<std::vector<std::string>> ct) :
		word(wd), word_line_number(wdln), context(ct) {}
	
	
private:
	// 需要查询的单词
	std::string word;
	// 需要查询的单词对应的 line 的 set
	std::shared_ptr<std::set<line_no>> word_line_number;
	// 整个文本
	std::shared_ptr<std::vector<std::string>> context;

};

// 单词查询函数
inline
QueryResult 
TextQuery::query(std::string& s)
{
	// 定义一个静态 set 表示没有数据
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	// 查找 s
	auto find_it = word_line_num_mp.find(s);
	if (find_it == word_line_num_mp.end())
		return QueryResult(s, nodata, context_line);
	else
		return QueryResult(s, word_line_num_mp[s], context_line);
}

// 打印内容
std::ostream& print(std::ostream& stream, QueryResult& qr)
{

	stream << "This word appears " << (qr.word_line_number)->size() << " times" << std::endl;

	for (auto it = (qr.word_line_number)->begin(); it != (qr.word_line_number)->end(); ++it)
	{
		stream << "(line num = " << *it + 1 << ") : " << (*(qr.context))[*it] << std::endl;
	}


	return stream;
}


#endif // TEXTQUERY