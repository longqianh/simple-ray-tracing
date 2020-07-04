#pragma once
#include<iostream>
using namespace std;

#ifndef PI
#define PI 3.14159265358979323846264338
#endif
#ifndef INF
#define INF 1e15
#endif



class Surface
{
private:
	double rho;
	double nd; // 与下一个面之间的主色光折射率
	double nf,nc; // 与下一个面之间的F光和C光折射率
	double vd; // 与下一个面之间的阿贝常数
	double d; // 到下一个面的距离
	double X; // 
	double PA; 
	// bool label; // true：最后一面


public:
	// Surface(double a=0,double b=1.0){ 
	// 	rho=a;
	// 	nd=b;
	// }
	Surface(){}
	Surface(double d,double r,double nd){
		this->nd=nd;
		this->d=d;
		if(r>INF){
			this->rho=0;
		}
		else{
			this->rho=1/r;
		}
	}
	~Surface(){}

	void set_d(double d)
	{
		this->d=d;
	}

	void set_rho(double r){
		if(r>INF){
			this->rho=0;
		}
		else{
			this->rho=1/r;
		}
	}
	void set_nd(double nd){
		this->nd=nd;
	}
	void set_nf(double nf){
		this->nf=nf;
	}
	void set_nc(double nc){
		this->nc=nc;
	}


	void set_PA(double PA){
		this->PA=PA;
		X=PA*PA*rho/2;
		// cout<<"PA set -- "<<PA<<endl;
		// cout<<"X set -- "<<X<<endl;
	}

	double get_d() const
	{
		return d;
	}

	double get_rho() const
 	{
		return rho;
	}
	double get_nd() const
	{
		return nd;
	}

	double get_nf() const
	{
		return nf;
	}
	double get_nc() const
	{
		return nc;
	}

	double get_X() const
	{
		return X;
	}

	double get_PA() const
	{
		return PA;
	}
};



// // 透镜类 : 设计失败
// class Lens
// {
// private:

// 	static int len_num;


// protected:
// 	int sf_num;
// 	double thick;
// 	string name;

// public:

// 	Lens(){}
// 	Lens(string s="len "+to_string(len_num)){
// 		len_num++;
// 		name=s;
// 	}
// 	~Lens(){}


// 	string get_name(){
// 		// cout<<name<<endl;
// 		return name;
// 	}
// 	double get_thick(){
// 		return thick;
// 	}

// 	int get_sfnum(){
// 		return sf_num;
// 	}

// 	// virtual Surface get_surface()=0;
	

// };


// class SingleLen:public Lens
// {
// private:
// 	Surface sf[2];

// public:
// 	SingleLen(double* rho,double* nd,double t){
// 		sf_num=2;
// 		for(int i=0;i<sf_num;i++){
// 			sf[i].set_rho(rho[i]);
// 			sf[i].set_nd(nd[i]);
// 		}
		
// 		thick=t;
// 	}
// 	~SingleLen(){}


// 	Surface get_sf(int index){
// 		return sf[index];
// 	}
	
// };


// class DoubleLen:public Lens
// {
// private:
// 	Surface sf[3];

// public:
// 	DoubleLen(double* rho,double* nd,double t){
// 		sf_num=3;
// 		for(int i=0;i<sf_num;i++){
// 			sf[i].set_rho(rho[i]);
// 			sf[i].set_nd(nd[i]);
// 		}
		
// 		thick=t;
// 	}
// 	~DoubleLen(){}


// 	Surface get_sf(int index){
// 		return sf[index];
// 	}
	
// };


// class TriLen:public Lens
// {
// private:
// 	Surface sf[4];

// public:
// 	TriLen(double* rho,double* nd,double t){
// 		sf_num=4;
// 		for(int i=0;i<sf_num;i++){
// 			sf[i].set_rho(rho[i]);
// 			sf[i].set_nd(nd[i]);
// 		}
		
// 		thick=t;
// 	}
// 	~TriLen(){}


// 	Surface get_sf(int index){
// 		return sf[index];
// 	}
	
// };
// int Lens::len_num=1;