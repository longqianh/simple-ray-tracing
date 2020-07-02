#include<iostream>
using namespace std;


class Ray
{
private:

	double U;
	double l;
	double i; // 入射角
	double lh;

public:
	Ray(double a,double b){
		U=a;
		l=b;
	}
	~Ray(){}




	void set_U(double x){
		U=x;
	}
	void set_l(double x){
		l=x;
	}

	void cal_i(){

	}
	void cal_lh(){

	}
	
	double get_U(){
		return U;
	}
	double get_l(){
		return l;
	}
	double get_i(){
		return i;
	}
	double get_lh(){
		return lh;
	}


	// void draw(){}
	
};