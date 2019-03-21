//计算类头文件
#include <sstream> 
#include <math.h>
//定义π
#define PI 3.14159265358979323846
class Calculate {
public:
	//字符串转数字辅助函数
	template <class Type>
	Type static stringToNum(const std::string& str)
	{
		istringstream iss(str);
		Type num;
		iss >> num;
		return num;
	}

	/*
	boc调制的功率谱密度
	f:频率点，单位为Hz
	fs：子载波频率，单位为Hz
	fc：扩频码速率，单位为Hz
	return：f频率的功率谱密度
	*/
	double static boc_f(double f, double fs, double fc);

	/*
	bpsk调制的功率谱密度
	f:频率点，单位为Hz
	fc：扩频码速率，单位为Hz
	return：f频率的功率谱密度
	*/
	double static bpsk_f(double f, double fc);

	/*
	boc调制带限后的剩余功率
	fs：子载波频率，单位为Hz
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的剩余功率
	*/
	double static boc_lamda(double fs, double fc, double beta);

	/*
	bpsk调制带限后的剩余功率
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的剩余功率
	*/
	double static bpsk_lamda(double fc, double beta);

	/*
	boc调制带限后的均方根带宽
	fs：子载波频率，单位为Hz
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的均方根带宽
	*/
	double static boc_brms(double fs, double fc, double beta);

	/*
	bpsk调制带限后的均方根带宽
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的有效矩形带宽
	*/
	double static bpsk_brms(double fc, double beta);

	/*
	boc调制带限后的有效矩形带宽
	fs：子载波频率，单位为Hz
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的有效矩形带宽
	*/
	double static boc_brect(double fs, double fc, double beta);
	
	/*
	bpsk调制带限后的有效矩形带宽
	fs：子载波频率，单位为Hz
	fc：扩频码速率，单位为Hz
	beta：接收机带宽
	return：beta带限后的有效矩形带宽
	*/
	double static bpsk_brect(double fc, double beta);

	/*
	boc为干扰信号时，对boc调制的频谱隔离系数
	fs：接收信号子载波频率
	fc：接收信号扩频码速率
	beta：接收带宽
	fs_a：干扰信号子载波频率
	fc_a：干扰信号扩频码速率
	betat：发射机带宽
	return：boc为干扰信号时，对boc调制的频谱隔离系数
	*/
	double static boc_boc_kls(double fs, double fc, double beta, double fs_a, double fc_a,double betat);

	/*
	bpsk为干扰信号时，对boc调制的频谱隔离系数
	fs：接收信号子载波频率
	fc：接收信号扩频码速率
	beta：接收带宽
	fc_a：干扰信号扩频码速率
	betat：发射机带宽
	return：bpsk为干扰信号时，对boc调制的频谱隔离系数
	*/
	double static boc_bpsk_kls(double fs, double fc, double beta, double fc_a, double betat);

	/*
	boc为干扰信号时，对bpsk调制的频谱隔离系数
	fc：接收信号扩频码速率
	beta：接收带宽
	fs_a：干扰信号子载波频率
	fc_a：干扰信号扩频码速率
	betat：发射机带宽
	boc为干扰信号时，对bpsk调制的频谱隔离系数
	*/
	double static bpsk_boc_kls(double fc, double beta, double fs_a, double fc_a, double betat);
	
	/*
	pskc为干扰信号时，对bpsk调制的频谱隔离系数
	fc：接收信号扩频码速率
	beta：接收带宽
	fc_a：干扰信号扩频码速率
	betat：发射机带宽
	bpsk为干扰信号时，对bpsk调制的频谱隔离系数
	*/
	double static bpsk_bpsk_kls(double fc, double beta, double fc_a, double betat);
	
	/*
	计算boc调制自相关函数
	t：自相关时间，单位为s
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：t时间时的自相关函数
	*/
	double static boc_autocorrelation(double t, double fs, double fc, double beta);
	
	/*
	计算bpsk调制自相关函数
	t：自相关时间，单位为s
	fc：扩频码速率
	beta：接收机带宽
	return：t时间时的自相关函数
	*/
	double static bpsk_autocorrelation(double t, double fc, double beta);
	
	/*
	计算boc调制功率谱主瓣的最大频偏
	fs：boc子载波频率
	fc：boc扩频码速率
	return：boc调制功率谱主瓣的最大频偏
	*/
	double static boc_frequency_offset(double fs, double fc, double beta);
	
	/*
	计算boc调制的最大功率谱密度
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：boc调制的最大功率谱密度
	*/
	double static boc_maxf(double fs, double fc, double beta);
	
	/*
	计算bpsk调制的最大功率谱密度
	fc：扩频码速率
	beta：接收机带宽
	return：bpsk调制的最大功率谱密度
	*/
	double static bpsk_maxf(double fc, double beta);
	
	/*
	计算boc90%功率的带宽
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：boc90%功率的带宽
	*/
	double static boc_beta_90(double fs, double fc, double beta);
	
	/*
	计算bpsk90%功率的带宽
	fc：扩频码速率
	beta：接收机带宽
	return：bpsk90%功率的带宽
	*/
	double static bpsk_beta_90(double fc, double beta);
	
	/*
	计算boc的带外损失
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：boc的带外损失
	*/
	double static boc_beta_loss(double fs, double fc, double beta);
	
	/*
	计算bpsk的带外损失
	fc：扩频码速率
	beta：接收机带宽
	return：bpsk的带外损失
	*/
	double static bpsk_beta_loss(double fc, double beta);
	
	/*
	计算boc自相关函数主峰与第一副峰的时延
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：boc自相关函数主峰与第一副峰的时延
	*/
	double static boc_autocorrelation_delay(double fs, double fc, double beta);

	/*
	计算boc自相关函数副峰与第一主峰的幅度平方之比
	delay：boc自相关函数主峰与第一副峰的时延
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	return：boc自相关函数副峰与第一主峰的幅度平方之比
	*/
	double static boc_autocorrelation_amplitude_ratio(double delay, double fs, double fc, double beta);
	
	/*
	画boc调制-NELP方差-间隔图形，默认载噪比固定
	delta：超前滞后本地码间隔
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	tco：鉴相器相关积分时间
	return：返回boc调制对应输入的超前滞后本地码间隔的码跟踪误差
	*/
	double static boc_NELP_delta(double delta, double fs, double fc, double beta, double tco);
	
	/*
	画boc调制-NELP方差-载噪比图形，超前滞后本地码间隔由输入确定
	delta：超前滞后本地码间隔
	cn：载噪比
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	tco：鉴相器相关积分时间
	return：返回boc调制对应输入的载噪比的码跟踪误差
	*/
	double static boc_NELP_CN0(double delta, double cn0, double fs, double fc, double beta,double tco);
	
	/*
	画bpsk调制-NELP方差-间隔图形，默认载噪比固定
	delta：超前滞后本地码间隔
	fc：扩频码速率
	beta：接收机带宽
	tco：鉴相器相关积分时间
	return：返回boc调制对应输入的超前滞后本地码间隔的码跟踪误差
	*/
	double static bpsk_NELP_delta(double delta, double fc, double beta, double tco);
	
	/*
	画bpsk调制-NELP方差-载噪比图形，超前滞后本地码间隔由输入确定
	delta：超前滞后本地码间隔
	cn：载噪比
	fc：扩频码速率
	beta：接收机带宽
	tco：鉴相器相关积分时间
	return：返回boc调制对应输入的载噪比的码跟踪误差
	*/
	double static bpsk_NELP_CN0(double delta, double cn0, double fc, double beta, double tco);
	
	/*
	画boc调制多径误差包络图形（多径反射信号相对于直达信号的相位为2π的偶数倍）
	t：多径时延
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	delta：超前滞后本地码间隔
	*/
	double static boc_multipath_error_Pos(double t, double fs, double fc, double beta, double delta);
	
	/*
	画boc调制多径误差包络图形（多径反射信号相对于直达信号的相位为2π的奇数倍）
	t：多径时延
	fs：子载波频率
	fc：扩频码速率
	beta：接收机带宽
	delta：超前滞后本地码间隔
	*/
	double static boc_multipath_error_Neg(double t, double fs, double fc, double beta, double delta);

	/*
	画bpsk调制多径误差包络图形（多径反射信号相对于直达信号的相位为2π的偶数倍）
	t：多径时延
	fc：扩频码速率
	beta：接收机带宽
	delta：超前滞后本地码间隔
	*/
	double static bpsk_multipath_error_Pos(double t, double fc, double beta, double delta);

	/*
	画bpsk调制多径误差包络图形（多径反射信号相对于直达信号的相位为2π的奇数倍）
	t：多径时延
	fc：扩频码速率
	beta：接收机带宽
	delta：超前滞后本地码间隔
	*/
	double static bpsk_multipath_error_Neg(double t, double fc, double beta, double delta);
};