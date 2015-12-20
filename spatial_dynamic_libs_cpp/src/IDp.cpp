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


#include <iostream>
#include "PlanarVectorDynamicsFunctions.h"
#include "Matrix.h"
#include "PlanarVectorArithmetic.h"
#include "PlanarVectorDynamicsFunctions.h"
#include "ArrayRelease.h"

using namespace std;


float* pvdf::IDp(pvmc* model, float* q_i, float* qd_i, float* qdd_i, float* f_ext, float* grav_accn)
{
	pvdf* pvdf_aux = new pvdf [model[0].NB];
	matrix matrix_aux;
	pva pva_aux;

	tau = new float [model[0].NB];

	float* a_grav = NULL;

	if (grav_accn == 0)
	{
		float a_grav_pos[6] = {0,0,0};
		a_grav = a_grav_pos;
	}
	else
	{
		float a_grav_pos[6] = {0,grav_accn[0],grav_accn[1]};
		a_grav = a_grav_pos;
	}

	if ((f_ext != 0)&& (grav_accn != 0)) external_force = 1;
	
	for (i=0;i<model[0].NB;i++)
	{
		pvdf_aux[i].jcalcp(model[i].jcode,q_i[i]);
		pvdf_aux[i].vJ = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qd_i[i]);
		pvdf_aux[i].Xup = matrix_aux.Multiplication(pvdf_aux[i].Xj,3,3,model[i].Xtree,3,3);

		if (model[i].parent == 0)
		{
			pvdf_aux[i].v = pvdf_aux[i].vJ;
			float* Xup_a_grav = matrix_aux.ScalarMulti(matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,a_grav,0,3),0,3,-1);
			float* S_qdd = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qdd_i[i]);
			pvdf_aux[i].a = matrix_aux.Sum(Xup_a_grav,S_qdd,4);
		}
		else
		{
			int temp = model[i].parent - 1;
			pvdf_aux[i].v = matrix_aux.Sum(matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].v,0,3),pvdf_aux[i].vJ,4);

			float* asd = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].v,0,3);
			
			float* Xup_a = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].a,0,3);
			float* S_qdd = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qdd_i[i]);
			float* crmp_vJ = matrix_aux.Multiplication(pva_aux.crmp(pvdf_aux[i].v),3,3,pvdf_aux[i].vJ,0,3);

			float* aux = matrix_aux.Sum(Xup_a,S_qdd,4);
			pvdf_aux[i].a = matrix_aux.Sum(aux,crmp_vJ,4);
		}
		
		float* I_a = matrix_aux.Multiplication(model[i].I,3,3,pvdf_aux[i].a,0,3);
		float* crfp_I = matrix_aux.Multiplication(pva_aux.crfp(pvdf_aux[i].v),3,3,model[i].I,3,3);
		float* crfp_I_v = matrix_aux.Multiplication(crfp_I,3,3,pvdf_aux[i].v,0,3);

		pvdf_aux[i].f = matrix_aux.Sum(I_a,crfp_I_v,4);
	
		if (external_force)
		{
			int as = f_ext[i];
			pvdf_aux[i].f = matrix_aux.ScalarAdd(pvdf_aux[i].f,3,as,1);
		}
	}


	for (i=model[0].NB - 1;i>=0;i--)
	{
		float *temp = matrix_aux.Multiplication(pvdf_aux[i].S,0,3,pvdf_aux[i].f,0,3);

		tau[i] = temp[0];
			if (model[i].parent != 0)
			{
				int temp = model[i].parent - 1;
				float* Xup_f = matrix_aux.Multiplication(matrix_aux.Transponse(pvdf_aux[i].Xup,3,3),3,3,pvdf_aux[i].f,0,3);

				pvdf_aux[temp].f = matrix_aux.Sum(pvdf_aux[temp].f,Xup_f); 
			}
	}
	
	return tau;
}
