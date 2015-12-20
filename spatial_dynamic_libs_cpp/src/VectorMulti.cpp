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
/// file VectroMulti.cpp
//
//
//
//
//
//



#include <iostream>
#include "Matrix.h"

using namespace std;

float* matrix::VectorMulti (float* A, float* B)
{	
	C_VectorMulti = new float [sizeof(A)];

	if (sizeof(A) == sizeof(B))
	{
		for (i=0;i<sizeof(A);i++)
		{
			C_VectorMulti[i] = A[i]*B[i];
		}
	}
	else 
	{
		cout << " vector dimensions does not match";
	}

	return C_VectorMulti;;
}

double* matrix::VectorMulti (double* A, double* B)
{	
	double* C_VectorMulti_d = new double [sizeof(A)];

	if (sizeof(A) == sizeof(B))
	{
		for (i=0;i<sizeof(A);i++)
		{
			C_VectorMulti_d[i] = A[i]*B[i];
		}
	}
	else 
	{
		cout << " vector dimensions does not match";
	}

	return C_VectorMulti_d;;
}