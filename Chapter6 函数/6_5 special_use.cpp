#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_6_44_47


#ifdef PROBLEM_6_42
string make_plural(size_t ctr, const string& word, const string& ending = "s")
{
	return (ctr > 1) ? word + ending : word;
}
#endif

#ifdef PROBLEM_6_44_46
inline bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}

constexpr bool isShorter(const string& s1, const string& s2)
{
	return s1.size() < s2.size();
}
#endif

void print(const int ia[], size_t size)
{
#ifndef NDEBUG
	cerr << __func__ << ": array size is " << size << endl;
#endif // !NDEBUG

}


int main()
{
#ifdef PROBLEM_6_42
	/* ---------------- 6.42 ---------------- */
	// 复数，形参赋予默认值
	string word = "word";
	string words;
	words = make_plural(word.size(), word);
	cout << "words  = " << words << endl;
#endif

#ifdef PROBLEM_6_44_46
	
#endif
	int ia[3] = { 1,2,3 };
	print(ia, 3);
	return 0;
}
