//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	float twoPi = 3.1415927*2.0;
	int length = pDoc->getSize();
	int width = pDoc->getLineWidth();
	int angle = pDoc->getLineAngle();
	int size = pDoc->getSize();
	float radian = (angle / 360.00)*twoPi;
	
	
	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	glLineWidth((GLfloat)width);

	glBegin(GL_LINES);
	SetColor(source);
	float v1x = (size / 2.0)*cosf(radian);
	float v1y = (size / 2.0)*sinf(radian);
	float v2x = -v1x;
	float v2y = -v1y;

	glVertex2d(target.x + v1x, target.y + v1y);
	glVertex2d(target.x + v2x, target.y + v2y);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

