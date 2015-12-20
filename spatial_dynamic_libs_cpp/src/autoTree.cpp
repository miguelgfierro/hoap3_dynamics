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
//// file autoTree.cpp
//
//

#include <iostream>
#include "ModelConstructors.h"
#include "SpatialVectorArithmetic.h"
#include "Matrix.h"
#include "ArrayRelease.h"

using namespace std;

mc* mc::autoTree (int nb, int bf, int skew, int taper)
{
	mc* model = new mc [nb];
	matrix matrix_aux;
	sva sva_aux;

	I = new float [36];
	Xtree = new float [36];
		
	float diag[9] = {
		0.0025,0,0,
		0,1.015/12,0,
		0,0,1.015/12};

	model[0].NB = nb;
	for (i=0;i<nb;i++) model[i].pitch = 0;

	for (i=0;i<nb;i++)
	{
		model[i].parent = matrix_aux.Floor((i+matrix_aux.Ceil(bf))/bf);

		model[i].len = matrix_aux.PowerScalar(taper,i);

		if(model[i].parent == 0)
		{
			float aux_array[3] = {0,0,0};
			model[i].Xtree = sva_aux.Xtrans(aux_array);
		}
		else 
		{	
			int temp = 0;
			temp = model[i].parent; 
			float aux_array[3] = {model[temp].len,0,0};

			model[i].Xtree = matrix_aux.Multiplication(sva_aux.Xrotx(skew),6,6,sva_aux.Xtrans(aux_array),6,6);
		}

		model[i].mass = matrix_aux.PowerScalar(taper,3*i);

		float t = model[i].mass * model[i].len*model[i].len;

		float aux_array[3] = {0.5,0,0};
		CoM = matrix_aux.ScalarMulti(aux_array,0,3,model[i].len);
		Icm = matrix_aux.ScalarMulti(diag,3,3,t);
		model[i].I = sva_aux.mcI(model[i].mass,CoM,Icm);
	}

	return model;
}
