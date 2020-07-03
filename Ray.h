#include<iostream>
using namespace std;


class Ray
{
protected:

	double U;
	double y;
	double l;
	double i; // 入射角
	// double lh;


public:
	Ray(){}
	Ray(double U){
		this->U=U;
	}
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
		cout<<"U: "<<U<<endl;
		cout<<"l: "<<l<<endl;
	}
	// void draw(){}
	
};


class FAL: public Ray
{
public:
	FAL(){}
	FAL(double U): Ray(U) {}
	~FAL(){}
	
};