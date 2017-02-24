//
// TriangleBrush.cpp
//
// The implementation of Triangle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "TriangleBrush.h"

extern float frand();

TriangleBrush::TriangleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void TriangleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (!dlg->getEnableAutoDraw())
		saveState();
	BrushMove(source, target);
}

void TriangleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int triangleAmount = 100;
	float size = pDoc->getSize();
	float radius = size;
	if (radius < 1)
		radius = 1;
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

	glBegin(GL_POLYGON);
	SetColor(source);
	glVertex2f((GLfloat)x, (GLfloat)y + size);
	glVertex2f((GLfloat)x + sqrt(3) * size/2, (GLfloat)y - size/2);
	glVertex2f((GLfloat)x - sqrt(3) * size / 2, (GLfloat)y - size / 2);

	

	glEnd();
}

void TriangleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* TriangleBrush::BrushName(void) {
	return ImpBrush::BrushName();
}