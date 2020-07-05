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
		for(int k=0;k<nsf;k++){
			sf[k].set_d(dists[k]);
			sf[k].set_rho(rs[k]);
			sf[k].set_n(nds[k]);
			this->dists[k]=dists[k];
			this->rs[k]=rs[k];
			this->nds[k]=nds[k];
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
		
	Ray ray_tracing(FPR rayin, double ku=1,double kw=1,string info="First Paraxial Ray-tracing");
	Ray ray_tracing(SPR rayin, double ku=1, double kw=1,string info="Second Paraxial Ray-tracing");
	Ray ray_tracing(FAR rayin, double ku=1, double kw=1,string info="First Actual Ray-tracing");
	SAR ray_tracing(SAR rayin, double ku=1, double kw=1,string info="Second Actual Ray-tracing");


	double cal_y0(double l,double y_or_W,double ku=1,double kw=1);

	double cal_y(double l,double y_or_W,double ku=1,double kw=1);

	double cal_SA(double l,double ku=1);

	double cal_LCAx(double *nfs,double *ncs,double l, double ku=1); // Lateral Chromatic Aberration

	double cal_LCAy(double *nfs,double *ncs,double l,double y_or_W, double kw=1); // Longitudinal Chromatic Aberration

	double* cal_Distortion(double l,double y_or_W,double ku=1,double kw=1);

	double cal_Coma(double l,double y_or_W,double ku=1,double kw=1);

	double* cal_FCs(double l,double y_or_W, double ku=1,double kw=1); // Field Curvature and Astigmatism

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
	FPR rayin1(-INF);
	SPR rayin2(-INF,3);// W != 0 即可，出瞳距不变
	Ray rayout1,rayout2; 
	rayout1=ray_tracing(rayin1);
	rayout2=ray_tracing(rayin2);
	double u2=rayout1.get_U();
	f=(a/2)/abs(u2); 
	lH=rayout1.get_l()-f;
	lp=rayout2.get_l();
}

// 利用多态
Ray OptSys::ray_tracing(FPR rayin,double ku,double kw,string info){
	
	double u1,u2; // u1 -- u, u2 -- u'
	double l1,l2;
	double i;
	double n2,n1=1; // n2 -- n', n1 -- n
	bool isINF;

	Ray rayout(info);
	l1=rayin.get_l();

	isINF=(l1<=-INF);

	if(!isINF)
	{
		u1=atan((a/2)/l1); // ?
		rayin.set_U(u1);
	}
		
	
	for(int k=0;k<nsf;k++){
		double d=sf[k].get_d(); 
		double rho=sf[k].get_rho();
		
		if(isINF&&k==0) i=(a/2)*rho;
		else i=(rho*l1-1)*u1;				

		// if(k==0)rayin.set_i(i);	
		
		n2=sf[k].get_n();
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




Ray OptSys::ray_tracing(SPR rayin,double ku,double kw,string info){

	double u1,u2;
	double l1=0,l2;
	double i1,i2;
	double n2,n1=1;
	double L;
	bool isINF; 
	Ray rayout(info);
	L=rayin.get_L();
	isINF=(L<=-INF);

	if(isINF){			
		double w=rayin.get_W();
		u1=kw*w;

	}

	else{
		double y=rayin.get_y();
		u1=atan(kw*y/L); 

	}
	u1=sin(u1);

	rayin.set_U(u1);
	for(int k=0;k<nsf;k++)
	{
		double d=sf[k].get_d(); 
		double rho=sf[k].get_rho();

		n2=sf[k].get_n();
		i1=(rho*l1-1)*u1;
		i2=n1/n2*i1;	
		
		u2=(n2-n1)/n2*i1+u1;
		l2=1/rho*(1+i2/u2);


		l1=l2-d;
		n1=n2; // n1是n2前面的折射率
		u1=u2;

	}

	rayout.set_U(u2);
	rayout.set_l(l2);

	return rayout;
}

Ray OptSys::ray_tracing(FAR rayin,double ku,double kw,string info){

	double U1,U2; // U,U'
	double l1,l2; // l,l'
	double I1,I2; // I,I'
	double n1=1,n2; // n,n'
	double d,rho;
	bool isINF;

	l1=rayin.get_l();
	isINF=(l1<=-INF);

	Ray rayout(info);

	if(!isINF)
	{
		U1=asin(ku*sin(atan((a/2)/l1)));
		rayin.set_U(U1);
	} 
	
	for(int k=0;k<nsf;k++){
		d=sf[k].get_d(); 
		rho=sf[k].get_rho();
		n2=sf[k].get_n();

		if(isINF&&k==0){
			
			I1=asin(ku*(a/2)*rho);
			I2=asin(n1/n2*(a/2)*ku*rho);
		}

		else{
			I1=asin((l1*rho-1)*sin(U1));
			I2=asin(n1/n2*(l1*rho-1)*sin(U1));
		}

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

SAR OptSys::ray_tracing(SAR rayin,double ku,double kw,string info){

	double U1,U2; // U,U'
	double l1,l2; // l,l'
	double I1,I2; // I,I'
	double n1=1,n2; // n,n'
	double L; // 物距
	double d,rho;
	double t1,t2,s1,s2; 
	double y;
	double U2tmp[nsf],tmp1s[nsf],tmp2s[nsf];
	bool isINF;

	string label=rayin.get_label();
	L=rayin.get_L();
	isINF=(L<=-INF);

	SAR rayout;

	if(isINF)
	{
		double W=rayin.get_W();

		U1=kw*W; 
		if(label=="up"){
			l1=ku*(a/2)/tan(U1);
		}

		else if(label=="cf"){
			l1=0;
			t1=-INF;
			s1=t1;
			rayin.set_s(s1);
			rayin.set_t(t1);
		}

		else if(label=="dn")
		{
			l1=-ku*(a/2)/tan(U1);
		}
		rayin.set_l(l1);
	} 

	else
	{
		y=rayin.get_y();
		
		if(label=="up")
		{
			U1=-atan((-y*kw+ku*a/2)/L);
			l1=-ku*(a/2)/((-y*kw+ku*a/2)/L);
		}
		else if(label == "cf")
		{
			U1=-atan(-y*kw/L);
			l1=0;
			t1=-sqrt(y*y+L*L);
			s1=t1;

			rayin.set_s(s1);
			rayin.set_t(t1);
		}
		else if(label=="dn"){
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
		n2=sf[k].get_n();

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

		if(label=="cf")
		{
			double PA=l1*sin(U1)/cos((I1-U1)/2);
			sf[k].set_PA(PA);

		}
		
		l1=l2-d;
		U1=U2;
		n1=n2; // n1是n2前面的折射率		
	}
	
	rayout.set_U(U2);
	rayout.set_l(l2);
	n1=1;

	if(label=="cf")
	{
		for(int k=0;k<nsf;k++)
		{		
			double X1,X2,D;
			double tmp1=tmp1s[k],tmp2=tmp2s[k];
			
			d=sf[k].get_d();
			rho=sf[k].get_rho();
			n2=sf[k].get_n();

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

double OptSys::cal_y0(double l,double y_or_W,double ku,double kw)
{
	FPR rayin1(l);
	SPR rayin2(l,y_or_W);


	if(l<=-INF)
	{
		double W=rayin2.get_W();
		return myabs(f*tan(kw*W));
	}

	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,ku,kw);
	rayout2=ray_tracing(rayin2,ku,kw);


	return myabs((rayout2.get_l()-rayout1.get_l())*tan(rayout2.get_U()));


}

double OptSys::cal_y(double l,double y_or_W,double ku,double kw)
{

	FPR rayin1(l);
	SAR rayin2(l,y_or_W);
	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,ku,kw);
	rayout2=ray_tracing(rayin2,ku,kw);
	
	// cout<<rayout2.get_l()<<endl;
	// cout<<endl;
	// cout<<"RAY1 L "<<rayout1.get_l()<<endl;
	// cout<<"RAY2 L "<<rayout2.get_l()<<endl;
	// cout<<"RAY2 U "<<rayout2.get_U()<<endl;
	// cout<<"1 🐭"<<endl;
	// rayout1.show_rayinfo();
	// cout<<"1 🐭"<<endl;
	// cout<<endl;
	// cout<<"2 🐭"<<endl;
	// rayout2.show_rayinfo();
	// cout<<"2 🐭"<<endl;


	return myabs((rayout2.get_l()-rayout1.get_l())*tan(rayout2.get_U()));


}


double* OptSys::cal_Distortion(double l,double y_or_W,double ku,double kw)
{
	// static double d[2]; // 使用静态变量 会出现地址错误
	double *d=new double[2]; 
	double y1=cal_y(l,y_or_W,ku,kw);
	double y0=cal_y0(l,y_or_W,ku,kw);
	// cout<<"y0 ⛽️ y0 "<<y0<<endl;
	// cout<<"y1 ⛽️ y1 "<<y1<<endl;
	d[0]=y1-y0; // 绝对畸变
	// cout<<d[0]<<endl;
	d[1]=d[0]/y0; // 相对畸变
	// cout<<d[1]<<endl;
	// cout<<&d<<endl;
	return d;
}


double OptSys::cal_SA(double l,double ku)
{
	FPR rayin1(l);
	FAR rayin2(l);
	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,ku);
	rayout2=ray_tracing(rayin2,ku);
	// cout<<rayout2.get_l()<<"######"<<endl;
	// cout<<rayout1.get_l()<<"######"<<endl;
	return rayout2.get_l()-rayout1.get_l();
}

double OptSys::cal_LCAx(double *nfs,double *ncs,double l, double ku)
{	

	OptSys sys_f(a,nsf,dists,rs,nfs);
	OptSys sys_c(a,nsf,dists,rs,ncs);
	Ray rayout1,rayout2;

	if(ku==0)
	{
		FPR rayin1(l),rayin2(l);		
		rayout1=sys_f.ray_tracing(rayin1,ku);	
		rayout2=sys_c.ray_tracing(rayin2,ku);
	}

	else
	{
		FAR rayin1(l),rayin2(l);
		rayout1=sys_f.ray_tracing(rayin1,ku);	
		rayout2=sys_c.ray_tracing(rayin2,ku);
	}

	// cout<<endl;
	// cout<<"1 ✊"<<endl;
	// rayout1.show_rayinfo();
	// cout<<"1 ✊"<<endl;
	// cout<<endl;
	// cout<<"2 ✊"<<endl;
	// rayout2.show_rayinfo();
	// cout<<"2 ✊"<<endl;
	// cout<<endl;

	return rayout1.get_l()-rayout2.get_l();

}



double OptSys::cal_LCAy(double *nfs,double *ncs,double l,double y_or_W,double kw)
{
	OptSys sys_f(a,nsf,dists,rs,nfs);
	OptSys sys_c(a,nsf,dists,rs,ncs);
	double yf=sys_f.cal_y(l,y_or_W,1,kw);
	double yc=sys_c.cal_y(l,y_or_W,1,kw);
	
	return yf-yc;

}

double* OptSys::cal_FCs(double l,double y_or_W,double ku,double kw)
{
	SAR rayin(l,y_or_W);
	SAR rayout;
	rayout=ray_tracing(rayin,ku,kw);
	double l2=rayout.get_l();
	double U=rayout.get_U();
	double t=rayout.get_t();
	double s=rayout.get_s();
	double X=sf[nsf-1].get_X();


	static double FC[3];
	double xt=t*cos(U)+X-l2;
	double xs=s*cos(U)+X-l2;
	
	FC[0]=xt,FC[1]=xs,FC[2]=xt-xs;

	return FC;

}

double OptSys::cal_Coma(double l,double y_or_W,double ku,double kw)
{	
	double coma;
	double yp=cal_y(l,y_or_W,ku,kw);
	double y_up,y_dn;

	FPR rayin(l);
	SAR rayin_up(l,y_or_W,"up");
	SAR rayin_dn(l,y_or_W,"dn");
	Ray rayout;
	SAR rayout_up,rayout_dn;

	rayout=ray_tracing(rayin,ku,kw);
	rayout_up=ray_tracing(rayin_up,ku,kw);
	rayout_dn=ray_tracing(rayin_dn,ku,kw);
	
	y_up=(rayout_up.get_l()-rayout.get_l())*tan(rayout_up.get_U());
	y_dn=(rayout_dn.get_l()-rayout.get_l())*tan(rayout_dn.get_U());

	return (y_up-y_dn)/2-yp;




}