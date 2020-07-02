#include<iostream>
#include "Ray.h"
using namespace std;


// 光学元件类
class Lens
{
private:

	double rho1; // radius of curvature
	double rho2;
	double t; // thick
	double n; // 


public:
	Lens();
	~Lens();

	void help(){

	}
	void set_paras(){

	}

	void print_paras(){
		;
	}

	double get_rho(int x){
		if(x==1){
			return this->rho1;
		}
		else{
			return this->rho2;
		}
	}


	double get_thick(){
		return t;
	}

	double get_n(){
		// get refractive index
		return n;
	}

	Ray get_rayout(Ray rayin){
		Ray rayout;
		return rayout;
	}


	
};