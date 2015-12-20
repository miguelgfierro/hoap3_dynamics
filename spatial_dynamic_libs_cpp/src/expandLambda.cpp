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
/// file expandLambda.cpp
//
//
//
//
//



#include <iostream>
#include "BranchInducedSparsity.h"

using namespace std;


float* bis::expandLambda (float* lambda, int SizeLambda, float* nf, int SizeNF)
{
	for (i=0; i<SizeNF; i++) n += nf[i];

	map = NULL;
	newLambda = NULL;

	newLambda = new float [n - 1];
	map = new int [SizeLambda - 1];

	for (i=0;i<n-1;i++) newLambda[i] = i;

	map[0] = 0;

	for (i=0; i<SizeLambda; i++)
	{
		map[i+1] = map[i] + nf[i];
	}


	for (i=0; i<SizeLambda; i++)
	{
		int temp = map[i];
		int temp2 = lambda[i];

		newLambda[temp] = map[temp2];
	}
	return newLambda;

}