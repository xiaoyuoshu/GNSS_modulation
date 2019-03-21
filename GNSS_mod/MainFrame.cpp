#include "MyApp.h"
#include "MainFrame.h"
#include "Calculate.h"
/*
*
* 编写视图View
*
*/

MainFrame::MainFrame(const wxString & title, int wid, int hei)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(wid, hei))
{
	//获取并设定屏幕分辨率
	width = wid;
	height = hei;

	//鬼鬼，为什么没有html这样的缩进呢，辣鸡

	wxBoxSizer* outerBoxer;
	outerBoxer = new wxBoxSizer(wxHORIZONTAL);

	panelLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(350, -1), wxTAB_TRAVERSAL);
	panelLeft->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	panelLeft->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));

	wxBoxSizer* leftBoxer;
	leftBoxer = new wxBoxSizer(wxVERTICAL);

	panelLeft_child_1 = new wxPanel(panelLeft, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	panelLeft_child_1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	wxBoxSizer* topBoxer;
	topBoxer = new wxBoxSizer(wxVERTICAL);

	signal_1_title = new wxStaticText(panelLeft_child_1, wxID_ANY, wxT("信号1"), wxDefaultPosition, wxSize(-1, -1), 0);
	signal_1_title->Wrap(-1);
	signal_1_title->SetFont(wxFont(24, 70, 90, 92, false, wxEmptyString));
	signal_1_title->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	signal_1_title->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	topBoxer->Add(signal_1_title, 0, wxALIGN_CENTER | wxALL, 5);

	signal_1_choice = new wxComboBox(panelLeft_child_1, wxID_ANY, wxT("选择调制信号"), wxDefaultPosition, wxSize(200, -1), 0, NULL, 0);
	signal_1_choice->Append(wxT("BOC调制"));
	signal_1_choice->Append(wxT("BPSK调制"));
	signal_1_choice->SetFont(wxFont(12, 70, 90, 90, false, wxEmptyString));

	topBoxer->Add(signal_1_choice, 0, wxALL, 5);

	signal_1_mainPanel = new wxPanel(panelLeft_child_1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	signal_1_mainPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	wxBoxSizer* signal_1_mainBoxer;
	signal_1_mainBoxer = new wxBoxSizer(wxHORIZONTAL);

	signal_1_inPanel = new wxPanel(signal_1_mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* signal_1_in_fgSizer;
	signal_1_in_fgSizer = new wxFlexGridSizer(5, 4, 40, 0);
	signal_1_in_fgSizer->SetFlexibleDirection(wxHORIZONTAL);
	signal_1_in_fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_ALL);

	signal_1_in_title = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("输入参数"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_title->Wrap(-1);
	signal_1_in_title->SetFont(wxFont(12, 70, 90, 92, false, wxEmptyString));

	signal_1_in_fgSizer->Add(signal_1_in_title, 0, wxALL, 5);

	nulltext1 = new wxStaticText(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext1->Wrap(-1);
	signal_1_in_fgSizer->Add(nulltext1, 0, wxALL, 5);

	isUseSignal1_text = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("显示波形"), wxDefaultPosition, wxDefaultSize, 0);
	isUseSignal1_text->Wrap(-1);
	signal_1_in_fgSizer->Add(isUseSignal1_text, 0, wxALL, 5);

	isUseSignal1 = new wxCheckBox(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(isUseSignal1, 0, wxALIGN_CENTER | wxALL, 5);

	signal_1_in_fs = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("fs/1.023Mhz:"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fs->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_fs, 0, wxALL, 5);

	signal_1_in_fs_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_fs_input, 0, wxALL, 5);

	signal_1_in_fc = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("fc/1.023Mhz:"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fc->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_fc, 0, wxALL, 5);

	signal_1_in_fc_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_fc_input, 0, wxALL, 5);

	signal_1_in_beta = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("βr/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_beta->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_beta, 0, wxALL, 5);

	signal_1_in_beta_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_beta_input, 0, wxALL, 5);

	signal_1_in_betat = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("βt/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_betat->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_betat, 0, wxALL, 5);

	signal_1_in_betat_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_betat_input, 0, wxALL, 5);

	signal_1_in_tco = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("Tco/ms："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_tco->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_tco, 0, wxALL, 5);

	signal_1_in_tco_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_tco_input, 0, wxALL, 5);

	signal_1_in_d = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("△=δTc："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_d->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_d, 0, wxALL, 5);

	signal_1_in_d_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_d_input, 0, wxALL, 5);

	signal_1_in_signal = new wxStaticText(signal_1_inPanel, wxID_ANY, wxT("signal："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_signal->Wrap(-1);
	signal_1_in_fgSizer->Add(signal_1_in_signal, 0, wxALL, 5);

	signal_1_in_signal_input = new wxTextCtrl(signal_1_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_in_fgSizer->Add(signal_1_in_signal_input, 0, wxALL, 5);


	signal_1_inPanel->SetSizer(signal_1_in_fgSizer);
	signal_1_inPanel->Layout();
	signal_1_in_fgSizer->Fit(signal_1_inPanel);
	signal_1_mainBoxer->Add(signal_1_inPanel, 1, wxEXPAND | wxALL, 5);

	signal_1_outPanel = new wxPanel(signal_1_mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* signal_1_out_fgSizer;
	signal_1_out_fgSizer = new wxFlexGridSizer(5, 3, 30, 0);
	signal_1_out_fgSizer->SetFlexibleDirection(wxBOTH);
	signal_1_out_fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	signal_1_out_title = new wxStaticText(signal_1_outPanel, wxID_ANY, wxT("输出参数"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_title->Wrap(-1);
	signal_1_out_title->SetFont(wxFont(12, 70, 90, 92, false, wxEmptyString));

	signal_1_out_fgSizer->Add(signal_1_out_title, 0, wxALL, 5);

	nulltext4 = new wxStaticText(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext4->Wrap(-1);
	signal_1_out_fgSizer->Add(nulltext4, 0, wxALL, 5);

	nulltext5 = new wxStaticText(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext5->Wrap(-1);
	signal_1_out_fgSizer->Add(nulltext5, 0, wxALL, 5);

	signal_1_out_lamda = new wxStaticText(signal_1_outPanel, wxID_ANY, wxT("λ："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_lamda->Wrap(-1);
	signal_1_out_fgSizer->Add(signal_1_out_lamda, 0, wxALL, 5);

	signal_1_out_lamda_output = new wxTextCtrl(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_lamda_output->SetEditable(false);
	signal_1_out_fgSizer->Add(signal_1_out_lamda_output, 0, wxALL, 5);

	signal_1_calculate_lamda = new wxButton(signal_1_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_fgSizer->Add(signal_1_calculate_lamda, 0, wxALL, 5);

	signal_1_out_brms = new wxStaticText(signal_1_outPanel, wxID_ANY, wxT("βrms/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_brms->Wrap(-1);
	signal_1_out_fgSizer->Add(signal_1_out_brms, 0, wxALL, 5);

	signal_1_out_brms_output = new wxTextCtrl(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_brms_output->SetEditable(false);
	signal_1_out_fgSizer->Add(signal_1_out_brms_output, 0, wxALL, 5);

	signal_1_calculate_brms = new wxButton(signal_1_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_fgSizer->Add(signal_1_calculate_brms, 0, wxALL, 5);

	signal_1_out_brect = new wxStaticText(signal_1_outPanel, wxID_ANY, wxT("βrect/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_brect->Wrap(-1);
	signal_1_out_fgSizer->Add(signal_1_out_brect, 0, wxALL, 5);

	signal_1_out_brect_output = new wxTextCtrl(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_brect_output->SetEditable(false);
	signal_1_out_fgSizer->Add(signal_1_out_brect_output, 0, wxALL, 5);

	signal_1_calculate_brect = new wxButton(signal_1_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_fgSizer->Add(signal_1_calculate_brect, 0, wxALL, 5);

	signal_1_out_kls = new wxStaticText(signal_1_outPanel, wxID_ANY, wxT("Kls/(dB/Hz)："), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_kls->Wrap(-1);
	signal_1_out_fgSizer->Add(signal_1_out_kls, 0, wxALL, 5);

	signal_1_out_kls_output = new wxTextCtrl(signal_1_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_kls_output->SetEditable(false);
	signal_1_out_fgSizer->Add(signal_1_out_kls_output, 0, wxALL, 5);

	signal_1_calculate_kls = new wxButton(signal_1_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_1_out_fgSizer->Add(signal_1_calculate_kls, 0, wxALL, 5);


	signal_1_outPanel->SetSizer(signal_1_out_fgSizer);
	signal_1_outPanel->Layout();
	signal_1_out_fgSizer->Fit(signal_1_outPanel);
	signal_1_mainBoxer->Add(signal_1_outPanel, 1, wxEXPAND | wxALL, 5);


	signal_1_mainPanel->SetSizer(signal_1_mainBoxer);
	signal_1_mainPanel->Layout();
	signal_1_mainBoxer->Fit(signal_1_mainPanel);
	topBoxer->Add(signal_1_mainPanel, 1, wxEXPAND | wxALL, 5);


	panelLeft_child_1->SetSizer(topBoxer);
	panelLeft_child_1->Layout();
	topBoxer->Fit(panelLeft_child_1);
	leftBoxer->Add(panelLeft_child_1, 1, wxEXPAND | wxALL, 5);

	panelLeft_child_2 = new wxPanel(panelLeft, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	panelLeft_child_2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	wxBoxSizer* topBoxer2;
	topBoxer2 = new wxBoxSizer(wxVERTICAL);

	signal_2_title = new wxStaticText(panelLeft_child_2, wxID_ANY, wxT("信号2"), wxDefaultPosition, wxSize(-1, -1), 0);
	signal_2_title->Wrap(-1);
	signal_2_title->SetFont(wxFont(24, 70, 90, 92, false, wxEmptyString));
	signal_2_title->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	signal_2_title->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	topBoxer2->Add(signal_2_title, 0, wxALIGN_CENTER | wxALL, 5);

	signal_2_choice = new wxComboBox(panelLeft_child_2, wxID_ANY, wxT("选择调制信号"), wxDefaultPosition, wxSize(200, -1), 0, NULL, 0);
	signal_2_choice->Append(wxT("BOC调制"));
	signal_2_choice->Append(wxT("BPSK调制"));
	signal_2_choice->SetFont(wxFont(12, 70, 90, 90, false, wxEmptyString));

	topBoxer2->Add(signal_2_choice, 0, wxALL, 5);

	signal_2_mainPanel = new wxPanel(panelLeft_child_2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	signal_2_mainPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

	wxBoxSizer* signal_2_mainBoxer;
	signal_2_mainBoxer = new wxBoxSizer(wxHORIZONTAL);

	signal_2_inPanel = new wxPanel(signal_2_mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* signal_2_in_fgSizer;
	signal_2_in_fgSizer = new wxFlexGridSizer(5, 4, 40, 0);
	signal_2_in_fgSizer->SetFlexibleDirection(wxBOTH);
	signal_2_in_fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	signal_2_in_title = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("输入参数"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_title->Wrap(-1);
	signal_2_in_title->SetFont(wxFont(12, 70, 90, 92, false, wxEmptyString));

	signal_2_in_fgSizer->Add(signal_2_in_title, 0, wxALL, 5);

	nulltext50 = new wxStaticText(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext50->Wrap(-1);
	signal_2_in_fgSizer->Add(nulltext50, 0, wxALL, 5);

	isUseSignal2_text = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("显示波形"), wxDefaultPosition, wxDefaultSize, 0);
	isUseSignal2_text->Wrap(-1);
	signal_2_in_fgSizer->Add(isUseSignal2_text, 0, wxALL, 5);

	isUseSignal2 = new wxCheckBox(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(isUseSignal2, 0, wxALIGN_CENTER | wxALL, 5);

	signal_2_in_fs = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("fs/1.023Mhz:"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fs->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_fs, 0, wxALL, 5);

	signal_2_in_fs_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_fs_input, 0, wxALL, 5);

	signal_2_in_fc = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("fc/1.023Mhz:"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fc->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_fc, 0, wxALL, 5);

	signal_2_in_fc_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_fc_input, 0, wxALL, 5);

	signal_2_in_beta = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("βr/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_beta->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_beta, 0, wxALL, 5);

	signal_2_in_beta_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_beta_input, 0, wxALL, 5);

	signal_2_in_betat = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("βt/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_betat->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_betat, 0, wxALL, 5);

	signal_2_in_betat_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_betat_input, 0, wxALL, 5);

	signal_2_in_tco = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("Tco/ms："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_tco->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_tco, 0, wxALL, 5);

	signal_2_in_tco_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_tco_input, 0, wxALL, 5);

	signal_2_in_d = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("△=δTc："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_d->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_d, 0, wxALL, 5);

	signal_2_in_d_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_d_input, 0, wxALL, 5);

	signal_2_in_signal = new wxStaticText(signal_2_inPanel, wxID_ANY, wxT("signal："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_signal->Wrap(-1);
	signal_2_in_fgSizer->Add(signal_2_in_signal, 0, wxALL, 5);

	signal_2_in_signal_input = new wxTextCtrl(signal_2_inPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_in_fgSizer->Add(signal_2_in_signal_input, 0, wxALL, 5);


	signal_2_inPanel->SetSizer(signal_2_in_fgSizer);
	signal_2_inPanel->Layout();
	signal_2_in_fgSizer->Fit(signal_2_inPanel);
	signal_2_mainBoxer->Add(signal_2_inPanel, 1, wxEXPAND | wxALL, 5);

	signal_2_outPanel = new wxPanel(signal_2_mainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* signal_2_out_fgSizer;
	signal_2_out_fgSizer = new wxFlexGridSizer(5, 3, 30, 0);
	signal_2_out_fgSizer->SetFlexibleDirection(wxBOTH);
	signal_2_out_fgSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	signal_2_out_title = new wxStaticText(signal_2_outPanel, wxID_ANY, wxT("输出参数"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_title->Wrap(-1);
	signal_2_out_title->SetFont(wxFont(12, 70, 90, 92, false, wxEmptyString));

	signal_2_out_fgSizer->Add(signal_2_out_title, 0, wxALL, 5);

	nulltext8 = new wxStaticText(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext8->Wrap(-1);
	signal_2_out_fgSizer->Add(nulltext8, 0, wxALL, 5);

	nulltext9 = new wxStaticText(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	nulltext9->Wrap(-1);
	signal_2_out_fgSizer->Add(nulltext9, 0, wxALL, 5);

	signal_2_out_lamda = new wxStaticText(signal_2_outPanel, wxID_ANY, wxT("λ："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_lamda->Wrap(-1);
	signal_2_out_fgSizer->Add(signal_2_out_lamda, 0, wxALL, 5);

	signal_2_out_lamda_output = new wxTextCtrl(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_lamda_output->SetEditable(false);
	signal_2_out_fgSizer->Add(signal_2_out_lamda_output, 0, wxALL, 5);

	signal_2_calculate_lamda = new wxButton(signal_2_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_fgSizer->Add(signal_2_calculate_lamda, 0, wxALL, 5);

	signal_2_out_brms = new wxStaticText(signal_2_outPanel, wxID_ANY, wxT("βrms/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_brms->Wrap(-1);
	signal_2_out_fgSizer->Add(signal_2_out_brms, 0, wxALL, 5);

	signal_2_out_brms_output = new wxTextCtrl(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_brms_output->SetEditable(false);
	signal_2_out_fgSizer->Add(signal_2_out_brms_output, 0, wxALL, 5);

	signal_2_calculate_brms = new wxButton(signal_2_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_fgSizer->Add(signal_2_calculate_brms, 0, wxALL, 5);

	signal_2_out_brect = new wxStaticText(signal_2_outPanel, wxID_ANY, wxT("βrect/MHz："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_brect->Wrap(-1);
	signal_2_out_fgSizer->Add(signal_2_out_brect, 0, wxALL, 5);

	signal_2_out_brect_output = new wxTextCtrl(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_brect_output->SetEditable(false);
	signal_2_out_fgSizer->Add(signal_2_out_brect_output, 0, wxALL, 5);

	signal_2_calculate_brect = new wxButton(signal_2_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_fgSizer->Add(signal_2_calculate_brect, 0, wxALL, 5);

	signal_2_out_kls = new wxStaticText(signal_2_outPanel, wxID_ANY, wxT("Kls/(dB/Hz)："), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_kls->Wrap(-1);
	signal_2_out_fgSizer->Add(signal_2_out_kls, 0, wxALL, 5);

	signal_2_out_kls_output = new wxTextCtrl(signal_2_outPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_kls_output->SetEditable(false);
	signal_2_out_fgSizer->Add(signal_2_out_kls_output, 0, wxALL, 5);

	signal_2_calculate_kls = new wxButton(signal_2_outPanel, wxID_ANY, wxT("计算"), wxDefaultPosition, wxDefaultSize, 0);
	signal_2_out_fgSizer->Add(signal_2_calculate_kls, 0, wxALL, 5);


	signal_2_outPanel->SetSizer(signal_2_out_fgSizer);
	signal_2_outPanel->Layout();
	signal_2_out_fgSizer->Fit(signal_2_outPanel);
	signal_2_mainBoxer->Add(signal_2_outPanel, 1, wxEXPAND | wxALL, 5);


	signal_2_mainPanel->SetSizer(signal_2_mainBoxer);
	signal_2_mainPanel->Layout();
	signal_2_mainBoxer->Fit(signal_2_mainPanel);
	topBoxer2->Add(signal_2_mainPanel, 1, wxEXPAND | wxALL, 5);


	panelLeft_child_2->SetSizer(topBoxer2);
	panelLeft_child_2->Layout();
	topBoxer2->Fit(panelLeft_child_2);
	leftBoxer->Add(panelLeft_child_2, 1, wxEXPAND | wxALL, 5);


	panelLeft->SetSizer(leftBoxer);
	panelLeft->Layout();
	outerBoxer->Add(panelLeft, 1, wxEXPAND | wxALL, 5);

	panelRIGHT = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(450, -1), wxTAB_TRAVERSAL);
	panelRIGHT->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	wxBoxSizer* rightBoxer;
	rightBoxer = new wxBoxSizer(wxVERTICAL);

	rightTitle = new wxStaticText(panelRIGHT, wxID_ANY, wxT("波形图"), wxDefaultPosition, wxDefaultSize, 0);
	rightTitle->Wrap(-1);
	rightTitle->SetFont(wxFont(36, 70, 90, 92, false, wxEmptyString));
	rightTitle->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	rightTitle->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION));

	rightBoxer->Add(rightTitle, 0, wxALIGN_CENTER | wxALL, 5);

	right_mianPanel = new wxPanel(panelRIGHT, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxFlexGridSizer* imageBoxer;
	imageBoxer = new wxFlexGridSizer(2, 0, 0, 0);
	imageBoxer->SetFlexibleDirection(wxBOTH);
	imageBoxer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxGridSizer* buttonBoxer;
	buttonBoxer = new wxGridSizer(0, 7, 0, 0);

	imageType1 = new wxButton(right_mianPanel, wxID_ANY, wxT("时域波形"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageType1, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);

	imageType41 = new wxButton(right_mianPanel, wxID_ANY, wxT("频域波形"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageType41, 0, wxALL, 5);

	imageType2 = new wxButton(right_mianPanel, wxID_ANY, wxT("自相关函数"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageType2, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);

	imageType3 = new wxButton(right_mianPanel, wxID_ANY, wxT("码跟踪误差"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageType3, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);

	imageType4 = new wxButton(right_mianPanel, wxID_ANY, wxT("多径对精度影响"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageType4, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);

	imageSave = new wxButton(right_mianPanel, wxID_ANY, wxT("保存波形"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(imageSave, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_TOP | wxALL, 5);

	initDataset = new wxButton(right_mianPanel, wxID_ANY, wxT("生成表格"), wxDefaultPosition, wxDefaultSize, 0);
	buttonBoxer->Add(initDataset, 0, wxALL, 5);


	imageBoxer->Add(buttonBoxer, 1, wxEXPAND, 5);

	imagePanel = new wxPanel(right_mianPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, 900), wxTAB_TRAVERSAL);
	imagePanel->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	imagePanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVEBORDER));
	imageBoxer->Add(imagePanel, 1, wxEXPAND | wxALL, 5);


	right_mianPanel->SetSizer(imageBoxer);
	right_mianPanel->Layout();
	imageBoxer->Fit(right_mianPanel);
	rightBoxer->Add(right_mianPanel, 1, wxEXPAND | wxALL, 5);


	panelRIGHT->SetSizer(rightBoxer);
	panelRIGHT->Layout();
	outerBoxer->Add(panelRIGHT, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(outerBoxer);
	this->Layout();

	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");
	this->Centre(wxBOTH);


	//事件绑定
	EVENT_CONNECT();

}

