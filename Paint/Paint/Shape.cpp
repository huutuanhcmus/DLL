#include "stdafx.h"
#include "Shape.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
namespace MyShape {
	CShape::CShape()
	{
	}


	CShape::~CShape()
	{
	}

	void CLine::Draw(HDC hdc, Graphics* graphics, Pen* pen) {
		graphics->DrawLine(pen, start.x, start.y, end.x, end.y);
	}

	CShape* CLine::Create() {
		return new CLine;
	}

	void CLine::SetData(POINT start, POINT end, bool flag) {
		this->start = start;
		this->end = end;
	}

	CLine::CLine()
	{
	}


	CLine::~CLine()
	{
	}

	void CRectangle::Draw(HDC hdc, Graphics* graphics, Pen* pen) {

		graphics->DrawRectangle(pen, start.x, start.y, end.x - start.x, end.y - start.y);
	}

	CShape* CRectangle::Create() {
		return new CRectangle;
	}

	void CRectangle::SetData(POINT start, POINT end, bool flag) {
		if (flag == false) {
			this->start = start;
			this->end = end;
		}
		else {
			this->start = start;
			this->end.x = start.x + min(end.x - start.x, end.y - start.y);
			this->end.y = start.y + min(end.x - start.x, end.y - start.y);
		}
	}

	CRectangle::CRectangle()
	{
	}


	CRectangle::~CRectangle()
	{
	}

	void CEllipse::Draw(HDC hdc, Graphics* graphics, Pen* pen) {
		graphics->DrawEllipse(pen, start.x, start.y, end.x - start.x, end.y - start.y);
	}

	CShape* CEllipse::Create() {
		return new CRectangle;
	}

	void CEllipse::SetData(POINT start, POINT end, bool flag) {
		if (flag == false) {
			this->start = start;
			this->end = end;
		}
		else {
			this->start = start;
			this->end.x = start.x + min(end.x - start.x, end.y - start.y);
			this->end.y = start.y + min(end.x - start.x, end.y - start.y);
		}
	}

	CEllipse::CEllipse()
	{
	}


	CEllipse::~CEllipse()
	{
	}
}
