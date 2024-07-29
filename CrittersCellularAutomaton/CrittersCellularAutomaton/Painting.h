#pragma once

#include <graphics.h>

class Critters;
class Painting
{
private:
	IMAGE imgLive, imgEmpty;		// �����ϸ������ϸ�������ͼ��

protected:
	void ChangeCellColor(COLORREF color);

public:
	void Init();
	void Deinit();
	void PaintWorld(Critters *critters);
	void PaintTestData(Critters* critters, DOUBLE time, INT test_count);
};
