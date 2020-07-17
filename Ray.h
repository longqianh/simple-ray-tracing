#pragma once
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
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


	void set_rayinfo(string rayinfo)
	{
		this->rayinfo=rayinfo;
	}

	string get_rayinfo() const
	{
		return this->rayinfo;
	}

	
	double get_U() const
	{
		return this->U;
	}
	
	double get_l() const
	{
		return this->l;
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
		this->rayinfo="FPR";
		this->U=0;
	}
	FPR(double l,string rayinfo):Ray(l,rayinfo)
	{
		this->U=0;
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
	// double W; // 物方视场角 弧度
	// double y; // 对应的物高


public:
	double W; // 物方视场角 弧度
	double y; // 对应的物高


	
	SPR(double l,double y_or_W):Ray(l)
	{
		if(l==-INF||l==INF)
		{
			this->W=-Angle2Arc(y_or_W);// 根据符号规则转化
		}
		else{
			this->y=y_or_W;
		}
		this->L=l;
		this->l=0; // 注：若孔径光阑不在第一面，这里的l需重新设置
	}

	SPR(double l,double y_or_W,string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			this->W=-Angle2Arc(y_or_W);
		}
		else{
			this->y=y_or_W;
		}
		this->L=l;
		this->l=0;
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
		return this->W;
	}
	double get_L() const
	{
		return this->L;
	
	}

	double get_y() const
	{
		return this->y;
	}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<<rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(U)<<endl;
		cout<<"Distance l -- ";
		if(this->l<=-INF)
		{
			cout<<"-INF"<<endl;
			cout<<"Angle of View W -- "<<W<<endl;
		}
		else if(this->l>=INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<< this->l<<endl;
			cout<<"Object Height y -- "<< this->y<<endl;
		}
	}
};


// First Actural Ray or meridian actual ray
// to overcome the conflict with MFC 
// changed the FAR to FRR

class FRR : public Ray  
{
public:
	FRR(double l):Ray(l)
	{
		this->rayinfo="FRR";
	}
	FRR(double l,string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;
	}

	~FRR(){}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<< this->rayinfo<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(this->U)<<endl;
		cout<<"Distance -- ";
		if(this->l<=-INF)
		{
			cout<<"-INF"<<endl;
		}
		else if(this->l>INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<< this->l<<endl;
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

protected:


public:
	SAR()
	{ 
		this->rayinfo="SAR";
		this->label="cf";
		this->t=-INF, this->s=-INF;
	}
	SAR(double l,double y_or_W):Ray(l)
	{
		if(l==-INF||l==INF)
		{
			this->W=-Angle2Arc(y_or_W);
			this->L=-INF;
		}
		else { this->y=y_or_W; }

		this->L=l;

		this->rayinfo="SAR";
		
		// 默认为主光线，可根据上下光线重新设置
		this->label="cf";
		this->l=0;
		this->t=-INF, this->s=-INF;
	}

	SAR(double l,double y_or_W,string label):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			this->W=-Angle2Arc(y_or_W);
		}
		else { this->y=y_or_W; }

		this->L=l;
		this->label=label;
		this->t=-INF, this->s=-INF;
		
	}

	SAR(double l,double y_or_W, string label, string rayinfo):Ray(l)
	{
		this->rayinfo=rayinfo;

		if(l==-INF||l==INF)
		{
			this->W=-Angle2Arc(y_or_W);
		}
		else { this->y=y_or_W; }

		this->L=l;
		this->t=-INF, this->s=-INF;
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
		return this->L;
	}

	double get_W() const
	{
		return this->W;
	}

	double get_y() const
	{
		return this->y;
	}

	double get_t() const
	{
		return this->t;
	}

	double get_s() const
	{
		return this->s;
	}

	string get_label() const
	{
		return this->label;
	}

	void show_rayinfo()
	{
		cout<<"Ray Information : "<< this->rayinfo<<endl;
		cout<<"Ray label -- "<< this->label<<endl;
		cout<<"Aperture Angle U -- "<<Arc2Angle(this->U)<<endl;
		cout<<"Distance l -- ";
		if(this->l<=-INF)
		{
			cout<<"-INF"<<endl;
			cout<<"Angle of View W -- "<< this->W<<endl;
		}
		else if(this->l>=INF)
		{
			cout<<"INF"<<endl;
		}
		else{
			cout<< this->l<<endl;
			cout<<"Object Height y -- "<< this->y<<endl;
		}

		if(this->label=="cf")
		{
			cout<<"Meridian Distance t -- "<< this->t<<endl;
		 	cout<<"Sagittarius Distance s -- "<< this->s<<endl;
		 }

	}
};
