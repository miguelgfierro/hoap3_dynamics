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

float* matrix::InvMat (float* A, int Size)
{
	matrix matrix_aux;
	float* InvMat = new float [Size*Size];
	double det = 1/matrix_aux.Determinant(A,Size);

	float* minor = new float [(Size-1)*(Size-1)];

	float aux = 0;

	for (i=0;i<Size*Size;i++) aux+=A[i];

	if (aux == Size)
	{
		for (int i=0; i<Size*Size; i++)
		{
			InvMat[i] = A[i];
		}
	}

	else
	{
		for(int j=0;j<Size;j++)
		{
			 for(int i=0;i<Size;i++)
			 {
			    // get the co-factor (matrix) of A(j,i)
				minor = matrix_aux.Minor(A,j,i,Size);

				InvMat[i*Size + j] = det*matrix_aux.Determinant(minor,Size-1);
		       
				if( (i+j)%2 == 1)
				{
					InvMat[i*Size + j] = -InvMat[i*Size + j];
				}
	        }
		}
	}

	return InvMat;
}

double* matrix::InvMat (double* A, int Size)
{
	matrix matrix_aux;
	double* InvMat = new double [Size*Size];
	double det = 1/matrix_aux.Determinant((float*)A,Size);

	cout <<"det inv: "<<det<<endl;
	double* minor = new double [(Size-1)*(Size-1)];

    for(int j=0;j<Size;j++)
    {
        for(int i=0;i<Size;i++)
        {
            // get the co-factor (matrix) of A(j,i)
			minor = matrix_aux.Minor(A,j,i,Size);

			InvMat[i*Size + j] = det*matrix_aux.Determinant(minor,Size-1);
		       
			if( (i+j)%2 == 1)
			{
				InvMat[i*Size + j] = -InvMat[i*Size + j];
			}
        }
    }

	return InvMat;
}


