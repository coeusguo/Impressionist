//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	this->mode(FL_ALPHA);
}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA
	//cout << (int)valid();
	if(!valid())
	{
			
		//glClearColor(0.7f, 0.7f, 0.7f, 0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		//glClear( GL_COLOR_BUFFER_BIT );

		//glDisable(GL_BLEND);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	//step1: clear canvas
	glClearColor(0.7f, 0.7f, 0.7f, 0); 
	glClear(GL_COLOR_BUFFER_BIT);


	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	//start memory location of m_ucPainting
	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		4 * ((m_pDoc->m_nPaintWidth * (startrow)) + scrollpos.x);
	m_pBackupStart = m_pDoc->m_ucBackup + 
		4 * ((m_pDoc->m_nPaintWidth * (startrow)) + scrollpos.x);
	

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;


	/*
	when first open the app
	other funtion call redraw such as clear canvas,refresh() etc
	*/

	//step2:load the painting to the canvas
	if ( m_pDoc->m_ucPainting)
		RestoreContent();

	
	/*
	GLvoid* m_pOriginBitstart = m_pDoc->m_ucBitmap +
		3 * ((m_pDoc->m_nPaintWidth * (startrow)) + scrollpos.x);
	glRasterPos2i(0, m_nWindowHeight - drawHeight);
	glRasterPos2i(0, m_nWindowHeight - m_nDrawHeight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
	glDrawPixels(m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pOriginBitstart);

	*/
	//step3: start drawing new stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );

			//SaveCurrentContent();
			//RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			m_pStartingPoint = target;
			break;
		case RIGHT_MOUSE_DRAG:
			RestoreContent();

			glLineWidth(2);
						// Draw a red line
			// Draw a red line
			glBegin(GL_LINES);
			glColor3ub(255, 0, 0);
			glVertex2d(m_pStartingPoint.x, m_pStartingPoint.y);
			glVertex2d(target.x, target.y);
			glEnd();
			break;
		case RIGHT_MOUSE_UP:
			RestoreContent();

			m_pDoc->setLineAngle(((int)(((atan2((double)target.y - m_pStartingPoint.y, (double)target.x - m_pStartingPoint.x) * 180) / M_PI) + 360)) % 360);
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	if (m_pDoc->m_pUI->getEnableAutoDraw()) {
		autoPaint();
		
		m_pDoc->m_pUI->setEnableAutoDraw(false);
	}
	//cout <<(int) m_pDoc->m_pUI->m_nPainterlyRun << endl;
	if (m_pDoc->m_pUI->m_nPainterlyRun) {
		//cout << "painterly start" << endl;
		painterly(m_pDoc->m_pUI->m_nPaintrelyIsInitialized);
		m_pDoc->m_pUI->m_nPaintrelyIsInitialized = true;
	}

	glFlush();


	//step4: save the content
	if(eventToDo != RIGHT_MOUSE_DOWN && eventToDo != RIGHT_MOUSE_DRAG)
		SaveCurrentContent();

	//save to backup
	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		m_pBackupStart);
	/*
	unsigned char* temp = new unsigned char[m_pDoc->m_nWidth * m_pDoc->m_nHeight * 4];
	memcpy(temp, m_pDoc->m_ucPainting, m_pDoc->m_nWidth * m_pDoc->m_nHeight * 4);
	*/
	unsigned char* data = m_pDoc->m_ucBackup;
	if (m_pDoc->m_pUI->m_nShowDimImage) {
	//if(true){
		int alpha = (int)(255 * (1 - m_pDoc->m_pUI->m_nDimAlpha));
		
		//store (1-alpha) value of dimmed image to undrawed pixel alpha channel
		for (int i = 0; i < m_pDoc->m_nWidth * m_pDoc->m_nHeight; i++)
		{
			if ((int)data[i * 4 + 3] == 0)
				data[i * 4 + 3] = alpha;
		}
		glDrawBuffer(GL_BACK);
		glRasterPos2i(0, m_nWindowHeight - drawHeight);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth);
		glDrawPixels(drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawPixels(drawWidth, drawHeight, GL_RGBA, GL_UNSIGNED_BYTE, m_pBackupStart);
		
	}
	
}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
		//cout << "event = enter" << endl;
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		m_pDoc->m_pUI->passCursorPoint(coord);
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		//if(coord.x<= m_nEndCol||coord.y>m_nStartRow)
		m_pDoc->m_pUI->passCursorPoint(coord);
		break;

	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);
	//glReadBuffer(GL_FRONT_AND_BACK);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGBA, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );

	
	if (m_pDoc->m_nWidth > 0 && m_pDoc->m_nHeight > 0)
		for (int i = 0; i < m_pDoc->m_nWidth * m_pDoc->m_nHeight; ++i){
			//if((int)m_pDoc->m_ucPainting[i * 4 + 3])
				//cout << (int)m_pDoc->m_ucPainting[i * 4 + 3];
			//((GLubyte*)m_pDoc->m_ucPainting)[i * 4 + 3] = 255;
		}

	/*
	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart1);
		*/
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );
	glDisable(GL_BLEND);
	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGBA, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

	/*test
	glDrawPixels(m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart1);
		*/

	//glDrawBuffer(GL_FRONT);
}

int PaintView::getStartRow()const {
	return m_nStartRow;
}

int PaintView::getStartCol()const {
	return m_nStartCol;
}

int PaintView::getEndRow()const {
	return m_nEndRow;
}

int PaintView::getEndCol()const {
	return m_nEndCol;
}

int PaintView::getDrawHeight()const {
	return m_nDrawHeight;
}

void PaintView::autoPaint() {
	ImpressionistUI* pUI = m_pDoc->m_pUI;
	m_pDoc->clearCanvas();
	vector<int> index;

	
	int spacing = pUI->getSpacing();
	
	int height = m_pDoc->m_nHeight;
	int width = m_pDoc->m_nWidth;
	
	ImpBrush* currentBrush = m_pDoc->m_pCurrentBrush;

	//randAttr part
	bool randAttr = pUI->getRandomAttr();
	int size = pUI->getSize();
	int lineWidth = pUI->getLineAngle();
	int lineAngle = pUI->getLineAngle();
	srand(time(0));

	//check whether alpha map is loaded
	if ((m_pDoc->currentType == BRUSH_ALPHA_MAP) && (m_pDoc->m_ucAlphamap == NULL)) {
		fl_alert("Pleas load an alpha map first!");
		return;
	}


	//number of spacing per row/column
	int xTimes = width / spacing;
	int yTimes = height / spacing;

	for (int i = 0; i < xTimes*yTimes; i++) 
		index.push_back(i);
	random_shuffle(index.begin(), index.end());


	int offset = m_nWindowHeight - m_nDrawHeight;
	int startX = spacing / 2;
	int startY = spacing / 2 + offset;
	//int Continue;
	//cin >> Continue;
	//Point startPoint = Point(startX, startY);
	
	for (int i = 0; i < index.size(); i++) {
		int position = index.at(i);
		int x = startX + (position % xTimes)*spacing;
		int y = startY + (position / xTimes)*spacing;
		Point p = Point(x, y);
		if (randAttr) {
			pUI->setSize(size + rand() % 10 - 5);
			pUI->setLineAngle(lineAngle + rand() % 90 - 45);
			pUI->setLineWidth(lineWidth + rand() % 10 - 5);
		}
		currentBrush->BrushBegin(p , p);
		currentBrush->BrushEnd(p, p);
	}

	//set back to origin
	pUI->setSize(size);
	pUI->setLineAngle(lineAngle);
	pUI->setLineWidth(lineWidth);
}

void PaintView::painterly(bool isInitialized) {
	//cout << "hey" << endl;
	ImpressionistUI* pUI = m_pDoc->m_pUI;
	ImpressionistDoc* pDoc = pUI->getDocument();
	int width = pDoc->m_nWidth;
	int height = pDoc->m_nHeight;


	if (!isInitialized) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 255, 255);
		glVertex2i(0,0);
		glVertex2i(width, 0);
		glVertex2i(width, height);
		glVertex2i(0, height);
		glEnd();
	}
	
	int brushType = pUI->m_nPainterlyCurrentStroke;
	int threshold = pUI->m_nPainterlyThreshold;
	float alpha = pUI->m_nPainterlyAlpha;
	int size = pUI->m_nPainterlyBrushSize;
	int gridSize = pUI->m_nPainterlyGirdSize * size;
	
	if (gridSize < 1)
		gridSize = 1;
	ImpBrush* currentBrush = ImpBrush::c_pBrushes[brushType];
	
	/*
	float jr = pUI->m_nPainterlyJr;
	float jg = pUI->m_nPainterlyJg;
	float jb = pUI->m_nPainterlyJb;

	*/
	float blurFactor = pUI->m_nPainterlyBlur;
	bool isFatorChanged = pUI->m_nPainterlyBlurChanged;
	
	if(pUI->m_nPainterlyBlurChanged||pDoc->m_ucBitmapBlur == NULL)
		pDoc->applyPainterlyGaussianFilter(blurFactor);


	unsigned char* canvas = pDoc->m_ucPainting;
	unsigned char* source = pDoc->m_ucBitmapBlur;


	float* differenceMap = new float[width*height];

	for (int i = 0; i < width*height; i++) 
		differenceMap[i] = sqrt(pow(source[i * 3] - canvas[i * 4], 2) + pow(source[i * 3 + 1] - canvas[i * 4 + 1], 2) + pow(source[i * 3 + 2] - canvas[i * 4 + 2], 2));

	
	vector<int*> points;
	for (int Y = gridSize / 2; Y <= height - gridSize / 2; Y += gridSize) {
		for (int X = gridSize / 2; X <= width - gridSize / 2; X += gridSize) {

			int areaError = 0;
			for (int y = Y - gridSize / 2; y <= Y + gridSize / 2; y++) {
				for (int x = X - gridSize / 2; x <= X + gridSize / 2; x++)
					areaError += differenceMap[y * width + x];
			}

			areaError /= pow(2 * (gridSize / 2) + 1, 2);

			if (areaError > threshold) {
				int maxDiff = -1;
				int* maxPoint = new int[2];

				for (int y = Y - gridSize / 2; y <= Y + gridSize / 2; y++) {
					for (int x = X - gridSize / 2; x <= X + gridSize / 2; x++) {
						if (differenceMap[y * width + x] > maxDiff) {
							maxDiff = differenceMap[y * width + x];
							maxPoint[0] = x;
							maxPoint[1] = y;


						}

					}
				}

				points.push_back(maxPoint);

			}
		}
	}
		int initialBrushSize = pDoc->getSize();
		//cout << points.size() << endl;
		random_shuffle(points.begin(),points.end());
		
		for (int i = 0; i < points.size(); i++) {
			int* point = points.at(i);

			Point p = Point(point[0], point[1]);
			pUI->setSize(size);
			//cout << currentBrush->BrushName();
			
			currentBrush->BrushBegin(p, p);
			currentBrush->BrushEnd(p, p);
			
		}

		for (int* n : points)
			delete[]n;
		points.clear();
		pUI->setSize(initialBrushSize);
		
		//cout << "finish" << endl;
	
}

