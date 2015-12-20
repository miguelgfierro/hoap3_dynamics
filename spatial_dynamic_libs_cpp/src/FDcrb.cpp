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
#include "hoap.h"


using namespace std;


float* df::FDcrb (mc* model, float* q_i, float* qd_i, float* tau, float* f_ext, float* grav_accn)
{
	qdd = new float [model[0].NB];
	matrix matrix_aux;
	df df_aux;

	if (f_ext == 0)
	{
		df_aux.HandC(model,q_i,qd_i);
	}
	else if ((f_ext != 0) && (grav_accn == 0))
	{
		df_aux.HandC(model,q_i,qd_i,f_ext);
	}
	else if ((f_ext != 0) && (grav_accn != 0))
	{
		df_aux.HandC(model,q_i,qd_i,f_ext,grav_accn);
	}
	else
	{
		cout << " ERROR";
	}

	float* tau_C = matrix_aux.Sum(tau,df_aux.C,2);

	send(df_aux.H,21,21,"H.txt");

	qdd = matrix_aux.LeftDiv(df_aux.H,model[0].NB,tau_C,0,model[0].NB);

	return qdd;
}


