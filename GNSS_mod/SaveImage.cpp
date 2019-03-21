#include "MainFrame.h"

/*
	保存图形函数
	原理：将当前波形绘制在memoryDC连接的bitmap中，并保存成png图形
*/
void MainFrame::SaveImage() {
	int w = 0, h = 0;
	//获得面板大小
	imagePanel->GetSize(&w, &h);
	wxBitmap bitmap(w, h);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();
	wxMemoryDC *DC = &memDC;
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
	memDC.SelectObject(wxNullBitmap);
	wxInitAllImageHandlers();
	bitmap.SaveFile(_T("image.png"), wxBITMAP_TYPE_PNG);
}