#pragma once
#include "Ray.h"
#include "Lens.h"
#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif
using namespace std;

class OptSys
{
private:
	int	nsf; // 系统面数
	int a; // 入瞳直径
	double f; // 系统焦距
	// double lH0; // 物方主面位置（相对第一面） 需使用set方法设置
	double lH; // 像方主面位置（相对最后一面）
	double lp; // 出瞳距

public:

	Surface *sf;
	double * dists;
	double * rs;
	double * ns;
	double * nds; // F、C系统所依附的主系统参数

	OptSys(){}
	OptSys(int a,int nsf,double *dists,double * rs,double *ns,double *nds=nullptr){
		
		if(nds!=nullptr){
			this->nds=new double[nsf];
		}
		else{
			this->nds=nullptr;
		}
		this->a=a;
		this->nsf=nsf;
		sf=new Surface[nsf];
		this->dists=new double[nsf];
		this->rs=new double[nsf];
		this->ns=new double[nsf];
		for(int k=0;k<nsf;k++){
			// if((k==nsf-1)&&(sizeof(dists)/sizeof(dists[0])<nsf-1))
			// {
			// 	sf[k].set_d(INF);
			// }
			sf[k].set_d(dists[k]);
			sf[k].set_rho(rs[k]);
			sf[k].set_n(ns[k]);
			this->dists[k]=dists[k];
			this->rs[k]=rs[k];
			this->ns[k]=ns[k];
			if(nds!=nullptr){
				this->nds[k]=nds[k];
			}

		}

		this->init_sys();


	}

	~OptSys()
	{
		delete [] sf;
		delete [] dists;
		delete [] rs;
		delete [] ns;
		if(nds!=nullptr){
			delete [] nds;
		}
	}


	double get_f() const { return f; }

	double get_lH() const { return lH; }

	// double get_lH0() const { return lH0; }

	double get_lp() const { return lp; }

	void show_sysinfo();

	void init_sys();

	void show_sflist();

	void set_lH0();

	Ray ray_tracing(FPR rayin, double ku=1,double kw=0,string info="First Paraxial Ray-tracing"); // 可以去掉kw
	Ray ray_tracing(SPR rayin, double ku=1, double kw=1,string info="Second Paraxial Ray-tracing");
	Ray ray_tracing(FRR rayin, double ku=1, double kw=0,string info="First Actual Ray-tracing");
	SAR ray_tracing(SAR rayin, double ku=1, double kw=1,string info="Second Actual Ray-tracing");


	double cal_y0(double l,double y_or_W,double ku=1,double kw=1);

	double cal_y(double l,double y_or_W,double ku=1,double kw=1);

	double cal_SA(double l,double ku=1);

	double cal_LCAx(double *nfs,double *ncs,double l, double ku=1); // Lateral Chromatic Aberration

	double cal_LCAy(double *nfs,double *ncs,double l,double y_or_W, double kw=1); // Longitudinal Chromatic Aberration

	double* cal_Distortion(double l,double y_or_W,double ku=1,double kw=1);

	double cal_Coma(double l,double y_or_W,double ku=1,double kw=1);

	double* cal_FCs(double l,double y_or_W, double ku=1,double kw=1); // Field Curvature and Astigmatism

	// void cal_allres(double l,double y_or_W, vector<double> &res );

};



void OptSys::show_sflist(){

	for(int i=0;i<nsf;i++){
		cout<<i+1<<" th surface: ";
		double rho=sf[i].get_rho();
		double thick=sf[i].get_d();
		if(rho==0){
			cout<<"radius -- "<<"inf"<<" , distance to the next surface -- "<<thick;				
		}
		else{
			cout<<"radius -- "<<1/rho<<" , distance to the next surface -- "<<thick;
		}
		cout<<" , diffraction index -- "<<sf[i].get_n()<<endl;

	}
}

void OptSys::show_sysinfo()
{
	cout<<"Optical System Parameters:"<<endl;
	cout<<"Surface Parameters:"<<endl;
	show_sflist();
	cout<<"Effective Focal Length -- "<<f<<endl;
	cout<<"Main Surface Distance -- "<<lH<<endl;
	cout<<"Exit Pupil Distance -- "<<lp<<endl;
	// if(nds!=nullptr)
	// {
	// 	cout<<"NDS"<<nds[0]<<endl;
	// }

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
	
	double u1=0,u2=0; // u1 -- u, u2 -- u'
	double l1=rayin.get_l();
	double l2=0;
	double i=0;
	double n2=1,n1=1; // n2 -- n', n1 -- n
	bool isINF=(l1<=-INF);

	Ray rayout(info);

	if(!isINF)
	{
		u1=atan((ku*a/2)/l1);  // add ku
		rayin.set_U(u1);
	}
		
	
	for(int k=0;k<nsf;k++){
		double d=sf[k].get_d(); 
		double rho=sf[k].get_rho();
		
		if(isINF&&k==0) i=ku*(a/2)*rho; // add ku
		else i=(rho*l1-1)*u1;				
		
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

	double u1=0,u2=0;
	double l1=0,l2=0;
	double i1=0,i2=0;
	double n2=1,n1=1;
	double L=rayin.get_L();

	bool isINF=(L<=-INF);
	Ray rayout(info);

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

Ray OptSys::ray_tracing(FRR rayin,double ku,double kw,string info){

	double U1=0,U2=0; // U,U'
	double l1=rayin.get_l();
	double l2=0; // l,l'
	double I1=0,I2=0; // I,I'
	double n1=1,n2=1; // n,n'
	double d=0,rho=0;
	bool isINF=(l1<=-INF);

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

	double U1=0,U2=0; // U,U'
	double l1=0,l2=0; // l,l'
	double I1=0,I2=0; // I,I'
	double n1=1,n2=1; // n,n'
	double L=rayin.get_L(); // 物距
	double d=0,rho=0;
	double t1=0,t2=0,s1=0,s2=0; 
	double y=0;
	double * U2tmp = new double[nsf](); // 须初始化为0
	double * tmp1s = new double[nsf]();
	double * tmp2s = new double[nsf]();

	bool isINF=(L<=-INF);

	string label=rayin.get_label();

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
			l1=ku*(a/2)/((-y*kw+ku*a/2)/L);
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
			l1=-ku*(a/2)/((-y*kw-ku*a/2)/L);
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

		l2=1/rho*(1+sin(I2)/sin(U2));
		U2=U1+I1-I2;
		U2tmp[k]=U2;

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

			double X1=0,X2=0,D=0;
			double tmp1=tmp1s[k],tmp2=tmp2s[k];
			
			d=sf[k].get_d();
			rho=sf[k].get_rho();
			n2=sf[k].get_n();

			double tmpa=(n2*tmp2-n1*tmp1)*rho;

			if(k<nsf-1)
			{
				X1=sf[k].get_X();					
				X2=sf[k+1].get_X();
				D=(d-X1+X2)/cos(U2tmp[k]);
			}
			

			t2=n2*tmp2*tmp2/(tmpa+n1*tmp1*tmp1/t1);
			s2=n2/(n1/s1+tmpa);
			t1=t2-D;
			s1=s2-D;
			n1=n2;
			// cout<<endl;
			// cout<<t2<<" "<<s2<<endl;
		}
		
		rayout.set_t(t2);
		rayout.set_s(s2);

	}
	// rayout.show_rayinfo();
	
	delete [] U2tmp;
	delete [] tmp1s;
	delete [] tmp2s;

	return rayout;
}



double OptSys::cal_y0(double l,double y_or_W,double ku,double kw)
{
	FPR rayin1(l);

	if(l<=-INF)
	{
		SPR rayin2(l,y_or_W);	
		double W=rayin2.get_W();
		return myabs(f*tan(kw*W)); // 输出正像高
	}

	double u1=0,u2=0; 
	double l1=l;
	double l2=0;
	double i=0;
	double n2=1,n1=1; 
	double beta=1;
	u1=atan((a/2)/l1);

	
	for(int k=0;k<nsf;k++)
	{

		double d=sf[k].get_d(); 
		double rho=sf[k].get_rho();
		i=(rho*l1-1)*u1;						
		n2=sf[k].get_n();
		u2=(n2-n1)/n2*i+u1;

		l2=(i+u1)/(u2*rho);
		beta*=(-l2/l1);
		l1=l2-d;
		n1=n2; // n1是n2前面的折射率			
		u1=u2;
	}

	return kw*y_or_W*beta;
	

}



double OptSys::cal_y(double l,double y_or_W,double ku,double kw)
{
	
	FPR rayin1(l);
	SAR rayin2(l,y_or_W);
	Ray rayout1,rayout2;
	if(nds==nullptr){
		rayout1=ray_tracing(rayin1,ku,kw);
	}
	else{
		OptSys sys_d(a,nsf,dists,rs,nds);
		rayout1=sys_d.ray_tracing(rayin1,ku,kw);
	}
	
	rayout2=ray_tracing(rayin2,ku,kw);


	return myabs((rayout2.get_l()-rayout1.get_l())*tan(rayout2.get_U()));


}


double* OptSys::cal_Distortion(double l,double y_or_W,double ku,double kw)
{
	// static double d[2]; // 使用静态变量 会出现地址错误
	double *d=new double[2](); 
	double y1=cal_y(l,y_or_W,ku,kw);
	double y0=cal_y0(l,y_or_W,ku,kw);
	d[0]=y1-y0; // 绝对畸变
	d[1]=d[0]/y0; // 相对畸变
	return d;
}


double OptSys::cal_SA(double l,double ku)
{
	FPR rayin1(l);
	FRR rayin2(l);
	Ray rayout1,rayout2;
	rayout1=ray_tracing(rayin1,ku);
	rayout2=ray_tracing(rayin2,ku);
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
		FRR rayin1(l),rayin2(l);
		rayout1=sys_f.ray_tracing(rayin1,ku);	
		rayout2=sys_c.ray_tracing(rayin2,ku);
	}

	return rayout1.get_l()-rayout2.get_l();

}



double OptSys::cal_LCAy(double *nfs,double *ncs,double l,double y_or_W,double kw)
{
	OptSys sys_f(a,nsf,dists,rs,nfs,ns);
	OptSys sys_c(a,nsf,dists,rs,ncs,ns);
	double yf=sys_f.cal_y(l,y_or_W,1,kw);
	double yc=sys_c.cal_y(l,y_or_W,1,kw);

	
	return yf-yc;

}

double* OptSys::cal_FCs(double l,double y_or_W,double ku,double kw)
{
	FPR rayin1(l);
	SAR rayin2(l,y_or_W);
	Ray rayout1;
	SAR rayout2;
	rayout1=ray_tracing(rayin1);
	rayout2=ray_tracing(rayin2,ku,kw);

	double l0=rayout1.get_l();
	double U=rayout2.get_U();
	double t=rayout2.get_t();
	double s=rayout2.get_s();
	double X=sf[nsf-1].get_X();

	double *FC = new double[3]();
	double xt=t*cos(U)+X-l0;
	double xs=s*cos(U)+X-l0;

	// cout<<cos(U)<<endl;
	// cout<<"l' -- "<<l2<<endl;
	// cout<<"U --"<< U<<endl;
	// cout<<"s -- "<<s <<endl;
	// cout<<"t --"<< t<<endl;

	
	FC[0]=xt,FC[1]=xs,FC[2]=xt-xs;

	return FC;

}

double OptSys::cal_Coma(double l,double y_or_W,double ku,double kw)
{	
	double coma=0;
	double yp=cal_y(l,y_or_W,ku,kw);
	double y_up=0,y_dn=0;

	FPR rayin(l);
	SAR rayin_up(l,y_or_W,"up");
	SAR rayin_dn(l,y_or_W,"dn");
	Ray rayout;
	SAR rayout_up,rayout_dn;

	rayout=ray_tracing(rayin,ku,kw);
	rayout_up=ray_tracing(rayin_up,ku,kw);
	rayout_dn=ray_tracing(rayin_dn,ku,kw);

	// cout<<yp<<endl;

	
	y_up=(rayout_up.get_l()-rayout.get_l())*tan(rayout_up.get_U());
	y_dn=(rayout_dn.get_l()-rayout.get_l())*tan(rayout_dn.get_U());

	// cout<<y_up<<endl;
	// cout<<y_dn<<endl;

	return myabs((y_up+y_dn)/2-yp); // 之前的bug：+写成了- orz

}


// void OptSys::set_lH0()
// {
// 	double * invrs = new double[nsf];
// 	double * invns = new double[nsf];
// 	double * invdists = new double[nsf];

// 	for(int k=0;k<nsf;k++)
// 	{
// 		invrs[k]=-rs[nsf-k-1];
// 		if(k<nsf-1)
// 		{
// 			invdists[k]=dists[nsf-k-2];
// 			invns[k]=ns[nsf-k-2];	
// 		}

// 		else if(k==nsf-1)
// 		{
// 			invdists[k]=INF;	
// 			invns[k]=1;
// 		} 
// 		// cout<<"RS "<<invrs[k]<<endl;
// 		// cout<<"DISTS "<<invdists[k]<<endl;
// 		// cout<<"NS "<<invns[k]<<endl;
// 	}

// 	OptSys invsys(a,nsf,dists,rs,ns); //利用逆系统获得物方主面位置
// 	lH0=-invsys.get_lH();

// 	delete []invrs;
// 	delete []invns;
// 	delete []invdists;
// }


	

// void OptSys::cal_allres(double *nfs,double *nds, double *ncs,double l,double y_or_W, vector<double> &res )
// {

// 	OptSys sys(a,nsf,dists,rs,nds);
// 	res.push_back(sys.get_f()); // f'
// 	res.push_back(sys.get_lH()); // lH'
// 	res.push_back(sys.get_lp()); // lp'
// 	Ray rayout;
	
// 	FPR ray1(l);
// 	FRR ray2(l);

// 	rayout=sys.ray_tracing(ray1);
// 	res.push_back(rayout.get_l()); // ld0'
// 	rayout=sys.ray_tracing(ray2); 
// 	res.push_back(rayout.get_l()); // ld'
// 	rayout=sys.ray_tracing(ray2,0.7);
// 	res.push_back(rayout.get_l()); // lud'

// 	res.push_back(sys.cal_y0(l,y_or_W)); // yd0'

// 	res.push_back(sys.cal_y0(l,y_or_W,1,0.7)); // ywd0'

// 	res.push_back(sys.cal_y(l,y_or_W)); // yd'

// 	res.push_back(sys.cal_y(l,y_or_W,1,0.7)); // ywd'

// 	OptSys sys_f(a,nsf,dists,rs,nfs,nds);
// 	rayout=sys_f.ray_tracing(ray1);
// 	res.push_back(rayout.get_l()); // lf0'
// 	rayout=sys_f.ray_tracing(ray2);
// 	res.push_back(rayout.get_l()); // lf'
// 	rayout=sys_f.ray_tracing(ray2,0.7);
// 	res.push_back(rayout.get_l()); // luf'

// 	res.push_back(sys_f.cal_y0(l,y_or_W)); // yf0'

// 	res.push_back(sys_f.cal_y0(l,y_or_W,1,0.7)); // ywf0'

// 	res.push_back(sys_f.cal_y(l,y_or_W)); // yf'

// 	res.push_back(sys_f.cal_y(l,y_or_W,1,0.7)); // ywf'

// 	OptSys sys_c(a,nsf,dists,rs,nfs,nds);
// 	rayout=sys_c.ray_tracing(ray1);
// 	res.push_back(rayout.get_l()); // lc0'
// 	rayout=sys_c.ray_tracing(ray2);
// 	res.push_back(rayout.get_l()); // lc'
// 	rayout=sys_c.ray_tracing(ray2,0.7);
// 	res.push_back(rayout.get_l()); // luc'

// 	res.push_back(sys_c.cal_y0(l,y_or_W)); // yc0'

// 	res.push_back(sys_c.cal_y0(l,y_or_W,1,0.7)); // ywc0'

// 	res.push_back(sys_c.cal_y(l,y_or_W)); // yc'

// 	res.push_back(sys_c.cal_y(l,y_or_W,1,0.7)); // ywc'

// 	res.push_back(sys.cal_SA(l)); // SA
// 	res.push_back(sys.cal_SA(l,0.7)); // SAu

// 	res.push_back(sys.cal_LCAx(nfs,ncs,l)); // LCAx
// 	res.push_back(sys.cal_LCAx(nfs,ncs,l,0.7)); // LCAXu
// 	res.push_back(sys.cal_LCAx(nfs,ncs,l,0)); // LCAxu0

// 	double * FCs=sys.cal_FCs(l,y_or_W,0);
// 	res.push_back(FCs[0]); // xt'
// 	res.push_back(FCs[1]); // xs'
// 	res.push_back(FCs[2]); // xts'

// 	double *Dt1s=sys.cal_Distortion(l,y_or_W);
// 	double *Dt2s=sys.cal_Distortion(l,y_or_W,1,0.7);

// 	res.push_back(Dt1s[0]); // adt (Absolute distortion)
// 	res.push_back(Dt2s[0]); // adtw
// 	res.push_back(Dt1s[1]); // rdt (Relutive distortion)
// 	res.push_back(Dt2s[1]); // rdtw

// 	res.push_back(sys.cal_Coma(l,y_or_W)); // coma1
// 	res.push_back(sys.cal_Coma(l,y_or_W,0.7)); // coma2
// 	res.push_back(sys.cal_Coma(l,y_or_W,1,0.7)); // coma3
// 	res.push_back(sys.cal_Coma(l,y_or_W,0.7,0.7)); // coma4


// }