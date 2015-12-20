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
//// file mpyLt.cpp
//
//
//
//
//
//
//

#include <iostream>
#include "BranchInducedSparsity.h"

using namespace std;

float* bis::mpyLt (float* L, int SizeL, float* lambda, float* x, int SizeX)
{	
	y_mpyLt = new float [SizeX];

	for (i=0;i<SizeL;i++)
	{
		y_mpyLt[i] = L[SizeL*i + i]*x[i];
		j = lambda[i];
		j--;
		
		while (j!=-1)
		{
			y_mpyLt[j] = y_mpyLt[j] + L[SizeL*i + j]*x[i];
			j = lambda[j];
			j--;
		}
	}

	return y_mpyLt;
}