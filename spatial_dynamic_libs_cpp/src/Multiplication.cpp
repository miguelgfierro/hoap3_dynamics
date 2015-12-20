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


void matrix::Multiplication (float* dst, float* A, int SizeAr, int SizeAc, float* B, int SizeBr, int SizeBc)
{	
	/// function used to  multiply matrix A with B and C
	if (SizeBr == 0)
	{
		for(j = 0; j < SizeBc; j++)
		{
			p = 0;
			for(k = 0; k < SizeAc; k++)
			{	
				p += A[j * SizeAc + k] * B[k];
				dst[j] = p;
			}
		}
	}
	else
	{
		for(i = 0; i < SizeAr; i++)
		{	for(j = 0; j < SizeBc; j++)
			{
				p = 0;
				for(k = 0; k < SizeAc; k++)
				{	
					p += A[i * SizeAc + k] * B[k * SizeBr + j];
					dst[i * SizeBc + j] = p;
				}
			}
	    }
	}
}


float* matrix::Multiplication (float* A, int SizeAr, int SizeAc, float* B, int SizeBr, int SizeBc, float* D, int SizeDr, int SizeDc)
{	
	/// function used to  multiply matrix A with B and C
	
	if (SizeBr == 0)
	{
		float* C_Multiply2 = NULL;
		C_Multiply2 = new float [SizeBc];

		for(j = 0; j < SizeBc; j++)
		{
			p = 0;
			for(k = 0; k < SizeAc; k++)
			{	
				p += A[j * SizeAc + k] * B[k];
				C_Multiply2[j] = p;
			}
		}
		return C_Multiply2;
	}
	else
	{
		float* C_Multiply2 = NULL;
		C_Multiply2 = new float [SizeAr * SizeBc];

		for(i = 0; i < SizeAr; i++)
		{	for(j = 0; j < SizeBc; j++)
			{
				p = 0;
				for(k = 0; k < SizeAc; k++)
				{	
					p += A[i * SizeAc + k] * B[k * SizeBr + j];
					C_Multiply2[i * SizeBc + j] = p;
				}
			}
	    }
	
		if (D != 0)
		{
			float* C_Multiply3 = new float [SizeAr * SizeDc];
		
			for(i = 0; i < SizeAr; i++)
			{	
				for(j = 0; j < SizeDc; j++)
				{
					p = 0;
					for(k = 0; k < SizeAc; k++)
					{	
						p += C_Multiply2[i * SizeAc + k] * D[k * SizeDr + j];
						C_Multiply3[i * SizeDc + j] = p;
					}
				}
			}
			return C_Multiply3;
		}
		
		return C_Multiply2;
	}
}

