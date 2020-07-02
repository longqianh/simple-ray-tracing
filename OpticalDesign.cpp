#include<iostream>
#include "Lens.h"
using namespace std;


class OptSys
{
public:
	void help(){
		;
	}
	void show_structure(){
		;
		// add optical structures in the form of matrix optics
	}

	void get_lens_num(){
		;
	}

	
	Ray get_sysrayout(){
		Ray sysrayout;
		return sysrayout;
	}

};







int main()
{
	Ray rayin;
	// rayin.help();
	// rayin.ray_setting(20,-5,5.33);
	// rayin.print_para();
	// Lens len1;
	// cout<<rayin.vd<<endl;
	return 0;

}

// 软件基本功能模块划分
// I/O：键盘输入、文件输入、屏幕输出、文件输出
// 光线追迹：近轴光线、子午面内实际光线、沿主光线的细光束像点计算
// 初始参数生成
// 像差计算
// 模块之间的调用关系

// 外部参数：物体位置l、物体高度y、孔径U、视场W
// 注意考虑无穷远和有限距离两种情况
// 内部参数：k个面
// k个曲率半径r、k-1个间距d、孔阑位置lp1(光阑放在第一面)