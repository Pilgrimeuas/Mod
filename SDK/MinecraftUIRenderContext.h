#pragma once
#include <string>
/* ����麯������,����ȥida�ܰ�׿��MCȥ���µ��麯�� */
/* ������Ƶ���ߵ�˵��������麯����һ��ʼ��û�б�� */

struct RectangleArea {
public:
	float w, x, y, z;

	RectangleArea(float w, float x, float y, float z) {
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct UIColor {
public:
	float r, g, b, a;
	UIColor(float r = 255, float g = 255, float b = 255, float a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

class TextMeasureData;
class CaretMeasureData;


class MinecraftUIRenderContext {
private:
	virtual void Destructor();
public:
	virtual float getLinelength(class BitmapFont&, std::string const&, float, bool);
private:
	virtual int getTextAlpha();
	virtual void setTextAlpha();
public:
	virtual void drawDebugText(RectangleArea const&, std::string const&, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&);
	virtual void drawText(class BitmapFont&, RectangleArea const&, std::string const&, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&);
	virtual void flushText(float);
private:
	virtual void drawImage();
	virtual void drawNineslice();
	virtual void flushImage();
	virtual void beginSharedMeshBatch();
	virtual void endSharedMeshBatch();
public:
	virtual void drawRectangle(RectangleArea const&, UIColor const&, float, int);
	virtual void fillRectangle(RectangleArea const&, UIColor const&, float);

};