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
	saveState();
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

	int x = target.x;
	int y = target.y;

	int startCol = dlg->m_paintView->getStartCol();
	int startRow = dlg->m_paintView->getStartRow() + dlg->m_mainWindow->h() - dlg->m_paintView->getDrawHeight() - 25;
	//int startRow = 0;
	int endCol = dlg->m_paintView->getEndCol();
	int endRow = startRow + dlg->m_paintView->getDrawHeight();

	if (x < startCol) {
		x = startCol;
	}

	if (x > endCol) {
		x = endCol;
	}

	if (y < startRow) {
		y = startRow;
	}

	if (y > endRow) {
		y = endRow;
	}

	glBegin(GL_TRIANGLE_FAN);
	SetColor(source);
	glVertex2f((GLfloat)x, (GLfloat)y);

	float xx = radius;
	float yy = 0;

	float unitAngle = twoPi / triangleAmount;
	glVertex2f(x + xx, y + yy);
	for (int i = 1; i <= triangleAmount; i++) {
		xx = radius*cosf(i*unitAngle);
		yy = radius*sinf(i*unitAngle);
		glVertex2f(x + xx, y + yy);
	}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* CircleBrush::BrushName(void) {
	return ImpBrush::BrushName();
}