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
#include "PlanarVectorDynamicsFunctions.h"
#include "PlanarVectorModelConstructors.h"


using namespace std;


float* pvdf::FDcrbp (pvmc* model, float* q_i, float* qd_i, float* tau, float* f_ext, float* grav_accn)
{
	qdd = new float [6];
	qdd = NULL;
	matrix matrix_aux;
	pvdf pvdf_aux;

	if (f_ext == 0)
	{
		pvdf_aux.HandCp(model,q_i,qd_i);
	}
	else if ((f_ext != 0) && (grav_accn == 0))
	{
		pvdf_aux.HandCp(model,q_i,qd_i,f_ext);
	}
	else if ((f_ext != 0) && (grav_accn != 0))
	{
		pvdf_aux.HandCp(model,q_i,qd_i,f_ext,grav_accn);
	}
	else
	{
		cout << " ERROR";
	}

	float* tau_C = matrix_aux.Sum(tau,pvdf_aux.C,2);

	cout << matrix_aux.Determinant(pvdf_aux.H,6)<<endl;

	qdd = matrix_aux.LeftDiv(pvdf_aux.H,6,tau_C,0,6);

	return qdd;
}