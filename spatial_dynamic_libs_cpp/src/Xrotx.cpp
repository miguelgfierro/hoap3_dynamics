//
// Author: Miguel González-Fierro <mgpalaci@ing.uc3m.es>, (C) 2011
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
/// file Xrotx.cpp
///
///
/// Xrotx  spatial coordinate transform (X-axis rotation).
/// Xrotx(theta) calculates the coordinate transform matrix from A to B
/// coordinates for spatial motion vectors, where coordinate frame B is
/// rotated by an angle theta (radians) relative to frame A about their
/// common X axis.


#include <iostream>
#include <math.h>
#include "SpatialVectorArithmetic.h"

using namespace std;




float* sva::Xrotx (double theta)
{
	float c = cos (theta);
	float s = sin (theta);

	if ((c<0.005)&&(c>-0.005)) c = 0;
	if ((s<0.005)&&(s>-0.005)) s = 0;
	if (s>0.999) s=1;
	if (c>0.999) c=1;
	if (s<-0.999) s=-1;
	if (c<-0.999) c=-1;

	x_rotx = NULL;
	x_rotx = new float [36];

	float X[36] = {
		1,0,0,0,0,0,
		0,c,s,0,0,0,
		0,-s,c,0,0,0,
		0,0,0,1,0,0,
		0,0,0,0,c,s,
		0,0,0,0,-s,c
	};

	for (int i=0;i<36;i++)
	x_rotx[i] = X[i];

	return x_rotx;
}

double* sva::Xrotx_d (double theta)
{
	double c = cos (theta);
	double s = sin (theta);

	if ((c<0.005)&&(c>-0.005)) c = 0;
	if ((s<0.005)&&(s>-0.005)) s = 0;
	if (s>0.999) s=1;
	if (c>0.999) c=1;
	if (s<-0.999) s=-1;
	if (c<-0.999) c=-1;

	x_rotx_d = NULL;
	x_rotx_d = new double [36];

	double X[36] = {
		1,0,0,0,0,0,
		0,c,s,0,0,0,
		0,-s,c,0,0,0,
		0,0,0,1,0,0,
		0,0,0,0,c,s,
		0,0,0,0,-s,c
	};

	for (int i=0;i<36;i++)
	x_rotx_d[i] = X[i];

	return x_rotx_d;
}