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
/// file mcI.cpp
///
///
/// mcI  spatial rigid-body inertia from mass, CoM and rotational inertia.
/// mcI(m,c,I) calculates the spatial inertia matrix of a rigid body from its
/// mass, centre of mass (3D vector) and rotational inertia (3x3 matrix)
/// about its centre of mass.

#include <iostream>
#include "SpatialVectorArithmetic.h"
#include "Matrix.h"


float* sva::mcI (float m, float* c, float* I)
{
	matrix object;

	rbi = NULL;
	rbi = new float [36];
	

	float a[9] = {
		0,-c[2],c[1],
		c[2],0,-c[0],
		-c[1],c[0],0};

	float* C = a;

	float *Ct = object.Transponse(C,3,3);				//matrix C transpo...
	float *CC = object.Multiplication(C,3,3,Ct,3,3);

	float *mCC = object.ScalarMulti(CC,3,3,m);
	float *I_mCC = object.Sum(I,9,mCC);

	float *mC = object.ScalarMulti(C,3,3,m);
	float *mCt = object.ScalarMulti(Ct,3,3,m);

	float RBI[36] = {
		I_mCC[0],I_mCC[1],I_mCC[2],mC[0],mC[1],mC[2],
		I_mCC[3],I_mCC[4],I_mCC[5],mC[3],mC[4],mC[5],
		I_mCC[6],I_mCC[7],I_mCC[8],mC[6],mC[7],mC[8],
		mCt[0],mCt[1],mCt[2],m,0,0,
		mCt[3],mCt[4],mCt[5],0,m,0,
		mCt[6],mCt[7],mCt[8],0,0,m,
	};


	for (int i=0; i<36; i++)
	rbi[i] = RBI[i];	

	return rbi;
}




