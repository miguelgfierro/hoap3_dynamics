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
#include <math.h>

//using namespace std;

double matrix::Determinant(float* A,int m)   
{
	U = new float [m*m];
	L = new float [m*m];

	for (int i=0;i<m;i++) L[i*m+i] = 1;
	for (int i=0;i<m*m;i++) U[i] = A[i];

	for ( int k = 0; k < m-1; ++k)
	{
		for (int i = k+1; i < m; ++i)
		{
			L[i*m + k] = U[i*m + k] / U[k*m + k];
			for ( int j = 0; j < m; ++j)
				U[i*m + j] -= U[m*k + j] * L[m*i + k];
		}
	}

	float det = U[0];
	for (int i = 1; i < m; ++i)
		det *= U[i*m + i];

		delete [] U;
		delete [] L;
		return det;
}

double matrix::Determinant(double* A,int m)   
{

	matrix matrix_aux;
 int i,j;
 double sum = 0;
 double* c = new double [(m-1)*(m-1)];
 if(m==2)
  { 
	double a0 = A[0];
	double a1 = A[1];
	double a2 = A[2];
	double a3 = A[3];

	sum = a0*a3 - a1*a2;
	return sum;
  }
 for(int p=0;p<m;p++)
 {
  int h = 0,k = 0;
  for(i=1;i<m;i++)
  {
	for( j=0;j<m;j++)
	{
	 if(j==p)
	  continue;
	 c[h*(m-1) + k] = A[i*m + j];
	 k++;
	 if(k == m-1)
	  {
		 h++;
		 k = 0;
	  }

	}
  }
double a = -1;
double aux = A[p];
  sum = sum + aux*pow(a,p)*matrix_aux.Determinant(c,m-1);
 }
 return sum;
}