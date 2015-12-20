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
#include "DynamicsFunctions.h"
#include "Matrix.h"
#include "SpatialVectorArithmetic.h"
#include "ModelConstructors.h"
#include "ArrayRelease.h"

using namespace std;


void df::ID_force(double* tau, double* Fx, double* Fy, double* Fz, mc* model, double* q_i, double* qd_i, double* qdd_i)
{
	df* df_aux = new df [model[0].NB];
	matrix matrix_aux;
	sva sva_aux;

	float* a_grav = NULL;
	float* a_grav_n = NULL;

	float a_grav_pos[6] = {0,0,0,0,0,-9.81};
	float a_grav_neg[6] = {0,0,0,0,0,9.81};
	a_grav = a_grav_pos;
	a_grav_n = a_grav_neg;
		
	for (i=0;i<model[0].NB;i++)
	{
		df_aux[i].jcalc(model[i].pitch,(float)q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,(float)qd_i[i]);
		df_aux[i].Xup = new float[36];
		matrix_aux.Multiplication(df_aux[i].Xup,df_aux[i].Xj,6,6,model[i].Xtree,6,6);

		if (model[i].parent == 0)
		{
			df_aux[i].v = df_aux[i].vJ;
			float Xup_a_grav[6];
			matrix_aux.Multiplication(Xup_a_grav,df_aux[i].Xup,6,6,a_grav_n,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			df_aux[i].a = matrix_aux.Sum(Xup_a_grav,S_qdd,4);

		}
		else
		{
			int temp = model[i].parent - 1;
			float Xup_v[6];
			matrix_aux.Multiplication(Xup_v,df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);

			float Xup_a[6]; float crm_vJ[6]; 
			matrix_aux.Multiplication(Xup_a,df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			matrix_aux.Multiplication(crm_vJ,sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* aux = matrix_aux.Sum(Xup_a,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(aux,crm_vJ,4);
		}
		delete [] df_aux[i].Xup;

		float I_a[6]; float crf_I[36]; float crf_I_v[6];
		matrix_aux.Multiplication(I_a,model[i].I,6,6,df_aux[i].a,0,6);
		matrix_aux.Multiplication(crf_I,sva_aux.crf(df_aux[i].v),6,6,model[i].I,6,6);
		matrix_aux.Multiplication(crf_I_v,crf_I,6,6,df_aux[i].v,0,6);

		df_aux[i].f = matrix_aux.Sum(I_a,crf_I_v);
	}

	float aux_Fx[] = {0,0,0,1,0,0};
	float aux_Fy[] = {0,0,0,0,1,0};
	float aux_Fz[] = {0,0,0,0,0,1};


	for (i=model[0].NB - 1;i>=0;i--)
	{
		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].f,0,6);
		float* temp_x = matrix_aux.Multiplication(aux_Fx,0,6,df_aux[i].f,0,6);
		float* temp_y = matrix_aux.Multiplication(aux_Fy,0,6,df_aux[i].f,0,6);
		float* temp_z = matrix_aux.Multiplication(aux_Fz,0,6,df_aux[i].f,0,6);

		tau[i] = temp[0];
		Fx[i] = temp_x[0];
		Fy[i] = temp_y[0];
		Fz[i] = temp_z[0];
	}
}


void df::ID_force(double* tau, double* Fx, double* Fy, double* Fz, mc* model, double* q_i, double* qd_i, double* qdd_i, df* f_ext, double* grav_accn)
{
	df* df_aux = new df [model[0].NB];
	matrix matrix_aux;
	sva sva_aux;

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
		df_aux[i].jcalc(model[i].pitch,(float)q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,(float)qd_i[i]);
		df_aux[i].Xup = new float[36];
		matrix_aux.Multiplication(df_aux[i].Xup,df_aux[i].Xj,6,6,model[i].Xtree,6,6);

		if (model[i].parent == 0)
		{
			df_aux[i].v = df_aux[i].vJ;
			float Xup_a_grav[6];
			matrix_aux.Multiplication(Xup_a_grav,df_aux[i].Xup,6,6,a_grav_n,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			df_aux[i].a = matrix_aux.Sum(Xup_a_grav,S_qdd,4);

		}
		else
		{
			int temp = model[i].parent - 1;
			float Xup_v[6];
			matrix_aux.Multiplication(Xup_v,df_aux[i].Xup,6,6,df_aux[temp].v,0,6);
			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);

			float Xup_a[6]; float crm_vJ[6]; 
			matrix_aux.Multiplication(Xup_a,df_aux[i].Xup,6,6,df_aux[temp].a,0,6);
			float* S_qdd = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]);
			matrix_aux.Multiplication(crm_vJ,sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);

			float* aux = matrix_aux.Sum(Xup_a,S_qdd,4);
			df_aux[i].a = matrix_aux.Sum(aux,crm_vJ,4);
		}
		delete [] df_aux[i].Xup;

		float I_a[6]; float crf_I[36]; float crf_I_v[6];
		matrix_aux.Multiplication(I_a,model[i].I,6,6,df_aux[i].a,0,6);
		matrix_aux.Multiplication(crf_I,sva_aux.crf(df_aux[i].v),6,6,model[i].I,6,6);
		matrix_aux.Multiplication(crf_I_v,crf_I,6,6,df_aux[i].v,0,6);

		df_aux[i].f = matrix_aux.Sum(I_a,crf_I_v);

		if (f_ext[i].f_ext != 0)
		{
			df_aux[i].f = matrix_aux.Sum(df_aux[i].f,f_ext[i].f_ext,1);
		}
	}

	float aux_Fx[] = {0,0,0,1,0,0};
	float aux_Fy[] = {0,0,0,0,1,0};
	float aux_Fz[] = {0,0,0,0,0,1};


	for (i=model[0].NB - 1;i>=0;i--)
	{
		float* temp = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].f,0,6);
		float* temp_x = matrix_aux.Multiplication(aux_Fx,0,6,df_aux[i].f,0,6);
		float* temp_y = matrix_aux.Multiplication(aux_Fy,0,6,df_aux[i].f,0,6);
		float* temp_z = matrix_aux.Multiplication(aux_Fz,0,6,df_aux[i].f,0,6);

		tau[i] = temp[0];
		Fx[i] = temp_x[0];
		Fy[i] = temp_y[0];
		Fz[i] = temp_z[0];
	}
}