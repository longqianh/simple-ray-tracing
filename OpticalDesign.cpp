#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "Ray.h"
#include "Lens.h"
using namespace std;

int Lens::len_num=1;

class OptErr
{
public:
	OptErr(){}
	~OptErr(){
	}
		
};


class OptSys
{
private:
	int	nsf;
	// Surface sf[nsf];
	// Surface * sf=new Surface [nsf];
	// Surface *sf[nsf];
	

	// vector<int> dist;
	// vector<Lens> lens;


public:

	Surface *sf;

	OptSys(int sf_num,double *dists,double * rs){
		nsf=sf_num;
		sf=new Surface[nsf];
		for(int i=0;i<nsf;i++){
			sf[i].set_d(dists[i]);
			sf[i].set_rho(rs[i]);
		}


	}
	~OptSys()
	{
		delete [] sf;
	}

	// void init_sf(double * dists,double * rs){
	// 	Surface sf1[nsf];

	// 	for (int i = 0; i < nsf; i++)
	// 	{
	// 		sf1[i].set_rho(rs[i]);
	// 		sf1[i].set_d(dists[i]);
	// 	}
	// 	sf=sf1;
	// }

	void show_sflist(){
		// cout<<'#'<<sf[0].get_rho()<<endl;


		for(int i=0;i<nsf;i++){
			cout<<i+1<<" th surface: ";
			double rho=sf[i].get_rho();
			double thick=sf[i].get_d();
			if(rho==0){
				cout<<"radius--"<<"∞"<<" , distance to the next surface--"<<thick<<endl;				
			}
			else{
				cout<<"radius--"<<1/rho<<" , distance to the next surface--"<<thick<<endl;
			}

		}
	}
	// void init_dist(double * dists){
		
	// 	for(int i=1;i<dists[int(dists[0])];i++){
	// 		dist.push_back(dists[i]);
	// 	}
	// }

	// void init_lens(double paras[][2],int n){
	// 	for(int i=0;i<n;i++){
	// 		Lens len;

	// 		lens.push_back(tmp);
	// 	}

	// }


	// void set_para(double *sys_paras,double len_paras[][2]){		
	// 	init_dist(sys_paras);
	// 	// init_lens()
	// }

	// int get_lens_num(){
	// 	return lens.size();
	// }

	

	// Ray get_sysrayout(Ray rayin){
	// 	Ray sysrayout;
	// 	return sysrayout;
	// }
	double cal_f(Ray rayin){
		double U=rayin.get_U();
		double l=rayin.get_l();
		if(l>1e7){
			;
		}
		return 0;
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
	int nsf=3;
	// double *dists=new double [nsf];
	// for()
	// double dists[nsf];
	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	OptSys sys(nsf,dists,rs);
	sys.show_sflist();
	
	// cout<<&sys.sf[1]<<endl;
	// printf("%lf\n",sys.sf[2].get_rho() );
	// sys.init_sf(dists,rs);
	
	// cout<<sys.sf[1].get_rho()<<endl;
	// cout<<sys.sf[2].get_rho()<<endl;

	// sys.show_sflist();
	// Ray rayin(1,2);
	// double f=sys.cal_f(rayin);




	// double U=10,l=-10;


	// Ray rayin;
	// rayin.set_para(U,l);

	// // OptSys optsys;
	// Lens len;
	// Lens len2;
	// cout<<Lens::len_cnt<<endl;
	// optsys.set_para(sys_paras,len_paras);

	// optsys.set_para(testdists,dist_num);
	// Lens len1;

	// Surface sf(5);
	// double rho=sf.get_rho();
	// double n=sf.get_n();
	// cout<<rho<<' '<<n<<endl;

	// Lens len1;
	// Lens len2;
	// len1.get_name();
	// len2.get_name();
	// double rhos[]={1,4,2,3};
	// double nds[]={1.1,1.3,1.5,3};

	// SingleLen sglen(rhos,nds,4);
	// cout<<sglen.get_sfnum()<<endl;
	// Ray myray(1,3);
	// DoubleLen dblen(rhos,nds,4);
	// cout<<dblen.get_sfnum()<<endl;
	// TriLen trilen(rhos,nds,4);
	// Surface sf1=trilen.get_sf(2);
	// cout<<sf1.get_rho()<<endl;
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