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


float* matrix::Eye (int Size)
{
	float* eye_matrix = new float [Size*Size];

	for (i=0;i<Size;i++)
	{
		for (j=0;j<Size;j++)
		{
			if(i==j)
			{
				eye_matrix[i*Size + j] = 1;
			}
			else
			{
				eye_matrix[i*Size + j] = 0;
			}
		}
	}

	return eye_matrix;
}

float* matrix::Zeros(int SizeAr, int SizeAc)
{
	if (SizeAr == 0)
	{	
		zeros = new float [SizeAc];
		for (i=0;i<SizeAc;i++) zeros[i] = 0;
		return zeros;
	}
	else
	{
		zeros = new float [SizeAr* SizeAc];

		for (i=0;i<SizeAr*SizeAc;i++) zeros[i] = 0;

		return zeros;
	}
}

float* matrix::Ones(int SizeAr, int SizeAc)
{
	ones = new float [SizeAr* SizeAc];

	for (i=0;i<SizeAr*SizeAc;i++) ones[i] = 1;

	return ones;
}

