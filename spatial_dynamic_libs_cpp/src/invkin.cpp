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
//// file invkin.cpp
//
//

#include <iostream>
#include "Matrix.h"
#include "DynamicsFunctions.h"
#include <math.h>

using namespace std;

void df::invkin (float* X, float* v, float* a)
{
	matrix matrix_aux;

	float q_aux[6];
	float qd_aux_array[6];
	float qdd_aux_array[6];
	float omegad[3];

	q = new float [6];
	qd = new float [6];
	qdd = new float [6]; 

	float E[9] = {
		X[0],X[1],X[2],
		X[6],X[7],X[8],
		X[12],X[13],X[14]};

	float* E_n = matrix_aux.ScalarMulti(E,3,3,-1);
	float* E_n_t = matrix_aux.Transponse(E_n,3,3);
	float X_aux[9] = {
		X[18],X[19],X[20],
		X[24],X[25],X[26],
		X[30],X[31],X[32]};

	float* rx = matrix_aux.Multiplication(E_n_t,3,3,X_aux,3,3);

	float r[3] = {rx[7], rx[2], rx[3]};
	
	q_aux[0] = r[0];
	q_aux[1] = r[1];
	q_aux[2] = r[2];

	q_aux[4] = atan2 (E[6],sqrt(E[0]*E[0]+E[3]*E[3]));
	q_aux[5] = atan2 (-1*E[3],E[0]);

	if (E[6]>0)
	{
		q_aux[3] = atan2 (E[5]+E[1],E[4]-E[2]) - q_aux[5];
	}
	else
	{
		q_aux[3] = atan2 (E[5]-E[1],E[4]+E[2]) + q_aux[5];
	}

	if (q_aux[3] > 3.14)
	{
		q_aux[3] = q_aux[3] - 2*3.14;
	}
	else if (q_aux[3] < -3.14)
	{
		q_aux[3] = q_aux[3] + 2*3.14;
	}


	c4 = cos(q_aux[3]);  s4 = sin(q_aux[3]);
	c5 = cos(q_aux[4]);  s5 = sin(q_aux[4]);

	float S[9] = {
		1,  0,    s5,
		0,  c4,  -s4*c5,
		0,  s4,   c4*c5};

	float omega[3] = {v[0],v[1],v[2]};

	float cross_r_omega[3] = {
		r[1]*omega[2] - r[2]*omega[1],
		-r[0]*omega[2] + r[2]*omega[0],
		r[0]*omega[1] - r[1]*omega[0]};

	float rd[3] = {
			v[3] - cross_r_omega[0],
			v[4] - cross_r_omega[1],
			v[5] - cross_r_omega[2]};

	qd_aux_array[0] = rd[0];
	qd_aux_array[1] = rd[1];
	qd_aux_array[2] = rd[2];

	float* s_omega = matrix_aux.LeftDiv(S,3,omega,0,3);

	qd_aux_array[3] = s_omega[0];
	qd_aux_array[4] = s_omega[1];
	qd_aux_array[5] = s_omega[2];

	c4d = -s4*qd_aux_array[3];  s4d = c4*qd_aux_array[3];
	c5d = -s5*qd_aux_array[4];  s5d = c5*qd_aux_array[4];

	float Sd[9] = {
		0,  0,     s5d,
		0,  c4d,  -s4d*c5-s4*c5d,
		0,  s4d,   c4d*c5+c4*c5d};

	omegad[0] = a[0];
	omegad[1] = a[1];
	omegad[2] = a[2];

	float cross_rd_omega[3] = {
		rd[1]*omega[2] - rd[2]*omega[1],
		-rd[0]*omega[2] + rd[2]*omega[0],
		rd[0]*omega[1] - rd[1]*omega[0]};

	float cross_r_omegad[3] = {
		r[1]*omegad[2] - r[2]*omegad[1],
		-r[0]*omegad[2] + r[2]*omegad[0],
		r[0]*omegad[1] - r[1]*omegad[0]};
	
	float rdd[3] = {
		a[3] - cross_rd_omega[0] - cross_r_omegad[0],
		a[4] - cross_rd_omega[1] - cross_r_omegad[1],
		a[5] - cross_rd_omega[2] - cross_r_omegad[2]};

	qdd_aux_array[0] = rdd[0];
	qdd_aux_array[1] = rdd[1];
	qdd_aux_array[2] = rdd[2];
	
	float aux[] = {qd_aux_array[3],qd_aux_array[4],qd_aux_array[5]};

	float* Sd_qd = matrix_aux.Multiplication(Sd,3,3,aux,0,3);
	float omegad_Sd_qd[3] = {
		omegad[0] - Sd_qd[0],
		omegad[1] - Sd_qd[1],
		omegad[2] - Sd_qd[2]};

	//	matrix_aux.Display(aux,0,3);
		
	float* qdd_p = matrix_aux.LeftDiv(S,3,omegad_Sd_qd,0,3);

	for (i=0;i<6;i++)
	{
		q[i] = q_aux[i];
		qd[i] = qd_aux_array[i];
		
		if(i<3) 
		{
			qdd[i] = qdd_aux_array[i];
		}
		else
		{
			qdd[i] = qdd_p[i-3];
		}
	}
}