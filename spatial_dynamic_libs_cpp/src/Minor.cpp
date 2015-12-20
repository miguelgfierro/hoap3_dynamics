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

float* matrix::Minor(float* A, int row, int col, int Size)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;

	float* B = new float [(Size-1)*(Size-1)];

    for(int i = 0; i < Size; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < Size; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    B[rowCount*(Size-1) + colCount] = A[i*Size + j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }

    return B;
}

double* matrix::Minor(double* A, int row, int col, int Size)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;

	double* B = new double [(Size-1)*(Size-1)];

    for(int i = 0; i < Size; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < Size; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    B[rowCount*(Size-1) + colCount] = A[i*Size + j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }

    return B;
}
