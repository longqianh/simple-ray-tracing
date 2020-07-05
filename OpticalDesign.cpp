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



string raytype;



void cal_test(){
	double ku=1,kw=1;
	int nsf=3;
	double a=20;
	bool isINF;
	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	double nds[]={1.5167969495,1.6727015725,1};
	double l=-500; // 物距：用户输入 左负右正
	double y=26; // 像高 ：上正下负
	double W=3; // 物方视场角：用户输入
	OptSys sys(a,nsf,dists,rs,nds);
	sys.show_sysinfo();
	cout<<endl;

	raytype="FPR";

	if(raytype=="FPR"){


		cout<<"First Paraxial Ray:"<<endl;
		FPR rayin1;
		
		isINF=true;
		Ray rayout1;
		
		rayout1=sys.ray_tracing(rayin1,isINF,"FPR,rayout,inf");

		rayout1.show_rayinfo();

		FPR rayin2;
		isINF=false;
		Ray rayout2;
		rayin2.set_l(l);
		
		rayout2=sys.ray_tracing(rayin2,isINF,"FPR,rayout,finite");
		rayout2.show_rayinfo();
	}
	
	cout<<endl;
	raytype="SPR";
	if(raytype=="SPR"){
		cout<<"Second Paraxial Ray:"<<endl;
		double W=3;
		Ray rayout1;
		
		SPR rayin1("SPR,inf");

		rayin1.set_W(W);
		rayin1.set_l(0);
		isINF=true;
		
		rayout1=sys.ray_tracing(rayin1,isINF,"SPR,rayout,inf ");
		rayout1.show_rayinfo();
	
		isINF=false;
		Ray rayout2("SPR,rayout,finite length ");

		SPR rayin2("SPR,inf");
		rayin2.set_W(W);
		rayin2.set_l(0);

		rayin2.set_l1(l);
		rayin2.set_y(y);
		rayout2=sys.ray_tracing(rayin2,isINF,"SPR,rayout,finite");
		rayout2.show_rayinfo();
	}

	cout<<endl;
	raytype="FAR";
	if(raytype=="FAR"){
		cout<<"First Actual Ray:"<<endl;
		FAR rayin1;
		isINF=true;
		Ray rayout1;
		
		rayout1=sys.ray_tracing(rayin1,isINF,"FAR,rayout,inf ");
		rayout1.show_rayinfo();


		FAR rayin2;
		isINF=false;
		Ray rayout2;
		rayin2.set_l(l);
		rayout2=sys.ray_tracing(rayin2,isINF,"FAR,rayout,finite ");
		rayout2.show_rayinfo();

	}

	cout<<endl;
	raytype="SAR";
	if(raytype=="SAR")
	{
		cout<<"Second Actual Ray"<<endl;
		SAR rayin_up("up"),rayin_cf("cf"),rayin_dn("dn");
		
		isINF=true;
		Ray rayout_up1,
		rayout_cf1,
		rayout_dn1;

		rayin_up.set_W(W);
		rayin_cf.set_W(W);
		rayin_dn.set_W(W);
		rayout_up1=sys.ray_tracing(rayin_up,isINF,"SAR,up-rayout,inf");
		rayout_cf1=sys.ray_tracing(rayin_cf,isINF,"SAR,chief-rayout,inf");
		rayout_dn1=sys.ray_tracing(rayin_dn,isINF,"SAR,down-rayout,inf");
		rayout_up1.show_rayinfo();
		rayout_cf1.show_rayinfo("cf");
		rayout_dn1.show_rayinfo();

		cout<<endl;


		isINF=false;
		rayin_up.set_y(y);
		rayin_cf.set_y(y);
		rayin_dn.set_y(y);
		rayin_up.set_l1(l);
		rayin_cf.set_l1(l);
		rayin_dn.set_l1(l);

		Ray rayout_up2,rayout_cf2,rayout_dn2;

		rayout_up2=sys.ray_tracing(rayin_up,isINF,"SAR,up-rayout,finite ");
		rayout_cf2=sys.ray_tracing(rayin_cf,isINF,"SAR,chief-rayout,finite ");
		rayout_dn2=sys.ray_tracing(rayin_dn,isINF,"SAR,down-rayout,finite ");
		rayout_up2.show_rayinfo();
		rayout_cf2.show_rayinfo("cf");
		rayout_dn2.show_rayinfo();
	}
	cout<<endl;
	cout<<sys.cal_y0(l,y)<<endl;
	cout<<sys.cal_y(l,y)<<endl;
	

	double *d;
	d=sys.cal_Distortion(l,y);
	// d=sys.cal_Distortion(l,y);
	cout<<d[0]<<" "<< d[1]<<endl;

	cout<<"SA "<<sys.cal_SA(l,false,0.7)<<endl;


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

