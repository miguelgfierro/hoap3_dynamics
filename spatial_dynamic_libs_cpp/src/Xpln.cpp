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
//// file Xpln.cpp
//
//
//
// Xpln  coordinate transform for planar vectors.
// Xpln(theta,r) calculates the coordinate transform matrix from A to B
// coordinates for planar motion vectors, where coordinate frame B is
// located at point r (2D vector expressed in A coords) relative to frame A,
// and is rotated by an angle theta (radians) relative to A.
//
//

#include <iostream>
#include <math.h>
#include "PlanarVectorArithmetic.h"
#include "Matrix.h"

using namespace std;

float* pva::Xpln (double theta, float* r)
{
	matrix matrix_aux;

	c = cos(theta);
	s = sin(theta);

	if ((c<0.005)&&(c>-0.005)) c = 0;
	else if ((s<0.005)&&(s>-0.005)) s = 0;
	else if (s>0.999) s=1;
	else if (c>0.999) c=1;
	else if (s<-0.999) s=-1;
	else if (c<-0.999) c=-1;
	
	X = new float [9];

	float d1 = s*r[0] - c*r[1];
	float d2 = c*r[0] + s*r[1];

	float x[9] = {
		1,0,0,
		d1,c,s,
		d2,-s,c,
		};

	for (i=0;i<9;i++) X[i] = x[i];

	return X;
}