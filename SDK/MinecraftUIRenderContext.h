#pragma once
#include <string>
#include "..\Mod\Utils\HMath.h"
#include "..\Mod\Utils\Game.h"
#include "ClientInstance.h"
#include "TextHolder.h"


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
		this->r = r / 255.f;
		this->g = g / 255.f;
		this->b = b / 255.f;
		this->a = a / 255.f;
	}
};

struct TextMeasureData {
	float textSize;
	int idk;
	bool displayShadow;
	bool bool2;
};

class BitmapFont;
class CaretMeasureData;

using MUICDrawText = void(__fastcall*)(class MinecraftUIRenderContext*, BitmapFont*, RectangleArea const&, TextHolder* , UIColor const&, float, float, TextMeasureData*, uintptr_t*);
//MUICDrawText drawtextCall;

class MinecraftUIRenderContext {
private:
	virtual void Destructor();
public:
	virtual float getLinelength(BitmapFont&, std::string const&, float, bool);
private:
	virtual int getTextAlpha();
	virtual void setTextAlpha();
public:
	virtual void drawDebugText(RectangleArea const&, std::string const&, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&);
	virtual void drawText(BitmapFont&, RectangleArea const&, std::string const&, UIColor const&, float, float, TextMeasureData const&, CaretMeasureData const&);
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


	static uintptr_t* drawtextCall;

	//�ǹٷ� �Զ��庯��
public:

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="pos">λ��</param>
	/// <param name="size">��С</param>
	/// <param name="color">��ɫ</param>
	void Fillshape(struct vec2_t, struct vec2_t, UIColor);
	/// <summary>
	/// �����ľ���
	/// </summary>
	/// <param name="pos">λ��(����)</param>
	/// <param name="size">��С</param>
	/// <param name="color">��ɫ</param>
	/// <param name="w">�߿���</param>
	void Drawshape(struct vec2_t pos, struct vec2_t size, UIColor, float w);

	void Drawtext(const vec2_t& pos, std::string* textStr, const UIColor& color, float textSize, float alpha) {
		
		static uintptr_t caretMeasureData = 0xFFFFFFFF;
		if (!Game::mcfont)
		{
			return;
		}
		TextHolder text(*textStr);
		RectangleArea rect(pos.x, pos.x + 1000, pos.y - 1, pos.y + 1000);

		TextMeasureData textMeasure{};
		memset(&textMeasure, 0, sizeof(TextMeasureData));
		textMeasure.textSize = textSize;

		reinterpret_cast<MUICDrawText>(drawtextCall)(this, Game::mcfont, rect, &text, color, alpha, 0, &textMeasure, &caretMeasureData);
	}
};