//
// AlphaMapBrush.cpp
//
// The implementation of Alpha Map Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "AlphaMapBrush.h"
#include <iostream>
using namespace std;

extern float frand();

AlphaMapBrush::AlphaMapBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void AlphaMapBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	if (pDoc->m_ucAlphamap == NULL) {
		fl_alert("Pleas load an alpha map first!");
		return;
	}
	saveState();
	glPointSize(1);

	BrushMove(source, target);
}

void AlphaMapBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("AlphaMapBrush::BrushMove  document is NULL\n");
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

	int height = pDoc->m_nAlphaMapHeight;
	int width = pDoc->m_nAlphaMapWidth;
	cout << width << "," << height << endl;
	unsigned char* alphaMap = pDoc->m_ucAlphamap;

	int beginY = -(height / 2);
	int beginX = -(width / 2);
	int endY = beginY + height;
	int endX = beginX + width;

	GLubyte color[4];
	memcpy(color, pDoc->GetOriginalPixel(source), 3);


	glBegin(GL_POINTS);
	for (int i = beginY; i < endY; i++) {
		for (int j = beginX; j < endX; j++) {
			color[3] = GLubyte(alphaMap[width*(i - beginY) + j - beginX])*pDoc->getAlpha();
			glColor4ubv(color);
			if ((x + j) > startCol && (x + j) < endCol) {
				if((y+i)>startRow&&(y+i)<endRow)
					glVertex2d(x + j, y + i);
			}
			
		}
	}
	glEnd();
}

void AlphaMapBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* AlphaMapBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

