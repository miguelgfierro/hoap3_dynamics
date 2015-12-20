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
/// file Xtrans.cpp
///
///
///
///
///
/// Calculate the 6x6 coordinate transform matrix that transforms a motion vector from A coordinates to B coordinates,
/// where the Cartesian frame that defines B coordinates (frame B) is translated relative to frame A by an amount r, 
/// which is a 3D vector giving the coordinates of the origin of frame B expressed in A coordinates


#include <iostream>
#include "SpatialVectorArithmetic.h"

using namespace std;



float* sva::Xtrans (float* r)
{
	x_trans = new float [36];

	float X[6 * 6] = {
		1,0,0,0,0,0,
		0,1,0,0,0,0,
		0,0,1,0,0,0,
		0,r[2],-r[1],1,0,0,
		-r[2],0,r[0],0,1,0,
		r[1],-r[0],0,0,0,1};

	for (int i=0;i<36;i++)
	x_trans[i] = X[i];

	return x_trans;
}


double* sva::Xtrans (double* r)
{
	x_trans_d = new double [36];

	float X[6 * 6] = {
		1,0,0,0,0,0,
		0,1,0,0,0,0,
		0,0,1,0,0,0,
		0,r[2],-r[1],1,0,0,
		-r[2],0,r[0],0,1,0,
		r[1],-r[0],0,0,0,1};

	for (int i=0;i<36;i++)
	x_trans_d[i] = X[i];

	return x_trans_d;
}