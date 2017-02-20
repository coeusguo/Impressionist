//
// GrayBrush.cpp
//
// The implementation of Gray Brush. It is a kind of PointBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "GrayBrush.h"

extern float frand();

GrayBrush::GrayBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void GrayBrush::BrushBegin(const Point source, const Point target)
{
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (!dlg->getEnableAutoDraw())
		saveState();

	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void GrayBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("GrayBrush::BrushMove  document is NULL\n");
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

	glBegin(GL_POINTS);
	grayColor(source);

	glVertex2d(x,y);

	glEnd();
}

void GrayBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

//get the name of current brush
char* GrayBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

void GrayBrush::grayColor(Point source) {
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	color[3] = GLubyte(pDoc->getAlpha() * 255);
	
	int merge = ((int)color[0] + (int)color[1] + (int)color[2]) / 3;
	color[0] = (GLubyte)merge;
	color[1] = (GLubyte)merge;
	color[2] = (GLubyte)merge;
	glColor4ubv(color);
}
