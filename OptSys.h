#pragma once
#include "Ray.h"
#include "Lens.h"
#include "utils.h"
#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif


class OptAber
{
public:
	OptAber();
	~OptAber();
	
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
		FPR rayin;
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

	// double get_y0(){
	// 	return y0;
	// }


	double get_f() const 
	{
		return f;
	}

	double get_lH() const 
	{
		return lH;
	}


	// 利用多态
	Ray ray_tracing(FPR rayin,bool isINF, double ku=1,double kw=1){
		double u1,u2; // u1:u, u2:u'
		double l1,l2;
		double i;
		double n2,n1=1; // n2:n', n1:n
		// string label = rayin.get_label();
		// cout<<"Rayin type: "<<label<<endl;
		Ray rayout;

		if(isINF)
		{
			l1=-INF;
			rayin.set_U(0);	
		} 
		else
		{
			l1=rayin.get_l();
			u1=atan(a/l1);
			rayin.set_U(u1);
		}
			
		
		for(int k=0;k<nsf;k++){
			double d=sf[k].get_d(); 
			double rho=sf[k].get_rho();
			
			if(isINF&&k==0) i=(a/2)*rho;
			else i=(rho*l1-1)*u1;				

			if(k==0)rayin.set_i(i);	
			
			n2=sf[k].get_nd();
			u2=(n2-n1)/n2*i+u1;

			l2=(i+u1)/(u2*rho);
			l1=l2-d;
			n1=n2; // n1是n2前面的折射率			
			u1=u2;

		}
		
		rayout.set_U(u2);
		rayout.set_l(l2);

		return rayout;
	}




	Ray ray_tracing(SPR rayin,bool isINF,double ku=1,double kw=1){

		double u1,u2;
		double l1=0,l2;
		double i;
		double n2,n1=1;
		 // n2:n', n1:n
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

	Ray ray_tracing(FAR rayin,bool isINF,double ku=1,double kw=1){

		double U1,U2; // U,U'
		double l1,l2; // l,l'
		double I1,I2; // I,I'
		double n1=1,n2; // n,n'
		double d,rho;
		Ray rayout;

		if(isINF)
		{
			l1=-INF;
			rayin.set_U(0);
		}

		else
		{
			l1=rayin.get_l();
			U1=asin(ku*sin(atan((a/2)/l1)));
			rayin.set_U(U1);
		} 
		
		
		for(int k=0;k<nsf;k++){
			d=sf[k].get_d(); 
			rho=sf[k].get_rho();
			n2=sf[k].get_nd();

			if(isINF&&k==0){
				
				I1=asin(ku*(a/2)*rho);
				I2=asin(n1/n2*(a/2)*ku*rho);
			}

			else{
				I1=asin((l1*rho-1)*sin(U1));
				I2=asin(n1/n2*(l1*rho-1)*sin(U1));
			}
			
		
			// else if (!isINF&&k==0) I=(rho*l1-1)*u1;
			U2=U1+I1-I2;
			l2=1/rho*(1+sin(I2)/sin(U2));
			
			l1=l2-d;
			U1=U2;
			n1=n2; // n1是n2前面的折射率
				
		}
		
		rayout.set_U(U2);
		rayout.set_l(l2);

		return rayout;
	
	}

	Ray ray_tracing(SAR rayin,bool isINF,double ku=1,double kw=1){

		double U1,U2; // U,U'
		double l1,l2; // l,l'
		double I1,I2; // I,I'
		double n1=1,n2; // n,n'
		double L; // 物距
		double d,rho;
		double s,t;
		double y;
		double *U2tmp= new double[nsf];

		string label=rayin.get_label();

		Ray rayout;


		if(isINF){
			double W=rayin.get_W();

			U1=-kw*W; // 负号
			t=-INF;
			s=-INF;
			if(label=="up"){
				l1=ku*(a/2)/tan(U1);
				// cout<<"UP"<<l1<<endl;
			}
			else if(label=="cf"){
				l1=0;
			}
			else if(label=="dn")
			{
				l1=-ku*(a/2)/tan(U1);
				// cout<<"DN"<<l1<<endl;	
			}
			rayin.set_l(l1);
		} 

		else{
			L=rayin.get_l1();	
			y=rayin.get_y();
			t=-sqrt(y*y+L*L);
			s=t;
			if(label=="up")
			{
				U1=-atan((-y*kw+ku*a/2)/L);
				l1=-ku*(a/2)/((-y*kw+ku*a/2)/L);
			}
			else if(label == "cf")
			{
				U1=-atan(-y*kw/L);
				l1=0;
			}
			else if(label=="dn"){
				cout<<"dn "<<(-y*kw-ku*a/2)/L<<endl;
				U1=-atan((-y*kw-ku*a/2)/L);
				l1=ku*(a/2)/((-y*kw-ku*a/2)/L);
			}
			rayin.set_U(U1);
			rayin.set_l(l1);
		} 
		// cout<<"L1"<<l1<<endl;
		if(label=="cf")
		{
			rayin.set_s(s);
			rayin.set_t(t);
		}
		
		
		
		for(int k=0;k<nsf;k++){
			d=sf[k].get_d(); 
			rho=sf[k].get_rho();
			n2=sf[k].get_nd();

			I1=asin((L*rho-1)*sin(U1));
			I2=asin((n1/n2)*(L*rho-1)*sin(U1));
			l2=1/rho*(1+sin(I2)/sin(U2));
			U2=U1+I1-I2;
			U2tmp[k]=U2;
			l2=1/rho*(1+sin(I2)/sin(U2));
			if(label=="cf"){
				double PA=l1*sin(U1)/cos((I1-U1)/2);
				cout<<" PA "<<PA<<endl;
				sf[k].set_PA(PA);
			}
			
			l1=l2-d;
			U1=U2;
			n1=n2; // n1是n2前面的折射率		
		}
		
		rayout.set_U(U2);
		rayout.set_l(l2);

		if(label=="cf")
		{
			for(int k=0;k<nsf-1;k++)
			{
				d=sf[k].get_d();
				double X1=sf[k].get_X();
				double X2=sf[k+1].get_X();
				double D=(d-X1+X2)/cos(U2tmp[k]);
				t-=D;
				s-=D;
			}

			rayout.set_t(t);
			rayout.set_s(s);
			
		}
		delete [] U2tmp;
		
		
		return rayout;
	
	}

	// OptAber cal_aber(SAR rayin_up,SAR rayin_cf,SAR rayin_dn)
	// {
	// 	OptAber abers;
	// 	return abers;
	// }

};