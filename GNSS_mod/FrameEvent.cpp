#include "MyApp.h"
#include "MainFrame.h"
#include "Calculate.h"
#include <regex>
#include "TableFrame.h"

using namespace std;

/*
*
* 编写控制器 
*
*/


void MainFrame::EVENT_CONNECT() {
	signal_1_in_fs_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_fs_input_e), NULL, this);
	signal_1_in_fc_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_fc_input_e), NULL, this);
	signal_1_in_tco_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_tco_input_e), NULL, this);
	signal_1_in_beta_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_beta_input_e), NULL, this);
	signal_1_in_betat_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_betat_input_e), NULL, this);
	signal_1_in_d_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_d_input_e), NULL, this);
	signal_1_in_signal_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_1_in_signal_input_e), NULL, this);
	//输入框2
	signal_2_in_fs_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_fs_input_e), NULL, this);
	signal_2_in_fc_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_fc_input_e), NULL, this);
	signal_2_in_tco_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_tco_input_e), NULL, this);
	signal_2_in_beta_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_beta_input_e), NULL, this);
	signal_1_in_betat_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_betat_input_e), NULL, this);
	signal_2_in_d_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_d_input_e), NULL, this);
	signal_2_in_signal_input->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::signal_2_in_signal_input_e), NULL, this);

	//按钮组1
	signal_1_calculate_lamda->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_1_calculate_lamda_e), NULL, this);
	signal_1_calculate_brms->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_1_calculate_brms_e), NULL, this);
	signal_1_calculate_kls->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_1_calculate_kls_e), NULL, this);
	signal_1_calculate_brect->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_1_calculate_brect_e), NULL, this);

	//按钮组2
	signal_2_calculate_lamda->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_2_calculate_lamda_e), NULL, this);
	signal_2_calculate_brms->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_2_calculate_brms_e), NULL, this);
	signal_2_calculate_kls->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_2_calculate_kls_e), NULL, this);
	signal_2_calculate_brect->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::signal_2_calculate_brect_e), NULL, this);

	//按钮组3
	imageType1->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageType1_e), NULL, this);
	imageType41->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageType41_e), NULL, this);
	imageType2->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageType2_e), NULL, this);
	imageType3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageType3_e), NULL, this);
	imageType4->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageType4_e), NULL, this);
	imageSave->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::imageSave_e), NULL, this);
	initDataset->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::initDataset_e), NULL, this);

	//tt
	imagePanel->Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::Paint), NULL, this);
}



//信号一输入fs
void MainFrame::signal_1_in_fs_input_e(wxCommandEvent& event) {
	SetStatusText("BOC调制的子载波频率，单位为MHz，此处输入的应为1.023MHz的倍数");
}
//信号一输入fc
void MainFrame::signal_1_in_fc_input_e(wxCommandEvent& event) {
	SetStatusText("BOC或BPSK调制的扩频码速率，单位为MHz，此处输入的应为1.023MHz的倍数");
}
//信号一输入tco
void MainFrame::signal_1_in_tco_input_e(wxCommandEvent& event) {
	SetStatusText("鉴相器相关积分时间，单位为ms，常见输入为5ms和20ms");
}
//信号一输入beta
void MainFrame::signal_1_in_beta_input_e(wxCommandEvent& event) {
	SetStatusText("接收机带宽，单位为MHz，常见输入为24MHz");
}
//信号一输入betat
void MainFrame::signal_1_in_betat_input_e(wxCommandEvent& event) {
	SetStatusText("发射机带宽，单位为MHz，常见输入为24MHz、30MHz");
}
//信号一输入d
void MainFrame::signal_1_in_d_input_e(wxCommandEvent& event) {
	SetStatusText("超前—滞后本地码间隔，单位为ns，适当的输入为，BPSK:50ns,BOC(5,2):80ns,BOC(8,4):50ns,BOC(10,5):40ns");
}
//信号一输入signal
void MainFrame::signal_1_in_signal_input_e(wxCommandEvent& event) {
	SetStatusText("调制信号1的输入信号，格式应为10101的二进制码组");
}

//信号二输入fs
void MainFrame::signal_2_in_fs_input_e(wxCommandEvent& event) {
	SetStatusText("BOC调制的子载波频率，单位为MHz，此处输入的应为1.023MHz的倍数");
}
//信号二输入fc
void MainFrame::signal_2_in_fc_input_e(wxCommandEvent& event) {
	SetStatusText("BOC或BPSK调制的扩频码速率，单位为MHz，此处输入的应为1.023MHz的倍数");
}
//信号二输入tco
void MainFrame::signal_2_in_tco_input_e(wxCommandEvent& event) {
	SetStatusText("鉴相器相关积分时间，单位为ms，常见输入为5ms和20ms");
}
//信号二输入beta
void MainFrame::signal_2_in_beta_input_e(wxCommandEvent& event) {
	SetStatusText("接收机带宽，单位为MHz，常见输入为24MHz");
}
//信号二输入betat
void MainFrame::signal_2_in_betat_input_e(wxCommandEvent& event) {
	SetStatusText("发射机带宽，单位为MHz，常见输入为24MHz、30MHz");
}
//信号二输入d
void MainFrame::signal_2_in_d_input_e(wxCommandEvent& event) {
	SetStatusText("超前—滞后本地码间隔，单位为ns，适当的输入为，BPSK:50ns,BOC(5,2):80ns,BOC(8,4):50ns,BOC(10,5):40ns");
}
//信号二输入signal
void MainFrame::signal_2_in_signal_input_e(wxCommandEvent& event) {
	SetStatusText("调制信号1的输入信号，格式应为10101的二进制码组");
}

//信号一计算λ
void MainFrame::signal_1_calculate_lamda_e(wxCommandEvent& event) {
	SetStatusText("带限后的剩余功率，需要输入接收机带宽");
	//获取输入信号类型。
	wxString type = signal_1_choice->GetValue();
	wxString lamda;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			lamda.Printf(_T("%lf"), Calculate::boc_lamda(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_1_out_lamda_output->SetValue(lamda);
		}
		else {
			//未获得正确输入
			signal_1_out_lamda_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			lamda.Printf(_T("%lf"), Calculate::bpsk_lamda(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_1_out_lamda_output->SetValue(lamda);
		}
		else {
			//未获得正确输入
			signal_1_out_lamda_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_lamda_output->SetValue(_T("未选择信号类型"));
	}
}
//信号一计算brms
void MainFrame::signal_1_calculate_brms_e(wxCommandEvent& event) {
	SetStatusText("带限后的均方根（RMS）带宽，单位为MHz，需要输入接收机带宽");
	wxString type = signal_1_choice->GetValue();
	wxString brms;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算brms
			brms.Printf(_T("%lf"), Calculate::boc_brms(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brms输出框的值
			signal_1_out_brms_output->SetValue(brms);
		}
		else {
			//未获得正确输入
			signal_1_out_brms_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			brms.Printf(_T("%lf"), Calculate::bpsk_brms(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_1_out_brms_output->SetValue(brms);
		}
		else {
			//未获得正确输入
			signal_1_out_brms_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_brms_output->SetValue(_T("未选择信号类型"));
	}
}
//信号一计算kls
void MainFrame::signal_1_calculate_kls_e(wxCommandEvent& event) {
	SetStatusText("频谱隔离系数，单位为dB/Hz，需要输入接收信号的接收带宽，干扰信号的发射带宽和接收带宽，其中信号一为接收信号，信号二为干扰信号");
	wxString type_self = signal_1_choice->GetValue();
	wxString type_another = signal_2_choice->GetValue();
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	wxString kls;
	if (type_self.Contains(_T("BOC")) && type_another.Contains(_T("BOC"))) {

		string fs = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());

		string fs_a = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc_a = string(signal_2_in_fc_input->GetValue().mb_str());
		string betat = string(signal_2_in_betat_input->GetValue().mb_str());

		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(fs_a, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::boc_boc_kls(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fs_a)*1.023 * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_1_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_1_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type_self.Contains(_T("BOC")) && type_another.Contains(_T("BPSK"))) {
		string fs = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());

		string fc_a = string(signal_2_in_fc_input->GetValue().mb_str());
		string betat = string(signal_2_in_betat_input->GetValue().mb_str());

		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::boc_bpsk_kls(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_1_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_1_out_kls_output->SetValue(_T("参数缺少或错误"));
		}

	}
	else if (type_self.Contains(_T("BPSK")) && type_another.Contains(_T("BOC"))) {
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());

		string fs_a = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc_a = string(signal_2_in_fc_input->GetValue().mb_str());
		string betat = string(signal_2_in_betat_input->GetValue().mb_str());

		if (regex_match(fc, r) && regex_match(beta, r) && regex_match(fs_a, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::bpsk_boc_kls(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fs_a)*1.023 * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_1_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_1_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type_self.Contains(_T("BPSK")) && type_another.Contains(_T("BPSK"))) {
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());

		string fc_a = string(signal_2_in_fc_input->GetValue().mb_str());
		string betat = string(signal_2_in_betat_input->GetValue().mb_str());

		if (regex_match(fc, r) && regex_match(beta, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::bpsk_bpsk_kls(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_1_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_1_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		signal_1_out_kls_output->SetValue(_T("未选择信号类型"));
	}
}
//信号一计算brect
void MainFrame::signal_1_calculate_brect_e(wxCommandEvent& event) {
	SetStatusText("带限后的有效矩形带宽，单位为MHz，需要输入接收机带宽");
	//获取输入信号类型。
	wxString type = signal_1_choice->GetValue();
	wxString brect;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算brect
			brect.Printf(_T("%lf"), Calculate::boc_brect(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brect输出框的值
			signal_1_out_brect_output->SetValue(brect);
		}
		else {
			//未获得正确输入
			signal_1_out_brect_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_1_in_fc_input->GetValue().mb_str());
		string beta = string(signal_1_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算brect
			brect.Printf(_T("%lf"), Calculate::bpsk_brect(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brect输出框的值
			signal_1_out_brect_output->SetValue(brect);
		}
		else {
			//未获得正确输入
			signal_1_out_brect_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_brect_output->SetValue(_T("未选择信号类型"));
	}
}

//信号二计算λ
void MainFrame::signal_2_calculate_lamda_e(wxCommandEvent& event) {
	SetStatusText("带限后的剩余功率，需要输入接收机带宽");
	wxString type = signal_2_choice->GetValue();
	wxString lamda;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			lamda.Printf(_T("%lf"), Calculate::boc_lamda(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_2_out_lamda_output->SetValue(lamda);
		}
		else {
			//未获得正确输入
			signal_2_out_lamda_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			lamda.Printf(_T("%lf"), Calculate::bpsk_lamda(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_2_out_lamda_output->SetValue(lamda);
		}
		else {
			//未获得正确输入
			signal_2_out_lamda_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_lamda_output->SetValue(_T("未选择信号类型"));
	}
}
//信号二计算brms
void MainFrame::signal_2_calculate_brms_e(wxCommandEvent& event) {
	SetStatusText("带限后的均方根（RMS）带宽，单位为MHz，需要输入接收机带宽");
	wxString type = signal_2_choice->GetValue();
	wxString brms;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算brms
			brms.Printf(_T("%lf"), Calculate::boc_brms(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brms输出框的值
			signal_2_out_brms_output->SetValue(brms);
		}
		else {
			//未获得正确输入
			signal_2_out_brms_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算λ
			brms.Printf(_T("%lf"), Calculate::bpsk_brms(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置λ输出框的值
			signal_2_out_brms_output->SetValue(brms);
		}
		else {
			//未获得正确输入
			signal_2_out_brms_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_brms_output->SetValue(_T("未选择信号类型"));
	}
}
//信号二计算kls
void MainFrame::signal_2_calculate_kls_e(wxCommandEvent& event) {
	SetStatusText("频谱隔离系数，单位为dB/Hz，需要输入接收信号的接收带宽，干扰信号的发射带宽和接收带宽，其中信号二为接收信号，信号一为干扰信号");
	wxString type_self = signal_2_choice->GetValue();
	wxString type_another = signal_1_choice->GetValue();
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	wxString kls;
	if (type_self.Contains(_T("BOC")) && type_another.Contains(_T("BOC"))) {

		string fs = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());

		string fs_a = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc_a = string(signal_1_in_fc_input->GetValue().mb_str());
		string betat = string(signal_1_in_betat_input->GetValue().mb_str());

		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(fs_a, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::boc_boc_kls(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fs_a)*1.023 * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_2_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_2_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type_self.Contains(_T("BOC")) && type_another.Contains(_T("BPSK"))) {
		string fs = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());

		string fc_a = string(signal_1_in_fc_input->GetValue().mb_str());
		string betat = string(signal_1_in_betat_input->GetValue().mb_str());

		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::boc_bpsk_kls(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_2_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_2_out_kls_output->SetValue(_T("参数缺少或错误"));
		}

	}
	else if (type_self.Contains(_T("BPSK")) && type_another.Contains(_T("BOC"))) {
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());

		string fs_a = string(signal_1_in_fs_input->GetValue().mb_str());
		string fc_a = string(signal_1_in_fc_input->GetValue().mb_str());
		string betat = string(signal_1_in_betat_input->GetValue().mb_str());

		if (regex_match(fc, r) && regex_match(beta, r) && regex_match(fs_a, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::bpsk_boc_kls(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fs_a)*1.023 * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_2_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_2_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type_self.Contains(_T("BPSK")) && type_another.Contains(_T("BPSK"))) {
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());

		string fc_a = string(signal_1_in_fc_input->GetValue().mb_str());
		string betat = string(signal_1_in_betat_input->GetValue().mb_str());

		if (regex_match(fc, r) && regex_match(beta, r) && regex_match(fc_a, r) && regex_match(betat, r)) {
			//计算brms
			kls.Printf(_T("%lf"), Calculate::bpsk_bpsk_kls(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(fc_a)*1.023 * 1000000, Calculate::stringToNum<double>(betat) * 1000000));
			//设置brms输出框的值
			signal_2_out_kls_output->SetValue(kls);
		}
		else {
			//未获得正确输入
			signal_2_out_kls_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		signal_2_out_kls_output->SetValue(_T("未选择信号类型"));
	}
}
//信号二计算brect
void MainFrame::signal_2_calculate_brect_e(wxCommandEvent& event) {
	SetStatusText("带限后的有效矩形带宽，单位为MHz，需要输入接收机带宽");
	//获取输入信号类型。
	wxString type = signal_2_choice->GetValue();
	wxString brect;
	std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
	//判断信号类型
	if (type.Contains(_T("BOC"))) {
		//获得输入
		string fs = string(signal_2_in_fs_input->GetValue().mb_str());
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
			//计算brect
			brect.Printf(_T("%lf"), Calculate::boc_brect(Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brect输出框的值
			signal_2_out_brect_output->SetValue(brect);
		}
		else {
			//未获得正确输入
			signal_2_out_brect_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else if (type.Contains(_T("BPSK"))) {
		//获得输入
		string fc = string(signal_2_in_fc_input->GetValue().mb_str());
		string beta = string(signal_2_in_beta_input->GetValue().mb_str());
		if (regex_match(fc, r) && regex_match(beta, r)) {
			//计算brect
			brect.Printf(_T("%lf"), Calculate::bpsk_brect(Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000));
			//设置brect输出框的值
			signal_2_out_brect_output->SetValue(brect);
		}
		else {
			//未获得正确输入
			signal_2_out_brect_output->SetValue(_T("参数缺少或错误"));
		}
	}
	else {
		//nothing to do
		signal_1_out_brect_output->SetValue(_T("未选择信号类型"));
	}
}

//生成时域波形
void MainFrame::imageType1_e(wxCommandEvent& event) {
	SetStatusText("生成时域波形");
	ImageType = TIME_DOMAIN;
	imageType3->SetLabel(_T("码跟踪误差"));
	imagePanel->Refresh();
}
//生成频域波形
void MainFrame::imageType41_e(wxCommandEvent& event) {
	SetStatusText("生成频域波形");
	ImageType = FREQUENCY_DOMAIN;
	imageType3->SetLabel(_T("码跟踪误差"));
	imagePanel->Refresh();
}
//生成自相关函数波形
void MainFrame::imageType2_e(wxCommandEvent& event) {
	SetStatusText("生成归一化自相关函数波形，需要输入接收机带宽");
	ImageType = AUTOCORRELATION;
	imageType3->SetLabel(_T("码跟踪误差"));
	imagePanel->Refresh();
}
//生成码跟踪误差波形
void MainFrame::imageType3_e(wxCommandEvent& event) {
	wxString str = imageType3->GetLabel();
	if (str.Contains(_T("切换x轴为△"))) {
		SetStatusText("生成  码跟踪均方根误差-超前滞后本地码间隔  波形，需要输入接收机带宽和鉴相器相关积分时间，此时载噪比默认为30db-Hz");
		ImageType = TRACKING_ERROR;
		imageType3->SetLabel(_T("切换x轴为C/N0"));
	}
	else if (str.Contains(_T("切换x轴为C/N0"))) {
		SetStatusText("生成  码跟踪均方根误差-期望信号载噪比  波形，需要输入接收机带宽、鉴相器相关积分时间、超前滞后本地码间隔");
		ImageType = TRACKING_ERROR_CN0;
		imageType3->SetLabel(_T("切换x轴为△"));
	}
	else {
		ImageType = TRACKING_ERROR;
		SetStatusText("生成  码跟踪均方根误差-超前滞后本地码间隔  波形，需要输入接收机带宽和鉴相器相关积分时间，此时载噪比默认为30db-Hz");
		imageType3->SetLabel(_T("切换x轴为C/N0"));
	}
	imagePanel->Refresh();
}

//生成多径精度影响波形
void MainFrame::imageType4_e(wxCommandEvent& event) {
	SetStatusText("生成多径误差包络波形，需要输入接收机带宽、超前滞后本地码间隔");
	ImageType = MULTIPATH_ERROR;
	imageType3->SetLabel(_T("码跟踪误差"));
	imagePanel->Refresh();
}
//保存波形
void MainFrame::imageSave_e(wxCommandEvent& event) {
	MainFrame::SaveImage();
	SetStatusText("保存波形成功");
}
//生成表格
void MainFrame::initDataset_e(wxCommandEvent& event) {
	TableFrame * tableFrame = new TableFrame(_T("常见GPS调制信号特性"));
	tableFrame->Show(true);
	SetStatusText("生成并保存表格成功");
}

//触发绘图事件
void MainFrame::Paint(wxPaintEvent& event) {
	wxPaintDC dc(this->imagePanel);
	wxPaintDC *DC = &dc;

	switch (ImageType)
	{
	case TIME_DOMAIN:
		draw_time_domain(DC);
		break;
	case FREQUENCY_DOMAIN:
		draw_frequency_domain(DC);
		break;
	case AUTOCORRELATION:
		draw_autocorrelation(DC);
		break;
	case TRACKING_ERROR:
		draw_tracking_error_delta(DC);
		break;
	case MULTIPATH_ERROR:
		draw_multipath_error(DC);
		break;
	case TRACKING_ERROR_CN0:
		draw_tracking_error_CN0(DC);
		break;
	default:
		draw_time_domain(DC);
		break;
	}
}
