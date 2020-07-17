#pragma once
#include <iostream>
#include <vector>
#include "OptSys.h"

double* get_SAs(OptSys &sys,double l, double interval = 0.01); //球差曲线～随孔径变化的球差
double* get_DTs(OptSys &sys, double l, double y_or_W, double interval = 0.01); // 相对畸变曲线～随视场变化的相对畸变
double* get_LCAxs(OptSys &sys, double* nfs, double* ncs, double l, double interval = 0.01); // 位置色差曲线～随孔径变化的位置色差
double* get_LCAys(OptSys &sys, double* nfs, double* ncs, double l, double y_or_W, double interval = 0.01); // 倍率色差曲线～随视场变化的倍率色差	
double* get_ATMs(OptSys &sys, double l, double y_or_W, double interval = 0.01); // 像散曲线～随视场变化的像散

