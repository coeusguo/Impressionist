//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "MosaicBrush.h"

extern float frand();

MosaicBrush::MosaicBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
	prevSize = 10;
}

void MosaicBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (!dlg->getEnableAutoDraw()&& !dlg->m_nPainterlyRun)
		saveState();

	if (prevSize != pDoc->getSize()) {
		pDoc->generateMosaicMap();
		prevSize = pDoc->getSize();
	}
	BrushMove(source, target);
}

void MosaicBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
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

	int size = pDoc->getSize();

	glPointSize(1);
	glBegin(GL_POINTS);
	GLubyte color[3];
	for (int Y = y - size / 2; Y <= y + size / 2; Y++) {
		for (int X = x - size / 2; X <= x + size / 2; X++) {
			memcpy(color, pDoc->getMosaicMapPixel(X,Y), 3);
			glColor3ub(color[0],color[1],color[2]);
			glVertex2d(X, Y);
		}
	}
	glEnd();
}

void MosaicBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* MosaicBrush::BrushName(void) {
	return ImpBrush::BrushName();
}