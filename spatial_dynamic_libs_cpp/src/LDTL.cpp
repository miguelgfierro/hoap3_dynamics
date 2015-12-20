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
/// file LDTL.cpp
//
//
//
//
//


#include <iostream>
#include "BranchInducedSparsity.h"
#include "Matrix.h"


using namespace std;

void bis::LTDL (float* H, int SizeH, float*lambda)
{
	matrix temp;
	bis bis_aux;

	D_ltdl = new float [SizeH*SizeH];
	L_ltdl = new float [SizeH*SizeH];

	float* h = H;

	for (k=SizeH-1;k>=0;k--)
	{
		i = lambda[k];
		i--;
			
			while (i!=-1)
			{
				a = h[k*SizeH + i] / h[SizeH*k +k];
				j = i;
			
				while (j!=-1)
				{
					h[i*SizeH +j] = h[i*SizeH +j] - a*h[k*SizeH +j];
					j = lambda[j];
					j--;
					
				}

				h[k*SizeH + i] = a;
				i = lambda[i];
				i--;
			}
	}


	D_ltdl = temp.DiagOfDiag(H,SizeH);
	L_ltdl = temp.Eye(SizeH);

	for (i=1; i<SizeH; i++)
	{
		for (k=1; k<i+1; k++)
		{
			L_ltdl[SizeH*i + k - 1] = h[SizeH*i + k - 1];
		}
	}
}
