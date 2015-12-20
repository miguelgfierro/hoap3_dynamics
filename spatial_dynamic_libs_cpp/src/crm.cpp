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
/// file crm.cpp
///
///
/// crm  spatial cross-product operator (motion).
/// crm(v) calculates the 6x6 matrix such that the expression crm(v)*m is the
/// cross product of the spatial motion vectors v and m.




#include <iostream>
#include "SpatialVectorArithmetic.h"

using namespace std;



void sva::crm (float* dst, float* v)
{
	float VCROSS[36] = {
		0,-v[2],v[1],0,0,0,
		v[2],0,-v[0],0,0,0,
		-v[1],v[0],0,0,0,0,
		0,-v[5],v[4],0,-v[2],v[1],
		v[5],0,-v[3],v[2],0,-v[0],
		-v[4],v[3],0,-v[1],v[0],0
	};

	for (int i=0;i<36;i++)
	dst[i] = VCROSS[i];
}
float* sva::crm (float* v)
{
	vcross_crm = new float [36];

	float VCROSS[36] = {
		0,-v[2],v[1],0,0,0,
		v[2],0,-v[0],0,0,0,
		-v[1],v[0],0,0,0,0,
		0,-v[5],v[4],0,-v[2],v[1],
		v[5],0,-v[3],v[2],0,-v[0],
		-v[4],v[3],0,-v[1],v[0],0
	};

	for (int i=0;i<36;i++)
	vcross_crm[i] = VCROSS[i];

	return vcross_crm;
}
double* sva::crm (double* v)
{
	vcross_crm_d = new double [36];

	double VCROSS[36] = {
		0,-v[2],v[1],0,0,0,
		v[2],0,-v[0],0,0,0,
		-v[1],v[0],0,0,0,0,
		0,-v[5],v[4],0,-v[2],v[1],
		v[5],0,-v[3],v[2],0,-v[0],
		-v[4],v[3],0,-v[1],v[0],0
	};

	for (int i=0;i<36;i++)
	vcross_crm_d[i] = VCROSS[i];

	return vcross_crm_d;
}
