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


float* matrix::ScalarMulti (float* A, int SizeAr, int SizeAc, float Scalar, int sign)		/// function for scalar multiplication 
{


	float* A_res  = NULL;
	A_res= new float [SizeAr*SizeAc];
	if (sign == 0)
	{
		if (SizeAr == 0)
		{
			for (i=0; i<SizeAc; i++)
			{
				A_res[i] = A[i]*Scalar; 
			}
		}
		else
		{
			for (i=0; i<SizeAr*SizeAc; i++)
			{
				A_res[i] = A[i]*Scalar; 
			}
		}
	}

	else if (sign == 1)
	{
		if (SizeAr == 0)
		{
			for (i=0; i<SizeAc; i++)
			{
				A_res[i] = A[i]/Scalar; 
			}
		}
		else
		{
			for (i=0; i<SizeAr*SizeAc; i++)
			{
				A_res[i] = A[i]/Scalar; 
			}
		}
	}

	else
	{
		cout << "NOT RECOGNIZED COMMEND";
	}

	

	return A_res;
}



double* matrix::ScalarMulti (double* A, int SizeAr, int SizeAc, double Scalar, int sign)		/// function for scalar multiplication 
{
	double* A_res_d = NULL;
	A_res_d = new double [SizeAr*SizeAc];
	if (sign == 0)
	{
		if (SizeAr == 0)
		{
			for (i=0; i<SizeAc; i++)
			{
				A_res_d[i] = A[i]*Scalar; 
			}
		}
		else
		{
			for (i=0; i<SizeAr*SizeAc; i++)
			{
				A_res_d[i] = A[i]*Scalar; 
			}
		}
	}

	else if (sign == 1)
	{
		if (SizeAr == 0)
		{
			for (i=0; i<SizeAc; i++)
			{
				A_res_d[i] = A[i]/Scalar; 
			}
		}
		else
		{
			for (i=0; i<SizeAr*SizeAc; i++)
			{
				A_res_d[i] = A[i]/Scalar; 
			}
		}
	}

	else
	{
		cout << "NOT RECOGNIZED COMMEND";
	}

	

	return A_res_d;
}

