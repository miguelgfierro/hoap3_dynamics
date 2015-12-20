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
//// file VectorDivision.cpp
//
//
//
//
//
//
//
//
#include <iostream>
#include "Matrix.h"

float* matrix::VectorDivision (float* A, int SizeAr, int SizeAc, float* B, int SizeB)
{
	C_Vector_Div = new float [SizeAr];

	if (SizeAc == 0)
	{
		for(i = 0; i < SizeB; i++)
		{
			temp = A[i]/B[i];
			C_Vector_Div[0] += temp;
		}

		C_Vector_Div[0] /= SizeB; 
	}


	else
	{
		for(i = 0; i < SizeAr; i++)
		{	for(j = 0; j < SizeB; j++)
			{
				temp = A[i * SizeAc + j] / B[j];
				C_Vector_Div[i] += temp;
			}
		C_Vector_Div[i] = C_Vector_Div[i]/SizeB;
		}
	}

	return C_Vector_Div;

}

double* matrix::VectorDivision (double* A, int SizeAr, int SizeAc, double* B, int SizeB)
{
	double* C_Vector_Div_d = new double [SizeAr];

	if (SizeAc == 0)
	{
		for(i = 0; i < SizeB; i++)
		{
			temp = A[i]/B[i];
			C_Vector_Div_d[0] += temp;
		}

		C_Vector_Div_d[0] /= SizeB; 
	}


	else
	{
		for(i = 0; i < SizeAr; i++)
		{	for(j = 0; j < SizeB; j++)
			{
				temp = A[i * SizeAc + j] / B[j];
				C_Vector_Div_d[i] += temp;
			}
		C_Vector_Div_d[i] = C_Vector_Div_d[i]/SizeB;
		}
	}

	return C_Vector_Div_d;

}