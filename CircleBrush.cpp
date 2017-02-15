//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int triangleAmount = 100;
	int size = pDoc->getSize();
	float radius = size / 2.0;
	float twoPi = 3.1415927*2.0;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);
	glVertex2f((GLfloat)target.x, (GLfloat)target.y);

	float x = radius;
	float y = 0;

	float unitAngle = twoPi / triangleAmount;
	glVertex2f(target.x + x, target.y + y);
	for (int i = 1; i <= triangleAmount; i++) {
		x = radius*cosf(i*unitAngle);
		y = radius*sinf(i*unitAngle);
		glVertex2f(target.x + x, target.y + y);
	}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

