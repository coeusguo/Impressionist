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

	filter[0] = 0; filter[1] = -1; filter[2] = 0;

	filter[3] =-1; filter[4] = 5; filter[5] = -1;
	
	filter[6] = 0; filter[7] = -1; filter[8] = 0;
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
	float* buffer = new float[9 * 9 * 3];
	memset(buffer, 0, 9 * 9 * 3);

	
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

	for (int Y = -4; Y < 5; Y++) {
		for (int X = -4; X < 5; X++) {
			applyFilter(x+X,y+Y,buffer,((X+4)+(Y+4)*9)*3);
		}
	}
	
	

	glPointSize(1);
	glBegin(GL_POINTS);

	for (int i = 0; i < 9 * 9; i++) {
		
			glColor3ub((GLubyte)buffer[3*i],(GLubyte) buffer[3*i+1], (GLubyte)buffer[3*i+2]);
			int dx = i % 9;
			int dy = i / 9;
			glVertex2d(x + dx - 4, y + dy - 4);
		
	}

	glEnd();
	delete[]buffer;
}

void SharpenBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* SharpenBrush::BrushName(void) {
	return ImpBrush::BrushName();
}

void SharpenBrush::applyFilter(int x,int y,float*buffer,int index) {
	ImpressionistDoc* pDoc = GetDocument();

	for (int color = 0; color < 3; color++) {
		float result = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				result+=     (    (float)(*(pDoc->GetOriginalPixel(x + i, y + j) +color))    )*    filter[(i+1)*3+j+1];
				
			}
		}
		if (result > 255)
			result = 255;
		if (result < 0)
			result = 0;
		buffer[index + color] = result;
	}
}
