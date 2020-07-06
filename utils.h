#pragma once
#ifndef PI
#define PI 3.14159265358979323846264338
#endif

double Angle2Arc(double angle){
	return angle*PI/180;
}

double Arc2Angle(double arc){
	return arc*180/PI;
}

double myabs(double x){
	return x>0?x:-x;
}