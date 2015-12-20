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

#include <iostream>
#include "Matrix.h"

//using namespace std;

float* matrix::Transponse (float* A, int SizeAr, int SizeAc)   // function used to determine transpose matrix A (A')
{
	C_transponse = new float [SizeAc * SizeAr];

	for(i = 0; i < SizeAr; i++)
	{
		for(j = 0; j < SizeAc; j++)
		{
			p1 = i * SizeAc + j; 
			p2 = j * SizeAr + i; 
			C_transponse[p2] = A[p1];
		}
	}

	return C_transponse;

}

double* matrix::Transponse (double* A, int SizeAr, int SizeAc)   // function used to determine transpose matrix A (A')
{
	double* C_transponse_d = new double [SizeAc * SizeAr];

	for(i = 0; i < SizeAr; i++)
	{
		for(j = 0; j < SizeAc; j++)
		{
			p1 = i * SizeAc + j; 
			p2 = j * SizeAr + i; 
			C_transponse_d[p2] = A[p1];
		}
	}

	return C_transponse_d;

}
