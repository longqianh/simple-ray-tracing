#include<iostream>
// #include "Ray.h"
using namespace std;

// 光学元件类

class Surface
{
private:
	double rho;
	double nd; // 与下一个面之间的主色光折射率
	double nf,nc; // 与下一个面之间的F光和C光折射率
	double vd; // 与下一个面之间的阿贝常数


public:
	Surface(double a=0,double b=1.0){ 
		rho=a;
		nd=b;
	}
	~Surface(){}

	double get_rho(){
		return rho;
	}
	double get_nd(){
		return nd;
	}

	double get_nf(){
		return nf;
	}
	double get_nc(){
		return nc;
	}

	void set_rho(double x){
		rho=x;
	}
	void set_nd(double x){
		nd=x;
	}
	void set_nf(double x){
		nf=x;
	}
	void set_nc(double x){
		nc=x;
	}


	void get_paras(){}

};




class Lens
{
private:

	static int len_num;


protected:
	int sf_num;
	double thick;
	string name;

public:



	Lens(string s="len "+to_string(len_num)){
		len_num++;
		name=s;
	}
	~Lens(){}


	string get_name(){
		// cout<<name<<endl;
		return name;
	}
	double get_thick(){
		return thick;
	}

	int get_sfnum(){
		return sf_num;
	}

	// virtual Surface get_surface()=0;
	

};


class SingleLen:public Lens
{
private:
	Surface sf[2];

public:
	SingleLen(double* rho,double* nd,double t){
		sf_num=2;
		for(int i=0;i<sf_num;i++){
			sf[i].set_rho(rho[i]);
			sf[i].set_nd(nd[i]);
		}
		
		thick=t;
	}
	~SingleLen(){}


	Surface get_sf(int index){
		return sf[index];
	}
	
};


class DoubleLen:public Lens
{
private:
	Surface sf[3];

public:
	DoubleLen(double* rho,double* nd,double t){
		sf_num=3;
		for(int i=0;i<sf_num;i++){
			sf[i].set_rho(rho[i]);
			sf[i].set_nd(nd[i]);
		}
		
		thick=t;
	}
	~DoubleLen(){}


	Surface get_sf(int index){
		return sf[index];
	}
	
};


class TriLen:public Lens
{
private:
	Surface sf[4];

public:
	TriLen(double* rho,double* nd,double t){
		sf_num=4;
		for(int i=0;i<sf_num;i++){
			sf[i].set_rho(rho[i]);
			sf[i].set_nd(nd[i]);
		}
		
		thick=t;
	}
	~TriLen(){}


	Surface get_sf(int index){
		return sf[index];
	}
	
};
