#pragma once
#include<iostream>
#include<math.h>
#include "utils.h"
using namespace std;
#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif


class Ray
{
protected:

	double U; //弧度
	double l; // 物距
	// double i; // 入射角 弧度
	string rayinfo; // 一些信息

public:

	Ray(){} 
	Ray(double l)
	{
		this->l=l;
	}
	Ray(string rayinfo)
	{
		this->rayinfo=rayinfo;
	}
 	
 	Ray(double l,string rayinfo)
	{
		this->l=l;
		this->rayinfo=rayinfo;
	}
	
	virtual ~Ray(){}


	void set_U(double U){
		this->U=U;
	}
	
	void set_l(double l){
		this->l=l;
	}
	// void set_i(double i){
	// 	this->i=i;
	// }

	void set_rayinfo(string rayinfo)
	{
		this->rayinfo=rayinfo;
	}

	string get_rayinfo() const
	{
		return rayinfo;
	}

	
	double get_U() const
	{
		return U;
	}
	
	double get_l() const
	{
		return l;
	}

	virtual void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance l -- ";
		if(l<=-INF)
		{
			cout<<"-INF"<<endl;
		}
		else if(l>INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<<l<<endl;
		}
	}
	
};

// First Paraxial Ray

class FPR: public Ray
{

public:

	FPR(double l):Ray(l)
	{
		rayinfo="FPR"; 
		U=0;
	}
	FPR(double l,string rayinfo):Ray(l,rayinfo)
	{
		U=0;
	}

	~FPR(){}


	void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance l -- ";
		if(l<=-INF)
		{
			cout<<"-INF"<<endl;
		}
		else if(l>INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<<l<<endl;
		}

	}

};

// Second Paraxial Ray
class SPR: public Ray
{
private:
	double L; // 对应的物距
	double y; // 对应的物高
	double W; // 物方视场角 弧度

public:
	
	SPR(double l,double y_or_W):Ray(l)
	{
		if(l==-INF||l==INF)
		{
			W=-Angle2Arc(y_or_W);// 根据符号规则转化
		}
		else{
			y=y_or_W;
		}
		L=l;
		l=0; // 注：若孔径光阑不在第一面，这里的l需重新设置
	}

	SPR(double l,double y_or_W,string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			W=-Angle2Arc(y_or_W);
		}
		else{
			y=y_or_W;
		}
		L=l;
		l=0; 
	}

	~SPR(){}


	void set_W(double W){
		this->W=W;
	}
	
	void set_L(double L){
		this->L=L;
	}

	void set_y(double y){
		this->y=y;
	}

	double get_W() const
	{
		return W;
	}
	double get_L() const
	{
		return L;
	
	}

	double get_y() const
	{
		return y;
	}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance l -- ";
		if(l<=-INF)
		{
			cout<<"-INF"<<endl;
			cout<<"Angle of View W -- "<<W<<endl;
		}
		else if(l>=INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<<l<<endl;
			cout<<"Object Height y -- "<<y<<endl;
		}
	}
};

// First Actural Ray or meridian actual ray
class FAR : public Ray  
{
public:
	FAR(double l):Ray(l)
	{
		rayinfo="FAR";
	}
	FAR(double l,string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;
	}

	~FAR(){}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance -- ";
		if(l<=-INF)
		{
			cout<<"-INF"<<endl;
		}
		else if(l>INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<<l<<endl;
		}
	}

	
};

// Second Actural Ray 
class SAR : public Ray  
{
private:
	double L;
	double W;
	double y;
	double t,s;
	string label; // 区分主、上、下光线

public:
	SAR(){ rayinfo="SAR"; }
	SAR(double l,double y_or_W):Ray(l)
	{
		if(l==-INF||l==INF)
		{
			W=-Angle2Arc(y_or_W);
			L=-INF;
		}
		else { y=y_or_W; }

		L=l;

		rayinfo="SAR";
		
		// 默认为主光线，可根据上下光线重新设置
		label="cf";
		l=0; 
	}

	SAR(double l,double y_or_W,string label):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			W=-Angle2Arc(y_or_W);
		}
		else { y=y_or_W; }

		L=l;
		this->label=label;
		
	}

	SAR(double l,double y_or_W, string label, string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			W=-Angle2Arc(y_or_W);
		}
		else { y=y_or_W; }

		L=l;
		this->label=label;
		this->rayinfo=rayinfo;
		
		
	}
	
	~SAR(){}

	void set_label(string label)
	{
		this->label=label;
	}

	void set_L(double L)
	{
		this->L=L;
	}

	void set_W(double W){
		this->W=W; // 根据符号规则转化
	}

	void set_y(double y){
		this->y=y;
	}


	void set_t(double t)
	{
		this->t=t;
	}

	void set_s(double s)
	{
		this->s=s;
	}


	double get_L() const
	{
		return L;
	}

	double get_W() const
	{
		return W;
	}

	double get_y() const
	{
		return y;
	}

	double get_t() const
	{
		return t;
	}

	double get_s() const
	{
		return s;
	}

	string get_label() const
	{
		return label;
	}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Ray label -- "<<label<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance l -- ";
		if(l<=-INF)
		{
			cout<<"-INF"<<endl;
			cout<<"Angle of View W -- "<<W<<endl;
		}
		else if(l>=INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<<l<<endl;
			cout<<"Object Height y -- "<<y<<endl;
		}

		if(label=="cf")
		{
			cout<<"Meridian Distance t -- "<<t<<endl;
		 	cout<<"Sagittarius Distance s -- "<<s<<endl;
		 }

	}
};
