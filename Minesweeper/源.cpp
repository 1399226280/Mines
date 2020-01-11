/*
*���ߣ�Ұ���Ὥ
*������ڣ�2020.1.11
*��Ŀ����ɨ�ס�
*˵��������Ϸ��һ�����׵����飬������Ϸʵ�ڲ������ּ򵥵Ļ��Ȼ���Ѿ�ʱ�ڶ��ο����ˣ������ɻ������ʵ��ĳһ���������Բ���
*			���ʱ�������Ŀ���ҵ�������ҵ��Ϊ��ʵ���ܵ�����ͬ�ѶȵĹ��ܣ����ڵ�ʱ�����ᶯ̬�����ڴ棬ֻ��Ӳ����������6�����������
*			��������660�д�����깤������Ҳ�����ù�������һ��ѧ�ڵ�ѧϰ����������ζ�̬�����ڴ棬Ҳ���������ʵ�������ά������ڴ棬
*			���Ǿ�����������һ�飬����3��ʱ�䣬�����������������˵ȫ�µ�ɨ�׵ĳ��֣���Ҳ�����Ҷ����ѧ��������ѧ֪ʶ�Ĺ����ˡ�
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <graphics.h>
#include <iostream>
#include <windows.h>
char* tips_init = "��ѡ����Ҫ��ս���Ѷȣ�\n1.��\t2.һ��\t3.����\n�������Ӧ���֣�";
char* tips_err = "������ĸ�ʽ�������������룡";
int Tips();																//�����ʾ�������Ѷ���Ϣlevel
int Boom;																//����һ���׸����ı���
int Len;																	//���峤�ȣ�����Init_Map�и�ֵ��ʼ��
int size = 16;														//ͼƬ��С
int count = 0;														//�ж�ʤ������
int** Init_Map(int level);										//��ʼ����ͼ�����ø��ӵĸ������׵ĸ�����
void Random_map(int** p_map);						//�ڵ�ͼ�в���
void LoadImg_Windows();									//����ͼƬ������ͼ�λ����洰�ڣ�,���ھ����hwnd���ڴκ����г�ʼ����ֵ
void Print_Img_Map(int** p_map);						//���ͼƬ��ͼ��ˢ��ͼƬ
int PalyGame(int** p_map);									//����¼�������ֵΪ����󵥻���ͼƬ����ֵ���׵���ֵΪ-1
void Open_Zero(int** p_map, int x, int y);			//ʹ�õݹ飬�Զ�����0��Χ��0�ĸ��ӣ�����0��Χ�Ź����ھŹ����ҵ�0��ݹ�֮ǰ����
void DeleteArr(int** p_map, int* len);					//�ͷ��ڴ�
IMAGE img[12];
HWND hwnd;														//���ھ��
int main()
{
	int* len = &Len;												//ָ��ȼ�������ָ��
	int* boom = &Boom;										//ָ���ױ�����ָ��
	int** p_map;														//ָ���ͼ�Ķ���ָ��
	int* p_size = &size;											//ָ��ͼƬ��С
	p_map = Init_Map(Tips());								//ָ���ͼ�ĵ�ַ
	LoadImg_Windows();										//����ͼƬ������ͼ�λ����洰�ڣ�,���ھ����hwnd���ڴ˺����б���ʼ����ֵ
	Random_map(p_map);
	while (1)
	{
		Print_Img_Map(p_map);								//ˢ��ͼƬ
		if (PalyGame(p_map) == -1)
		{
			Print_Img_Map(p_map);
			if (MessageBox(hwnd, L"��̫��������Ҫ����ѡ���Ѷ�����һ����", L"Tips:", MB_RETRYCANCEL) == 4)
			{
				closegraph();
				DeleteArr(p_map, len);
				return main();
			}
			closegraph();
			return 0;
		}
		if ((*len) * (*len) - (*boom) == count)
		{
			if (MessageBox(hwnd, L"��ϲ�㣡��ʤ�ˣ���Ҫ����ѡ���Ѷȼ�����ս��", L"Tips:", MB_OKCANCEL) == 1)
			{
				closegraph();
				DeleteArr(p_map, len);
				return main();
			}
			closegraph();
			DeleteArr(p_map, len);
			return 0;
		}
	}
}
int Tips()																//�����ʾ������ȡ�Ѷ���Ϣ
{
	int level;															//�����Ѷȵȼ�����
	std::cout << tips_init;										//�����ʾ��Ϣ
	std::cin >> level;												//��ȡ�Ѷ���Ϣ
	if ((int)level > 3 || (int)level < 1)						//�жϸ�ʽ
	{
		std::cout << tips_err;
		return Tips();
	}
	return (int)level;
}
int** Init_Map(int level)										//��ʼ����ͼ
{
	int* len = &Len;
	int* p_Boom = NULL;
	p_Boom = &Boom;
	switch (level)													//�����û���ѡ�ȼ�����ʼ����ͼ��С�Լ��׵ĸ���
	{
	case 1:
		*len = 10;
		*p_Boom = 10;
		break;
	case 2:
		*len = 20;
		*p_Boom = 50;
		break;
	case 3:
		*len = 30;
		*p_Boom = 100;
		break;
	}

	int** p_map = new int* [*len + 2];   				//���ٴ�СΪlen���ڴ�ռ�ָ��һάָ��,+2��Ϊ�˶��帨����
	for (int i = 0; i < *len + 2; i++)
	{
		p_map[i] = new int[*len + 2];
	}																		//��ÿһ��һάָ�붼���ٴ�СΪlen���ڴ�ռ䣬ʵ���˶�̬������ά����
	for (int i = 0; i < *len + 2; i++)						//����ά�����ʼ��
	{
		for (int j = 0; j < *len + 2; j++)
		{
			*(p_map[i] + j) = 0;
		}
	}
	return p_map;													//���ص�ͼָ��ĵ�ַ��ʹ��new����ĵ�ַ��������delete���ں������ý����󲻻ᱻ�ͷţ�������Ϊ����ֵ����
}
void Random_map(int** p_map)
{
	int* p_size = &size;
	srand((unsigned int)time(NULL));
	int x;
	int y;
	int* len = &Len;
	const int* p_boom = &Boom;
	int count = 0;
	//std::cout << p_map;
	while (count < *p_boom)								//�����㷨
	{
		x = (int)((rand() % (*len)) + 1);
		y = (int)((rand() % (*len)) + 1);
		if (*(p_map[x] + y) == 0)
		{
			*(p_map[x] + y) = -1;								//�������
			count++;
		}
	}
	for (int i = 1; i <= *len; i++)
	{
		for (int j = 1; j <= *len; j++)
		{
			if (*(p_map[i] + j) == 0)
			{
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (*(p_map[m] + n) == -1)
						{
							*(p_map[i] + j) = *(p_map[i] + j) + 1;
						}
					}
				}
			}
		}
	}
	///*
	for (int j = 1; j <= *len; j++)							//����
	{
		for (int i = 1; i <= *len; i++)
		{
			*(p_map[i] + j) = *(p_map[i] + j) + 20;
			//std::cout << *(p_map[i] + j);
		}
		//std::cout << std::endl;
	}
	//*/
}
void Print_Img_Map(int** p_map)
{
	int* len = &Len;
	int* p_size = &size;
	for (int j = 1; j <= *len; j++)							//ת��x,y��
	{
		for (int i = 1; i <= *len; i++)
		{
			printf_s("%2d", *(p_map[i] + j));
			if (*(p_map[i] + j) == -1)
			{
				putimage((i - 1) * (*p_size), (j - 1) * (*p_size), &img[9]);
			}
			else if (*(p_map[i] + j) >= 0 && *(p_map[i] + j) <= 8)
			{
				putimage((i - 1) * (*p_size), (j - 1) * (*p_size), &img[*(p_map[i] + j)]);
			}
			else if (*(p_map[i] + j) >= 19 && *(p_map[i] + j) <= 28)
			{
				putimage((i - 1) * (*p_size), (j - 1) * (*p_size), &img[10]);
			}
			else if (*(p_map[i] + j) >= 29)
			{
				putimage((i - 1) * (*p_size), (j - 1) * (*p_size), &img[11]);
			}
			//std::cout << *(p_map[i] + j);
		}
		std::cout << std::endl;
	}
}
void LoadImg_Windows()
{
	int* p_size = &size;														//img_size
	HWND* p_hwnd = &hwnd;
	*p_hwnd = initgraph(Len * size, Len * size, SHOWCONSOLE);
	loadimage(&img[0], L"0.bmp", *p_size, *p_size);		//button_onclick
	loadimage(&img[1], L"1.bmp", *p_size, *p_size);
	loadimage(&img[2], L"2.bmp", *p_size, *p_size);
	loadimage(&img[3], L"3.bmp", *p_size, *p_size);
	loadimage(&img[4], L"4.bmp", *p_size, *p_size);
	loadimage(&img[5], L"5.bmp", *p_size, *p_size);
	loadimage(&img[6], L"6.bmp", *p_size, *p_size);
	loadimage(&img[7], L"7.bmp", *p_size, *p_size);
	loadimage(&img[8], L"8.bmp", *p_size, *p_size);
	loadimage(&img[9], L"9.bmp", *p_size, *p_size);		//��
	loadimage(&img[10], L"10.bmp", *p_size, *p_size);    //button_normal
	loadimage(&img[11], L"11.bmp", *p_size, *p_size);	//flag
}
int PalyGame(int** p_map)
{
	int x;
	int y;
	MOUSEMSG msg = { 0 };
	int* p_size = &size;
	while (1)
	{
		msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:						//����������
			x = msg.x / (*p_size) + 1;
			y = msg.y / (*p_size) + 1;
			if (*(p_map[x] + y) >= 19 && *(p_map[x] + y) <= 28)
			{
				if (*(p_map[x] + y) == 20)
				{
					Open_Zero(p_map, x, y);
				}
				else {
					*(p_map[x] + y) = *(p_map[x] + y) - 20;
					count++;
				}
				std::cout << *(p_map[x] + y);
			}
			return *(p_map[x] + y);
		case WM_RBUTTONDOWN:						//����Ҽ�����
			x = msg.x / (*p_size) + 1;
			y = msg.y / (*p_size) + 1;
			if (*(p_map[x] + y) >= 19 && *(p_map[x] + y) <= 28)
			{
				*(p_map[x] + y) = *(p_map[x] + y) + 50;
			}
			else if (*(p_map[x] + y) >= 29)
			{
				*(p_map[x] + y) = *(p_map[x] + y) - 50;
			}
			return *(p_map[x] + y);
		}
	}
}
void Open_Zero(int** p_map, int x, int y)
{
	*(p_map[x] + y) = *(p_map[x] + y) - 20;
	count++;
	int* len = &Len;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 1 && i <= *len && j >= 1 && j <= *len)
			{
				if (*(p_map[i] + j) > 19 && *(p_map[i] + j) <= 28)
				{
					if (*(p_map[i] + j) != 20)
					{
						*(p_map[i] + j) = *(p_map[i] + j) - 20;
						count++;
					}
					else
					{
						Open_Zero(p_map, i, j);
					}
				}
			}
		}
	}
}
void DeleteArr(int** p_map, int* len)					//�ͷŶ���ָ��������ڴ棬�����ڴ�й¶
{
	for (int i = 0; i < (*len + 2); i++)
	{
		delete[] p_map[i];
	}
	delete[] p_map;
}