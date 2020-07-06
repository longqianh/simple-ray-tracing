#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <iomanip>
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







void cal_test(){
	double ku=1,kw=1;
	int nsf=3;
	double a=20;
	bool isINF;
	string raytype;
	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	double nfs[]={1.5223709191,1.6875154791,1};
	double nds[]={1.5167969495,1.6727015725,1};
	double ncs[]={1.5143226707,1.6666104143,1};
	
	double l=-500; // 物距：用户输入 左负右正
	double y=26; // 像高 ：上正下负
	double W=3; // 物方视场角：用户输入
	OptSys sys(a,nsf,dists,rs,nds);


	sys.show_sysinfo();
	cout<<setprecision(7)<<endl; // 控制保留7位有效数字

	raytype="FPR";

	if(raytype=="FPR"){

		cout<<"First Paraxial Ray:"<<endl;
		FPR rayin1(-INF);
		Ray rayout1;
		rayout1=sys.ray_tracing(rayin1,1,1,"FPR,rayout,inf");
		rayout1.show_rayinfo();

		FPR rayin2(l);
		Ray rayout2;
		
		rayout2=sys.ray_tracing(rayin2,1,1,"FPR,rayout,finite");
		rayout2.show_rayinfo();
	}
	
	cout<<endl;
	raytype="SPR";
	if(raytype=="SPR")
	{
		cout<<"Second Paraxial Ray:"<<endl;
		Ray rayout1,rayout1_W;
		
		SPR rayin1(-INF,3);
		
		rayout1=sys.ray_tracing(rayin1,1,1,"SPR,rayout,inf ");
		rayout1.show_rayinfo();

		rayout1_W=sys.ray_tracing(rayin1,1,0.7,"SPR,rayout,inf,0.7W ");
		rayout1_W.show_rayinfo();
	
		Ray rayout2;

		SPR rayin2(l,y);
	
		rayout2=sys.ray_tracing(rayin2,1,1,"SPR,rayout,finite");
		rayout2.show_rayinfo();
	}

	cout<<endl;
	raytype="FAR";
	if(raytype=="FAR"){
		cout<<"First Actual Ray:"<<endl;
		FAR rayin1(-INF);
		Ray rayout1,rayout1_U;
		
		rayout1=sys.ray_tracing(rayin1,1,1,"FAR,rayout,inf ");
		rayout1.show_rayinfo();

		rayout1_U=sys.ray_tracing(rayin1,0.7,1,"FAR,rayout,inf,0.7U ");
		rayout1_U.show_rayinfo();

		FAR rayin2(l);
		Ray rayout2,rayout2_U;

		rayout2=sys.ray_tracing(rayin2,1,1,"FAR,rayout,finite ");
		rayout2.show_rayinfo();
		rayout2_U=sys.ray_tracing(rayin2,0.7,1,"FAR,rayout,finite,0.7U ");
		rayout2_U.show_rayinfo();
	}

	cout<<endl;
	raytype="SAR";
	if(raytype=="SAR")
	{
		cout<<"Second Actual Ray"<<endl;
		SAR rayin_up1(-INF,3,"up"),rayin_cf1(-INF,3,"cf"),rayin_dn1(-INF,3,"dn");
		
		Ray rayout_up1,rayout_cf1,rayout_dn1;

		rayout_up1=sys.ray_tracing(rayin_up1,1,1,"SAR,up-rayout,inf");
		rayout_cf1=sys.ray_tracing(rayin_cf1,1,1,"SAR,chief-rayout,inf");
		rayout_dn1=sys.ray_tracing(rayin_dn1,1,1,"SAR,down-rayout,inf");
		rayout_up1.show_rayinfo();
		rayout_cf1.show_rayinfo();
		rayout_dn1.show_rayinfo();

		cout<<endl;
		SAR rayin_up2(l,y,"up"),rayin_cf2(l,y,"cf"),rayin_dn2(l,y,"dn");

		Ray rayout_up2,rayout_cf2,rayout_dn2;

		rayout_up2=sys.ray_tracing(rayin_up2,1,1,"SAR,up-rayout,finite ");
		rayout_cf2=sys.ray_tracing(rayin_cf2,1,1,"SAR,chief-rayout,finite ");
		rayout_dn2=sys.ray_tracing(rayin_dn2,1,1,"SAR,down-rayout,finite ");
		rayout_up2.show_rayinfo();
		rayout_cf2.show_rayinfo();
		rayout_dn2.show_rayinfo();
	}

	cout<<endl;
	OptSys sys_f(a,nsf,dists,rs,nfs);
	OptSys sys_c(a,nsf,dists,rs,ncs);
	cout<<"Exit Ray :"<<endl;
	cout<<"Ideal image height -- inf -- nd -- "<<sys.cal_y0(-INF,3,1,1)<<endl;
	cout<<"Ideal image height -- inf -- nd -- 0.7W --  "<<sys.cal_y0(-INF,3,1,0.7)<<endl;
	
	cout<<"Ideal image height -- inf -- nf -- "<<sys_f.cal_y0(-INF,3,1,1)<<endl;
	cout<<"Ideal image height -- inf -- nf -- 0.7W --  "<<sys_f.cal_y0(-INF,3,1,0.7)<<endl;
	
	cout<<"Ideal image height -- inf -- nc -- "<<sys_c.cal_y0(-INF,3,1,1)<<endl;
	cout<<"Ideal image height -- inf -- nc -- 0.7W -- "<<sys_c.cal_y0(-INF,3,1,0.7)<<endl;

	cout<<"Ideal image height -- finite -- nd -- "<<sys.cal_y0(l,y,1,1)<<endl;
	cout<<"Ideal image height -- finite -- nd -- 0.7W --  "<<sys.cal_y0(-INF,3,1,0.7)<<endl;
	
	cout<<"Ideal image height -- finite -- nf -- "<<sys_f.cal_y0(l,y,1,1)<<endl;
	cout<<"Ideal image height -- finite -- nf -- 0.7W --  "<<sys_f.cal_y0(-INF,3,1,0.7)<<endl;
	
	cout<<"Ideal image height -- finite -- nc -- "<<sys_c.cal_y0(l,y,1,1)<<endl;
	cout<<"Ideal image height -- finite -- nc -- 0.7W -- "<<sys_c.cal_y0(l,y,1,0.7)<<endl;

	cout<<"Actual image height -- inf -- nd -- "<<sys.cal_y(-INF,3,1,1)<<endl;
	cout<<"Actual image height -- inf -- nd -- 0.7W -- "<<sys.cal_y(-INF,3,1,0.7)<<endl;

	cout<<"Actual image height -- inf -- nf -- "<<sys_f.cal_y(-INF,3,1,1)<<endl;
	cout<<"Actual image height -- inf -- nf -- 0.7W -- "<<sys_f.cal_y(-INF,3,1,0.7)<<endl;

	cout<<"Actual image height -- inf -- nc -- "<<sys_c.cal_y(-INF,3,1,1)<<endl;
	cout<<"Actual image height -- inf -- nc -- 0.7W -- "<<sys_c.cal_y(-INF,3,1,0.7)<<endl;

	cout<<"Actual image height -- finite -- nd -- "<<sys.cal_y(l,y,1,1)<<endl;
	cout<<"Actual image height -- finite -- nd -- 0.7W -- "<<sys.cal_y(l,y,1,0.7)<<endl;

	cout<<"Actual image height -- finite -- nf -- "<<sys_f.cal_y(l,y,1,1)<<endl;
	cout<<"Actual image height -- finite -- nf -- 0.7W -- "<<sys_f.cal_y(l,y,1,0.7)<<endl;

	cout<<"Actual image height -- finite -- nc -- "<<sys_c.cal_y(l,y,1,1)<<endl;
	cout<<"Actual image height -- finite -- nc -- 0.7W -- "<<sys_c.cal_y(l,y,1,0.7)<<endl;

	cout<<endl;
	cout<<"Aberrations : "<<endl;
	double *d1,*d2;
	d1=sys.cal_Distortion(-INF,3);
	// cout<<&d1<<endl;
	d2=sys.cal_Distortion(l,y);
	// cout<<&d2<<endl;
	cout<<"Absolute Distortion -- inf -- "<<d1[0]<<endl;
	cout<<"Relative Distortion -- inf -- "<<d1[1]<<endl;

	cout<<"Absolute Distortion -- finite -- "<<d2[0]<<endl;
	cout<<"Relative Distortion -- finite -- "<<d2[1]<<endl;


	cout<<"Spheroical Aberration -- inf -- "<<sys.cal_SA(-INF,1)<<endl;
	cout<<"Spheroical Aberration -- inf -- 0.7U -- "<<sys.cal_SA(-INF,0.7)<<endl;

	cout<<"Spheroical Aberration -- finite -- "<<sys.cal_SA(l,1)<<endl;
	cout<<"Spheroical Aberration -- finite -- 0.7U -- "<<sys.cal_SA(l,0.7)<<endl;


	// cout<<"Lateral Chromatic Aberration -- inf -- Aperture 0 -- "<<sys.cal_LCAx(nfs,ncs,-INF,0)<<endl;
	cout<<"Lateral Chromatic Aberration -- inf -- Aperture 0.7 -- "<<sys.cal_LCAx(nfs,ncs,-INF,0.7)<<endl;
	cout<<"Lateral Chromatic Aberration -- inf -- Aperture 1 -- "<<sys.cal_LCAx(nfs,ncs,-INF,1)<<endl;
	// cout<<"Lateral Chromatic Aberration -- finite -- Aperture 0 -- "<<sys.cal_LCAx(nfs,ncs,l,0)<<endl;
	cout<<"Lateral Chromatic Aberration -- finite -- Aperture 0.7 -- "<<sys.cal_LCAx(nfs,ncs,l,0.7)<<endl;
	cout<<"Lateral Chromatic Aberration -- finite -- Aperture 1 -- "<<sys.cal_LCAx(nfs,ncs,l,1)<<endl;

	// cout<<"Longitudinal Chromatic Aberration -- inf -- Aperture 0 -- "<<sys.cal_LCAy(nfs,ncs,-INF,3,0)<<endl;
	cout<<"Longitudinal Chromatic Aberration -- inf -- Aperture 0.7 -- "<<sys.cal_LCAy(nfs,ncs,-INF,3,0.7)<<endl;
	cout<<"Longitudinal Chromatic Aberration -- inf -- Aperture 1 -- "<<sys.cal_LCAy(nfs,ncs,-INF,3,1)<<endl;
	// cout<<"Longitudinal Chromatic Aberration -- finite -- Aperture 0 -- "<<sys.cal_LCAy(nfs,ncs,l,y,0)<<endl;
	cout<<"Longitudinal Chromatic Aberration -- finite -- Aperture 0.7 -- "<<sys.cal_LCAy(nfs,ncs,l,y,0.7)<<endl;
	cout<<"Longitudinal Chromatic Aberration -- finite -- Aperture 1 -- "<<sys.cal_LCAy(nfs,ncs,l,y,1)<<endl;

	cout<<"Coma -- inf -- "<<sys.cal_Coma(-INF,W)<<endl;
	cout<<"Coma -- finite -- "<<sys.cal_Coma(l,y)<<endl;

	double *FC1,*FC2;

	FC1=sys.cal_FCs(-INF,W);
	FC2=sys.cal_FCs(l,y);

	cout<<"Field Curvature -- inf -- "<<"t-- "<<FC1[0]<<"s--"<<FC1[1]<<endl;
	cout<<"Astigmatism -- inf -- "<<FC1[2]<<endl;
	
	cout<<"Field Curvature -- finite -- "<<"t-- "<<FC2[0]<<"s--"<<FC2[1]<<endl;
	cout<<"Astigmatism -- finite -- "<<FC2[2]<<endl;
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

// 优化：去掉isINF