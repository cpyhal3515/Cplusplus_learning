#include<iostream>
#include<vector>
using namespace std;

// 定义目前的题目序号
#define PROBLEM_5_10

int main()
{
	#ifdef PROBLEM_5_5
	/* ---------------- 5.5 ---------------- */
	// 使用条件语句将数字成绩转换成字母成绩
	const int peo_num = 10;
	int score_int_list[peo_num] = { 100, 85, 73, 22, 90, 67, 44, 33, 88, 93 };
	vector<char> score_char_list;
	for (const int sc : score_int_list)
	{
		if (sc >= 90)
		{
			score_char_list.push_back('A');
		}
		else if (sc >= 80)
		{
			score_char_list.push_back('B');
		}
		else if (sc >= 60)
		{
			score_char_list.push_back('C');
		}
		else
		{
			score_char_list.push_back('D');
		}
	}

	for (const char sc : score_char_list)
	{
		cout << sc << " ";
	}
	cout << endl;

	#endif // PROBLEM_5_5

	#ifdef PROBLEM_5_6
	/* ---------------- 5.6 ---------------- */
	// 使用条件运算符将数字成绩转换成字母成绩
	const int peo_num = 10;
	int score_int_list[peo_num] = { 100, 85, 73, 22, 90, 67, 44, 33, 88, 93 };
	vector<char> score_char_list;
	for (const int sc : score_int_list)
	{
		(sc >= 90) ? score_char_list.push_back('A') : \
		(sc >= 80) ? score_char_list.push_back('B') : \
		(sc >= 60) ? score_char_list.push_back('C') : \
		score_char_list.push_back('D');
	}

	for (const char sc : score_char_list)
	{
		cout << sc << " ";
	}
	cout << endl;

	#endif

	#ifdef PROBLEM_5_10
	/* ---------------- 5.10 ---------------- */
	// 统计元音字母
	string context_str = "buoqnakANIPUEIOPBUIWNPVUONLSnbfueiooae";
	
	int acnt = 0;
	int ecnt = 0;
	int icnt = 0;
	int ocnt = 0;
	int ucnt = 0;

	for (const char ch : context_str)
	{
		switch (ch)
		{
			case 'a':
			case 'A':
				++acnt;
				break;
			case 'e' :
			case 'E':
				++ecnt;
				break;
			case 'i':
			case 'I':
				++icnt;
				break;
			case 'o':
			case 'O':
				++ocnt;
				break;
			case 'u':
			case 'U':
				++ucnt;
				break;
			default:
				break;
		}
	}

	cout << "acnt = " << acnt << " , ecnt = " << \
		ecnt << " , icnt = " << icnt << " , ocnt = " << \
		ocnt << " , ucnt = " << ucnt << endl;

	#endif



	return 0;
}