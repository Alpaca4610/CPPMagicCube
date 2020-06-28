#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

static int cube[19][19]{ 0 };//存储幻方数据的二维数组
static int xyindex[2]{ 10,1 };//用来访问幻方中元素的索引，初始位置为第一行的中部

void judge() {//根据幻方的生成规则进行索引判断和变换的函数
	int temp[2]{ xyindex[0],xyindex[1] };//使用一个临时数组存储未变换前的索引，便于后续碰到已经填充的方格可以还原
	if (xyindex[0] % 19 == 0) {//判断幻方索引是否到达最右端
		if (xyindex[0] == 19 && xyindex[1] == 1) {//判断幻方索引是否同时到达最右端和最顶端
			xyindex[1]++;//按照幻方变换规则变换索引
		}
		else {
			xyindex[1]--;
			xyindex[0] = 1;
		}
	}
	else if (xyindex[0] >= 1 && xyindex[0] <= 18 && xyindex[1] == 1) {//判断幻方索引是否到达最顶端
		xyindex[1] = 19;//按照幻方变换规则变换索引
		xyindex[0] ++;
	}
	else {
		xyindex[0]++;//正常情况下的幻方索引变换
		xyindex[1]--;
	}
	while (cube[xyindex[0] - 1][xyindex[1] - 1] != 0) {//判断变换后的幻方索引对应的方格是否有数据填充
		xyindex[0] = temp[0];//若填充，则跳回变换前的幻方索引，再跳转到下一个未填充的方格
		xyindex[1] = temp[1] + 1;
		temp[1] = xyindex[1];
	}
}
int main() {
	for (int i = 0; i < 19 * 19; i++) {//填满十九阶的幻方需要执行19*19次操作
		if (cube[xyindex[0] - 1][xyindex[1] - 1] == 0) {//0代表该方格未填充，若未填充，则按规则填充幻方
			cube[xyindex[0] - 1][xyindex[1] - 1] = i + 1;
		}
		judge();//填充完成之后，幻方索引跳转
	}
	for (int i = 0; i < 19; i++) {//嵌套循环按行按列输出幻方的内容
		cout << endl;
		for (int j = 0; j < 19; j++) {
			cout << std::setw(3) << cube[j][i] << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 19; i++) {//计算幻方每行的和
		int sum = 0;
		for (int j = 0; j < 19; j++) {
			sum += cube[i][j];
		}
		cout << "第" << i << "行的元素和为：" << sum << endl;
	}
	cout << "幻方四个顶点的元素和为：" << cube[0][0] + cube[0][18] + cube[18][0] + cube[18][18] << endl;//计算幻方四角的和
	return 0;
}