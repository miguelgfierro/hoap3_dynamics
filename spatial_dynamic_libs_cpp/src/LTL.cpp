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
//// file LTL.cpp
//
//

#include <iostream>
#include "BranchInducedSparsity.h"
#include <math.h>
#include "Matrix.h"

using namespace std;

float* bis::LTL (float* H, int SizeH, float* lambda)
{
	matrix test;
	L_ltl = new float [SizeH*SizeH];
	float* h = H;

	for (k=SizeH-1; k>=0;k--)
	{

		H[SizeH*k + k] = sqrt(H[SizeH*k + k]); 
		i = lambda[k];
		i--;
		
		cout <<"i: "<<i<<endl;
		test.Display(H,3,3);
		cout<<endl;

		

		while (i!=-1)
		{
			H[SizeH*k + i] = H[SizeH*k + i] / H[SizeH*k + k];
			i = lambda[i];
			i--;
		}
		
		i = lambda [k];
		i--;
		while (i!=-1)
		{
			j=i;
			j;
			while(j!=-1)
			{
				H[SizeH*i+j] = H[SizeH*i+j] - H[SizeH*k+i]*H[SizeH*k+j];  
				j = lambda[j];
				j--;
			}

			i = lambda[i];
			i--;
		}
	}

	for(i=0; i<SizeH*SizeH; i++) L_ltl[i] = H[i]; 

	for(i=0;i<SizeH;i++)
	{
		for(j=1;j<SizeH;j++)
		{
			if(j>i)
			{
				L_ltl[i*SizeH + j] = 0;
			}
		}
	}
	return L_ltl;
}
