#include<iostream>
#include<vector>
#include <string.h>
#include "Lens.h"
using namespace std;

class OptErr
{
public:
	OptErr();
	~OptErr();
		
};





class OptSys
{
private:
	vector<int> dist;
	vector<Lens> lens;



public:

	void init_dist(double * dists){
		
		for(int i=1;i<dists[int(dists[0])];i++){
			dist.push_back(dists[i]);
		}
	}

	void init_lens(double paras[][2],int n){
		for(int i=0;i<n;i++){
			Lens len;
			
			lens.push_back(tmp);
		}

	}


	void set_para(double *sys_paras,double len_paras[][2]){		
		init_dist(sys_paras);
		// init_lens()
	}
	void help(){
		;
	}


	

	int get_lens_num(){
		return lens.size();
	}

	

	Ray get_sysrayout(Ray rayin){
		Ray sysrayout;
		return sysrayout;
	}

	void cal_opt_errs(){
		;
	}

	void show_structure(){
		;
		// add optical structures in the form of matrix optics
	}

};




int main()
{
	double U=10,l=-10;


	double sys_paras[2]={1,10};// dist_num, dists
	double len_paras[2][2];

	Ray rayin;
	rayin.set_para(U,l);

	OptSys optsys;
	optsys.set_para(sys_paras,len_paras);

	// optsys.set_para(testdists,dist_num);
	// Lens len1;


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