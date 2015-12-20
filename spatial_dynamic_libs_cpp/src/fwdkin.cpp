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
//// file fwdkin.cpp
//
//

#include <iostream>
#include "Matrix.h"
#include "DynamicsFunctions.h"
#include <math.h>

using namespace std;

void df::fwdkin(float *q, float *qd, float *qdd)
{
	matrix matrix_aux;

	X = new float [6*6];
	v =	new float [6];
	a = new float [6];

	c4 = cos(q[3]);  s4 = sin(q[3]);
	c5 = cos(q[4]);  s5 = sin(q[4]);
	c6 = cos(q[5]);  s6 = sin(q[5]);

	float E[9] = {
	 c5*c6,		c4*s6+s4*s5*c6,  s4*s6-c4*s5*c6,
     -c5*s6,	c4*c6-s4*s5*s6,  s4*c6+c4*s5*s6,
	 s5,		-s4*c5,          c4*c5};

	 float r[3] = {q[0],q[1],q[2]};

	 float R[9] = {
		 0,		-r[2],	r[1],
		 r[2],	0,		-r[0],
		 -r[1],	r[0],	0};

	float* E_R = matrix_aux.Multiplication(matrix_aux.ScalarMulti(E,3,3,-1),3,3,R,3,3);

	float X_aux [6*6] = {
		E[0],E[1],E[2],0,0,0,
		E[3],E[4],E[5],0,0,0,
		E[6],E[7],E[8],0,0,0,
		E_R[0],E_R[1],E_R[2],E[0],E[1],E[2],
		E_R[3],E_R[4],E_R[5],E[3],E[4],E[5],
		E_R[6],E_R[7],E_R[8],E[6],E[7],E[8]};


	float S[9] = {
		1,  0,    s5,
		0,  c4,  -s4*c5,
		0,  s4,   c4*c5};
	float* S_p = S;
	float qd_aux[3] = {qd[3],qd[4],qd[5]}; 
	float* qd_aux_p = qd_aux;
	float rd[3] = {qd[0],qd[1],qd[2]};

	omega = matrix_aux.Multiplication(S_p,3,3,qd_aux_p,0,3);

	float cross_r_omega[3] = {
		r[1]*omega[2] - r[2]*omega[1],
		-r[0]*omega[2] + r[2]*omega[0],
		r[0]*omega[1] -r[1]*omega[0]};

		//matrix_aux.Display(cross_r_omega,0,3);
		
	float v_aux[6] = {
		omega[0],
		omega[1],
		omega[2],
		rd[0] + cross_r_omega[0],
		rd[1] + cross_r_omega[1],
		rd[2] + cross_r_omega[2]};

	c4d = -s4*qd[3];  s4d = c4*qd[3];
	c5d = -s5*qd[4];  s5d = c5*qd[4];

	float Sd[9] = {
		0, 0, s5d,
		0, c4d, -s4d*c5-s4*c5d,
		0, s4d, c4d*c5+c4*c5d};

	float* Sd_p = Sd;
	float qdd_aux[3] = {qdd[3],qdd[4],qdd[5]};
	float* qdd_aux_p = qdd_aux;

	float* S_qdd = matrix_aux.Multiplication(S_p,3,3,qdd_aux_p,0,3);
	float* Sd_qd = matrix_aux.Multiplication(Sd_p,3,3,qd_aux_p,0,3);

	omegad = matrix_aux.Sum(S_qdd,Sd_qd);

	float rdd[3] = {qdd[0],qdd[1],qdd[2]};
	
	float cross_rd_omega[3] = {
		rd[1]*omega[2] - rd[2]*omega[1],
		-rd[0]*omega[2] + rd[2]*omega[0],
		rd[0]*omega[1] - rd[1]*omega[0]};

	float cross_r_omegad[3] = {
		r[1]*omegad[2] - r[2]*omegad[1],
		-r[0]*omegad[2] + r[2]*omegad[0],
		r[0]*omegad[1] - r[1]*omegad[0]};
	
	float a_aux[6] = {
		omegad[0],
		omegad[1],
		omegad[2],
		rdd[0]+cross_rd_omega[0]+cross_r_omegad[0],
		rdd[1]+cross_rd_omega[1]+cross_r_omegad[1],
		rdd[2]+cross_rd_omega[2]+cross_r_omegad[2]};

	for (i=0;i<36;i++) 
	{
		if (i<6)
		{
			v[i] = v_aux[i];
			a[i] = a_aux[i];
		}
		X[i] = X_aux[i];
	}

}