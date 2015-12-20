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

void df::FDf (mc* model, float* Xfb, float* vfb, float* q_i, float* qd_i, float* tau, float* f_ext, float* grav_accn)
{

	int NBR = model[0].NB - 6;
	int* parent_r = new int [model[0].NB - 6];

	qdd_fdf = new float [NBR];
	df* df_aux = new df [NBR];
	sva sva_aux;
	matrix matrix_aux;

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


	for (i=0;i<model[0].NB - 6;i++)
	{
		int aux = model[i+6].parent - 6;
		parent_r[i] = aux;
	}

	vfb = matrix_aux.Multiplication(Xfb,6,6,vfb,0,6);

	for (i=0;i<NBR;i++)
	{
		int temp = parent_r[i] - 1;

		df_aux[i].jcalc(model[i+6].pitch,q_i[i]);
		df_aux[i].vJ  = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qd_i[i]);
		df_aux[i].Xup = matrix_aux.Multiplication(df_aux[i].Xj,6,6,model[i+6].Xtree,6,6);

		if (parent_r[i] == 0)
		{
			float* Xup_vfb = matrix_aux.Multiplication(df_aux[i].Xup,6,6,vfb,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_vfb,df_aux[i].vJ,4);
		}
		else
		{
			float* Xup_v = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);
		}
		float* crm_v = sva_aux.crm(df_aux[i].v);
		float* crf_v = sva_aux.crf(df_aux[i].v);

		df_aux[i].c = matrix_aux.Multiplication(crm_v,6,6,df_aux[i].vJ,0,6);
		df_aux[i].IA = model[i+6].I;

		float* crf_v_IA= matrix_aux.Multiplication(crf_v,6,6,df_aux[i].IA,6,6);

		df_aux[i].pA = matrix_aux.Multiplication(crf_v_IA,6,6,df_aux[i].v,0,6);
	}

	df_aux[0].IAfb = model[5].I;

	float* crf_v = sva_aux.crf(vfb);
	float* crf_v_IAfb = matrix_aux.Multiplication(crf_v,6,6,df_aux[0].IAfb,6,6);
	df_aux[0].pAfb = matrix_aux.Multiplication(crf_v_IAfb,6,6,vfb,0,6);

	for (i=NBR-1;i>=0;i--)
	{
		df_aux[i].U = matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].S,0,6);
		df_aux[i].d = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].U,0,6);
		float* S_pA = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].pA,0,6);

		float temp = tau[i] - S_pA[0];
		df_aux[i].u1 = temp;

		float* U_d = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].d[0],1);
		float* U_div_d_t_U = matrix_aux.VectorToMatrix(U_d,6,df_aux[i].U,6);
			
		df_aux[i].Ia = matrix_aux.Sum(df_aux[i].IA,U_div_d_t_U,2);

		float* U_u = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].u1);
		float* U_u_d = matrix_aux.ScalarMulti(U_u,0,6,df_aux[i].d[0],1);
		float* Ia_c = matrix_aux.Multiplication(df_aux[i].Ia,6,6,df_aux[i].c,0,6);
		float* pA_Ic_c = matrix_aux.Sum(df_aux[i].pA,Ia_c);

		df_aux[i].pa = matrix_aux.Sum(pA_Ic_c,U_u_d); 

		if (parent_r[i] == 0)
		{
			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_Ia =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[0].Ia,6,6);
			float* Xup_Ia_Xup = matrix_aux.Multiplication(Xup_Ia,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pa = matrix_aux.Multiplication(Xup_t,6,6,df_aux[0].pa,0,6);

			df_aux[0].IAfb = matrix_aux.Sum(df_aux[0].IAfb,Xup_Ia_Xup,3);
			df_aux[0].pAfb = matrix_aux.Sum(df_aux[0].pAfb,Xup_t_pa,4);
		}
		else
		{
			int temp = parent_r[i] - 1;

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_Ia =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].Ia,6,6);
			float* Xup_Ia_Xup = matrix_aux.Multiplication(Xup_Ia,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pa = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pa,0,6);

			df_aux[temp].IA = matrix_aux.Sum(df_aux[temp].IA,Xup_Ia_Xup,3);
			df_aux[temp].pA = matrix_aux.Sum(df_aux[temp].pA,Xup_t_pa,4);
		}
	}

	float* ICfb_n = matrix_aux.ScalarMulti(df_aux[0].IAfb,6,6,-1);

	afb = matrix_aux.LeftDiv(ICfb_n,6,df_aux[0].pAfb,0,6);

	
	for(i=0;i<NBR;i++)
	{
		if (parent_r[i] == 0)
		{
			float* Xup_afb = matrix_aux.Multiplication(df_aux[i].Xup,6,6,afb,0,6);
			df_aux[i].a = matrix_aux.Sum(Xup_afb,df_aux[i].c,4);
		}
		else
		{
			int temp = parent_r[i] - 1;
				
			float* Xup_a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
			df_aux[i].a = matrix_aux.Sum(Xup_a,df_aux[i].c,4);
		}
		float* Ua = matrix_aux.Multiplication(df_aux[i].U,0,6,df_aux[i].a,0,6);
		
		float aux = Ua[0];
		float u_Ua = df_aux[i].u1 - aux;

		qdd_fdf[i] = u_Ua/df_aux[i].d[0];

		float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_fdf[i]);
		df_aux[i].a = matrix_aux.Sum(df_aux[i].a,S_qdd,4);
	}

	float* aux = matrix_aux.LeftDiv(Xfb,6,afb,0,6);
	afb = matrix_aux.Sum(aux,a_grav,4);
}




