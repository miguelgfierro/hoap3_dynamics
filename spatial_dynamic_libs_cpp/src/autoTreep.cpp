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
//// file autoTreep.cpp
//
//
//
//
//
//
#include <iostream>
#include "Matrix.h"
#include "PlanarVectorModelConstructors.h"
#include "PlanarVectorArithmetic.h"
#include "ArrayRelease.h"
#include <math.h>

using namespace std;


pvmc* pvmc::autoTreep (int nb, int bf, int taper)
{	
	pva pva_aux;
	matrix matrix_aux;
	pvmc* model;

	model = new pvmc [nb];

	model[0].NB = nb;
	for (i=0;i<nb;i++) model[i].jcode = 1;

	for (i=0;i<nb;i++)
	{
		model[i].parent = matrix_aux.Floor(matrix_aux.Floor(i+1 +matrix_aux.Ceil(bf))/bf);
		
		if (model[i].parent == 0)
		{
			float array_aux[2] = {0,0};
			model[i].Xtree = pva_aux.Xpln(0,array_aux);
		}
		else 
		{
			float temp = pow(taper, model[i].parent-1);
			float array_aux[2] = {temp,0};
			model[i].Xtree = pva_aux.Xpln(0,array_aux);
		}
		model[i].len = matrix_aux.PowerScalar(taper,i);
		model[i].mass = matrix_aux.PowerScalar(taper,3*i);

		float array_aux_p[2] = {(model[i].len)/2,0};
		float* array_aux = array_aux_p;
		
		float I_aux = model[i].mass*model[i].len*model[i].len*1.015/12; 

		model[i].I = pva_aux.mcIp(model[i].mass, array_aux, I_aux);
	}
	return model;
}