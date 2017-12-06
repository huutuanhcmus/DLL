#pragma once
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
namespace MyShape {
	class CShape
	{
	public:
		virtual void Draw(HDC hdc, Graphics* graphics, Pen* pen) = 0;
		virtual CShape* Create() = 0;
		virtual void SetData(POINT start, POINT end, bool flag) = 0;
		CShape();
		~CShape();
	};

	class CLine : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		CShape* Create();
		void SetData(POINT start, POINT end, bool flag);
		CLine();
		~CLine();
	};

	class CRectangle : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		CShape* Create();
		void SetData(POINT start, POINT end, bool flag);
		CRectangle();
		~CRectangle();
	};

	class CEllipse : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		CShape* Create();
		void SetData(POINT start, POINT end, bool flag);
		CEllipse();
		~CEllipse();
	};
}
