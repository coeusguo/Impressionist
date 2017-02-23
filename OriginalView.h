//
// originalview.h
//
// The header file for original view of the input images
//

#ifndef ORIGINALVIEW_H
#define ORIGINALVIEW_H

#include <FL/Fl.H>

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>

#include "ImpBrush.h"

enum { ORIGIN_IMAGE = 0, ANOTHER_IMAGE, EDGE_IMAGE };
class ImpressionistDoc;

class OriginalView : public Fl_Gl_Window
{
public:
	OriginalView(int x, int y, int w, int h, const char *l);
	
	void draw();
	void refresh();
	void setCursor(const Point& p);
	void drawCursor();
	void resizeWindow(int width, int height);
	void setViewType(int type);
	int getViewType();
	ImpressionistDoc*	m_pDoc;

private:
	int	m_nWindowWidth, 
		m_nWindowHeight;
	
	int viewType;
	//store the original height and width of the loaded picture
	int iniWidth;
	int iniHeight;

	Point cursor;


};

#endif