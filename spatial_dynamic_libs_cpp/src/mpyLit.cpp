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
//// file mpyLit.cpp
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

float* bis::mpyLit (float* L, int SizeL, float* lambda, float* x, int SizeX)
{
	y_mpyLit = new float [SizeX];

	for (i=SizeL - 1;i>=0;i++)
	{
		x[i] = x[i]/L[SizeL*i + i];
		j = lambda[i];
		j--;

		while (j!=-1)
		{
			
			x[j] = x[j] - L[SizeL*i + j]*x[i];
			j = lambda[j];
			j--;
		}
	}

	for (i=0;i<SizeX;i++) y_mpyLit[i] = x[i];
	return y_mpyLit;
}