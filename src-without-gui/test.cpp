#include<stdio.h>
#include "API_funcs.h"
using namespace std;


int main()
{
	cal_test();


	// int nsf=3;
	// double a=20;
	// double l=-500;
	// double y=26;
	// double dists[]={4,2.5,60};
	// double rs[]={62.5,-43.65,-124.35};
	// double nfs[]={1.5223709191,1.6875154791,1};
	// double nds[]={1.5167969495,1.6727015725,1};
	// double ncs[]={1.5143226707,1.6666104143,1};
	
	// OptSys sys;
	// // sys.show_sysinfo();
	// sys.set_sys(a,nsf,dists,rs,nds,nfs,ncs);
	// sys.show_sysinfo();
	// vector<double> res;
	// double * ans=sys.get_DTs(l,y);

	// // sys.cal_allres(res,l,y,nfs,ncs);
	// cout<<"[";
	// for(int k=0;k<100;k++){
	// 	cout<<ans[k]<<',';

	// }
	// cout<<']';

	// double tmp=sys.cal_SA(l);
	// cout<<tmp;
	// FPR rayin(-500);
	// Ray rayout1=sys.ray_tracing(rayin);
	// Ray rayout2=sys.ray_tracing(rayin,0.7);
	// rayout1.show_rayinfo();
	// rayout2.show_rayinfo();
	// cout<<sys.cal_SA(l,0.5)<<endl;
	// double SAs[100]={0};
	// double LCAx[100]={0};
	// for (int ku = 1; ku<100; ku++)
	// {
	// 	SAs[ku]=sys.cal_SA(l,ku/100.0);
	// 	// sys.cal_LCAx(nfs,ncs,l)
	// }
	// cout<<"[";
	// for (int i = 0; i < 100; ++i)
	// {
	// 	if(i<99)
	// 	{
	// 		cout<<SAs[i]<<",";
	// 	}
	// 	else
	// 		cout<<SAs[i];
		
	// }
	// cout<<"]";
	// return 0;

}


	// double ku=1,kw=1;
	// int nsf=3;
	// double a=20;
	// bool isINF;
	// string raytype;
	// double dists[]={4,2.5,60};
	// double rs[]={62.5,-43.65,-124.35};
	// double nfs[]={1.5223709191,1.6875154791,1};
	// double nds[]={1.5167969495,1.6727015725,1};
	// double ncs[]={1.5143226707,1.6666104143,1};
	
	// double l=-500; // 物距：用户输入 左负右正
	// double y=26; // 像高 ：上正下负
	// double W=3; // 物方视场角：用户输入
	// double y_or_W=y;
	// vector<double> res;
	// cal_res(a,nsf,dists,rs,nfs,nds,ncs,l,y_or_W,res);
	// double * p=res.data();
	// for (int k = 0; k<res.size() ; k++)
	// {
	// 	cout<<*(p+k)<<endl;
	// }