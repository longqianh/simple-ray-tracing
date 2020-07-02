#include<iostream>
#include "Ray.h"
using namespace std;


// 光学元件类
class Lens
{
private:

	int sf_num;
	double vd;
	double nf,nd,nc;
	// double rho1; // radius of curvature
	// double rho2;
	double t; // thick
	double n; // 

	struct Surface// surface
	{
		double rho;
	};
	
	struct Surface sf[5];


public:
	Lens(){;}
	~Lens(){;}

	void help(){

	}

	void set_paras(int sf_num,double *rho){
		for(int i=0;i<sf_num;i++){
			sf[i].rho=rho[i];	
		}
		
	}

	void print_paras(){
		;
	}

	double get_rho(int x){
		// if(x==1){
		// 	return rho1;
		// }
		// else{
		// 	return rho2;
		// }
		return 0;
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