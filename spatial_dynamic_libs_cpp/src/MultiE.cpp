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

using namespace std;

double* matrix::MultiE (double* A, double* B, int SizeBr, int SizeBc)
{	
	double* C_Multiply2 = new double[SizeBc*SizeBr];

	for(j = 0; j < SizeBc*SizeBr; j++)
	{
		C_Multiply2[j] = A[j]*B[j];
	}
	
	return C_Multiply2;
}

float matrix::MultiVect (float* A, float* B, int SizeBr)
{	
	float result; 

	for(j = 0; j < SizeBr; j++)
	{
		result = A[j]*B[j];
	}
	
	return result;
}