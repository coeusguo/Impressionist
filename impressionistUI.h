//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
	
	PaintView*			m_paintView;
	OriginalView*		m_origView;

//for color dialog
	Fl_Window*			m_colorDialog;
	Fl_Slider*			m_RedColorSlider;
	Fl_Slider*			m_GreenColorSlider;
	Fl_Slider*			m_BlueColorSlider;
	Fl_Button*          m_ApplyScalingButton;
	float				m_nRedScale;
	float				m_nGreenScale;
	float				m_nBlueScale;
// for dimmed view dialog
	Fl_Window*			m_dimDialog;
	Fl_Slider*			m_dimAlphaSlider;
	Fl_Button*			m_dimButton;
	float				m_nDimAlpha;
	bool				m_nShowDimImage;
// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaSlider;

	Fl_Button*          m_ClearCanvasButton;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getLineWidth();
	int					getLineAngle();
	double				getAlpha();
	void				setSize(int size);
	void				passCursorPoint(const Point& p);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	float		m_nAlpha;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		brushDirectionControlType[3];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void cb_SwapWindows(Fl_Menu_* o, void* v);
	static void cb_colors(Fl_Menu_* o, void* v);
	static void cb_undo(Fl_Menu_* o, void* v);
	static void cb_dissolve_image(Fl_Menu_* o,void* v);
	static void cb_mural_image(Fl_Menu_* o, void* v);
	static void cb_load_alpha_map(Fl_Menu_* o, void* v);
	static void cb_ShowDimDialog(Fl_Menu_* o, void* v);

	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void cb_brushDirectionType(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_LineWidthSlides(Fl_Widget* o, void* v);
	static void	cb_LineAngleSlides(Fl_Widget* o, void* v);
	static void	cb_AlphaSlides(Fl_Widget* o, void* v);
	static void	cb_RedSlides(Fl_Widget* o, void* v);
	static void	cb_GreenSlides(Fl_Widget* o, void* v);
	static void	cb_BlueSlides(Fl_Widget* o, void* v);
	static void cb_ApplyColorScaling(Fl_Widget* o, void* v);
	static void cb_dimAlphaSlides(Fl_Widget* o, void* v);
	static void cb_dim_button(Fl_Widget* o, void* v);
	
};

#endif

/*swap original view and paint view
m_paintView->position();
m_paintView->x();
m_paintView->y();
*/