/*
任务9.21-9.27 学生成绩统计器 第二版
2026212245 赵孝楠

以下为9.21-9.27任务第二版
由于上周提交的第一版尚有许多疏漏之处，所以第二版对此进行了一些完善，使其尽可能地贴近任务要求

[注意]由于包含了头文件<windows.h>，代码可能需要在windows平台上，才能正常运行

*/

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct student
{
	string name;
	string id;
	int score = 0;
};

vector<student> student_information;

void student_add()
{
	cout << "\n[注意]您正在新建学生信息，请按照提示输入该新建学生的相关信息,并按下回车键确认！\n";
	student student_temp;

	while (true)
	{
		cout << "[注意]请输入新建学生姓名：";
		getline(cin, student_temp.name, '\n');
		
		if (student_information.empty())		//初次建立信息，不进入防重名检查
		{
			cout << "[注意]请输入新建学生学号：";
			getline(cin, student_temp.id, '\n');

			cout << "[注意]成绩信息中请勿包含空格或非数字信息，且成绩范围为0-100区间的整数，否则可能会导致信息错误或缺失！\n[注意]请输入新建学生成绩：";
			while (cin >> student_temp.score)
			{
				if (student_temp.score >= 0 && student_temp.score <= 100)
				{
					cin.ignore(999, '\n');		//防止未被读取的部分遗留在缓冲区影响下一次读取
					cout << "[注意]该新建学生信息已保存！\n";
					student_information.push_back(student_temp);
					return;
				}
				else
				{
					cin.ignore(999, '\n');
					cout << "[注意]您所输入的成绩不符合规范，请重新输入！\n";
					cout << "[注意]请输入新建学生成绩：";
					continue;
				}
			}
			cout << "[注意]您输入了非法信息，该信息无法保存，请重新输入信息！\n";		//防止死循环
			cin.clear();
			cin.ignore(999,'\n');
			continue;
		}
		else
		{
			for (int i = 0; i < student_information.size(); i++)		//进入防重名检测
			{
				if (student_temp.name == student_information[i].name)
				{
					cout << "[注意]您所输入的学生姓名已存在，请重新输入！\n";
					break;
				}
				else if (i == student_information.size() - 1 && student_temp.name != student_information[i].name)
				{
					cout << "[注意]请输入新建学生学号：";
					getline(cin, student_temp.id, '\n');

					cout << "[注意]成绩信息中请勿包含空格或非数字信息，且成绩范围为0-100区间的整数，否则可能会导致信息错误或缺失！\n[注意]请输入新建学生成绩：";
					while (cin >> student_temp.score)
					{
						if (student_temp.score >= 0 && student_temp.score <= 100)
						{
							cin.ignore(999, '\n');
							cout << "[注意]该新建学生信息已保存！\n";
							student_information.push_back(student_temp);
							return;
						}
						else
						{
							cin.ignore(999, '\n');
							cout << "[注意]您所输入的成绩不符合规范，请重新输入！\n";
							cout << "[注意]请输入新建学生成绩：";
							continue;
						}
					}
					cout << "[注意]您输入了非法信息，该信息无法保存，请重新输入信息！\n";
					cin.clear();
					cin.ignore(999,'\n');
					break;
				}
				else
				{
					continue;
				}
			}
			continue;
		}
	}
};

void student_find()
{
	if (student_information.empty())
	{
		cout << "\n[注意]您尚未保存任何学生信息！\n";
			return;
	}
	else
	{
		cout << "\n[注意]您正在按姓名查找学生，请按照提示输入该学生的姓名，并按下回车键确认！\n";
		string find_input;
		cout << "[注意]请输入学生姓名：";
		getline(cin, find_input, '\n');

		for (int i = 0; i < student_information.size(); i++)
		{
			if (find_input == student_information[i].name)
			{
				cout << "[注意]该学生相关信息如下：\n\n";
				cout << "[姓名|学号|成绩]\n";
				cout << "[" << student_information[i].name << "|" << student_information[i].id << "|" << student_information[i].score << "]\n";
				break;
			}
			else if (i == student_information.size() - 1 && find_input != student_information[i].name)
			{
				cout << "[注意]没有该学生的相关信息！\n";
				return;
			}
			else
			{
				continue;
			}
		}
		return;
	}
}

bool sort_base(student a, student b)		//自定义排序规则，成绩高的在前
{
	return a.score > b.score;
}

void student_sort()
{
	if (student_information.empty())
	{
		cout << "\n[注意]您尚未保存任何学生信息！\n";
		return;
	}
	else
	{
		sort(student_information.begin(), student_information.end(), sort_base);		//调用排序函数
		cout << "[注意]若学生成绩相同，则按照保存学生信息时的默认顺序进行排序！\n[注意]学生成绩排序情况如下：\n";
		cout << "\n[排名|姓名|学号|成绩]\n";
		for (int i = 0; i < student_information.size(); i++)
		{
			cout << "(" << i + 1 << ") " << "[" << student_information[i].name << "|" << student_information[i].id << "|" << student_information[i].score << "]\n";
		}
		return;
	}
}

void student_statistics()
{
	if (student_information.empty())
	{
		cout << "\n[注意]您尚未保存任何学生信息！\n";
		return;
	}
	else
	{
		sort(student_information.begin(), student_information.end(), sort_base);		//调用排序函数
		double score_sum = 0, score_average = 0, score_max = 0, score_min = 0, score_pass = 0, score_no_pass = 0;
		
		for (int i = 0; i < student_information.size(); i++)		//average计算
		{
			score_sum += student_information[i].score;
		}
		score_average = score_sum / student_information.size();

		score_max = student_information[0].score;		//max计算

		score_min = student_information[student_information.size() - 1].score;		//min计算

		for (int i = 0; i < student_information.size(); i++)		//pass or no_pass计算
		{
			if (student_information[i].score >= 60)
			{
				score_pass += 1;
			}
			else
			{
				score_no_pass += 1;
			}
		}

		cout << "[注意]学生成绩统计情况如下：\n\n";
		cout << "[平均分] " << fixed << setprecision(2) << score_average << "\n";
		cout << fixed << setprecision(0);
		cout << "[最高分] " << score_max << "\n";
		cout << "[最低分] " << score_min << "\n";
		cout << "[及格人数] " << score_pass << "\n";
		cout << "[不及格人数] " << score_no_pass << "\n";

		while (true)
		{
			cout << "\n[注意]若您想进一步查看成绩统计情况下的相关学生信息或退出此功能，请输入所需功能前对应的数字序号，并按下回车键确认，以使用该功能！\n\n";
			cout << "[1]最高分学生信息\n";
			cout << "[2]最低分学生信息\n";
			cout << "[3]及格学生信息\n";
			cout << "[4]不及格学生信息\n";
			cout << "[5]退出\n\n";
			cout << "[注意]输入内容中请勿包含空格或非数字信息，否则可能会导致错误！\n[注意]请输入数字序号：";
			string function_input;
			cin >> function_input;

			if (function_input == "1")
			{
				cout << "\n[注意]最高分学生信息如下：\n\n[姓名|学号|成绩]\n";
				cout << "[" << student_information[0].name << "|" << student_information[0].id << "|" << student_information[0].score << "]\n";
				continue;
			}
			else if (function_input == "2")
			{
				cout << "\n[注意]最低分学生信息如下：\n\n[姓名|学号|成绩]\n";
				cout << "[" << student_information[student_information.size() - 1].name << "|" << student_information[student_information.size() - 1].id << "|" << student_information[student_information.size() - 1].score << "]\n";
				continue;
			}
			else if (function_input == "3")
			{
				int r3 = 0;
				for (int i = 0; i < student_information.size(); i++)	
				{
					if (r3 == 0 && i == student_information.size() - 1 && student_information[i].score < 60)
					{
						cout << "[注意]没有成绩及格的学生！\n";
						break;
					}
					if (student_information[i].score >= 60)
					{
						if (r3 == 0)
						{
							cout << "\n[注意]若学生成绩相同，则按照保存学生信息时的默认顺序进行排序！\n[注意]及格学生信息如下：\n\n[姓名|学号|成绩]\n";
							r3 = 1;
						}
						cout << "[" << student_information[i].name << "|" << student_information[i].id << "|" << student_information[i].score << "]\n";
					}
				}
				continue;
			}
			else if (function_input == "4")
			{
				int r4 = 0;
				for (int i = 0; i < student_information.size(); i++)	
				{
					if (r4 == 0 && i == student_information.size() - 1 && student_information[i].score >= 60)
					{
						cout << "[注意]没有成绩不及格的学生！\n";
						break;
					}
					if (student_information[i].score < 60)
					{
						if (r4 == 0)
						{
							cout << "\n[注意]若学生成绩相同，则按照保存学生信息时的默认顺序进行排序！\n[注意]不及格学生信息如下：\n\n[姓名|学号|成绩]\n";
							r4 = 1;
						}
						cout << "[" << student_information[i].name << "|" << student_information[i].id << "|" << student_information[i].score << "]\n";
					}
				}
				continue;
			}
			else if (function_input == "5")
			{
				return;
			}
			else
			{
				cout << "\n[注意]没有对应的数字序号，请重新输入！\n";
			}
		}
	}
}

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);

	while (true)
	{
		cout << "\n[注意]您正处于“学生成绩统计器”系统主页，请输入所需功能前对应的数字序号，并按下回车键确认，以使用该功能！\n\n";
		cout << "[1]新建学生信息\n";
		cout << "[2]按姓名查找学生\n";
		cout << "[3]学生成绩排序\n";
		cout << "[4]学生成绩统计情况及查看\n";
		cout << "[5]退出\n\n";
		cout << "[注意]输入内容中请勿包含空格或非数字信息！\n[注意]请输入数字序号：";
		string function_input;
		cin >> function_input;

		if (function_input == "1")
		{
			cin.ignore();
			student_add();
			continue;
		}
		else if (function_input == "2")
		{
			cin.ignore();
			student_find();
			continue;
		}
		else if (function_input == "3")
		{
			cin.ignore();
			student_sort();
			continue;
		}
		else if (function_input == "4")
		{
			cin.ignore();
			student_statistics();
			continue;
		}
		else if (function_input == "5")
		{
			return 0;
		}
		else
		{
			cin.ignore(999, '\n');
			cout << "\n[注意]没有对应的数字序号，请重新输入！\n";
		}
	}
	return 0;
}