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
/// file XtoV.cpp
///
///
/// % XtoV  obtain spatial vector from small-angle transform.
/// XtoV(X) interprets X as the coordinate transform from A to B coordinates,
/// and calculates the constant spatial velocity of a third frame, C(t), that
/// travels from A to B in one time unit.  Thus, C(0)=A, C(1)=B, dC/dt is a
/// constant, and the return value is the spatial velocity of C.  The
/// calculation uses a small-angle approximation, and is therefore only exact
/// if A and B are parallel.  The return value, v, is an invariant of X
/// (i.e., v=X*v), and can therefore be regarded as being expressed in either
/// A or B coordinates.




#include <iostream>
#include "SpatialVectorArithmetic.h"

using namespace std;




float* sva::Xtov (float *X)
{
	v = NULL;
	v = new float [6];

	float V[6] = {
		0.5*(X[1+12] - X [3+6]),
		0.5*(X[2] - X[12]),
		0.5*(X[6] - X[1]),
		0.5*(X[4+12] - X[5+6]),
		0.5*(X[5] - X[3+12]),
		0.5*(X[3+6] - X[4])
	};
	for (int i=0;i<6;i++)
	v[i] = V[i];

	return v;
}

double* sva::Xtov (double *X)
{
	v_d = NULL;
	v_d = new double [6];

	float V[6] = {
		0.5*(X[1+12] - X [3+6]),
		0.5*(X[2] - X[12]),
		0.5*(X[6] - X[1]),
		0.5*(X[4+12] - X[5+6]),
		0.5*(X[5] - X[3+12]),
		0.5*(X[3+6] - X[4])
	};
	for (int i=0;i<6;i++)
	v_d[i] = V[i];

	return v_d;
}
