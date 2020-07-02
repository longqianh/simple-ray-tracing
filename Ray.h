#include<iostream>
using namespace std;


class Ray
{
private:

	double U;
	double l;



public:
	Ray(){;}
	~Ray(){;}

	double i; // 入射角
	double lh;

	void help(){

		cout<<"输入顺序: 物距、入射孔径角"<<endl;

	}

	void set_para(double _U,double _l){
		U=_U;
		l=_l;
	}

	void print_para(){
		cout<<"物距: "<<l<<" mm"<<endl;
		cout<<"入射孔径角: "<<U<< "度"<<endl;
	

	}
	
};