/*
1��ʵ����Ŀ��CDMA ����
2��ʵ�����ݣ�
��1�� ������� 5 ������������ 8 λ��Ƭ M1��M2��M3��M4��M5��
��2�� �ֱ������ M1��M2��M3��M4��M5���������� 8 λ��Ƭ��
3��ʵ�鱨�����ݣ�
��1�� CDMA �ŵ�����ԭ��
��2�� ������ɵĵ� 5 ��������������Ƭ M1��M2��M3��M4��M5��
��3�� ��ȡ��ĳ����Ƭ������ȫ����Ƭ���㷨��
��4�� ��¼�� M1 ��������Ƭ������ 10 ���� M1��������Ƭ������ 10 ���ļ�¼ȫ����Ƭ��
��Ϊ����ļ�Ϊһ����
��5�� ��¼�� M2 ��������Ƭ������ 10 ���� M2��������Ƭ������ 10 ���ļ�¼ȫ����Ƭ��
��Ϊ����ļ�Ϊһ����
��6�� ��¼�� M3 ��������Ƭ������ 10 ���� M3��������Ƭ������ 10 ���ļ�¼ȫ����Ƭ��
��Ϊ����ļ�Ϊһ����
��7�� ��¼�� M4 ��������Ƭ������ 10 ���� M4��������Ƭ������ 10 ���ļ�¼ȫ����Ƭ��
��Ϊ����ļ�Ϊһ����
��8�� ��¼�� M5 ��������Ƭ������ 10 ���� M5��������Ƭ������ 10 ���ļ�¼ȫ����Ƭ��
��Ϊ����ļ�Ϊһ����
�Ƚ��� M1��M2��M3��M4��M5 ��������Ƭ�������򵥷���ԭ��
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
int * tenToTwo(int ten) {//ʮ����ת������
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
int panduan(int a, int b) {//�����򷵻�0
	int* mapian1 = tenToTwo(a);
	int* mapian2 = tenToTwo(b);
	for (int i = 0; i<8; i++)//���������е�0ת����-1
	{
		if (mapian1[i] == 0)	mapian1[i] = -1;
		if (mapian2[i] == 0)	mapian2[i] = -1;
	}
	int res = 0;
	for (int j = 0; j<8; j++)res += mapian1[j] * mapian2[j];
	return res;
}
int* getZhengjiaoMapian(int mapian)
{//��ȡĳ����Ƭ������ȫ����Ƭ�����һ��λ�÷�����
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
int* creatRandomMapian()//����5��������������Ƭ��ʮ���ƣ�
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
			bool bol = false;//�����ж����ɵ�������Ƿ��֮ǰ�����ظ���������
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
		cout << "��Ƭ" << i + 1 << ":";
		for (int j = 0; j < 8; j++)cout << mp[j];
		cout << endl;
		int *zhengjiao = getZhengjiaoMapian(mapian[i]);
		int index = 0;
		cout << "����Ƭ" << i + 1 << "��������Ƭ��" << zhengjiao[255] << "��,����ʮ��Ϊ��" << endl;
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


