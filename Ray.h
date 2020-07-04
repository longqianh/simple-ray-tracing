#pragma once
#include<iostream>
#include "utils.h"
using namespace std;


class Ray
{
protected:

	double U; //弧度
	// double W; //弧度
	// double y;
	double l; // 物距
	double i; // 入射角 弧度
	string label;
	// double lh;


public:
	Ray(){label="GR"; } // general ray
	~Ray(){}


	void set_U(double U){
		this->U=U;
	}
	
	void set_l(double l){
		this->l=l;
	}
	void set_i(double i){
		this->i=i;
	}

	string get_label() const
	{
		return label;
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

	void show_rayinfo(){
		cout<<"Ray type: "<<label<<endl;
		cout<<"U: "<<Arc2Angle(U)<<endl;
		if(abs(l)>0.01)cout<<"l: "<<l<<endl;
	}
	// void draw(){}
	
};


class FPL: public Ray
{
private:
	double l1;
public:
	FPL(){
		label="FPL"; // First Paraxial Light
	}
	FPL(double U){
		this->U=U;
		label="FPL"; 
	}
	~FPL(){}
	


};

class SPL: public Ray
{
private:
	double l1; // 对应的物距
	double y; // 对应的物高
	double W; // 物方视场角 弧度

public:
	SPL(){
		label="SPL"; // Second Paraxial Light
		l=0;
	}
	SPL(double W){
		label="SPL"; 
		l=0;
		this->W=W;
	}
	~SPL(){}


	void set_W(double W){
		this->W=W;
	}
	
	
	void set_l1(double l1){
		this->l1=l1;
	}

	void set_y(double y){
		this->y=y;
	}

	double get_W() const
	{
		return W;
	}
	double get_l1() const
	{
		return l1;
	
	}

	double get_y() const
	{
		return y;
	}

};