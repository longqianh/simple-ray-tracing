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

class OptSys
{
private:
	int	nsf; // 系统面数
	int a; // 入瞳直径
	double f; // 系统焦距
	double lH; // 像方主面距离
	double lp; // 出瞳距

	

public:

	Surface *sf;
	double * dists;
	double * rs;
	double * nds;

	OptSys(){}
	OptSys(int a,int nsf,double *dists,double * rs,double *nds){
		
		
		this->a=a;
		this->nsf=nsf;
		sf=new Surface[nsf];
		this->dists=new double[nsf];
		this->rs=new double[nsf];
		this->nds=new double[nsf];
		for(int i=0;i<nsf;i++){
			sf[i].set_d(dists[i]);
			sf[i].set_rho(rs[i]);
			sf[i].set_nd(nds[i]);
			this->dists[i]=dists[i];
			this->rs[i]=rs[i];
			this->nds[i]=nds[i];
		}

		this->init_sys();


	}

	~OptSys()
	{
		delete [] sf;
		delete [] dists;
		delete [] rs;
		delete [] nds;
	}

	double get_f() const { return f; }

	double get_lH() const { return lH; }

	double get_lp() const { return lp; }

	void show_sysinfo();

	void init_sys();

	void show_sflist();
		
	Ray ray_tracing(SAR rayin,bool isINF=false,string label="SAR raytracing",double ku=1,double kw=1);
	Ray ray_tracing(FPR rayin,bool isINF=false,string label="FPR ray-tracing", double ku=1,double kw=1);
	Ray ray_tracing(SPR rayin,bool isINF=false,string label="SPR ray-tracing",double ku=1,double kw=1);
	Ray ray_tracing(FAR rayin,bool isINF=false,string label="FAR ray-tracing", double ku=1,double kw=1);


	double cal_y0(double l,double y,bool isINF=false,double ku=1,double kw=1,double W=0);

	double cal_y(double l,double y,bool isINF=false,double ku=1,double kw=1);

	double cal_SA(double l,bool isINF=false, double ku=1,double kw=1);

	double cal_LCAx(double l,bool isINF, double ku,double *nfs,double *ncs); // Longitudinal Chromatic Aberration

	double cal_LCAy(); // Lateral Chromatic Aberration

	double* cal_Distortion(double l,double y,bool isINF=false,double ku=1,double kw=1);

	double cal_Coma();

	double cal_FC(); // Field Curvature

	double cal_ATM(); // Astigmatism
};// get_nd nc nf








// double get_y0(){
// 	return y0;
// }
void OptSys::show_sysinfo()
{
	cout<<"Optical System Parameters:"<<endl;
	cout<<"Surface Parameters:"<<endl;
	show_sflist();
	cout<<"Effective Focal Length -- "<<f<<endl;
	cout<<"Main Surface Distance -- "<<lH<<endl;
	cout<<"Exit Pupil Distance -- "<<lp<<endl;

}
void OptSys::show_sflist(){

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


void OptSys::init_sys()
{
	FPR rayin1;
	SPR rayin2;
	Ray rayout1,rayout2;
	bool isINF=true;
	rayin1.set_U(0);
	rayin2.set_l(0);
	rayin2.set_W(3); // W != 0 即可，出瞳距不变
	rayout1=ray_tracing(rayin1,isINF);
	rayout2=ray_tracing(rayin2,isINF);
	double u2=rayout1.get_U();
	f=(a/2)/abs(u2); 
	lH=rayout1.get_l()-f;
	lp=rayout2.get_l();
}

// 利用多态
Ray OptSys::ray_tracing(FPR rayin,bool isINF,string label, double ku,double kw){
	double u1,u2; // u1:u, u2:u'
	double l1,l2;
	double i;
	double n2,n1=1; // n2:n', n1:n

	Ray rayout(label);

	if(isINF)
	{
		l1=-INF;
		rayin.set_U(0);	
	} 
	else
	{
		l1=rayin.get_l();
		u1=atan((a/2)/l1); // ?
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




Ray OptSys::ray_tracing(SPR rayin, bool isINF,string label,double ku,double kw){

	double u1,u2;
	double l1=0,l2;
	double i;
	double n2,n1=1;

	Ray rayout(label);

	
	if(isINF){			
		double w=rayin.get_W();
		u1=sin(kw*w);
	}

	else{
		double y=rayin.get_y();
		double L=rayin.get_l1();
		u1=sin(atan(kw*y/L)); // ?
		rayin.set_l1(L);
		rayin.set_U(u1);
		 
	
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
	// cout<<"L2 "<<l2<<endl;


	return rayout;
}

Ray OptSys::ray_tracing(FAR rayin,bool isINF,string label, double ku,double kw){

	double U1,U2; // U,U'
	double l1,l2; // l,l'
	double I1,I2; // I,I'
	double n1=1,n2; // n,n'
	double d,rho;
	Ray rayout(label);

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

Ray OptSys::ray_tracing(SAR rayin,bool isINF,string label,double ku,double kw){

	double U1,U2; // U,U'
	double l1,l2; // l,l'
	double I1,I2; // I,I'
	double n1=1,n2; // n,n'
	double L; // 物距
	double d,rho;
	double t1,t2,s1,s2; 
	double y;
	double U2tmp[nsf],tmp1s[nsf],tmp2s[nsf];

	string rayin_label=rayin.get_raytype();

	Ray rayout(label);


	if(isINF){
		double W=rayin.get_W();

		U1=kw*W; // 负号
		if(rayin_label=="up"){
			l1=ku*(a/2)/tan(U1);
		}

		else if(rayin_label=="cf"){
			l1=0;
			t1=-INF;
			s1=t1;
			rayin.set_s(s1);
			rayin.set_t(t1);
		}
		else if(rayin_label=="dn")
		{
			l1=-ku*(a/2)/tan(U1);
		}
		rayin.set_l(l1);
	} 

	else{
		L=rayin.get_l1();	
		y=rayin.get_y();
		
		if(rayin_label=="up")
		{
			U1=-atan((-y*kw+ku*a/2)/L);
			l1=-ku*(a/2)/((-y*kw+ku*a/2)/L);
		}
		else if(rayin_label == "cf")
		{
			U1=-atan(-y*kw/L);
			l1=0;
			t1=-sqrt(y*y+L*L);
			s1=t1;

			rayin.set_s(s1);
			rayin.set_t(t1);
		}
		else if(rayin_label=="dn"){
			// cout<<"dn "<<(-y*kw-ku*a/2)/L<<endl;
			U1=-atan((-y*kw-ku*a/2)/L);
			l1=ku*(a/2)/((-y*kw-ku*a/2)/L);
		}
		rayin.set_U(U1);
		rayin.set_l(l1);
	} 
	
	
	
	for(int k=0;k<nsf;k++)
	{
		d=sf[k].get_d(); 
		rho=sf[k].get_rho();
		n2=sf[k].get_nd();

		I1=asin((l1*rho-1)*sin(U1));
		I2=asin((n1/n2)*sin(I1));
		tmp1s[k]=cos(I1);
		tmp2s[k]=cos(I2);

		// cout<<" I1 "<<Arc2Angle(I1)<<endl;
		// cout<<" I2 "<<Arc2Angle(I2)<<endl;

		l2=1/rho*(1+sin(I2)/sin(U2));
		U2=U1+I1-I2;
		// cout<<" U2 "<<cos(U2)<<endl;
		
		// U2tmp[k]=U2;
		l2=1/rho*(1+sin(I2)/sin(U2));
		if(rayin_label=="cf"){
			double PA=l1*sin(U1)/cos((I1-U1)/2);
			// cout<<" PA "<<PA<<endl;
			sf[k].set_PA(PA);

		}
		
		l1=l2-d;
		U1=U2;
		n1=n2; // n1是n2前面的折射率		
	}
	
	rayout.set_U(U2);
	rayout.set_l(l2);
	n1=1;

	if(rayin_label=="cf")
	{
		for(int k=0;k<nsf;k++)
		{		
				double X1,X2,D;
				double tmp1=tmp1s[k],tmp2=tmp2s[k];
				

				d=sf[k].get_d();
				rho=sf[k].get_rho();
				n2=sf[k].get_nd();

				double a=(n2*tmp2-n1*tmp1)*rho;

				if(k<nsf-1)
				{
					X1=sf[k].get_X();					
					X2=sf[k+1].get_X();
					D=(d-X1+X2)/cos(U2tmp[k]);
				}
				

				t2=n2*tmp1*tmp1/(a+n1*tmp1*tmp1/t1);
				s2=n2/(n1/s1+(n2*tmp2-n1*tmp1)*rho);
				t1=t2-D;
				s1=s2-D;
				n1=n2;
				
		}
		
		rayout.set_t(t2);
		rayout.set_s(s2);
	}
	

	return rayout;
}

double OptSys::cal_y0(double l,double y,bool isINF,double ku,double kw,double W)
{
	if(isINF){
		W=Angle2Arc(3);
		return f*tan(kw*W);
	}

	FPR rayin1;
	rayin1.set_l(l);
	SPR rayin2;
	rayin2.set_l1(l);
	rayin2.set_y(y);

	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,isINF,"calculate ideal image height--l1",ku,kw);
	rayout2=ray_tracing(rayin2,isINF,"calculate ideal image height--l2",ku,kw);


	return (rayout2.get_l()-rayout1.get_l())*tan(rayout2.get_U());


}

double OptSys::cal_y(double l,double y,bool isINF,double ku,double kw)
{
	FPR rayin1;
	rayin1.set_l(l);
	SAR rayin2("cf");
	rayin2.set_l1(l);
	rayin2.set_y(y);

	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,isINF,"calculate actual image height--l1",ku,kw);
	rayout2=ray_tracing(rayin2,isINF,"calculate actual image height--l2",ku,kw);

	// cout<<endl;
	// cout<<"RAY1 L "<<rayout1.get_l()<<endl;
	// cout<<"RAY2 L "<<rayout2.get_l()<<endl;
	// cout<<"RAY2 U "<<rayout2.get_U()<<endl;

	return (rayout2.get_l()-rayout1.get_l())*tan(rayout2.get_U());


}


double* OptSys::cal_Distortion(double l,double y,bool isINF,double ku,double kw)
{
	static double d[2]; 
	double y1=cal_y(l,y,isINF,ku,kw);
	double y0=cal_y0(l,y,isINF,ku,kw);
	d[0]=y1-y0; // 绝对畸变
	d[1]=abs(d[0]/y0); // 相对畸变
	return d;
}


double OptSys::cal_SA(double l,bool isINF,double ku,double kw)
{
	FPR rayin1;
	rayin1.set_l(l);
	FAR rayin2;
	rayin2.set_l(l);
	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,isINF,"cal_SA",ku,kw);
	rayout2=ray_tracing(rayin2,isINF,"cal_SA",ku,kw);
	return rayout2.get_l()-rayout1.get_l();
}

double OptSys::cal_LCAx(double l,bool isINF, double ku,double *nfs,double *ncs)
{	

	OptSys sys_f(a,nsf,dists,rs,nfs);
	OptSys sys_c(a,nsf,dists,rs,ncs);

	if(ku==0)
	{
		FPR rayin1,rayin2;
		Ray rayout1,rayout2;
		rayin1.set_l(l);
		rayin2.set_l(l);
		rayout1=sys_f.ray_tracing(rayin1,isINF,"cal_LCAx");	
		rayout2=sys_c.ray_tracing(rayin2,isINF,"cal_LCAx");
		return rayout1.get_l()-rayout2.get_l();

	}
	else
	{
		FAR rayin1,rayin2;
		Ray rayout1,rayout2;
		rayin1.set_l(l);
		rayin2.set_l(l);
		rayout1=sys_f.ray_tracing(rayin1,isINF,"cal_LCAx",ku);	
		rayout2=sys_c.ray_tracing(rayin2,isINF,"cal_LCAx",ku);

		return rayout1.get_l()-rayout2.get_l();
	}
}