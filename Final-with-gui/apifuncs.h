#pragma once
#include <iostream>
#include <vector>
#include "OptSys.h"

double* get_SAs(OptSys &sys,double l, double interval = 0.01); //������ߡ���׾��仯�����
double* get_DTs(OptSys &sys, double l, double y_or_W, double interval = 0.01); // ��Ի������ߡ����ӳ��仯����Ի���
double* get_LCAxs(OptSys &sys, double* nfs, double* ncs, double l, double interval = 0.01); // λ��ɫ�����ߡ���׾��仯��λ��ɫ��
double* get_LCAys(OptSys &sys, double* nfs, double* ncs, double l, double y_or_W, double interval = 0.01); // ����ɫ�����ߡ����ӳ��仯�ı���ɫ��	
double* get_ATMs(OptSys &sys, double l, double y_or_W, double interval = 0.01); // ��ɢ���ߡ����ӳ��仯����ɢ

