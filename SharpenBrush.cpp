//
// SharpenBrush.cpp
//
// The implementation of Sharpen Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SharpenBrush.h"

extern float frand();

SharpenBrush::SharpenBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
	
{
	filter[0][0] = 0; filter[0][1] = -1; filter[0][2] = 0;

	filter[1][0] = -1; filter[1][1] = 5; filter[1][2] = -1;
	
	filter[2][0] = 0; filter[2][1] = -1; filter[2][2] = 0;
}

void SharpenBrush::BrushBegin(const Point source, const Point target)
{
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if(!dlg->getEnableAutoDraw())
		saveState();
	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void SharpenBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (!dlg->getEnableAutoDraw())
		saveState();


	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

	int x = target.x;
	int y = target.y;
	
	//store the  pixels
	float*** buffer = new float**[9];
	for (int i = 0; i < 9; i++) {
		buffer[i] = new float*[9];
		for (int j = 0; j < 9; j++)
			buffer[i][j] = new float[3];
	}

	
	int startCol = dlg->m_paintView->getStartCol();
	int startRow = dlg->m_paintView->getStartRow() + dlg->m_mainWindow->h() - dlg->m_paintView->getDrawHeight() - 25;
	//int startRow = 0;
	int endCol = dlg->m_paintView->getEndCol();
	int endRow = startRow + dlg->m_paintView->getDrawHeight();

	if (x < startCol) {
		x = startCol + 4;
	}

	if (x >= endCol) {
		x = endCol-4;
	}

	if (y <= startRow) {
		y = startRow+4;
	}

	if (y >= endRow) {
		y = endRow-4;
	}

	for (int i = -4; i < 5; i++) {
		for (int j = -4; j < 5; j++) {
			applyFilter(x+i,y+j,buffer,i+4,j+4);
		}
	}
	
	

	glPointSize(1);
	glBegin(GL_POINTS);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			glColor3ub((GLubyte)buffer[i][j][0],(GLubyte) buffer[i][j][1], (GLubyte)buffer[i][j][2]);
			glVertex2d(x + i - 4, y + j - 4);
		}
	}

	glEnd();
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			delete[]buffer[i][j];
		}
		delete[]buffer[i];
	}
	delete[]buffer;
}

void SharpenBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* SharpenBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

void SharpenBrush::applyFilter(int x,int y,float***buffer,int row,int col) {
	ImpressionistDoc* pDoc = GetDocument();

	for (int color = 0; color < 3; color++) {
		float result = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				result+=     (    (float)(*(pDoc->GetOriginalPixel(x + i, y + j) +color))    )*    filter[i+1][j+1];
				
			}
		}
		if (result > 255)
			result = 255;
		if (result < 0)
			result = 0;
		buffer[row][col][color] = result;
	}
}
