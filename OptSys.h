#pragma once
#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <iomanip>
#include "Ray.h"
#include "Surface.h"
using namespace std;

#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif

class OptSys
{
private:
	int	nsf=0; // 系统面数
	int a=0; // 入瞳直径
	double f=0; // 系统焦距
	double lH=0; // 像方主面位置（相对最后一面）
	double lp=0; // 出瞳距
	// double lH0; // 物方主面位置（相对第一面） 需使用set方法设置

public:

	Surface* sf = nullptr;
	double* dists = nullptr;
	double* rs = nullptr;
	double* ns = nullptr;
	double* nds = nullptr; // F、C系统所依附的主系统参数

	OptSys(){}
	OptSys(int a, int nsf, double* dists, double* rs, double* ns, double* nds = nullptr) {

		if (nds != nullptr) {
			this->nds = new double[nsf];
		}
		else {
			this->nds = nullptr;
		}
		this->a = a;
		this->nsf = nsf;
		sf = new Surface[nsf];
		this->dists = new double[nsf];
		this->rs = new double[nsf];
		this->ns = new double[nsf];
		for (int k = 0; k < nsf; k++) {
			sf[k].set_d(dists[k]);
			sf[k].set_rho(rs[k]);
			sf[k].set_n(ns[k]);
			this->dists[k] = dists[k];
			this->rs[k] = rs[k];
			this->ns[k] = ns[k];
			if (nds != nullptr) {
				this->nds[k] = nds[k];
			}

		}

		this->init_sys();


	}

	~OptSys()
	{
		delete[] sf;
		delete[] dists;
		delete[] rs;
		delete[] ns;
		if (nds != nullptr) {
			delete[] nds;
		}
		// delete [] SAs;
	}


	double get_f() const { return f; }
	double get_lH() const { return lH; }
	double get_lp() const { return lp; }
	double get_a() const { return a; }
	int get_nsf() const { return nsf; }
	void set_sys(int a, int nsf, double* dists, double* rs, double* ns, double* nds = nullptr);
	void show_sflist();
	void show_sysinfo();
	void init_sys();

	Ray ray_tracing(FPR rayin, double ku = 1, double kw = 0, string info = "First Paraxial Ray-tracing"); // 可以去掉kw
	Ray ray_tracing(SPR rayin, double ku = 1, double kw = 1, string info = "Second Paraxial Ray-tracing");
	Ray ray_tracing(FRR rayin, double ku = 1, double kw = 0, string info = "First Actual Ray-tracing");
	SAR ray_tracing(SAR rayin, double ku = 1, double kw = 1, string info = "Second Actual Ray-tracing");
	
	double cal_y0(double l, double y_or_W, double ku = 1, double kw = 1);
	double cal_y(double l, double y_or_W, double ku = 1, double kw = 1);
	double cal_SA(double l, double ku = 1);
	double* cal_DT(double l, double y_or_W, double ku = 1, double kw = 1);
	double cal_LCAx(double* nfs, double* ncs, double l, double ku = 1); // Lateral Chromatic Aberration
	double cal_LCAy(double* nfs, double* ncs, double l, double y_or_W, double kw = 1); // Longitudinal Chromatic Aberration
	double* cal_FCs(double l, double y_or_W, double ku = 1, double kw = 1); // Field Curvature and Astigmatism
	double cal_Coma(double l, double y_or_W, double ku = 1, double kw = 1);
	void cal_allres(vector<double>& res, double l, double y_or_W, double* nfs, double* ncs);
	// 获得绘像差图所需的数据
	//double* get_SAs(double l, double interval = 0.01); //球差曲线～随孔径变化的球差
	//double* get_DTs(double l, double y_or_W, double interval = 0.01); // 相对畸变曲线～随视场变化的相对畸变
	//double* get_LCAxs(double* nfs, double* ncs, double l, double interval = 0.01); // 位置色差曲线～随孔径变化的位置色差
	//double* get_LCAys(double* nfs, double* ncs, double l, double y_or_W, double interval = 0.01); // 倍率色差曲线～随视场变化的倍率色差	
	//double* get_ATMs(double l, double y_or_W, double interval = 0.01); // 像散曲线～随视场变化的像散
	


};


