#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "Ray.h"
#include "Lens.h"
using namespace std;

#ifndef PI
#define PI 3.1415926535898
#endif
#ifndef INF
#define INF 1e7
#endif

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
	int a; // 入瞳直径
	

public:

	Surface *sf;
	OptSys(){}
	OptSys(int a,int nsf,double *dists,double * rs,double *nds){
		
		this->a=a;
		this->nsf=nsf;

		sf=new Surface[nsf];
		for(int i=0;i<nsf;i++){
			sf[i].set_d(dists[i]);
			sf[i].set_rho(rs[i]);
			sf[i].set_nd(nds[i]);
		}


	}
	~OptSys()
	{
		delete [] sf;
	}

	void show_syspara(){}

	void show_sflist(){

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




	// 利用多态
	Ray ray_tracing(FAL rayin){
		Ray rayout;
		// u1:u, u2:u'
		double u1=rayin.get_U();
		double u2;
		double l1,l2;
		double i;
		double n2,n1=1;// n2:n', n1:n

		// u1=sin(u1*PI/180); // u1较大时 会影响tan
		// cout<<"# u1 # "<<u1<<endl;
		l1=-a/tan(u1*PI/180);
		// cout<<"# l1 # "<<l1<<endl;
		rayin.set_l(l1);
		// cout<<"# l1 # "<<l1<<endl;

		for(int k=0;k<nsf;k++){
			double d=sf[k].get_d(); //cout<<"# "<<d<<endl;
			double rho;
			// cout<<"# l1 # "<<l1<<endl;
			if(k==0&&l1<-INF){
					i=a*sf[0].get_rho(); 
					rayin.set_i(i);	
				
			}
			else{
				// cout<<"# l1 # "<<l1<<endl;
				rho=sf[k].get_rho();
				// cout<<"# rho # "<<rho<<endl;
				// cout<<"# l1 # "<<l1<<endl;
				// cout<<"# u1 # "<<u1<<endl;
				i=(rho*l1-1)*u1; //cout<<"# i # "<<i<<endl;
				if(k==0){rayin.set_i(i);}
				
			}

			n2=sf[k].get_nd();
			u2=(n2-n1)/n2*i+u1;

			l2=(i+u1)/(u2*rho);

			
			l1=l2-d;
			n1=n2; // n1是n2前面的折射率
			u1=u2;
			cout<<l1<<endl;

		}

		// cout<<"#"<<u2*180/PI<<endl;
		double u2_angle=u2*180/PI-360*int((u2*180/PI)/360);
		rayout.set_U(u2_angle);
		rayout.set_l(l2);

		// 判断ray类型

		return rayout;
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
	double a=20;

	// double *dists=new double [nsf];
	// for()
	// double dists[nsf];

	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	double nds[]={1.5,1.4,1};
	OptSys sys(a,nsf,dists,rs,nds);
	// sys.show_sflist();

	FAL rayin(30);
	Ray rayout=sys.ray_tracing(rayin);
	rayout.show_rayinfo()
;


	
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