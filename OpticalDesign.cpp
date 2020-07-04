#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "Ray.h"
#include "Lens.h"
#include "utils.h"
#include "OptSys.h"
using namespace std;

#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif



// double ku=1,kw=1,flag=0;
// double y;

string raytype;



class OptErr
{
public:
	OptErr(){}
	~OptErr(){
	}
		
};



void cal_test(){
	int nsf=3;
	double a=20;
	bool isINF;
	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	double nds[]={1.5167969495,1.6727015725,1};
	Ray rayout;
	OptSys sys(a,nsf,dists,rs,nds);
	sys.show_sysinfo();
	cout<<endl;

	raytype="FPR";

	if(raytype=="FPR"){

		cout<<"First Paraxial Ray:"<<endl;
		FPR rayin1;
		
		isINF=true;
		cout<<"Ray output for the ray incident from infinity:"<<endl;
		rayin1.set_U(0);
		rayout=sys.ray_tracing(rayin1,isINF);

		rayout.show_rayinfo();

		FPR rayin2;
		isINF=false;
		cout<<"Ray output for the ray incident from a limited distance:"<<endl;
		double l=-500;
		rayin2.set_l(l);
		rayin2.set_U(atan(a/l));
		rayout=sys.ray_tracing(rayin2,isINF);
		rayout.show_rayinfo();
	}
	
	cout<<endl;
	raytype="SPR";
	if(raytype=="SPR"){
		cout<<"Second Paraxial Ray:"<<endl;
		SPR rayin1;
		rayin1.set_l(0);
		isINF=true;
		cout<<"Ray output for the paraxial ray incident from infinity:"<<endl;
		double W=3;
		rayin1.set_W(Angle2Arc(W));
		rayout=sys.ray_tracing(rayin1,isINF);
		rayout.show_rayinfo();
	
		isINF=false;
		cout<<"Ray output for the paraxial ray incident from a limited distance:"<<endl;

		SPR rayin2;
		rayin1.set_l(0);
		double l=-500; // 物距
		double y=26; // 物高
		rayin2.set_l1(l);
		rayin2.set_y(y);
		rayout=sys.ray_tracing(rayin2,isINF);
		rayout.show_rayinfo();
	}

	cout<<endl;
	raytype="FAR";
	if(raytype=="FAR"){
		cout<<"First Actual Ray:"<<endl;
		FAR rayin1;
		isINF=true;
		cout<<"Ray output for the actual ray incident from infinity:"<<endl;
		
		rayin1.set_U(0);
		rayout=sys.ray_tracing(rayin1,isINF);
		rayout.show_rayinfo();


		FAR rayin2;
		isINF=false;
		double l=-500;
		rayin2.set_l(l);
		rayin2.set_U(asin(ku*sin(atan((a/2)/l))));
		rayout=sys.ray_tracing(rayin2,isINF);
		rayout.show_rayinfo();

	}

	cout<<endl;
	raytype="SAR";
	// if(raytype=="SAR"){
	// 	cout<<"Second Actual Ray:"<<endl;
		
	// 	SAR rayin1;
	// 	isINF=true;
	// 	cout<<"Ray output for the actual ray incident from infinity:"<<endl;
		
	// 	// rayin1.set_U(0);
		// rayout=sys.ray_tracing(rayin1,isINF);
		// rayout.show_rayinfo();


		// FAR rayin2;
		// isINF=false;
		// double l=-500;
		// rayin2.set_l(l);
		// rayin2.set_U(asin(ku*sin(atan((a/2)/l))));
		// rayout=sys.ray_tracing(rayin2,isINF);
		// rayout.show_rayinfo();

	// }

}





int main()
{
	cal_test();

	
	return 0;

}
// 备忘
// 输入正l 然后l=-l
// ku作为参数 而不是全局变量 避免干扰


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

// H开头：环保
// 
// MFC高