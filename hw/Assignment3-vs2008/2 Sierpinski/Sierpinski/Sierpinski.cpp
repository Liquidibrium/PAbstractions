/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "gobjects.h"
#include <cmath>
using namespace std;
#define PI 3.14159265
void drawTriangle(GWindow& canvas,const double& THETA, GPoint& p,double edgeLength ,const double& rotateAngle){
	double x0 , y0 ,x1 , y1 , x2 ,y2 ;
	x0 = p.getX();
	y0 = p.getY();
	x1 = x0 + edgeLength * cos(rotateAngle * PI / 180);
	y1 = y0 - edgeLength * sin(rotateAngle * PI / 180);
	x2 = x0 + edgeLength * cos((THETA + rotateAngle) * PI / 180);
	y2 = y0 - edgeLength * sin((THETA + rotateAngle) * PI / 180);
	canvas.add(new GLine(x0, y0, x1, y1));
	canvas.add(new GLine(x1, y1, x2, y2));
	canvas.add(new GLine(x0, y0, x2, y2));
}
void drawFractal(GWindow& canvas, double edgeLength, int fractalOrder, const double& THETA, GPoint p ,const double& rotateAngle){
	if(fractalOrder==0)	return;
	double x1 = p.getX() + edgeLength / 4;
	double y1 = p.getY() - (edgeLength * sqrt(3.0) /4);
	GPoint p1(x1,y1);
	drawTriangle(canvas,THETA,p1,edgeLength / 2,rotateAngle);
	drawFractal(canvas,  edgeLength / 2, fractalOrder - 1,  THETA, p, rotateAngle);
	drawFractal(canvas,  edgeLength / 2, fractalOrder - 1,  THETA, p1, rotateAngle);
	GPoint p2((p.getX()) + edgeLength / 2,p.getY());
	drawFractal(canvas,  edgeLength / 2, fractalOrder - 1,  THETA, p2, rotateAngle);
}
int main() {
	const static double THETA = 60;
	const static double rotateAngle = -60;
	const static double startAngle = 0;
	int edgeLength, fractalOrder;
	cout<<" enter edge length : ";
	cin>>edgeLength;
	cout<<" enter fractal order : ";
	cin>>fractalOrder;
	GWindow canvas(1000,700);
	double startX = (canvas.getWidth() - edgeLength) / 2;
	double startY = (canvas.getHeight() + edgeLength * sqrt(3.0) / 2) / 2;
	GPoint p(startX, startY);
	drawTriangle(canvas, THETA, p, edgeLength,startAngle);
	drawFractal(canvas, edgeLength, fractalOrder, THETA,p,rotateAngle);
    return 0;
}
