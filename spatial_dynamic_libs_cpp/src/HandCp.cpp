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
#include "Matrix.h"
#include "ArrayRelease.h"
#include "PlanarVectorModelConstructors.h"
#include "PlanarVectorDynamicsFunctions.h"


using namespace std;

void pvdf::HandCp (pvmc* model, float* q_i, float* qd_i, float* f_ext, float* grav_accn)
{
	pvdf* pvdf_aux = new pvdf [model[0].NB];
	pva pva_aux;
	matrix matrix_aux;
	int max = model[0].NB;
	C = new float [max];
	H = new float [max*max];


	float* a_grav = NULL;
	float* a_grav_n = NULL;

	if (grav_accn == 0)
	{
		float a_grav_pos[3] = {0,0,0};
		a_grav = a_grav_pos;
		a_grav_n = a_grav;
	}
	else
	{
		float a_grav_pos[3] = {0,grav_accn[0],grav_accn[1]};
		float a_grav_neg[3] = {0,-grav_accn[0],-grav_accn[1]};
		a_grav = a_grav_pos;
		a_grav_n = a_grav_neg;
	}

	if ((f_ext != 0) && (grav_accn != 0 )) external_force = 1;

	for (i=0;i<model[0].NB;i++)
	{
		pvdf_aux[i].jcalcp(model[i].jcode,q_i[i]);
		pvdf_aux[i].vJ = matrix_aux.ScalarMulti(pvdf_aux[i].S,0,3,qd_i[i]);
		pvdf_aux[i].Xup = matrix_aux.Multiplication(pvdf_aux[i].Xj,3,3,model[i].Xtree,3,3);

		if (model[i].parent == 0)
		{
			pvdf_aux[i].v = pvdf_aux[i].vJ;
			pvdf_aux[i].avp = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,a_grav_n,0,3);
		}
		else
		{
			int temp = model[i].parent - 1;

			float* temp2 = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].v,0,3);

			pvdf_aux[i].v = matrix_aux.Sum(temp2,pvdf_aux[i].vJ,4);

			float* Xup_avp = matrix_aux.Multiplication(pvdf_aux[i].Xup,3,3,pvdf_aux[temp].avp,0,3);
	
			float* crm_vJ = matrix_aux.Multiplication(pva_aux.crmp(pvdf_aux[i].v),0,3,pvdf_aux[i].vJ,0,3);
			pvdf_aux[i].avp = matrix_aux.Sum(Xup_avp,crm_vJ,4);

		}

		float* I_avp = matrix_aux.Multiplication(model[i].I,3,3,pvdf_aux[i].avp,0,3);

		float* crf_v = pva_aux.crfp(pvdf_aux[i].v);
		float* crf_I = matrix_aux.Multiplication(crf_v,3,3,model[i].I,3,3);
		float* crf_I_v = matrix_aux.Multiplication(crf_I,3,3,pvdf_aux[i].v,0,3);

		pvdf_aux[i].fvp = matrix_aux.Sum(I_avp,crf_I_v);

		if (external_force)
		{
			int as = f_ext[i];
			pvdf_aux[i].fvp = matrix_aux.ScalarAdd(pvdf_aux[i].fvp,3,as,1);
		}
	}

	for (i = model[0].NB - 1;i>=0;i--)
	{
		float* temp = matrix_aux.Multiplication(pvdf_aux[i].S,0,3,pvdf_aux[i].fvp,0,3);
	
		C[i] = temp[0];

		if (model[i].parent != 0)
		{
			int temp = model[i].parent - 1;
			float* Xup_fvp = matrix_aux.Multiplication(matrix_aux.Transponse(pvdf_aux[i].Xup,3,3),3,3,pvdf_aux[i].fvp,0,3);

			pvdf_aux[temp].fvp = matrix_aux.Sum(pvdf_aux[temp].fvp,Xup_fvp);
		}
	}

	for (i=0;i<model[0].NB;i++) pvdf_aux[i].IC = model[i].I;

	for (i=model[0].NB - 1;i>=0;i--)
	{
		int temp = model[i].parent - 1;
		if (temp != - 1)
		{
			float* Xup_t = matrix_aux.Transponse(pvdf_aux[i].Xup,3,3);
			float* Xup_t_IC = matrix_aux.Multiplication(Xup_t,3,3,pvdf_aux[i].IC,3,3);
			float* Xup_t_IC_Xup= matrix_aux.Multiplication(Xup_t_IC,3,3,pvdf_aux[i].Xup,3,3);

			pvdf_aux[temp].IC = matrix_aux.Sum(pvdf_aux[temp].IC,Xup_t_IC_Xup,3);
		}	
	}

	for (i=0;i<model[0].NB*model[0].NB;i++) H[i]=0;
	for (i=0;i<model[0].NB;i++)
	{
		fh = matrix_aux.Multiplication(pvdf_aux[i].IC,3,3,pvdf_aux[i].S,0,3);
		float* temp = matrix_aux.Multiplication(pvdf_aux[i].S,0,3,fh,0,3);

		H[i*max + i] = temp[0];
		j = i;
		while (model[j].parent > 0)
		{

			float* Xup_t = matrix_aux.Transponse(pvdf_aux[j].Xup,3,3);
			fh = matrix_aux.Multiplication(Xup_t,3,3,fh,0,3);

			j = model[j].parent;
			j--;
			float* temp = matrix_aux.Multiplication(pvdf_aux[j].S,0,3,fh,0,3);

			H[i*max + j] = temp[0];
			H[j*max + i] = H[i*max + j];

		}
	}
}