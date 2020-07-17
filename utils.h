#pragma once
#ifndef PI
#define PI 3.14159265358979323846264338
#endif

inline double Angle2Arc(double angle){
	return angle*PI/180;
}

inline double Arc2Angle(double arc){
	return arc*180/PI;
}

inline double myabs(double x){
	return x>0?x:-x;
}


