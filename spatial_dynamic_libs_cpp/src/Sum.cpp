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

void  matrix::Sum(float* dst, float* A, float* B, int sign)  /// function is used to sume matrix A with matrix B
{
	if (sign == 0)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
		}
		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			dst[i] = A[i] + B[i];
		}
	}

	if (sign == 1)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
		}
		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			dst[i] = A[i] - B[i];
		}
	}
	if (sign == 2)
	{
		int Size = 6;
		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				dst[i*Size + j] = A[i*Size + j]-B[i*Size + j];
			}
		}
	}
		if (sign == 3)
	{
		int Size = 6;
		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				dst[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
	}
			if (sign == 4)
	{
		int Size = 0;
		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				dst[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
	}
}
float*  matrix::Sum(float* A, float* B, int sign)  /// function is used to sume matrix A with matrix B
{
	if (sign == 0)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
			return 0;
		}
		C_sum = new float [sizeof(A)*sizeof(A)];

		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			C_sum[i] = A[i] + B[i];
		}
		return C_sum;
	}

	if (sign == 1)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
			return 0;
		}
		C_sum = new float [sizeof(A)*sizeof(A)];

		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			C_sum[i] = A[i] - B[i];
		}
	
		return C_sum;
	}
	if (sign == 2)
	{
		C_sum = new float [36];
		int Size = 6;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum[i*Size + j] = A[i*Size + j]-B[i*Size + j];
			}
		}
		return C_sum;
	}
		if (sign == 3)
	{
		C_sum = new float [36];
		int Size = 6;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
		return C_sum;
	}
			if (sign == 4)
	{
		C_sum = new float [6];
		int Size = 0;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
		return C_sum;
	}

	//delete C;
}

float* matrix::Sum (float* A, int SizeA, float* B, int Sign)
{
	if (Sign == 0)
	{	
		C_sum = new float [SizeA];

		for (i=0; i<SizeA; i++)
		{
			C_sum[i] = A[i] + B[i];
		}
		return C_sum;
	}

	if (Sign == 1)
	{	
		C_sum = new float [SizeA];

		for (i=0; i<SizeA; i++)
		{
			C_sum[i] = A[i] - B[i];
		}
		return C_sum;
	}
}




//double 

double*  matrix::Sum(double* A, double* B, int sign)  /// function is used to sume matrix A with matrix B
{
	if (sign == 0)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
			return 0;
		}
		C_sum_d = new double [sizeof(A)*sizeof(A)];

		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			C_sum_d[i] = A[i] + B[i];
		}
		cout<<endl;
	
		return C_sum_d;
	}

	if (sign == 1)
	{	if (sizeof(A) != sizeof(B)) 
		{	
			cout << " ERROR - Matrix dimensions must agree";
			return 0;
		}
		C_sum_d = new double [sizeof(A)*sizeof(A)];

		for (i=0; i<sizeof(A)*sizeof(A); i++)
		{
			C_sum_d[i] = A[i] - B[i];
		}
	
		return C_sum_d;
	}
	if (sign == 2)
	{
		C_sum_d = new double [36];
		int Size = 6;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum_d[i*Size + j] = A[i*Size + j]-B[i*Size + j];
			}
		}
		return C_sum_d;
	}
		if (sign == 3)
	{
		C_sum_d = new double [36];
		int Size = 6;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum_d[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
		return C_sum_d;
	}
			if (sign == 4)
	{
		C_sum_d = new double [6];
		int Size = 0;

		for (i=0;i<6;i++)
		{
			for (j=0;j<6;j++)
			{
				C_sum_d[i*Size + j] = A[i*Size + j]+B[i*Size + j];
			}
		}
		return C_sum_d;
	}

	//delete C;
}

double* matrix::Sum (double* A, int SizeA, double* B, int Sign)
{
	if (Sign == 0)
	{	
		C_sum_d = new double [SizeA];

		for (i=0; i<SizeA; i++)
		{
			C_sum_d[i] = A[i] + B[i];
		}
		return C_sum_d;
	}

	if (Sign == 1)
	{	
		C_sum_d = new double [SizeA];

		for (i=0; i<SizeA; i++)
		{
			C_sum_d[i] = A[i] - B[i];
		}
		return C_sum_d;
	}
}
