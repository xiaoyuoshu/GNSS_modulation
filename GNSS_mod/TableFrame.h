#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
//表格窗口
class TableFrame : public wxFrame
{
public:
	wxGrid* grid;
	//表格框架
	TableFrame(const wxString & title);
	//退出函数
	void OnQuit(wxCommandEvent & event);
	//保存表格函数
	void SaveTable();
};