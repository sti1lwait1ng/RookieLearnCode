#include "Painting.h"
#include "Defines.h"
#include "Critters.h"
#include <time.h>
#include <cstdio>

const int img_size = 3;

// ��ʼ��
void Painting::Init()
{
	// ������ͼ����
	initgraph(1280, 900);

	// �����������
	srand((unsigned)time(NULL));

	// ��������ͼ���Ĵ�С
	Resize(&imgLive, img_size, img_size);
	Resize(&imgEmpty, img_size, img_size);

	// ���������������ͼ��
	SetWorkingImage(&imgLive);
	setcolor(GREEN);
	setfillstyle(GREEN);
	fillellipse(0, 0, img_size - 1, img_size - 1);

	// ���������������ͼ��
	SetWorkingImage(&imgEmpty);
	setcolor(DARKGRAY);
	rectangle(1, 1, img_size - 2, img_size - 2);

	// �ָ���Ĭ�ϴ��ڵĻ�ͼ
	SetWorkingImage(NULL);

	// �����˵��
	setfont(24, 0, L"����");
	outtextxy(254, 18, L"�� �� �� Ϸ - �� ��");
	RECT r = { 920, 180, 1060, 620 };
	setfont(16, 0, L"����");
	drawtext(L"������Ϸ��飺\n����������Ϸ����һ����ά�������磬��������е�ÿ�������ס		"
				"��һ�����ŵĻ����˵�ϸ����һ��ϸ������һ��ʱ������ȡ���������������������л��ŵ�		ϸ����������\n"
				"��Ϸ���ƣ�\n 0-9: �����ٶ�(��--��)\n ESC: �˳�\n�ո�: 		��ͣ|����\n   S: ����ϸ���Է��ηֲ�������\n"
				"   R: ����ϸ������ֲ�������\n   B: ����ϸ���ض��ֲ�������\n   T: �������ģʽ����ʼ��ʱ\n   C: ��ת��������",
		&r, DT_WORDBREAK);
}

// ��������
void Painting::PaintWorld(Critters* critters)
{
	ChangeCellColor(critters->GetColorValue());

	for (int x = 0; x < k_cells_size; x++)
		for (int y = 0; y < k_cells_size; y++)
			putimage(20 + y * img_size, 60 + x * img_size, critters->GetCellIsAlive(x, y) ? &imgLive : &imgEmpty);

}


// ���Ʋ�������
void Painting::PaintTestData(Critters* critters, DOUBLE time, INT test_count)
{
	TCHAR buffer_count[100], buffer_time[100]; // ȷ���������㹻��

	setfillstyle(SOLID_FILL, BLACK); // ���豳��ɫΪ��ɫ
	bar(920, 600, 920 + 200, 600 + 200); // �ñ���ɫ����ı�����
	_stprintf(buffer_count, _T("��ִ�д���: %d"), test_count);
	_stprintf(buffer_time, _T("��ִ��ʱ��: %.6f��"), time);
	setcolor(WHITE);
	setfont(16, 0, L"����");
	outtextxy(920, 600, buffer_count);
	outtextxy(920, 620, buffer_time);
	
	PaintWorld(critters);
}

void Painting::Deinit()
{
	closegraph();
}

void Painting::ChangeCellColor(COLORREF color)
{
	SetWorkingImage(&imgLive);
	setcolor(color);
	setfillstyle(color);
	fillellipse(0, 0, img_size - 1, img_size - 1);

	SetWorkingImage(NULL);
}
