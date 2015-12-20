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
#include "ModelConstructors.h"
#include "SpatialVectorArithmetic.h"


using namespace std;



void df::HD (mc* model, float* fd, float* q_i, float* qd_i, float* qdd_i, float* tau)
{
	qdd_out = new float [model[0].NB];
	tau_out = new float [model[0].NB];
	matrix matrix_aux;
	sva sva_aux;
	df* df_aux = new df [model[0].NB];

	float* a_grav = NULL;
	float* a_grav_n = NULL;

	float a_grav_pos[6] = {0,0,0,0,0,-9.81};
	float a_grav_neg[6] = {0,0,0,0,0,9.81};
	a_grav = a_grav_pos;
	a_grav_n = a_grav_neg;


	for (i=0;i<model[0].NB;i++)
	{
		df_aux[i].jcalc(model[i].pitch,q_i[i]);
		df_aux[i].vJ = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qd_i[i]);
		df_aux[i].Xup = matrix_aux.Multiplication(df_aux[i].Xj,6,6,model[i].Xtree,6,6);

		if (model[i].parent == 0)
		{
			df_aux[i].v = df_aux[i].vJ;
			df_aux[i].c = matrix_aux.Zeros(0,6);
		}
		else
		{
			int temp = model[i].parent - 1;
			float* Xup_v = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);

			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);
			df_aux[i].c = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);
		}

		if (fd[i] == 0)
		{
			df_aux[i].c = matrix_aux.Sum(df_aux[i].c,matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]),4);
		}

		df_aux[i].IA = model[i].I;

		float* crf_I = matrix_aux.Multiplication(sva_aux.crf(df_aux[i].v),6,6,model[i].I,6,6);

		df_aux[i].pA = matrix_aux.Multiplication(crf_I,6,6,df_aux[i].v,0,6);
	}


	for (i=model[0].NB - 1;i>=0;i--)
	{
		int temp = model[i].parent - 1;
		
		if (fd[i] == 0)
		{
			if (model[i].parent != 0)
			{	
				Ia = df_aux[i].IA;
				pa = matrix_aux.Sum(df_aux[i].pA,matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].c,0,6));

				float* Xup_Ia_Xup = matrix_aux.Multiplication(matrix_aux.Transponse(df_aux[i].Xup,6,6),6,6,Ia,6,6,df_aux[i].Xup,6,6);
				float* Xup_pa = matrix_aux.Multiplication(matrix_aux.Transponse(df_aux[i].Xup,6,6),6,6,pa,0,6);

				df_aux[temp].IA = matrix_aux.Sum(df_aux[temp].IA,Xup_Ia_Xup,3);
				df_aux[temp].pA = matrix_aux.Sum(df_aux[temp].pA,Xup_pa,4);	
			}
		}
		else
		{
		df_aux[i].U = matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].S,0,6);
		df_aux[i].d = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].U,0,6);
		float* S_pA = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].pA,0,6);

		float temp = tau[i] - S_pA[0];
		df_aux[i].u1 = temp;

		if (model[i].parent != 0)
		{
			int temp = model[i].parent - 1;
			
			float* U_d = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].d[0],1);
			float* U_div_d_t_U = matrix_aux.VectorToMatrix(U_d,6,df_aux[i].U,6);
			
			df_aux[i].Ia = matrix_aux.Sum(df_aux[i].IA,U_div_d_t_U,2);

			float* U_u = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].u1);
			float* U_u_d = matrix_aux.ScalarMulti(U_u,0,6,df_aux[i].d[0],1);
			float* Ia_c = matrix_aux.Multiplication(df_aux[i].Ia,6,6,df_aux[i].c,0,6);
			float* pA_Ic_c = matrix_aux.Sum(df_aux[i].pA,Ia_c);

			df_aux[i].pa = matrix_aux.Sum(pA_Ic_c,U_u_d); 

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_Ia =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].Ia,6,6);
			float* Xup_Ia_Xup = matrix_aux.Multiplication(Xup_Ia,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pa = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pa,0,6);

			df_aux[temp].IA = matrix_aux.Sum(df_aux[temp].IA,Xup_Ia_Xup,3);
			df_aux[temp].pA = matrix_aux.Sum(df_aux[temp].pA,Xup_t_pa,4);
			}
		}
	}
	
	for (i=0;i<model[0].NB;i++)
	{
		if (model[i].parent == 0)
		{
			float* Xup_agrav = matrix_aux.Multiplication(df_aux[i].Xup,6,6,a_grav_n,0,6);
			df_aux[i].a = matrix_aux.Sum(Xup_agrav,df_aux[i].c,4);
		}
		else
		{
			int temp = model[i].parent - 1;
			float* Xup_a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);

			df_aux[i].a = matrix_aux.Sum(Xup_a,df_aux[i].c,4);
		}	

		if (fd[i] == 0)
		{
			qdd_out[i] = qdd_i[i];

			float* IA_a = matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].a,0,6);
			float* IA_a_pA = matrix_aux.Sum(IA_a,df_aux[i].pA,4);

			float* aux = matrix_aux.Multiplication(df_aux[i].S,0,6,IA_a_pA,0,6);

			tau_out[i] = aux[0];
		}
		else
		{
			float* Ua = matrix_aux.Multiplication(df_aux[i].U,0,6,df_aux[i].a,0,6);
		
			float aux = Ua[0];
			float u_Ua = df_aux[i].u1 - aux;

			qdd_out[i] = u_Ua/df_aux[i].d[0];

			float* S_qdd_out = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_out[i]);
			df_aux[i].a = matrix_aux.Sum(df_aux[i].a,S_qdd_out,4);

			tau_out[i] = tau[i];
		}
	}
}


void df::HD (mc* model, float* fd, float* q_i, float* qd_i, float* qdd_i, float* tau, df* f_ext, float* grav_accn)
{
	qdd_out = new float [model[0].NB];
	tau_out = new float [model[0].NB];
	matrix matrix_aux;
	sva sva_aux;
	df* df_aux = new df [model[0].NB];

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
			df_aux[i].c = matrix_aux.Zeros(0,6);
		}
		else
		{
			int temp = model[i].parent - 1;
			float* Xup_v = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].v,0,6);

			df_aux[i].v = matrix_aux.Sum(Xup_v,df_aux[i].vJ,4);
			df_aux[i].c = matrix_aux.Multiplication(sva_aux.crm(df_aux[i].v),6,6,df_aux[i].vJ,0,6);
		}

		if (fd[i] == 0)
		{
			df_aux[i].c = matrix_aux.Sum(df_aux[i].c,matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_i[i]),4);
		}

		df_aux[i].IA = model[i].I;

		float* crf_I = matrix_aux.Multiplication(sva_aux.crf(df_aux[i].v),6,6,model[i].I,6,6);

		df_aux[i].pA = matrix_aux.Multiplication(crf_I,6,6,df_aux[i].v,0,6);

		if (f_ext[i].f_ext != 0)
		{
			df_aux[i].pA = matrix_aux.Sum(df_aux[i].pA,f_ext[i].f_ext,1);
		}
	}


	for (i=model[0].NB - 1;i>=0;i--)
	{
		int temp = model[i].parent - 1;
		
		if (fd[i] == 0)
		{
			if (model[i].parent != 0)
			{	
				Ia = df_aux[i].IA;
				pa = matrix_aux.Sum(df_aux[i].pA,matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].c,0,6));

				float* Xup_Ia_Xup = matrix_aux.Multiplication(matrix_aux.Transponse(df_aux[i].Xup,6,6),6,6,Ia,6,6,df_aux[i].Xup,6,6);
				float* Xup_pa = matrix_aux.Multiplication(matrix_aux.Transponse(df_aux[i].Xup,6,6),6,6,pa,0,6);

				df_aux[temp].IA = matrix_aux.Sum(df_aux[temp].IA,Xup_Ia_Xup,3);
				df_aux[temp].pA = matrix_aux.Sum(df_aux[temp].pA,Xup_pa,4);	

			}
		}
		else
		{
		df_aux[i].U = matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].S,0,6);
		df_aux[i].d = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].U,0,6);
		float* S_pA = matrix_aux.Multiplication(df_aux[i].S,0,6,df_aux[i].pA,0,6);

		float temp = tau[i] - S_pA[0];
		df_aux[i].u1 = temp;

		if (model[i].parent != 0)
		{
			int temp = model[i].parent - 1;
			
			float* U_d = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].d[0],1);
			float* U_div_d_t_U = matrix_aux.VectorToMatrix(U_d,6,df_aux[i].U,6);
			
			df_aux[i].Ia = matrix_aux.Sum(df_aux[i].IA,U_div_d_t_U,2);

			float* U_u = matrix_aux.ScalarMulti(df_aux[i].U,0,6,df_aux[i].u1);
			float* U_u_d = matrix_aux.ScalarMulti(U_u,0,6,df_aux[i].d[0],1);
			float* Ia_c = matrix_aux.Multiplication(df_aux[i].Ia,6,6,df_aux[i].c,0,6);
			float* pA_Ic_c = matrix_aux.Sum(df_aux[i].pA,Ia_c);

			df_aux[i].pa = matrix_aux.Sum(pA_Ic_c,U_u_d); 

			float* Xup_t = matrix_aux.Transponse(df_aux[i].Xup,6,6);
			float* Xup_Ia =  matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].Ia,6,6);
			float* Xup_Ia_Xup = matrix_aux.Multiplication(Xup_Ia,6,6,df_aux[i].Xup,6,6);
			float* Xup_t_pa = matrix_aux.Multiplication(Xup_t,6,6,df_aux[i].pa,0,6);

			df_aux[temp].IA = matrix_aux.Sum(df_aux[temp].IA,Xup_Ia_Xup,3);
			df_aux[temp].pA = matrix_aux.Sum(df_aux[temp].pA,Xup_t_pa,4);
			}
		}
	}
	
	for (i=0;i<model[0].NB;i++)
	{
		if (model[i].parent == 0)
		{
			float* Xup_agrav = matrix_aux.Multiplication(df_aux[i].Xup,6,6,a_grav_n,0,6);
			df_aux[i].a = matrix_aux.Sum(Xup_agrav,df_aux[i].c,4);
		}
		else
		{
			int temp = model[i].parent - 1;
			float* Xup_a = matrix_aux.Multiplication(df_aux[i].Xup,6,6,df_aux[temp].a,0,6);

			df_aux[i].a = matrix_aux.Sum(Xup_a,df_aux[i].c,4);
		}	
		if (fd[i] == 0)
		{
			qdd_out[i] = qdd_i[i];

			float* IA_a = matrix_aux.Multiplication(df_aux[i].IA,6,6,df_aux[i].a,0,6);
			float* IA_a_pA = matrix_aux.Sum(IA_a,df_aux[i].pA,4);

			float* aux = matrix_aux.Multiplication(df_aux[i].S,0,6,IA_a_pA,0,6);

			tau_out[i] = aux[0];
		}
		else
		{
			float* Ua = matrix_aux.Multiplication(df_aux[i].U,0,6,df_aux[i].a,0,6);
		
			float aux = Ua[0];
			float u_Ua = df_aux[i].u1 - aux;

			qdd_out[i] = u_Ua/df_aux[i].d[0];

			float* S_qdd_out = matrix_aux.ScalarMulti(df_aux[i].S,0,6,qdd_out[i]);
			df_aux[i].a = matrix_aux.Sum(df_aux[i].a,S_qdd_out,4);

			tau_out[i] = tau[i];
		}
	}
}

	
