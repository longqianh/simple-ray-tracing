#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "Ray.h"
#include "Lens.h"
#include "utils.h"
using namespace std;

#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif



double ku=1,kw=1,flag=0;
// double y;

string raytype;



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
	double f;
	double lH;
	

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
		this->init_sys();



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
				cout<<"radius -- "<<"∞"<<" , distance to the next surface -- "<<thick<<endl;				
			}
			else{
				cout<<"radius -- "<<1/rho<<" , distance to the next surface -- "<<thick<<endl;
			}

		}
	}

	void init_sys()
	{
		FPL rayin;
		Ray rayout;
		bool isINF=true;
		rayin.set_U(0);

		// rayin.show_rayinfo();
		rayout=this->ray_tracing(rayin,isINF);
		double u2=rayout.get_U();
		// cout<<u2<<endl;
		// cout<<tan(u2);
		f=(a/2)/abs(u2);
		lH=rayout.get_l()-f;
		// cout<<"Effective Focal Length -- "<<f<<endl;

	}

	void show_sysinfo()
	{
		cout<<"Optical System Parameters:"<<endl;
		cout<<"Surface Parameters:"<<endl;
		show_sflist();
		cout<<"Effective Focal Length -- "<<f<<endl;
		cout<<"Main Surface Distance -- "<<lH<<endl;

	}


	double get_f() const 
	{
		return f;
	}

	double get_lH() const 
	{
		return lH;
	}


	// 利用多态
	Ray ray_tracing(FPR rayin,bool isINF){
		double u1,u2; // u1:u, u2:u'
		double l1,l2;
		double i;
		double n2,n1=1;// n2:n', n1:n
		// string label=rayin.get_label();
		// cout<<"Rayin type: "<<label<<endl;
		Ray rayout;

		if(isINF) l1=-INF;
		else l1=rayin.get_l();
		
		u1=rayin.get_U();
		
		// cout<<Arc2Angle(u1)<<endl;

		// cout<<u1<<" "<<sin(u1)<<endl;
		// l1=-(a/2)/tan(u1);
		// cout<<l1<<endl;// 需要加个判断 支持l和U
		// rayin.set_l(l1);
		for(int k=0;k<nsf;k++){
			// cout<<"#"<<k;
			double d=sf[k].get_d(); //cout<<"# "<<d<<endl;
			double rho=sf[k].get_rho();
			// cout<<" "<<rho<<" "<<d<<" "<<endl;
			
			if(isINF&&k==0) i=(a/2)*rho;
			else i=(rho*l1-1)*u1;				

			rayin.set_i(i);	
			
			n2=sf[k].get_nd();
			u2=(n2-n1)/n2*i+u1;

			l2=(i+u1)/(u2*rho);
			// cout<<" l1 "<<l1;
			// cout<<" l2 "<<l2;
			l1=l2-d;
			n1=n2; // n1是n2前面的折射率

			// cout<<" u1 "<<u1;
			// cout<<" u2 "<<u2<<endl;
			u1=u2;
			// cout<<"i"<<i<<endl;
			// cout<<"l1 "<<l1<<endl;
				
		}
		
		rayout.set_U(u2);
		rayout.set_l(l2);

		return rayout;
	}




	Ray ray_tracing(SPR rayin,bool isINF){

		double u1,u2;
		double l1=0,l2;
		double i;
		double n2,n1=1;// n2:n', n1:n
		// string label=rayin.get_label();
		// cout<<"Rayin type: "<<label<<endl;
		Ray rayout;

		
		if(isINF){			
			double w=rayin.get_W();
			u1=sin(kw*w);
			// cout<<u1<<endl;
		}

		else{
			double y=rayin.get_y();
			double L1=rayin.get_l1();
			u1=sin(atan(kw*(-y)/L1));
			// cout<<u1<<endl;
			
		}

		for(int k=0;k<nsf;k++){
			double d=sf[k].get_d(); //cout<<"# "<<d<<endl;
			double rho=sf[k].get_rho();
		
			i=(rho*l1-1)*u1; //cout<<"# i # "<<i<<endl;
			if(k==0){rayin.set_i(i);}
			
		
			n2=sf[k].get_nd();
			u2=(n2-n1)/n2*i+u1;
			// cout<<u2<<endl;

			l2=(i+u1)/(u2*rho);

			l1=l2-d;
			n1=n2; // n1是n2前面的折射率
			u1=u2;

		}

		rayout.set_U(u2);
		rayout.set_l(l2);


		return rayout;
	}

	Ray ray_tracing(FAR rayin,bool isINF){

		double U1,U2;
		double l1,l2;
		double I1,I2;
		double n2,n1=1;// n2:n', n1:n
		Ray rayout;

		if(isINF) l1=-INF;
		else l1=rayin.get_l();
		
		U1=rayin.get_U();
		
		for(int k=0;k<nsf;k++){
			double d=sf[k].get_d(); 
			double rho=sf[k].get_rho();
			n2=sf[k].get_nd();

			if(isINF&&k==0){
				U1=0;
				I1=asin(ku*(a/2)*rho);
				I2=asin(n2/n1*(a/2)*ku*rho);
			}

			else if(!isINF&&k==0){
				U2=asin(ku*sin(atan((a/2)/l)))
				I1=asin((l1-1)*sin(U1)
			}
			// else if (!isINF&&k==0) I=(rho*l1-1)*u1;


			rayin.set_i(i);	
			
			
			u2=(n2-n1)/n2*i+u1;

			l2=(i+u1)/(u2*rho);
			// cout<<" l1 "<<l1;
			// cout<<" l2 "<<l2;
			l1=l2-d;
			n1=n2; // n1是n2前面的折射率

			// cout<<" u1 "<<u1;
			// cout<<" u2 "<<u2<<endl;
			u1=u2;
			// cout<<"i"<<i<<endl;
			// cout<<"l1 "<<l1<<endl;
				
		}
		
		rayout.set_U(u2);
		rayout.set_l(l2);

		return rayout;
	
	}


	void cal_opt_errs(){
		;
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
		FPR rayin;
		
		isINF=true;
		cout<<"Ray output for the ray incident from infinity:"<<endl;
		rayin.set_U(0);
		rayout=sys.ray_tracing(rayin,isINF);

		rayout.show_rayinfo();

		
		isINF=false;
		cout<<"Ray output for the ray incident from a limited distance:"<<endl;
		double l=-500;
		rayin.set_l(l);
		rayin.set_U(atan(a/l));
		rayout=sys.ray_tracing(rayin,isINF);
		rayout.show_rayinfo();
	}
	
	cout<<endl;
	raytype="SPR";
	if(raytype=="SPR"){
		cout<<"Second Paraxial Ray:"<<endl;
		SPR rayin1;
		isINF=true;
		cout<<"Ray output for the ray incident from infinity:"<<endl;
		double W=3;
		rayin1.set_W(Angle2Arc(W));
		rayout=sys.ray_tracing(rayin1,isINF);
		rayout.show_rayinfo();
	
		isINF=false;
		cout<<"Ray output for the ray incident from a limited distance:"<<endl;

		SPR rayin2;
		double l=-500;
		double y=26;
		rayin2.set_l1(l);
		rayin2.set_y(y);
		rayout=sys.ray_tracing(rayin2,isINF);
		rayout.show_rayinfo();
	}

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