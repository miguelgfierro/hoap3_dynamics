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
//// file planarN.cpp
//
//
//
//
//
//
//
//

#include <iostream>
#include "SpatialVectorArithmetic.h"
#include "Matrix.h"
#include "ModelConstructors.h"
#include "ArrayRelease.h"

using namespace std;

mc* mc::planarN (int n)
{
	matrix matrix_aux;
	sva sva_aux;
	mc* robot = new mc [n];

	robot[0].NB = n;
	for (i=0;i<n;i++) 
	{
		robot[i].pitch = 0;
		robot[i].parent = i;
	}

	float diag_aux[9] = {
		0.01,0,0,
		0,1/12,0,
		0,0,1/12};

	float* diag = NULL;
	diag = new float [9];
	for (i=0;i<9;i++)diag[i] = diag_aux[i];

	for (i=0;i<n;i++)
	{
		float array_ar[3] = {0.5,0,0};
		float* array_aux = array_ar; 
		
		robot[i].I = sva_aux.mcI(1,array_aux,diag);

		if (i==0)
		{
			float array_aux[3] = {0,0,0};
			robot[i].Xtree = sva_aux.Xtrans(array_aux);
		}
		else
		{
			float array_aux[3] = {1,0,0};
			robot[i].Xtree = sva_aux.Xtrans(array_aux);
		}
	}

	delete [] diag;
	return robot;
}
