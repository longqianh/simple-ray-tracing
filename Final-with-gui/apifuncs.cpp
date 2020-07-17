#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
#include "apifuncs.h"



double* get_SAs(OptSys &sys, double l, double interval)
{
	int n = int(1 / interval);
	double* SAs = new double[n]();
	for (int i = 1; i <= n; i++)
	{
		double ku = double(i) / double(n);
		SAs[i] = sys.cal_SA(l, ku);
	}
	return SAs;
}


double* get_DTs(OptSys &sys, double l, double y_or_W, double interval)
{
	int n = int(1 / interval);
	double* DTs = new double[n]();
	for (int i = 1; i <= n; i++)
	{
		double kw = double(i) / double(n);
		double* tmp = sys.cal_DT(l, y_or_W, 1, kw);
		DTs[i] = tmp[1];
	}
	return DTs;
}


double* get_LCAxs(OptSys &sys,double* nfs, double* ncs, double l, double interval)
{
	int n = int(1 / interval);
	double* LCAxs = new double[n]();
	for (int i = 1; i <= n; i++)
	{
		double ku = double(i) / double(n);
		LCAxs[i] = sys.cal_LCAx(nfs, ncs, l, ku);
	}
	return LCAxs;
}
double* get_LCAys(OptSys &sys,double* nfs, double* ncs, double l, double y_or_W, double interval)
{
	int n = int(1 / interval);
	double* LCAys = new double[n]();
	for (int i = 1; i <= n; i++)
	{
		double kw = double(i) / double(n);
		LCAys[i] = sys.cal_LCAy(nfs, ncs, l, y_or_W, kw);
	}
	return LCAys;

}

double* get_ATMs(OptSys &sys, double l, double y_or_W, double interval)
{
	int n = int(1 / interval);
	double* ATMs = new double[n]();
	for (int i = 1; i <= n; i++)
	{
		double kw = double(i) / double(n);
		double* tmp = sys.cal_FCs(l, y_or_W, 1, kw);
		ATMs[i] = tmp[2];
	}
	return ATMs;
}
