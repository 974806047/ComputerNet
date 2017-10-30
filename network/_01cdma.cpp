/*
1、实验题目：CDMA 编码
2、实验内容：
（1） 随机生成 5 个互不正交的 8 位码片 M1、M2、M3、M4、M5。
（2） 分别求出与 M1、M2、M3、M4、M5所有正交的 8 位码片。
3、实验报告内容：
（1） CDMA 信道复用原理。
（2） 随机生成的的 5 个互不正交的码片 M1、M2、M3、M4、M5。
（3） 获取与某个码片正交的全部码片的算法。
（4） 记录与 M1 正交的码片数量及 10 个与 M1正交的码片，不足 10 个的记录全部码片，
互为反码的记为一个。
（5） 记录与 M2 正交的码片数量及 10 个与 M2正交的码片，不足 10 个的记录全部码片，
互为反码的记为一个。
（6） 记录与 M3 正交的码片数量及 10 个与 M3正交的码片，不足 10 个的记录全部码片，
互为反码的记为一个。
（7） 记录与 M4 正交的码片数量及 10 个与 M4正交的码片，不足 10 个的记录全部码片，
互为反码的记为一个。
（8） 记录与 M5 正交的码片数量及 10 个与 M5正交的码片，不足 10 个的记录全部码片，
互为反码的记为一个。
比较与 M1、M2、M3、M4、M5 正交的码片总数并简单分析原因。
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
int * tenToTwo(int ten) {//十进制转二进制
	if (ten > 255 || ten<0) return NULL;
	int *two = new int[8];
	for (int i = 0; i<8; i++)two[i] = 0;
	int ii = 0;
	while (ten) {
		two[ii] = ten % 2;
		ten /= 2;
		ii++;
	}
	return two;
}
int panduan(int a, int b) {//正交则返回0
	int* mapian1 = tenToTwo(a);
	int* mapian2 = tenToTwo(b);
	for (int i = 0; i<8; i++)//将二进制中的0转化成-1
	{
		if (mapian1[i] == 0)	mapian1[i] = -1;
		if (mapian2[i] == 0)	mapian2[i] = -1;
	}
	int res = 0;
	for (int j = 0; j<8; j++)res += mapian1[j] * mapian2[j];
	return res;
}
int* getZhengjiaoMapian(int mapian)
{//获取某个码片正交的全部码片，最后一个位置放数量
	int *allMapian=new int[256];
	int count = 0;
	for (int i=0; i<256; i++)
	{
		if (mapian == i) continue;
		if (panduan(i, mapian) == 0)
		{
			allMapian[count] = i;
			count++;
		}
	}
	allMapian[255] = count;
	return allMapian;
}
int* creatRandomMapian()//产生5个互不正交的码片（十进制）
{
	int max = 255, min = 0;
	int random = (rand() % (max - min + 1)) + min;
	
	int *mapian=new int[5];
	mapian[0] = random;
	for (int i = 1; i<5; i++)
	{
		while (true)
		{
			int rand1 = (rand() % (max - min + 1)) + min;
			bool bol = false;//用来判断生成的随机数是否和之前的数重复或者正交
			for (int j = 0; j<i; j++)
			{
				if (rand1 == mapian[j]) bol = true;
				if (panduan(rand1, mapian[j]) == 0)bol = true;
			}
			if (bol) continue;
			else
			{
				mapian[i] = rand1;
				break;
			}
		}
	}
	return mapian;
}

void main()
{
	int *mapian = creatRandomMapian();
	for (int i = 0; i < 5; i++) {
		int m = mapian[i];
		int *mp = tenToTwo(m);
		cout << "码片" << i + 1 << ":";
		for (int j = 0; j < 8; j++)cout << mp[j];
		cout << endl;
		int *zhengjiao = getZhengjiaoMapian(mapian[i]);
		int index = 0;
		cout << "与码片" << i + 1 << "正交的码片有" << zhengjiao[255] << "个,其中十个为：" << endl;
		for (int j = 0; j < zhengjiao[255]; j++) {
			if (index == 10) {
				index = 0;
				break;
			}
			int *two = tenToTwo(zhengjiao[j]);
			for (int k = 0; k < 8; k++)
				cout << two[k];
			cout << endl;
			index++;
		}
		
	}

	
	int a;
	cin >> a;
}


