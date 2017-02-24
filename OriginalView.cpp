//
// originalview.cpp
//
// The code maintaining the original view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "originalview.h"
#include<iostream>
#include <FL/fl_ask.h>

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

OriginalView::OriginalView(int			x, 
						   int			y, 
						   int			w, 
						   int			h, 
						   const char*	l)
							: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	viewType = ORIGIN_IMAGE;
}

void OriginalView::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucBitmap ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();
		
		int drawWidth, drawHeight;
		GLvoid* originBitstart;
		GLvoid* edgeBitstart;
		GLvoid* anotherBitstart;
		

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
		drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );

		int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + drawHeight);
		if ( startrow < 0 ) 
			startrow = 0;


		originBitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);
		edgeBitstart = m_pDoc->m_ucEdgeBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);
		anotherBitstart = m_pDoc->m_ucAnotherBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);
		glRasterPos2i(0, m_nWindowHeight - drawHeight);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth);
		glDrawBuffer(GL_BACK);
		switch (viewType) {
		case ORIGIN_IMAGE:
			// just copy image to GLwindow conceptually
			glDrawPixels(drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, originBitstart);
			break;
		case EDGE_IMAGE:
			glDrawPixels(drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, edgeBitstart);
			break;
		case ANOTHER_IMAGE:
			glDrawPixels(drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, anotherBitstart);
			break;
		default:
			fl_alert("Unknown error");
			return;
		}
		if(cursor.x<= drawWidth && cursor.y<= drawHeight&&cursor.x>=0&&cursor.y>=0)
			drawCursor();
	}
			
	glFlush();
}

void OriginalView::refresh()
{
	redraw();
}

void OriginalView::resizeWindow(int	width, 
								int	height)
{
	resize(x(), y(), width, height);
}

void OriginalView::setCursor(const Point &p) {
	cursor = p;
	redraw();
}

void OriginalView::drawCursor() {
	
	glPointSize(5);
	
	glBegin(GL_POINTS);
	glColor3ub(255, 0, 0);
	if (m_pDoc->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_UPSIDE_DOWN])
	{
		glVertex2d(m_nWindowWidth - cursor.x, cursor.y);
	}
	else if (m_pDoc->m_pCurrentBrush == ImpBrush::c_pBrushes[BRUSH_MIRROR])
	{
		glVertex2d(m_nWindowWidth - cursor.x, m_nWindowHeight - cursor.y);
	}
	else
	{
		glVertex2d(cursor.x, m_nWindowHeight - cursor.y);
	}
	glEnd();
}

void OriginalView::setViewType(int type) {
	viewType = type;
}

int OriginalView::getViewType() {
	return viewType;
}