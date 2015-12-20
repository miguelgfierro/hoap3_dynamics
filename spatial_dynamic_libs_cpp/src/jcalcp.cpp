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
//// file jcalc.cpp
//
//
//
//
//
//
//
//
//
#include <iostream>
#include "PlanarVectorDynamicsFunctions.h"
#include "PlanarVectorArithmetic.h"
#include "ArrayRelease.h"
#include "Matrix.h"


void pvdf::jcalcp (float code, float q)
{
	pva pva_aux;
	matrix matrix_aux;

	Xj = new float [36];
	S = new float [3];

	if (code == 1)
	{
		float array_aux2[2] = {0,0};
		float array_aux3[3] = {1,0,0};

		Xj = pva_aux.Xpln(q,array_aux2);
		for (i=0;i<3;i++)S[i] = array_aux3[i];
	}
	else if (code == 2)
	{
		float array_aux2[2] = {q,0};
		float array_aux3[3] = {0,1,0};

		Xj = pva_aux.Xpln(0,array_aux2);
		for (i=0;i<3;i++)S[i] = array_aux3[i];
	}
	else if (code == 3)
	{
		float array_aux2[2] = {0,q};
		float array_aux3[3] = {0,0,1};

		Xj = pva_aux.Xpln(0,array_aux2);
		for (i=0;i<3;i++)S[i] = array_aux3[i];
	}
	else
	{
		cout << "unrecognised joint code";
	}
}


