#include<iostream>
using namespace std;

class Ray
{
private:

	double vd;
	double U;
	double l;

public:
	Ray(){;}
	~Ray(){;}
	void help(){

		cout<<"输入顺序: 物距、入射孔径角、阿贝常数"<<endl;

	}

	void ray_setting(double _U,double _l,double _vd){
		vd=_vd;
		U=_U;
		l=_l;

	}

	void print_para(){
		cout<<"物距: "<<l<<" mm"<<endl;
		cout<<"入射孔径角: "<<U<< "度"<<endl;
		cout<<"阿贝常数: "<<vd<<endl;
	

	}
	
};