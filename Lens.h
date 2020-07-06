#pragma once
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
	double n; // 与下一个面之间的折射率
	double d; // 到下一个面的距离
	double X; // 
	double PA; 

public:
	Surface(){}
	Surface(double d,double r,double n){
		this->n=n;
		this->d=d;
		if(r>INF||r>-INF){
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
	void set_n(double n){
		this->n=n;
	}


	void set_PA(double PA){
		this->PA=PA;
		X=PA*PA*rho/2;
	}

	double get_d() const
	{
		return d;
	}

	double get_rho() const
 	{
		return rho;
	}
	double get_n() const
	{
		return n;
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



// 设计失败的透镜类
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