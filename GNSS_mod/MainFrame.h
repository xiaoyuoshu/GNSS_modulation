#include <wx/wx.h>
#include <wx/string.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/combobox.h>
#include <wx/statline.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>

#include <wx/frame.h>



#define TIME_DOMAIN 1
#define FREQUENCY_DOMAIN 2
#define AUTOCORRELATION 3
#define TRACKING_ERROR 4
#define TRACKING_ERROR_CN0 6
#define MULTIPATH_ERROR 5
/*
*
* 编写模型
*
*/

class MainFrame : public wxFrame
{
public:
	//构造函数
	MainFrame(const wxString & title, int wid, int hei);
	//集中绑定事件
	void EVENT_CONNECT();
	//初始窗口大小参数
	int width;
	int height;
	//事件函数
	//信号一fs输入事件
	void signal_1_in_fs_input_e(wxCommandEvent& event);
	//信号一fc输入事件
	void signal_1_in_fc_input_e(wxCommandEvent& event);
	//信号一相关积分时间输入事件
	void signal_1_in_tco_input_e(wxCommandEvent& event);
	//信号一接收机带宽输入事件
	void signal_1_in_beta_input_e(wxCommandEvent& event);
	//信号一发射机带宽输入事件
	void signal_1_in_betat_input_e(wxCommandEvent& event);
	//信号一超前滞后本地码间隔输入事件
	void signal_1_in_d_input_e(wxCommandEvent& event);
	//信号一信号码元输入事件
	void signal_1_in_signal_input_e(wxCommandEvent& event);

	//信号二fs输入事件
	void signal_2_in_fs_input_e(wxCommandEvent& event);
	//信号二fc输入事件
	void signal_2_in_fc_input_e(wxCommandEvent& event);
	//信号二相关积分时间输入事件
	void signal_2_in_tco_input_e(wxCommandEvent& event);
	//信号二接收机带宽输入事件
	void signal_2_in_beta_input_e(wxCommandEvent& event);
	//信号二发射机带宽输入事件
	void signal_2_in_betat_input_e(wxCommandEvent& event);
	//信号二超前滞后本地码间隔输入事件
	void signal_2_in_d_input_e(wxCommandEvent& event);
	//信号二信号码元输入事件
	void signal_2_in_signal_input_e(wxCommandEvent& event);
	
	//信号一带限剩余功率计算事件
	void signal_1_calculate_lamda_e(wxCommandEvent& event);
	//信号一带限后均方根带宽计算事件
	void signal_1_calculate_brms_e(wxCommandEvent& event);
	//信号一频谱隔离系数计算事件
	void signal_1_calculate_kls_e(wxCommandEvent& event);
	//信号一带限后等效矩形带宽计算事件
	void signal_1_calculate_brect_e(wxCommandEvent& event);

	//信号二带限剩余功率计算事件
	void signal_2_calculate_lamda_e(wxCommandEvent& event);
	//信号二带限后均方根带宽计算事件
	void signal_2_calculate_brms_e(wxCommandEvent& event);
	//信号二频谱隔离系数计算事件
	void signal_2_calculate_kls_e(wxCommandEvent& event);
	//信号二带限后等效矩形带宽计算事件
	void signal_2_calculate_brect_e(wxCommandEvent& event);

	//时域波形绘制事件
	void imageType1_e(wxCommandEvent& event);
	//频域波形绘制事件
	void imageType41_e(wxCommandEvent& event);
	//归一化自相关函数绘制事件
	void imageType2_e(wxCommandEvent& event);
	//NELP方差图形绘制事件
	void imageType3_e(wxCommandEvent& event);
	//多径误差图形绘制事件
	void imageType4_e(wxCommandEvent& event);
	//图形保存事件
	void imageSave_e(wxCommandEvent& event);
	//生成数据表格事件
	void initDataset_e(wxCommandEvent& event);
	//画图更新事件
	void Paint(wxPaintEvent& event);

	//绘图函数
	//绘制时域波形图
	void draw_time_domain(wxDC* dc);
	//绘制频域波形图
	void draw_frequency_domain(wxDC* dc);
	//绘制自相关函数图形
	void draw_autocorrelation(wxDC* dc);
	//绘制码跟踪误差-间隔时间图形
	void draw_tracking_error_delta(wxDC* dc);
	//绘制码跟踪误差-载噪比图形
	void draw_tracking_error_CN0(wxDC* dc);
	//绘制多径误差图形
	void draw_multipath_error(wxDC* dc);

	//保存图片函数
	void SaveImage();

	 //变量定义
	wxPanel* panelLeft;//左边面板
	wxPanel* panelLeft_child_1;//信号一面板
	wxStaticText* signal_1_title;//信号一标题
	wxComboBox* signal_1_choice;//信号一选择类型
	wxPanel* signal_1_mainPanel;//信号一主面板
	wxPanel* signal_1_inPanel;//信号一输入面板
	wxStaticText* signal_1_in_title;
	wxStaticText* nulltext1;
	wxStaticText* isUseSignal1_text;
	wxCheckBox* isUseSignal1;//信号二是否启用选择口
	wxStaticText* signal_1_in_fs;
	wxTextCtrl* signal_1_in_fs_input;//信号一fs输入框
	wxStaticText* signal_1_in_fc;
	wxTextCtrl* signal_1_in_fc_input;//信号一fc输入框
	wxStaticText* signal_1_in_tco;
	wxTextCtrl* signal_1_in_tco_input;//信号一tco输入框
	wxStaticText* signal_1_in_beta;
	wxTextCtrl* signal_1_in_beta_input;//信号一beta输入框
	wxStaticText* signal_1_in_d;
	wxTextCtrl* signal_1_in_d_input;//信号一时延输入框
	wxStaticText* signal_1_in_signal;
	wxTextCtrl* signal_1_in_signal_input;//信号一 信号输入框
	wxStaticText* signal_1_in_betat;
	wxTextCtrl* signal_1_in_betat_input;//信号一 beta t输入框
	wxPanel* signal_1_outPanel;//信号一输出面板
	wxStaticText* signal_1_out_title;
	wxStaticText* nulltext4;
	wxStaticText* nulltext5;
	wxStaticText* signal_1_out_lamda;
	wxTextCtrl* signal_1_out_lamda_output;//信号一输出λ
	wxButton* signal_1_calculate_lamda;//信号一λ计算按钮
	wxStaticText* signal_1_out_brms;
	wxTextCtrl* signal_1_out_brms_output;//信号一输出brms
	wxButton* signal_1_calculate_brms;//信号一brms输出按钮
	wxStaticText* signal_1_out_kls;
	wxTextCtrl* signal_1_out_kls_output;//信号一输出kls
	wxButton* signal_1_calculate_kls;//信号一kls输出按钮
	wxStaticText* signal_1_out_brect;
	wxTextCtrl* signal_1_out_brect_output;//信号一输出brect
	wxButton* signal_1_calculate_brect;//信号一brect输出按钮
	wxPanel* panelLeft_child_2;//信号二面板
	wxStaticText* signal_2_title;
	wxComboBox* signal_2_choice;//信号二选择框
	wxPanel* signal_2_mainPanel;
	wxPanel* signal_2_inPanel;
	wxStaticText* signal_2_in_title;
	wxStaticText* nulltext50;
	wxStaticText* isUseSignal2_text;
	wxCheckBox* isUseSignal2;//信号二是否启用选择口
	wxStaticText* signal_2_in_fs;
	wxTextCtrl* signal_2_in_fs_input;//信号二输入fs
	wxStaticText* signal_2_in_fc;
	wxTextCtrl* signal_2_in_fc_input;//信号二输入fc
	wxStaticText* signal_2_in_tco;
	wxTextCtrl* signal_2_in_tco_input;//信号二输入tco
	wxStaticText* signal_2_in_beta;
	wxTextCtrl* signal_2_in_beta_input;//信号二输入beta
	wxStaticText* signal_2_in_d;
	wxTextCtrl* signal_2_in_d_input;//信号二输入d
	wxStaticText* signal_2_in_signal;
	wxTextCtrl* signal_2_in_signal_input;//信号二输入信号
	wxStaticText* signal_2_in_betat;
	wxTextCtrl* signal_2_in_betat_input;//信号二 beta t输入框
	wxPanel* signal_2_outPanel;
	wxStaticText* signal_2_out_title;
	wxStaticText* nulltext8;
	wxStaticText* nulltext9;
	wxStaticText* signal_2_out_lamda;
	wxTextCtrl* signal_2_out_lamda_output;//信号二输出λ
	wxButton* signal_2_calculate_lamda;//信号二λ输出按钮
	wxStaticText* signal_2_out_brms;
	wxTextCtrl* signal_2_out_brms_output;//信号二输出brms
	wxButton* signal_2_calculate_brms;//信号二brms输出按钮
	wxStaticText* signal_2_out_kls;
	wxTextCtrl* signal_2_out_kls_output;//信号二输出kls
	wxButton* signal_2_calculate_kls;//信号二kls输出按钮
	wxStaticText* signal_2_out_brect;
	wxTextCtrl* signal_2_out_brect_output;//信号二输出brect
	wxButton* signal_2_calculate_brect;//信号二brect输出按钮
	wxPanel* panelRIGHT;
	wxStaticText* rightTitle;
	wxPanel* right_mianPanel;
	wxButton* imageType1;//时域波形绘制按钮
	wxButton* imageType41;//频域波形绘制按钮
	wxButton* imageType2;//自相关函数波形绘制按钮
	wxButton* imageType3;//码跟踪误差图形绘制按钮
	wxButton* imageType4;//多径误差绘制按钮
	wxButton* imageSave;//保存图形按钮
	wxButton* initDataset;//生成表格按钮
	wxPanel* imagePanel;

	//辅助参数定义，用于判断画什么图
	int ImageType = TIME_DOMAIN;
};