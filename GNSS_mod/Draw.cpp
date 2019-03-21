#include "MyApp.h"
#include "MainFrame.h"
#include <regex>
#include "Calculate.h"
using namespace std;

//画时域波形
void MainFrame::draw_time_domain(wxDC* dc) {
	int w=0, h=0;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画信号一x轴
	dc->DrawLine(wxPoint(0.03*w, h*0.3), wxPoint(0.98*w, h*0.3));
	//画信号一x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.3), wxPoint(0.98*w - 8, h*0.3 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.3), wxPoint(0.98*w - 8, h*0.3 - 8));
	//画信号一x轴标注
	dc->DrawText(_T("t"), wxPoint(0.95*w, h*0.3 + 30));
	//画信号一y轴
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.05*w, h*0.5));
	//画信号一轴箭头
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.05*w - 8, h*0.1 + 8));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.05*w + 8, h*0.1 + 8));
	//画信号一轴标注
	dc->DrawText(_T("signal"), wxPoint(0.05*w + 8, h*0.1 - 8));


	dc->SetPen(*wxBLACK_PEN);
	//画信号二x轴
	dc->DrawLine(wxPoint(0.03*w, h*0.8), wxPoint(0.98*w, h*0.8));
	//画信号二x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.8), wxPoint(0.98*w - 8, h*0.8 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.8), wxPoint(0.98*w - 8, h*0.8 - 8));
	//画信号二x轴标注
	dc->DrawText(_T("t"), wxPoint(0.95*w, h*0.8 + 30));
	//画信号二y轴
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.05*w, h));
	//画信号二轴箭头
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.05*w - 8, h*0.6 + 8));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.05*w + 8, h*0.6 + 8));
	//画信号二轴标注
	dc->DrawText(_T("signal"), wxPoint(0.05*w + 8, h*0.6 - 8));


	//画信号一
	if (isUseSignal1->GetValue()) {
		wxString type = signal_1_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		std::regex r_i("^[10]*$");
		if (type.Contains(_T("BOC"))) {
			string signal = string(signal_1_in_signal_input->GetValue().mb_str());
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			if (regex_match(signal, r_i) && regex_match(fs, r) && regex_match(fc, r)) {
				dc->DrawText(_T("信号一：BOC"), wxPoint(5, 5));
				int signal_len = signal.length();
				int element_len = 0.9*w / signal.length();
				int n = 2 * Calculate::stringToNum<double>(fs) / Calculate::stringToNum<double>(fc);
				int v_len = element_len / n;
				dc->SetPen(*wxBLACK_DASHED_PEN);
				for (int signal_inex = 0; signal_inex < signal_len; signal_inex++) {
					for (int i = 1; i <= n; i++) {
						dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.1), wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.5));
					}
				}
				dc->SetPen(*wxRED_PEN);
				for (int signal_inex = 0; signal_inex < signal_len; signal_inex++) {
					if (signal[signal_inex] == '0') {
						for (int i = 0; i < n; i++) {
							dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, i % 2 == 0 ? h*0.45 : h*0.15), wxPoint(0.05*w + (i + 1)*v_len + element_len*signal_inex, i % 2 == 0 ? h*0.45 : h*0.15));
						}
					}
					else{
						for (int i = 0; i < n; i++) {
							dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, i % 2 == 0 ? h*0.15 : h*0.45), wxPoint(0.05*w + (i + 1)*v_len + element_len*signal_inex, i % 2 == 0 ? h*0.15 : h*0.45));
						}
					}
				}	
			}
			else{
				dc->DrawText(_T("输入错误"), wxPoint(5, 5));

			}
		}
		else if (type.Contains(_T("BPSK"))) {
			string signal = string(signal_1_in_signal_input->GetValue().mb_str());
			if (regex_match(signal, r_i)) {
				dc->DrawText(_T("信号一：BPSK"), wxPoint(5, 5));
				int signal_len = signal.length();
				int element_len = 0.9*w / signal.length();
				dc->SetPen(*wxBLACK_DASHED_PEN);
				for (int signal_inex = 1; signal_inex <= signal_len; signal_inex++) {
					dc->DrawLine(wxPoint(0.05*w + element_len*signal_inex, h*0.1), wxPoint(0.05*w + element_len*signal_inex, h*0.5));
				}
				dc->SetPen(*wxRED_PEN);
				for (int signal_inex = 1; signal_inex <= signal_len; signal_inex++) {
					int i_x_o = (signal_inex - 1)*element_len+0.05*w, i_y_o = 0.3*h, x = 0, y = 0;
					if (signal[signal_inex-1] == '0') {
						for (x = i_x_o; x < signal_inex*element_len + 0.05*w; x++) {
							y = 0.3*h + sin((x - (signal_inex - 1)*element_len - 0.05*w) * 2 * PI / element_len)*0.15*h;
							dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(x, y));
							i_x_o = x;
							i_y_o = y;
						}
					}
					else {
						for (x = i_x_o; x < signal_inex*element_len + 0.05*w; x++) {
							y = 0.3*h - sin((x - (signal_inex - 1)*element_len - 0.05*w) * 2 * PI / element_len)*0.15*h;
							dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(x, y));
							i_x_o = x;
							i_y_o = y;
						}
					}
				}
			}
			else{
				dc->DrawText(_T("输入错误"), wxPoint(5, 5));
			}
		}
		else{
			dc->DrawText(_T("未选择信号类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal1->GetValue()) {
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		std::regex r_i("^[10]*$");
		if (type.Contains(_T("BOC"))) {
			string signal = string(signal_2_in_signal_input->GetValue().mb_str());
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			if (regex_match(signal, r_i) && regex_match(fs, r) && regex_match(fc, r)) {
				dc->DrawText(_T("信号二：BOC"), wxPoint(5, h*0.5 + 5));
				int signal_len = signal.length();
				int element_len = 0.9*w / signal.length();
				int n = 2 * Calculate::stringToNum<double>(fs) / Calculate::stringToNum<double>(fc);
				int v_len = element_len / n;
				dc->SetPen(*wxBLACK_DASHED_PEN);
				for (int signal_inex = 0; signal_inex < signal_len; signal_inex++) {
					for (int i = 1; i <= n; i++) {
						dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.1 + h*0.5), wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.5 + h*0.5));
					}
				}
				dc->SetPen(*wxRED_PEN);
				for (int signal_inex = 0; signal_inex < signal_len; signal_inex++) {
					if (signal[signal_inex] == '0') {
						for (int i = 0; i < n; i++) {
							dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.5 + (i % 2 == 0 ? h*0.45 : h*0.15)), wxPoint(0.05*w + (i + 1)*v_len + element_len*signal_inex, h*0.5 + (i % 2 == 0 ? h*0.45 : h*0.15)));
						}
					}
					else {
						for (int i = 0; i < n; i++) {
							dc->DrawLine(wxPoint(0.05*w + i*v_len + element_len*signal_inex, h*0.5 + (i % 2 == 0 ? h*0.15 : h*0.45)), wxPoint(0.05*w + (i + 1)*v_len + element_len*signal_inex, h*0.5 + (i % 2 == 0 ? h*0.15 : h*0.45)));
						}
					}
				}
			}
			else {
				dc->DrawText(_T("输入错误"), wxPoint(5, h*0.5 + 5));

			}
		}
		else if (type.Contains(_T("BPSK"))) {
			string signal = string(signal_2_in_signal_input->GetValue().mb_str());
			if (regex_match(signal, r_i)) {
				dc->DrawText(_T("信号二：BPSK"), wxPoint(5, h*0.5 + 5));
				int signal_len = signal.length();
				int element_len = 0.9*w / signal.length();
				dc->SetPen(*wxBLACK_DASHED_PEN);
				for (int signal_inex = 1; signal_inex <= signal_len; signal_inex++) {
					dc->DrawLine(wxPoint(0.05*w + element_len*signal_inex, h*0.5 + h*0.1), wxPoint(0.05*w + element_len*signal_inex, h*0.5 + h*0.5));
				}
				dc->SetPen(*wxRED_PEN);
				for (int signal_inex = 1; signal_inex <= signal_len; signal_inex++) {
					int i_x_o = (signal_inex - 1)*element_len + 0.05*w, i_y_o = h*0.5 + 0.3*h, x = 0, y = 0;
					if (signal[signal_inex - 1] == '0') {
						for (x = i_x_o; x < signal_inex*element_len + 0.05*w; x++) {
							y = h*0.5 + 0.3*h + sin((x - (signal_inex - 1)*element_len - 0.05*w) * 2 * PI / element_len)*0.15*h;
							dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(x, y));
							i_x_o = x;
							i_y_o = y;
						}
					}
					else {
						for (x = i_x_o; x < signal_inex*element_len + 0.05*w; x++) {
							y = h*0.5 + 0.3*h - sin((x - (signal_inex - 1)*element_len - 0.05*w) * 2 * PI / element_len)*0.15*h;
							dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(x, y));
							i_x_o = x;
							i_y_o = y;
						}
					}
				}
			}
			else {
				dc->DrawText(_T("输入错误"), wxPoint(5, h*0.5 + 5));
			}
		}
		else {
			dc->DrawText(_T("未选择信号类型"), wxPoint(5, h*0.5 + 5));
		}
	}
}

//画频域波形
void MainFrame::draw_frequency_domain(wxDC* dc) {
	int w = 0, h = 0;
	int i;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画x轴直线
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.98*w, h*0.9));
	//画x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 - 8));
	//画x轴标注
	dc->DrawText(_T("f/MHz"), wxPoint(0.95*w, h*0.9-30));
	//画y轴
	dc->DrawLine(wxPoint(0.5*w, h*0.9+20), wxPoint(0.5*w, h*0.05));
	//画y轴箭头
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w - 8, h*0.05 + 8));
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w + 8, h*0.05 + 8));
	//画y轴标注
	dc->DrawText(_T("G(f)/(dbw/Hz)"), wxPoint(0.5*w + 8, h*0.05 - 8));

	//更换虚线
	dc->SetPen(*wxBLACK_DASHED_PEN);
	//画横向标准线
	dc->DrawText(_T("-100"), wxPoint(0.5*w - 35, h*0.9 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.8), wxPoint(0.95*w, h*0.8));
	dc->DrawText(_T("-95"), wxPoint(0.5*w-30, h*0.8-20));
	dc->DrawLine(wxPoint(0.05*w, h*0.7), wxPoint(0.95*w, h*0.7));
	dc->DrawText(_T("-90"), wxPoint(0.5*w - 30, h*0.7 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.95*w, h*0.6));
	dc->DrawText(_T("-85"), wxPoint(0.5*w - 30, h*0.6 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.5), wxPoint(0.95*w, h*0.5));
	dc->DrawText(_T("-80"), wxPoint(0.5*w - 30, h*0.5 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.4), wxPoint(0.95*w, h*0.4));
	dc->DrawText(_T("-75"), wxPoint(0.5*w - 30, h*0.4 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.3), wxPoint(0.95*w, h*0.3));
	dc->DrawText(_T("-70"), wxPoint(0.5*w - 30, h*0.3 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.2), wxPoint(0.95*w, h*0.2));
	dc->DrawText(_T("-65"), wxPoint(0.5*w - 30, h*0.2 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("-60"), wxPoint(0.5*w - 30, h*0.1 - 20));

	//画竖向标准线
	dc->DrawText(_T("0"), wxPoint(0.5*w, h*0.9));
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.05*w, h*0.1));
	dc->DrawText(_T("-15"), wxPoint(0.05*w - 15, h*0.9));
	dc->DrawLine(wxPoint(0.2*w, h*0.9), wxPoint(0.2*w, h*0.1));
	dc->DrawText(_T("-10"), wxPoint(0.2*w - 15, h*0.9));
	dc->DrawLine(wxPoint(0.35*w, h*0.9), wxPoint(0.35*w, h*0.1));
	dc->DrawText(_T("-5"), wxPoint(0.35*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.65*w, h*0.9), wxPoint(0.65*w, h*0.1));
	dc->DrawText(_T("5"), wxPoint(0.65*w - 5, h*0.9));
	dc->DrawLine(wxPoint(0.80*w, h*0.9), wxPoint(0.80*w, h*0.1));
	dc->DrawText(_T("10"), wxPoint(0.8*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.95*w, h*0.9), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("15"), wxPoint(0.95*w - 15, h*0.9));
	
	//画信号一
	if (isUseSignal1->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxBLUE_PEN);
		dc->SetTextForeground(wxColour(0, 0, 255));
		//获得信号一类型
		wxString type = signal_1_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_1_in_fs_input->GetValue() + _T(",") + signal_1_in_fc_input->GetValue() + _T(")"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 15 * 1000000;
				y = Calculate::boc_f(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
				y = 10 * log10(y);
				i_y_o = 0.9*h - (y + 100) / 5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
					y = Calculate::boc_f(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
					y = 10 * log10(y);
					i_y = 0.9*h - (y + 100) / 5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			if (regex_match(fc, r)) {
				dc->DrawText(_T("信号一：BPSK(") + signal_1_in_fc_input->GetValue() + _T("*1.023)"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 15 * 1000000;
				y = Calculate::bpsk_f(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
				y = 10 * log10(y);
				i_y_o = 0.9*h - (y + 100) / 5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
					y = Calculate::bpsk_f(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
					y = 10 * log10(y);
					i_y = 0.9*h - (y + 100) / 5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号一：未选择类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal2->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxRED_PEN);
		dc->SetTextForeground(wxColour(255, 0, 0));
		//获得信号二类型
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r)) {
				dc->DrawText(_T("信号二：BOC(") + signal_2_in_fs_input->GetValue() + _T(",") + signal_2_in_fc_input->GetValue() + _T(")"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
				y = Calculate::boc_f(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
				y = 10 * log10(y);
				i_y_o = 0.9*h - (y + 100) / 5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
					y = Calculate::boc_f(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
					y = 10 * log10(y);
					i_y = 0.9*h - (y + 100) / 5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			if (regex_match(fc, r)) {
				dc->DrawText(_T("信号二：BPSK(") + signal_2_in_fc_input->GetValue() + _T("*1.023)"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
				y = Calculate::bpsk_f(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
				y = 10 * log10(y);
				i_y_o = 0.9*h - (y + 100) / 5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 15 * 1000000;
					y = Calculate::bpsk_f(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000);
					y = 10 * log10(y);
					i_y = 0.9*h - (y + 100) / 5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号二：未选择类型"), wxPoint(5, 25));
		}
	}
}

//画自相关函数
void MainFrame::draw_autocorrelation(wxDC* dc) {
	int w = 0, h = 0;
	int i;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画x轴直线
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.98*w, h*0.9));
	//画x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 - 8));
	//画x轴标注
	dc->DrawText(_T("时延/μs"), wxPoint(0.95*w - 10, h*0.9 - 30));
	//画y轴
	dc->DrawLine(wxPoint(0.5*w, h*0.9+20), wxPoint(0.5*w, h*0.05));
	//画y轴箭头
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w - 8, h*0.05 + 8));
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w + 8, h*0.05 + 8));
	//画y轴标注
	dc->DrawText(_T("归一化自相关值"), wxPoint(0.5*w + 8, h*0.05 - 8));

	//更换虚线
	dc->SetPen(*wxBLACK_DASHED_PEN);
	//画横向标准线
	dc->DrawText(_T("0"), wxPoint(0.5*w - 10, h*0.9 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.8), wxPoint(0.95*w, h*0.8));
	dc->DrawText(_T("0.125"), wxPoint(0.5*w-40, h*0.8-20));
	dc->DrawLine(wxPoint(0.05*w, h*0.7), wxPoint(0.95*w, h*0.7));
	dc->DrawText(_T("0.250"), wxPoint(0.5*w - 40, h*0.7 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.95*w, h*0.6));
	dc->DrawText(_T("0.375"), wxPoint(0.5*w - 40, h*0.6 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.5), wxPoint(0.95*w, h*0.5));
	dc->DrawText(_T("0.500"), wxPoint(0.5*w - 40, h*0.5 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.4), wxPoint(0.95*w, h*0.4));
	dc->DrawText(_T("0.625"), wxPoint(0.5*w - 40, h*0.4 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.3), wxPoint(0.95*w, h*0.3));
	dc->DrawText(_T("0.750"), wxPoint(0.5*w - 40, h*0.3 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.2), wxPoint(0.95*w, h*0.2));
	dc->DrawText(_T("0.875"), wxPoint(0.5*w - 40, h*0.2 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("1.000"), wxPoint(0.5*w - 40, h*0.1 - 20));

	//画竖向标准线
	dc->DrawText(_T("0"), wxPoint(0.5*w, h*0.9));
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.05*w, h*0.1));
	dc->DrawText(_T("-1.00"), wxPoint(0.05*w - 20, h*0.9));
	dc->DrawLine(wxPoint(0.1625*w, h*0.9), wxPoint(0.1625*w, h*0.1));
	dc->DrawText(_T("-0.75"), wxPoint(0.1625*w - 20, h*0.9));
	dc->DrawLine(wxPoint(0.275*w, h*0.9), wxPoint(0.275*w, h*0.1));
	dc->DrawText(_T("-0.50"), wxPoint(0.275*w - 20, h*0.9));
	dc->DrawLine(wxPoint(0.3875*w, h*0.9), wxPoint(0.3875*w, h*0.1));
	dc->DrawText(_T("-0.25"), wxPoint(0.3875*w - 20, h*0.9));
	dc->DrawLine(wxPoint(0.6125*w, h*0.9), wxPoint(0.6125*w, h*0.1));
	dc->DrawText(_T("0.25"), wxPoint(0.6125*w - 15, h*0.9));
	dc->DrawLine(wxPoint(0.725*w, h*0.9), wxPoint(0.725*w, h*0.1));
	dc->DrawText(_T("0.50"), wxPoint(0.725*w - 15, h*0.9));
	dc->DrawLine(wxPoint(0.8375*w, h*0.9), wxPoint(0.8375*w, h*0.1));
	dc->DrawText(_T("0.75"), wxPoint(0.8375*w - 15, h*0.9));
	dc->DrawLine(wxPoint(0.95*w, h*0.9), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("1.00"), wxPoint(0.95*w - 15, h*0.9));
	
	//画信号一
	if (isUseSignal1->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxBLUE_PEN);
		dc->SetTextForeground(wxColour(0, 0, 255));
		//获得信号一类型
		wxString type = signal_1_choice->GetValue(); 
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_1_in_fs_input->GetValue() + _T(",") + signal_1_in_fc_input->GetValue() + _T(")，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 0.000001;
				y = Calculate::boc_autocorrelation(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 0.000001;
					y = Calculate::boc_autocorrelation(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r)) {
				dc->DrawText(_T("信号一：BPSK(") + signal_1_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 0.000001;
				y = Calculate::bpsk_autocorrelation(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 0.000001;
					y = Calculate::bpsk_autocorrelation(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号一：未选择类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal2->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxRED_PEN);
		dc->SetTextForeground(wxColour(255, 0, 0));
		//获得信号二类型
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_2_in_fs_input->GetValue() + _T(",") + signal_2_in_fc_input->GetValue() + _T(")，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 0.000001;
				y = Calculate::boc_autocorrelation(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 0.000001;
					y = Calculate::boc_autocorrelation(x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r)) {
				dc->DrawText(_T("信号二：BPSK(") + signal_2_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.5*w) / (0.45*w) * 0.000001;
				y = Calculate::bpsk_autocorrelation(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.5*w) / (0.45*w) * 0.000001;
					y = Calculate::bpsk_autocorrelation(x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号二：未选择类型"), wxPoint(5, 25));
		}
	}
}

//画NELP-delta
void MainFrame::draw_tracking_error_delta(wxDC* dc) {
	int w = 0, h = 0;
	int i;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画x轴直线
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.98*w, h*0.9));
	//画x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 - 8));
	//画x轴标注
	dc->DrawText(_T("超前滞后本地码间隔/ns"), wxPoint(0.95*w - 110, h*0.9 - 30));
	//画y轴
	dc->DrawLine(wxPoint(0.5*w, h*0.9 + 20), wxPoint(0.5*w, h*0.05));
	//画y轴箭头
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w - 8, h*0.05 + 8));
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w + 8, h*0.05 + 8));
	//画y轴标注
	dc->DrawText(_T("NELP码跟踪误差/m"), wxPoint(0.5*w + 8, h*0.05 - 8));

	//更换虚线
	dc->SetPen(*wxBLACK_DASHED_PEN);
	//画横向标准线
	dc->DrawText(_T("0"), wxPoint(0.5*w - 10, h*0.9 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.8), wxPoint(0.95*w, h*0.8));
	dc->DrawText(_T("0.5"), wxPoint(0.5*w - 40, h*0.8 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.7), wxPoint(0.95*w, h*0.7));
	dc->DrawText(_T("1.0"), wxPoint(0.5*w - 40, h*0.7 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.95*w, h*0.6));
	dc->DrawText(_T("1.5"), wxPoint(0.5*w - 40, h*0.6 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.5), wxPoint(0.95*w, h*0.5));
	dc->DrawText(_T("2.0"), wxPoint(0.5*w - 40, h*0.5 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.4), wxPoint(0.95*w, h*0.4));
	dc->DrawText(_T("2.5"), wxPoint(0.5*w - 40, h*0.4 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.3), wxPoint(0.95*w, h*0.3));
	dc->DrawText(_T("3.0"), wxPoint(0.5*w - 40, h*0.3 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.2), wxPoint(0.95*w, h*0.2));
	dc->DrawText(_T("3.5"), wxPoint(0.5*w - 40, h*0.2 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("4.0"), wxPoint(0.5*w - 40, h*0.1 - 20));

	//画竖向标准线
	dc->DrawText(_T("120"), wxPoint(0.5*w, h*0.9));
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.05*w, h*0.1));
	dc->DrawText(_T("0"), wxPoint(0.05*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.1625*w, h*0.9), wxPoint(0.1625*w, h*0.1));
	dc->DrawText(_T("30"), wxPoint(0.1625*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.275*w, h*0.9), wxPoint(0.275*w, h*0.1));
	dc->DrawText(_T("60"), wxPoint(0.275*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.3875*w, h*0.9), wxPoint(0.3875*w, h*0.1));
	dc->DrawText(_T("90"), wxPoint(0.3875*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.6125*w, h*0.9), wxPoint(0.6125*w, h*0.1));
	dc->DrawText(_T("150"), wxPoint(0.6125*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.725*w, h*0.9), wxPoint(0.725*w, h*0.1));
	dc->DrawText(_T("180"), wxPoint(0.725*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.8375*w, h*0.9), wxPoint(0.8375*w, h*0.1));
	dc->DrawText(_T("210"), wxPoint(0.8375*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.95*w, h*0.9), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("240"), wxPoint(0.95*w - 10, h*0.9));

	//画信号一
	if (isUseSignal1->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxBLUE_PEN);
		dc->SetTextForeground(wxColour(0, 0, 255));
		//获得信号一类型
		wxString type = signal_1_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string tco = string(signal_1_in_tco_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_1_in_fs_input->GetValue() + _T(",") + signal_1_in_fc_input->GetValue() + _T(")，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_1_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string tco = string(signal_1_in_tco_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r)) {
				dc->DrawText(_T("信号一：BPSK(") + signal_1_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_1_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号一：未选择类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal2->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxRED_PEN);
		dc->SetTextForeground(wxColour(255, 0, 0));
		//获得信号二类型
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string tco = string(signal_2_in_tco_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r)) {
				dc->DrawText(_T("信号二：BOC(") + signal_2_in_fs_input->GetValue() + _T(",") + signal_2_in_fc_input->GetValue() + _T(")，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_2_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.5 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.5 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string tco = string(signal_2_in_tco_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r)) {
				dc->DrawText(_T("信号二：BPSK(") + signal_2_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_2_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_NELP_delta(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号二：未选择类型"), wxPoint(5, 25));
		}
	}
}

//画NELP-CN0
void MainFrame::draw_tracking_error_CN0(wxDC* dc) {
	int w = 0, h = 0;
	int i;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画x轴直线
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.98*w, h*0.9));
	//画x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 - 8));
	//画x轴标注
	dc->DrawText(_T("载噪比C/N0(dB-Hz)"), wxPoint(0.95*w - 110, h*0.9 - 30));
	//画y轴
	dc->DrawLine(wxPoint(0.5*w, h*0.9 + 20), wxPoint(0.5*w, h*0.05));
	//画y轴箭头
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w - 8, h*0.05 + 8));
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w + 8, h*0.05 + 8));
	//画y轴标注
	dc->DrawText(_T("NELP码跟踪误差/m"), wxPoint(0.5*w + 8, h*0.05 - 8));

	//更换虚线
	dc->SetPen(*wxBLACK_DASHED_PEN);
	//画横向标准线
	dc->DrawText(_T("0"), wxPoint(0.5*w - 10, h*0.9 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.8), wxPoint(0.95*w, h*0.8));
	dc->DrawText(_T("0.125"), wxPoint(0.5*w - 40, h*0.8 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.7), wxPoint(0.95*w, h*0.7));
	dc->DrawText(_T("0.250"), wxPoint(0.5*w - 40, h*0.7 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.95*w, h*0.6));
	dc->DrawText(_T("0.375"), wxPoint(0.5*w - 40, h*0.6 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.5), wxPoint(0.95*w, h*0.5));
	dc->DrawText(_T("0.500"), wxPoint(0.5*w - 40, h*0.5 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.4), wxPoint(0.95*w, h*0.4));
	dc->DrawText(_T("0.625"), wxPoint(0.5*w - 40, h*0.4 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.3), wxPoint(0.95*w, h*0.3));
	dc->DrawText(_T("0.750"), wxPoint(0.5*w - 40, h*0.3 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.2), wxPoint(0.95*w, h*0.2));
	dc->DrawText(_T("0.875"), wxPoint(0.5*w - 40, h*0.2 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("1.000"), wxPoint(0.5*w - 40, h*0.1 - 20));

	//画竖向标准线
	dc->DrawText(_T("30"), wxPoint(0.5*w, h*0.9));
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.05*w, h*0.1));
	dc->DrawText(_T("10"), wxPoint(0.05*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.1625*w, h*0.9), wxPoint(0.1625*w, h*0.1));
	dc->DrawText(_T("15"), wxPoint(0.1625*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.275*w, h*0.9), wxPoint(0.275*w, h*0.1));
	dc->DrawText(_T("20"), wxPoint(0.275*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.3875*w, h*0.9), wxPoint(0.3875*w, h*0.1));
	dc->DrawText(_T("25"), wxPoint(0.3875*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.6125*w, h*0.9), wxPoint(0.6125*w, h*0.1));
	dc->DrawText(_T("35"), wxPoint(0.6125*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.725*w, h*0.9), wxPoint(0.725*w, h*0.1));
	dc->DrawText(_T("40"), wxPoint(0.725*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.8375*w, h*0.9), wxPoint(0.8375*w, h*0.1));
	dc->DrawText(_T("45"), wxPoint(0.8375*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.95*w, h*0.9), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("50"), wxPoint(0.95*w - 10, h*0.9));

	//画信号一
	if (isUseSignal1->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxBLUE_PEN);
		dc->SetTextForeground(wxColour(0, 0, 255));
		//获得信号一类型
		wxString type = signal_1_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string tco = string(signal_1_in_tco_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_1_in_fs_input->GetValue() + _T(",") + signal_1_in_fc_input->GetValue() + _T(")，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_1_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 40 + 10;
				y = Calculate::boc_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10,-9), x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 40 + 10;
					y = Calculate::boc_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string tco = string(signal_1_in_tco_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号一：BPSK(") + signal_1_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_1_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_1_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 5));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 40 + 10;
				y = Calculate::bpsk_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 40 + 10;
					y = Calculate::bpsk_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号一：未选择类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal2->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxRED_PEN);
		dc->SetTextForeground(wxColour(255, 0, 0));
		//获得信号二类型
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string tco = string(signal_2_in_tco_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号二：BOC(") + signal_2_in_fs_input->GetValue() + _T(",") + signal_2_in_fc_input->GetValue() + _T(")，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_2_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 40 + 10;
				y = Calculate::boc_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 40 + 10;
					y = Calculate::boc_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string tco = string(signal_2_in_tco_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r) && regex_match(tco, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号二：BPSK(") + signal_2_in_fc_input->GetValue() + _T("*1.023MHz)，带宽为：") + signal_2_in_beta_input->GetValue() + _T("MHz，相关积分时间Tco为：") + signal_2_in_tco_input->GetValue() + _T("ms"), wxPoint(5, 25));
				//计算第一个点
				int i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 40 + 10;
				y = Calculate::bpsk_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
				i_y_o = 0.9*h - y / 0.125 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 40 + 10;
					y = Calculate::bpsk_NELP_CN0(Calculate::stringToNum<double>(spacing)*pow(10, -9), x, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(tco)*0.001);
					i_y = 0.9*h - y / 0.125 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号二：未选择类型"), wxPoint(5, 25));
		}
	}
}

//画多径误差
void MainFrame::draw_multipath_error(wxDC* dc) {
	int w = 0, h = 0;
	int i;
	//获得面板大小
	this->imagePanel->GetSize(&w, &h);
	//画x轴直线
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.98*w, h*0.9));
	//画x轴箭头
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 + 8));
	dc->DrawLine(wxPoint(0.98*w, h*0.9), wxPoint(0.98*w - 8, h*0.9 - 8));
	//画x轴标注
	dc->DrawText(_T("多径时延/ns"), wxPoint(0.95*w - 110, h*0.9 - 30));
	//画y轴
	dc->DrawLine(wxPoint(0.5*w, h*0.9 + 20), wxPoint(0.5*w, h*0.05));
	//画y轴箭头
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w - 8, h*0.05 + 8));
	dc->DrawLine(wxPoint(0.5*w, h*0.05), wxPoint(0.5*w + 8, h*0.05 + 8));
	//画y轴标注
	dc->DrawText(_T("多径误差包络/m"), wxPoint(0.5*w + 8, h*0.05 - 8));

	//更换虚线
	dc->SetPen(*wxBLACK_DASHED_PEN);
	//画横向标准线
	dc->DrawText(_T("-8"), wxPoint(0.5*w - 10, h*0.9 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.8), wxPoint(0.95*w, h*0.8));
	dc->DrawText(_T("-6"), wxPoint(0.5*w - 40, h*0.8 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.7), wxPoint(0.95*w, h*0.7));
	dc->DrawText(_T("-4"), wxPoint(0.5*w - 40, h*0.7 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.6), wxPoint(0.95*w, h*0.6));
	dc->DrawText(_T("-2"), wxPoint(0.5*w - 40, h*0.6 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.5), wxPoint(0.95*w, h*0.5));
	dc->DrawText(_T("0"), wxPoint(0.5*w - 40, h*0.5 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.4), wxPoint(0.95*w, h*0.4));
	dc->DrawText(_T("2"), wxPoint(0.5*w - 40, h*0.4 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.3), wxPoint(0.95*w, h*0.3));
	dc->DrawText(_T("4"), wxPoint(0.5*w - 40, h*0.3 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.2), wxPoint(0.95*w, h*0.2));
	dc->DrawText(_T("6"), wxPoint(0.5*w - 40, h*0.2 - 20));
	dc->DrawLine(wxPoint(0.05*w, h*0.1), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("8"), wxPoint(0.5*w - 40, h*0.1 - 20));

	//画竖向标准线
	dc->DrawText(_T("30"), wxPoint(0.5*w, h*0.9));
	dc->DrawLine(wxPoint(0.05*w, h*0.9), wxPoint(0.05*w, h*0.1));
	dc->DrawText(_T("0"), wxPoint(0.05*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.1625*w, h*0.9), wxPoint(0.1625*w, h*0.1));
	dc->DrawText(_T("30"), wxPoint(0.1625*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.275*w, h*0.9), wxPoint(0.275*w, h*0.1));
	dc->DrawText(_T("60"), wxPoint(0.275*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.3875*w, h*0.9), wxPoint(0.3875*w, h*0.1));
	dc->DrawText(_T("90"), wxPoint(0.3875*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.6125*w, h*0.9), wxPoint(0.6125*w, h*0.1));
	dc->DrawText(_T("150"), wxPoint(0.6125*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.725*w, h*0.9), wxPoint(0.725*w, h*0.1));
	dc->DrawText(_T("180"), wxPoint(0.725*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.8375*w, h*0.9), wxPoint(0.8375*w, h*0.1));
	dc->DrawText(_T("210"), wxPoint(0.8375*w - 10, h*0.9));
	dc->DrawLine(wxPoint(0.95*w, h*0.9), wxPoint(0.95*w, h*0.1));
	dc->DrawText(_T("240"), wxPoint(0.95*w - 10, h*0.9));

	//画信号一
	if (isUseSignal1->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxBLUE_PEN);
		dc->SetTextForeground(wxColour(0, 0, 255));
		//获得信号一类型
		wxString type = signal_1_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_1_in_fs_input->GetValue().mb_str());
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号一：BOC(") + signal_1_in_fs_input->GetValue() + _T(",") + signal_1_in_fc_input->GetValue() + _T(")"), wxPoint(5, 5));
				//画上部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
				//画下部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_1_in_fc_input->GetValue().mb_str());
			string beta = string(signal_1_in_beta_input->GetValue().mb_str());
			string spacing = string(signal_1_in_d_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r)  && regex_match(spacing, r)) {
				dc->DrawText(_T("信号一：BPSK(") + signal_1_in_fc_input->GetValue() + _T("*1.023MHz)"), wxPoint(5, 5));
				//计算第一个点
				//画上部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
				//画下部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号一：输入错误"), wxPoint(5, 5));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号一：未选择类型"), wxPoint(5, 5));
		}
	}

	//画信号二
	if (isUseSignal2->GetValue()) {
		double y = 0;
		double x = 0;
		int i_x = 0;
		int i_y = 0;
		int i_x_o = 0;
		int i_y_o = 0;
		dc->SetPen(*wxRED_PEN);
		dc->SetTextForeground(wxColour(255, 0, 0));
		//获得信号二类型
		wxString type = signal_2_choice->GetValue();
		std::regex r("([1-9]+[0-9]*|0)(\\.[\\d]+)?");
		if (type.Contains(_T("BOC"))) {
			//获得输入
			string fs = string(signal_2_in_fs_input->GetValue().mb_str());
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string spacing = string(signal_2_in_d_input->GetValue().mb_str());
			if (regex_match(fs, r) && regex_match(fc, r) && regex_match(beta, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号二：BOC(") + signal_2_in_fs_input->GetValue() + _T(",") + signal_2_in_fc_input->GetValue() + _T(")"), wxPoint(5, 25));
				//画上部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
				//画下部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::boc_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::boc_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fs)*1.023 * 1000000, Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else if (type.Contains(_T("BPSK"))) {
			//获得输入
			string fc = string(signal_2_in_fc_input->GetValue().mb_str());
			string beta = string(signal_2_in_beta_input->GetValue().mb_str());
			string spacing = string(signal_2_in_d_input->GetValue().mb_str());
			if (regex_match(fc, r) && regex_match(beta, r) && regex_match(spacing, r)) {
				dc->DrawText(_T("信号二：BPSK(") + signal_2_in_fc_input->GetValue() + _T("*1.023MHz)"), wxPoint(5, 25));
				//计算第一个点
				//画上部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_multipath_error_Pos(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
				//画下部
				i_x_o = 0.05*w;
				x = (i_x_o - 0.05*w) / 0.9 / w * 240;
				y = Calculate::bpsk_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
				i_y_o = 0.5*h - y / 30 * 0.1*h;
				i_y_o = i_y_o > 0.9*h ? 0.9*h : i_y_o;

				for (i_x = 0.05*w; i_x <= 0.95*w; i_x++) {
					x = (i_x - 0.05*w) / 0.9 / w * 240;
					y = Calculate::bpsk_multipath_error_Neg(x*pow(10, -9), Calculate::stringToNum<double>(fc)*1.023 * 1000000, Calculate::stringToNum<double>(beta) * 1000000, Calculate::stringToNum<double>(spacing)*pow(10, -9));
					i_y = 0.5*h - y / 30 * 0.1*h;
					i_y = i_y > 0.9*h ? 0.9*h : i_y;
					dc->DrawLine(wxPoint(i_x_o, i_y_o), wxPoint(i_x, i_y));
					i_x_o = i_x;
					i_y_o = i_y;
				}
			}
			else {
				//未获得正确输入
				dc->DrawText(_T("信号二：输入错误"), wxPoint(5, 25));
			}
		}
		else {
			//nothing to do
			dc->DrawText(_T("信号二：未选择类型"), wxPoint(5, 25));
		}
	}
}