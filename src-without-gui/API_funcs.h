#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <iomanip>
#include "OptSys.h"


#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif
using namespace std;

void cal_res(double a,int nsf, double *dists,double *rs,double * nfs, double * nds,double *ncs,double l,double y_or_W, vector<double> &res )
{

	OptSys sys(a,nsf,dists,rs,nds);
	res.push_back(sys.get_f()); // f'
	res.push_back(sys.get_lH()); // lH'
	res.push_back(sys.get_lp()); // lp'
	Ray rayout;
	
	FPR ray1(l);
	FRR ray2(l);

	rayout=sys.ray_tracing(ray1);
	res.push_back(rayout.get_l()); // ld0'
	rayout=sys.ray_tracing(ray2); 
	res.push_back(rayout.get_l()); // ld'
	rayout=sys.ray_tracing(ray2,0.7);
	res.push_back(rayout.get_l()); // lud'

	res.push_back(sys.cal_y0(l,y_or_W)); // yd0'

	res.push_back(sys.cal_y0(l,y_or_W,1,0.7)); // ywd0'

	res.push_back(sys.cal_y(l,y_or_W)); // yd'

	res.push_back(sys.cal_y(l,y_or_W,1,0.7)); // ywd'

	OptSys sys_f(a,nsf,dists,rs,nfs,nds);
	rayout=sys_f.ray_tracing(ray1);
	res.push_back(rayout.get_l()); // lf0'
	rayout=sys_f.ray_tracing(ray2);
	res.push_back(rayout.get_l()); // lf'
	rayout=sys_f.ray_tracing(ray2,0.7);
	res.push_back(rayout.get_l()); // luf'

	res.push_back(sys_f.cal_y0(l,y_or_W)); // yf0'

	res.push_back(sys_f.cal_y0(l,y_or_W,1,0.7)); // ywf0'

	res.push_back(sys_f.cal_y(l,y_or_W)); // yf'

	res.push_back(sys_f.cal_y(l,y_or_W,1,0.7)); // ywf'

	OptSys sys_c(a,nsf,dists,rs,nfs,nds);
	rayout=sys_c.ray_tracing(ray1);
	res.push_back(rayout.get_l()); // lc0'
	rayout=sys_c.ray_tracing(ray2);
	res.push_back(rayout.get_l()); // lc'
	rayout=sys_c.ray_tracing(ray2,0.7);
	res.push_back(rayout.get_l()); // luc'

	res.push_back(sys_c.cal_y0(l,y_or_W)); // yc0'

	res.push_back(sys_c.cal_y0(l,y_or_W,1,0.7)); // ywc0'

	res.push_back(sys_c.cal_y(l,y_or_W)); // yc'

	res.push_back(sys_c.cal_y(l,y_or_W,1,0.7)); // ywc'

	res.push_back(sys.cal_SA(l)); // SA
	res.push_back(sys.cal_SA(l,0.7)); // SAu

	res.push_back(sys.cal_LCAx(nfs,ncs,l)); // LCAx
	res.push_back(sys.cal_LCAx(nfs,ncs,l,0.7)); // LCAXu
	res.push_back(sys.cal_LCAx(nfs,ncs,l,0)); // LCAxu0

	double * FCs=sys.cal_FCs(l,y_or_W,0);
	res.push_back(FCs[0]); // xt'
	res.push_back(FCs[1]); // xs'
	res.push_back(FCs[2]); // xts'

	double *Dt1s=sys.cal_Distortion(l,y_or_W);
	double *Dt2s=sys.cal_Distortion(l,y_or_W,1,0.7);

	res.push_back(Dt1s[0]); // adt (Absolute distortion)
	res.push_back(Dt2s[0]); // adtw
	res.push_back(Dt1s[1]); // rdt (Relutive distortion)
	res.push_back(Dt2s[1]); // rdtw

	res.push_back(sys.cal_Coma(l,y_or_W)); // coma1
	res.push_back(sys.cal_Coma(l,y_or_W,0.7)); // coma2
	res.push_back(sys.cal_Coma(l,y_or_W,1,0.7)); // coma3
	res.push_back(sys.cal_Coma(l,y_or_W,0.7,0.7)); // coma4


}





// 测试用
void cal_test()
{
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
	raytype="FRR";
	if(raytype=="FRR"){
		cout<<"First Actual Ray:"<<endl;
		FRR rayin1(-INF);
		Ray rayout1,rayout1_U;
		
		rayout1=sys.ray_tracing(rayin1,1,1,"FRR,rayout,inf ");
		rayout1.show_rayinfo();

		rayout1_U=sys.ray_tracing(rayin1,0.7,1,"FRR,rayout,inf,0.7U ");
		rayout1_U.show_rayinfo();

		FRR rayin2(l);
		Ray rayout2,rayout2_U;

		rayout2=sys.ray_tracing(rayin2,1,1,"FRR,rayout,finite ");
		rayout2.show_rayinfo();
		rayout2_U=sys.ray_tracing(rayin2,0.7,1,"FRR,rayout,finite,0.7U ");
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
	OptSys sys_f(a,nsf,dists,rs,nfs,nds);
	// sys_f.show_sysinfo();
	OptSys sys_c(a,nsf,dists,rs,ncs,nds);
	cout<<"Exit Ray :"<<endl;
	cout<<"Ideal image height -- inf -- nd -- "<<sys.cal_y0(-INF,3,1,1)<<endl;
	cout<<"Ideal image height -- inf -- nd -- 0.7W --  "<<sys.cal_y0(-INF,3,1,0.7)<<endl;

	cout<<"Ideal image height -- finite -- nd -- "<<sys.cal_y0(l,y,1,1)<<endl;
	cout<<"Ideal image height -- finite -- nd -- 0.7W --  "<<sys.cal_y0(l,y,1,0.7)<<endl;
	
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
	
	double *d1,*d2,*d3,*d4;
	d1=sys.cal_Distortion(-INF,3);
	d2=sys.cal_Distortion(-INF,3,1,0.7);
	d3=sys.cal_Distortion(l,y);
	d4=sys.cal_Distortion(l,y,1,0.7);

	cout<<"Absolute Distortion -- inf -- "<<d1[0]<<endl;
	cout<<"Relative Distortion -- inf -- "<<d1[1]<<endl;

	cout<<"Absolute Distortion -- inf -- 0.7W -- "<<d2[0]<<endl;
	cout<<"Relative Distortion -- inf -- "<<d2[1]<<endl;

	cout<<"Absolute Distortion -- finite -- "<<d3[0]<<endl;
	cout<<"Relative Distortion -- finite -- "<<d3[1]<<endl;

	cout<<"Absolute Distortion -- finite -- 0.7W -- "<<d4[0]<<endl;
	cout<<"Relative Distortion -- finite -- "<<d4[1]<<endl;


	cout<<"Spheroical Aberration -- inf -- "<<sys.cal_SA(-INF,1)<<endl;
	cout<<"Spheroical Aberration -- inf -- 0.7U -- "<<sys.cal_SA(-INF,0.7)<<endl;

	cout<<"Spheroical Aberration -- finite -- "<<sys.cal_SA(l,1)<<endl;
	cout<<"Spheroical Aberration -- finite -- 0.7U -- "<<sys.cal_SA(l,0.7)<<endl;


	cout<<"Lateral Chromatic Aberration -- inf -- Aperture 0 -- "<<sys.cal_LCAx(nfs,ncs,-INF,0)<<endl;
	cout<<"Lateral Chromatic Aberration -- inf -- Aperture 0.7 -- "<<sys.cal_LCAx(nfs,ncs,-INF,0.7)<<endl;
	cout<<"Lateral Chromatic Aberration -- inf -- Aperture 1 -- "<<sys.cal_LCAx(nfs,ncs,-INF,1)<<endl;
	cout<<"Lateral Chromatic Aberration -- finite -- Aperture 0 -- "<<sys.cal_LCAx(nfs,ncs,l,0)<<endl;
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

	cout<<"Coma -- inf -- 0.7W -- "<<sys.cal_Coma(-INF,W,1,0.7)<<endl;
	cout<<"Coma -- finite -- 0.7W -- "<<sys.cal_Coma(l,y,1,0.7)<<endl;

	cout<<"Coma -- inf -- 0.7U -- "<<sys.cal_Coma(-INF,W,0.7,1)<<endl;
	cout<<"Coma -- finite -- 0.7U -- "<<sys.cal_Coma(l,y,0.7,1)<<endl;

	cout<<"Coma -- inf -- 0.7U&0.7W -- "<<sys.cal_Coma(-INF,W,0.7,0.7)<<endl;
	cout<<"Coma -- finite -- 0.7U&0.7W -- "<<sys.cal_Coma(l,y,0.7,0.7)<<endl;


	double *FC1, *FC2;

	FC1=sys.cal_FCs(-INF,W);
	FC2=sys.cal_FCs(l,y);
	cout<<"Field Curvature -- inf -- "<<"xt-- "<<FC1[0]<<" xs-- "<<FC1[1]<<endl;
	cout<<"Astigmatism -- inf -- "<<FC1[2]<<endl;
	

	cout<<"Field Curvature -- finite -- "<<"xt-- "<<FC2[0]<<" xs-- "<<FC2[1]<<endl;
	cout<<"Astigmatism -- finite -- "<<FC2[2]<<endl;


}

