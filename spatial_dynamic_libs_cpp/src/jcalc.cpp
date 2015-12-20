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



#include <iostream>
#include "DynamicsFunctions.h"
#include "SpatialVectorArithmetic.h"
#include "Matrix.h"

using namespace std;

void df::jcalc(float pitch, float q)
{
	matrix matrix_aux;
	sva sva_aux;

	S = NULL;
	Xj = NULL;

	Xj = new float [6*6];
	S = new float [6];

	if (pitch == 0)
	{
		Xj = sva_aux.Xrotz(q);
		float S_temp[6] = {0,0,1,0,0,0};

		for (i=0;i<6;i++) S[i] = S_temp[i];
	}
	else if (pitch == 999999)
	{
		cout<<"prismatic case";
	}
	else
	{
		float array_temp[3] = {0,0,q*pitch};
		Xj = matrix_aux.Multiplication(sva_aux.Xrotz(q),6,6,sva_aux.Xtrans(array_temp),6,6);
		float S_temp[6] = {0,0,1,0,0,pitch};
		for (i=0;i<6;i++) S[i] = S_temp[i];

	}
}
