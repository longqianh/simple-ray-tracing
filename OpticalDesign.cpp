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
#define INF 1e7
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
		this->set_f();



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

	void set_f()
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
		// cout<<"Effective Focal Length -- "<<f<<endl;

	}
	double get_f() const 
	{
		return f;
	}


	// 利用多态
	Ray ray_tracing(FPL rayin,bool isINF){
		double u1,u2; // u1:u, u2:u'
		double l1,l2;
		double i;
		double n2,n1=1;// n2:n', n1:n
		// string label=rayin.get_label();
		// cout<<"Rayin type: "<<label<<endl;
		Ray rayout;

		if(isINF)l1=-1e15;
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




	Ray ray_tracing(SPL rayin,bool isINF){

		double u1,u2;
		double l1=0,l2;
		double i;
		double n2,n1=1;// n2:n', n1:n
		string label=rayin.get_label();
		// cout<<"Rayin type: "<<label<<endl;
		Ray rayout;

		
		if(isINF){			
			double w=rayin.get_W();
			u1=sin(kw*w);
			// cout<<w<<endl;
		}

		else{
			double y=rayin.get_y();
			double L1=rayin.get_l1();
			u1=sin(atan(kw*(-y)/L1));
			// cout<<"#"<<y<<" "<<L1<<" "<<u1<<endl;
		}

		for(int k=0;k<nsf;k++){
			double d=sf[k].get_d(); //cout<<"# "<<d<<endl;
			double rho=sf[k].get_rho();
		
			i=(rho*l1-1)*u1; //cout<<"# i # "<<i<<endl;
			if(k==0){rayin.set_i(i);}
			
		
			n2=sf[k].get_nd();
			u2=(n2-n1)/n2*i+u1;

			l2=(i+u1)/(u2*rho);

			l1=l2-d;
			n1=n2; // n1是n2前面的折射率
			u1=u2;

		}

		rayout.set_U(u2);
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
	bool isINF;
	double dists[]={4,2.5,60};
	double rs[]={62.5,-43.65,-124.35};
	double nds[]={1.5167969495,1.6727015725,1};

	OptSys sys(a,nsf,dists,rs,nds);

	// cout<<"f: "<<sys.get_f()<<endl;
	// sys.show_sflist();
	Ray rayout;

	raytype="FPL";
	if(raytype=="FPL"){
		isINF=false;
		
		if(isINF){
			FPL rayin;
			rayin.set_U(0);
			rayout=sys.ray_tracing(rayin,isINF);
			cout<<rayout.get_l()<<endl;

			// cout<<sys.get_f();
		}
		else{
			double l=-500;
			FPL rayin;
			rayin.set_l(l);
			rayin.set_U(atan(a/l));
			// FPL rayin(Angle2Arc(1.1457628)); // 近轴的孔径范围？
			rayout=sys.ray_tracing(rayin,isINF);
			// cout<<Arc2Angle(rayout.get_U())<<endl;
			// cout<<rayout.get_l()<<endl;
		}
		
		// rayout.show_rayinfo();
	}
	

	// isINF=true;
	raytype="SPL";
	if(raytype=="SPL"){
		isINF=false;
		if(isINF){
			// W=cin.get();
			// y=cin.get();
			double W=3;
			SPL rayin(Angle2Arc(W));
		}
		else{
			// U=cin.get();
			// double U=1.1457628;
			double l=-500;
			// U=Angle2Arc(U);
			double y=26;
			SPL rayin;
			// rayin.set_U(atan());
			rayin.set_l1(l);
			rayin.set_y(y);
			rayout=sys.ray_tracing(rayin,isINF);
			// rayin.show_rayinfo();
		}
	}
	
	
	// cout<<"#"<<raytest.get_label()<<endl;
	// raytest.show_rayinfo();



	
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

	// cout<<"###"<<10/Angle2Arc(5.73655)<<endl;
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