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
	// double W; //弧度
	double t,s;
	double y;
	double l; // 物距
	double i; // 入射角 弧度
	string raytype;
	// double lh;


public:
	Ray(){raytype="GR";t=0;s=0; } // general ray
	Ray(string raytype)
	{
		this->raytype=raytype;
	}
	~Ray(){}

	void set_y(double y){
		this->y=y;
	}

	void set_U(double U){
		this->U=U;
	}
	
	void set_l(double l){
		this->l=l;
	}
	void set_i(double i){
		this->i=i;
	}

	void set_t(double t)
	{
		this->t=t;
	}

	void set_s(double s)
	{
		this->s=s;
	}

	void set_raytype(string raytype)
	{
		this->raytype=raytype;
	}

	string get_raytype() const
	{
		return raytype;
	}

	double get_y() const
	{
		return y;
	}

	double get_U() const
	{
		return U;
	}
	
	double get_l() const
	{
		return l;
	}
	double get_i() const
	{
		return i;
	}

	double get_t() const
	{
		return t;
	}

	double get_s() const
	{
		return s;
	}

	void show_rayinfo(string label=""){
		cout<<"Ray labels: "<<raytype<<endl;
		cout<<"U: "<<Arc2Angle(U)<<endl;
		if(l>0.01||l<-0.01)cout<<"l: "<<l<<endl;
		if(label=="cf")
		{
			cout<<"t: "<<t<<endl;
		 	cout<<"s: "<<s<<endl;
		 }

	}
	// void draw(){}
	
};

// First Paraxial Ray

class FPR: public Ray
{
private:
	double l1;
public:
	FPR(){
		y=0;
		raytype="FPR"; 
		
	}
	FPR(string raytype):Ray(raytype)
	{
		y=0;
	}
	~FPR(){}



};

// Second Paraxial Ray
class SPR: public Ray
{
private:
	double l1; // 对应的物距
	// double y; // 对应的物高
	double W; // 物方视场角 弧度

public:
	SPR(){
		raytype="SPR"; 
	}
	SPR(string raytype):Ray(raytype){}

	~SPR(){}


	void set_W(double W){
		this->W=W;
	}
	
	
	void set_l1(double l1){
		this->l1=l1;
	}

	// void set_y(double y){
	// 	this->y=y;
	// }

	double get_W() const
	{
		return W;
	}
	double get_l1() const
	{
		return l1;
	
	}

	// double get_y() const
	// {
	// 	return y;
	// }

};

// First Actural Ray or meridian actual ray
class FAR : public Ray  
{
public:
	FAR(){
		raytype="FAR";
		y=0;
	}
	FAR(string raytype):Ray(raytype)
	{
		y=0;
	}

	~FAR(){}



	
};

// Second Actural Ray 
class SAR : public Ray  
{
private:
	double l1;
	double W;

public:
	SAR(){
		raytype="SAR";
	}
	SAR(string raytype):Ray(raytype){}
	
	~SAR(){}

	void set_l1(double l1)
	{
		this->l1=l1;
	}



	void set_W(double W)
	{
		this->W=W;
	}

	double get_l1() const
	{
		return l1;
	}



	double get_W() const
	{
		return W;
	}

	
};
