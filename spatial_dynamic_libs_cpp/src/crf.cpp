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
/// file crf.cpp
///
///
/// crf  spatial cross-product operator (force).
/// crf(v) calculates the 6x6 matrix such that the expression crf(v)*f is the
/// cross product of the spatial motion vector v with the spatial force
/// vector f.




#include <iostream>
#include "SpatialVectorArithmetic.h"
#include "Matrix.h"

using namespace std;


void sva::crf (float* dst, float* v)
{
	matrix matrix_aux;
	float VCROSS[36] = {
		0,		v[2],	-v[1],	0,		0,		0,
		-v[2],	0,		v[0],	0,		0,		0,
		v[1],	-v[0],	0,		0,		0,		0,
		0,		v[5],	-v[4],	0,		v[2],	-v[1],
		-v[5],	0,		v[3],	-v[2],	0,		v[0],
		v[4],	-v[3],	0,		v[1],	-v[0],	0
	};
	
	for (int i=0; i<36; i++)
	dst[i] = VCROSS[i];

	dst = matrix_aux.Transponse(dst,6,6);
}

float* sva::crf (float* v)
{
	matrix matrix_aux;

	vcross_crf = new float [36];
	float VCROSS[36] = {
		0,		v[2],	-v[1],	0,		0,		0,
		-v[2],	0,		v[0],	0,		0,		0,
		v[1],	-v[0],	0,		0,		0,		0,
		0,		v[5],	-v[4],	0,		v[2],	-v[1],
		-v[5],	0,		v[3],	-v[2],	0,		v[0],
		v[4],	-v[3],	0,		v[1],	-v[0],	0
	};
	
	for (int i=0; i<36; i++)
	vcross_crf[i] = VCROSS[i];

	vcross_crf = matrix_aux.Transponse(vcross_crf,6,6);

	return vcross_crf;
}

double* sva::crf (double* v)
{
	matrix matrix_aux;

	vcross_crf_d = new double [36];
	double VCROSS[36] = {
		0,		v[2],	-v[1],	0,		0,		0,
		-v[2],	0,		v[0],	0,		0,		0,
		v[1],	-v[0],	0,		0,		0,		0,
		0,		v[5],	-v[4],	0,		v[2],	-v[1],
		-v[5],	0,		v[3],	-v[2],	0,		v[0],
		v[4],	-v[3],	0,		v[1],	-v[0],	0
	};
	
	for (int i=0; i<36; i++)
	vcross_crf_d[i] = VCROSS[i];

	vcross_crf_d = matrix_aux.Transponse(vcross_crf_d,6,6);

	return vcross_crf_d;
}