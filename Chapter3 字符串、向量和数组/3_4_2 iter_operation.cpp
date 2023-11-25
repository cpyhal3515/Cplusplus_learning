#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main()
{
	/*------------------ 3.25 ------------------*/
	// 划分分数段（迭代器）
	vector<int> score = { 91, 85, 76, 43, 65, 29, 58, 77, 84, 90, 99, 100};
	vector<int> score_stage(11, 0);
	for (auto it = score.begin(); it != score.end(); it++)
	{
		++score_stage[(*it) / 10];
	}
	for (auto it : score_stage)
		cout << it << endl;




	return 0;
}