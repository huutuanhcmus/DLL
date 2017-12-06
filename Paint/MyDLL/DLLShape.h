#pragma once

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;
#ifdef MATHLIBRARY_EXPORTS
#define SHAPELIBRARY_API __declspec(dllexport) 
#else
#define SHAPELIBRARY_API __declspec(dllimport) 
#endif

namespace MyDLL {
	class CShape
	{
	public:
		virtual SHAPELIBRARY_API void Draw(HDC hdc, Graphics* graphics, Pen* pen) = 0;
		virtual SHAPELIBRARY_API CShape* Create() = 0;
		virtual SHAPELIBRARY_API void SetData(POINT start, POINT end, bool flag) = 0;
		SHAPELIBRARY_API CShape();
		SHAPELIBRARY_API ~CShape();
	};

	class CLine : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		SHAPELIBRARY_API void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		SHAPELIBRARY_API CShape* Create();
		SHAPELIBRARY_API void SetData(POINT start, POINT end, bool flag);
		SHAPELIBRARY_API CLine();
		SHAPELIBRARY_API ~CLine();
	};

	class CRectangle : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		SHAPELIBRARY_API void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		SHAPELIBRARY_API CShape* Create();
		SHAPELIBRARY_API void SetData(POINT start, POINT end, bool flag);
		SHAPELIBRARY_API CRectangle();
		SHAPELIBRARY_API ~CRectangle();
	};

	class CEllipse : public CShape {
	private:
		POINT start;
		POINT end;
	public:
		SHAPELIBRARY_API void Draw(HDC hdc, Graphics* graphics, Pen* pen);
		SHAPELIBRARY_API CShape* Create();
		SHAPELIBRARY_API void SetData(POINT start, POINT end, bool flag);
		SHAPELIBRARY_API CEllipse();
		SHAPELIBRARY_API ~CEllipse();
	};
}

