//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();

	int getStartRow()const;

	int getEndRow()const;

	int getStartCol()const;

	int getEndCol()const;

	int getDrawHeight()const;

	void autoPaint();

	
	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	GLvoid* m_pBackupStart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;
			
	Point	m_pStartingPoint;

};

#endif