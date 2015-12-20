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
#include "DynamicsFunctions.h"
#include "SpatialVectorArithmetic.h"
#include "ModelConstructors.h"
#include <math.h>

using namespace std;



void df::HandC (mc* model, float* q_i, float* qd_i, float* f_ext, float* grav_accn)
{
	df* df_aux = new df [model[0].NB];
	sva sva_aux;
	matrix matrix_aux;
	int max = model[0].NB;
	C = new float [max];
	H = new float [max*max];


	float* a_grav = NULL;
	float* a_grav_n = NULL;

	if (grav_accn == 0)
	{
		float a_grav_pos[6] = {0,0,0,0,0,-9.81};
		float a_grav_neg[6] = {0,0,0,0,0,9.81};
		a_grav = a_grav_pos;
		a_grav_n = a_grav_neg;
	}
	else
	{
		float a_grav_pos[6] = {0,0,0,grav_accn[0],grav_accn[1],grav_accn[2]};
		float a_grav_neg[6] = {0,0,0,-1*grav_accn[0],-1*grav_accn[1],-1*grav_accn[2]};
		a_grav = a_grav_pos;
		a_grav_n = a_grav_neg;
	}


	for (i=0;i<model[0].NB;i++)
	{
		df_aux[i].jcalc(model[i].pitch,q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qd_i[i]);
		df_aux[i].Xup = matrix_aux.Multiplication(df_aux[i].Xj,6,6,model[i].Xtree,6,6);

		if (model[i].parent == 0)
		{
			df_aux[i].v = df_aux[i].vJ;
			df_aux[i].avp = matrix_aux.Multiplication(df_aux[i].Xup,6,6,a_grav_n,0,6);

		}
		else
		{
			int temp = model[i].parent - 1;

			float* temp2 = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);

			df_aux[i].v = matrix_aux.Sum(temp2,df_aux[i].vJ,4);

			float* Xup_avp = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].avp,0,6);
	
			float* crm_vJ = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),0,6,df_aux[i].vJ,0,6);
			df_aux[i].avp = matrix_aux.Sum(Xup_avp,crm_vJ,4);
		}

		float* I_avp = matrix_aux.Multiplication(model[i].I,6,6,df_aux[i].avp,0,6);

		float* crf_v = sva_aux.crf(df_aux[i].v);
		float* crf_I = matrix_aux.Multiplication(crf_v,6,6,model[i].I,6,6);
		float* crf_I_v = matrix_aux.Multiplication(crf_I,6,6,df_aux[i].v,0,6);

		df_aux[i].fvp = matrix_aux.Sum(I_avp,crf_I_v);
	}

	for (i = model[0].NB - 1;i>=0;i--)
	{
		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].fvp,0,6);

		C[i] = temp[0];

		if (model[i].parent != 0)
		{
			int temp = model[i].parent - 1;
			float* Xup_fvp = matrix_aux.Multiplication(matrix_aux.Transponse(df_aux[i].Xup,6,6),6,6,df_aux[i].fvp,0,6);

			df_aux[temp].fvp = matrix_aux.Sum(df_aux[temp].fvp,Xup_fvp);
		}
	}

	for (i=0;i<model[0].NB;i++) df_aux[i].IC = model[i].I;

	for (i=model[0].NB - 1;i>=0;i--)
	{
		int temp = model[i].parent - 1;
		if (temp != - 1)
		{
			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_t_IC = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].IC,6,6);
			float* Xup_t_IC_Xup= matrix_aux.Multiplication(Xup_t_IC,6,6,df_aux[i].Xup,6,6);

			df_aux[temp].IC = matrix_aux.Sum(df_aux[temp].IC,Xup_t_IC_Xup,3);
		}	
	}

	for (i=0;i<model[0].NB*model[0].NB;i++) H[i]=0;
	for (i=0;i<model[0].NB;i++)
	{
		fh = matrix_aux.Multiplication(df_aux[i].IC,6,6,df_aux[i].S,0,6);
		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,fh,0,6);

		H[i*max + i] = temp[0];
		j = i;
		while (model[j].parent > 0)
		{

			float* Xup_t = matrix_aux.Transponse(df_aux[j].Xup,6,6);
			fh = matrix_aux.Multiplication(Xup_t,6,6,fh,0,6);

			j = model[j].parent;
			j--;

			float* temp = matrix_aux.Multiplication(df_aux[j].S,0,6,fh,0,6);

			H[i*max + j] = temp[0];
			H[j*max + i] = H[i*max + j];

		}
	}
}

