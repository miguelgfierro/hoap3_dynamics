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
/// file mpyH.cpp
//
//
//

#include <iostream>
#include "BranchInducedSparsity.h"

using namespace std;

float* bis::mpyH (float* H, int SizeH, float* lambda, float* x, int SizeX)
{

	y_mpyH = new float [SizeX];

	for (i=0;i<SizeH;i++)
	{
		y_mpyH[i] = H[SizeH*i + i]*x[i];
	}

	for (i=SizeH - 1;i>=0;i--)
	{
		j = lambda[i];
		j--;

		while (j!=-1)
		{
			y_mpyH[i] = y_mpyH[i] + H[SizeH*i +j]*x[j];
			y_mpyH[j] = y_mpyH[j] + H[SizeH*i +j]*x[i];

			j = lambda[j];
			j--;
		}
	}



	return y_mpyH;
}