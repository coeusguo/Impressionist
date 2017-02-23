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
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Float_Input.H>
#include <string>
#include <vector>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"
using namespace std;

//painterly style and stroke enum

enum {IMPRESSIONIST = 0,EXPRESSIONIST,COLOR_WASH,POINTILLIST,CUSTOMIZE};
enum {P_CURVE_BRUSH = 0,P_CIRCLE_BRUSH,P_CLIP_LINE_BRUSH,P_LINE_BRUSH};
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
	Fl_Slider*			m_AutoPaintSpacingSlider;
	Fl_Slider*			m_ThresholdSlider;

	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*			m_RandomAttrButton;
	Fl_Button*			m_AutoPaintButton;
	Fl_Button*			m_EdgeClipingButton;
	Fl_Button*			m_AnotherGradientButton;
	Fl_Button*			m_DoItButton;

// for filter kernel setting dialog
	Fl_Window*			m_FilterKernelSettingDialog;
	Fl_Int_Input*		m_NumRowsInput;
	Fl_Int_Input*		m_NumColsInput;
	Fl_Button*			m_ConfirmKernelSettingButton;
// for filter kernel dialog
	Fl_Window*			m_FilterKernelDialog;
	vector<Fl_Float_Input*>		m_filterKernelInputMatrix;
	Fl_Button*			m_ApplyFilterKernel;
	Fl_Button*			m_Normalize;

//painterly dialog
	Fl_Window*			m_painterlylDialog;
	//dropdown and button
	Fl_Choice*			m_painterlyStyle;
	Fl_Choice*			m_painterlyStroke;
	Fl_Button*			m_painterlyRun;
	//horizontal sliders
	Fl_Slider*			m_painterlyThreshold;
	Fl_Slider*			m_painterlyCurvature;
	Fl_Slider*			m_painterlyBlur;
	Fl_Slider*			m_painterlyGridSize;
	Fl_Slider*			m_painterlyMinStrokeL;
	Fl_Slider*			m_painterlyMaxStrokeL;
	Fl_Slider*			m_painterlyAlpha;
	Fl_Slider*			m_painterlyLayers;
	Fl_Slider*			m_painterlyR0Level;
	//vertical sliders
	Fl_Slider*			m_painterlyJr;
	Fl_Slider*			m_painterlyJg;
	Fl_Slider*			m_painterlyJb;
	Fl_Slider*			m_painterlyJh;
	Fl_Slider*			m_painterlyJs;
	Fl_Slider*			m_painterlyJv;

	//painterly variables
	int		m_nPainterlyCurrentStyle;
	int		m_nPainterlyCurrentStroke;
	int		m_nPainterlyThreshold;
	float   m_nPainterlyCurvature;
	float   m_nPainterlyBlur;
	float   m_nPainterlyGirdSize;
	int		m_nPainterlyMinStrokeL;
	int		m_nPainterlyMaxStrokeL;
	float   m_nPainterlyAlpha;
	int		m_nPainterlyLayers;
	int		m_nPainterlyR0Level;
	float	m_nPainterlyJr;
	float	m_nPainterlyJg;
	float	m_nPainterlyJb;
	float	m_nPainterlyJh;
	float	m_nPainterlyJs;
	float	m_nPainterlyJv;
	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	int 				getSpacing();
	bool				getRandomAttr();

	// Interface to get attribute

	int					getSize();
	int					getLineWidth();
	int					getLineAngle();
	double				getAlpha();
	void				setSize(int size);
	void				setLineAngle(int angle);
	void				setLineWidth(int width);
	void				passCursorPoint(const Point& p);
	bool				getEnableAutoDraw();
	void				setEnableAutoDraw(bool value);
	bool				getEnableNormalize();
	int					getKernelWidth();
	int					getKernelHeight();
	int					getThreshold();
	bool				getEnableEdgeCliping();
	bool				getAnotherGradient();

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	float	m_nAlpha;
	int		m_nSpacing;
	bool	m_nRandomAttr;
	bool	m_nEnableAutoDraw;
	bool	m_nEnableNormalize;
	int		m_nKernelWidth;
	int		m_nKernelHeight;
	int		m_nThreshold;
	bool	m_nEnableEdgeClipping;
	bool	m_nAnotherGradient;
	int		m_nBrushDirectionTypeCatche;

	

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		brushDirectionControlType[3];
	static Fl_Menu_Item		painterlyStyleType[5];
	static Fl_Menu_Item		painterlyStrokeType[4];


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
	static void cb_filter_kernel_setting(Fl_Menu_* o, void* v);
	static void cb_switch_view_type(Fl_Menu_* o, void* v);
	static void cb_load_another_image(Fl_Menu_* o, void* v);
	static void cb_load_edge_image(Fl_Menu_* o, void* v);
	static void cb_painterly(Fl_Menu_* o, void* v);

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
	static void cb_AutoPaintSpacingSlides(Fl_Widget* o, void* v);
	static void cb_Rand_Attr_button(Fl_Widget* o, void* v);
	static void cb_Auto_Paint_button(Fl_Widget* o, void* v);
	static void cb_confirm_kernel_button(Fl_Widget* o, void* v);
	static void cb_ApplyFilterKernel(Fl_Widget* o, void* v);
	static void cb_normalize_toggle_button(Fl_Widget* o, void* v);
	static void cb_ThresholdSlides(Fl_Widget* o, void* v);
	static void cb_Generating_Edge_Image_button(Fl_Widget* o, void* v);
	static void cb_toggle_cliping_button(Fl_Widget* o, void* v);
	static void cb_another_gradient_button(Fl_Widget* o, void* v);
	//painterly
	static void cb_painterly_Type(Fl_Widget* o, void* v);
	static void cb_painterlyStrokeType(Fl_Widget* o, void* v);
	static void cb_painterly_run_button(Fl_Widget* o, void* v);
	static void cb_painterlyThresholdSlides(Fl_Widget* o, void* v);
	static void cb_paintlyCurvatureSlides(Fl_Widget* o, void* v);
	static void cb_painterlyBlurSlides(Fl_Widget* o, void* v);
	static void cb_painterlyGridSizeSlides(Fl_Widget* o, void* v);
	static void cb_painterlyMinStrokeSlides(Fl_Widget* o, void* v);
	static void cb_painterlyMaxStrokeSlides(Fl_Widget* o, void* v);
	static void cb_painterlyAlphaSlides(Fl_Widget* o, void* v);
	static void cb_painterlyLayerSlides(Fl_Widget* o, void* v);
	static void cb_painterlyR0LevelSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJrSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJgSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJbSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJhSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJsSlides(Fl_Widget* o, void* v);
	static void cb_painterlyJvSlides(Fl_Widget* o, void* v);
};

#endif

/*swap original view and paint view
m_paintView->position();
m_paintView->x();
m_paintView->y();
*/