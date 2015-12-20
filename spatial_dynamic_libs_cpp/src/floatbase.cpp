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
//// file floatbase.cpp
//
//

#include <iostream>
#include "ArrayRelease.h"
#include "SpatialVectorArithmetic.h"
#include "ModelConstructors.h"
#include "Matrix.h"

using namespace std;

mc* mc::floatbase (mc* model)
{
	mc* fbmodel = new mc [model[0].NB+5];
	sva sva_aux;
	matrix matrix_aux;
	
	fbmodel[0].NB = model[0].NB + 5;
	
	float inf = 999999;
	float pi_h = 1.57;
	float array_aux9[9] = {
		0,0,0,
		0,0,0,
		0,0,0};
	float array_aux3[3] = {0,0,0};

	for(i=0;i<6;i++)
	{
		fbmodel[i].parent = i;
		if (i<3) fbmodel[i].pitch = inf;
		else fbmodel[i].pitch = 0;
	}
	for (i=1;i<model[0].NB;i++)
	{
		int temp = i+5;
		fbmodel[temp].parent = model[i].parent + 5;
		fbmodel[temp].pitch = model[i].pitch;
	}

	
	fbmodel[0].Xtree = sva_aux.Xroty(pi_h);
	fbmodel[1].Xtree = matrix_aux.Multiplication(sva_aux.Xrotx(-pi_h),6,6,sva_aux.Xroty(-pi_h),6,6);
	fbmodel[2].Xtree = sva_aux.Xrotx(pi_h); 
	fbmodel[3].Xtree = sva_aux.Xroty(pi_h);
	fbmodel[4].Xtree = matrix_aux.Multiplication(sva_aux.Xrotx(-pi_h),6,6,sva_aux.Xroty(-pi_h),6,6);
	fbmodel[5].Xtree = sva_aux.Xrotx(pi_h); 

	for (i=6;i<fbmodel[0].NB;i++)
	{
		fbmodel[i].Xtree = model[i-5].Xtree;
	}


	for (i=0;i<fbmodel[0].NB;i++)
	{
		if(i<6)
		{
			fbmodel[i].I = sva_aux.mcI(0,array_aux3,array_aux9);
		}
		else
		{
			fbmodel[i].I = model[i-5].I;
		}
	}
	return fbmodel;
}