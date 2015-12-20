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
#include "ArrayRelease.h"


using namespace std;



void svaRelease (sva model)
{
	if (model.vcross_crf != NULL) delete [] model.vcross_crf;
	if (model.vcross_crm != NULL) delete [] model.vcross_crm;
	if (model.x_rotx != NULL) delete [] model.x_rotx;
	if (model.x_roty != NULL) delete [] model.x_roty;
	if (model.x_rotz != NULL) delete [] model.x_rotz;
	if (model.v != NULL) delete [] model.v;
	if (model.x_trans != NULL) delete [] model.x_trans;
	if (model.rbi != NULL) delete [] model.rbi;
}

void pvaRelease (pva model)
{
	if (model.v != NULL) delete [] model.v;
	if (model.X != NULL) delete [] model.X;
	if (model.rbi != NULL) delete [] model.rbi;
	if (model.vcross_crfp != NULL) delete [] model.vcross_crfp;
	if (model.vcross_crmp != NULL) delete [] model.vcross_crmp;
}

void bisRelease (bis model)
{
	if (model.newLambda != NULL) delete [] model.newLambda;
	if (model.L_ltl != NULL) delete [] model.L_ltl;
	if (model.L_ltdl != NULL) delete [] model.L_ltdl;
	if (model.D_ltdl != NULL) delete [] model.D_ltdl;
	if (model.y_mpyH != NULL) delete [] model.y_mpyH;
	if (model.y_mpyL != NULL) delete [] model.y_mpyL;
	if (model.y_mpyLt != NULL) delete [] model.y_mpyLt;
	if (model.y_mpyLi != NULL) delete [] model.y_mpyLi;
	if (model.y_mpyLit != NULL) delete [] model.y_mpyLit;
}

void matrixRelease (matrix model)
{
/*	if (model.eye_matrix != NULL) delete [] model.eye_matrix;
	if (model.diag != NULL) delete [] model.diag;
	if (model.C_sum != NULL) delete [] model.C_sum;
	if (model.C_Multiply2 != NULL) delete [] model.C_Multiply2;
	if (model.C_Multiply3 != NULL) delete [] model.C_Multiply3;
	if (model.C_transponse != NULL) delete [] model.C_transponse;
	if (model.zeros != NULL) delete [] model.zeros;*/
}

void mcRelease (mc *model, int Size)
{
	int i;
	//if (model[0].pitch != NULL) delete [] model[0].pitch;
	//if (model[0].parent != NULL) delete [] model[i].parent;
	for (i=0;i<Size;i++)
	{
		if (model[i].Xtree != NULL) delete [] model[i].Xtree;
	}
}
void mcRelease (mc model)
{
		//if (model.pitch != NULL) delete [] model.pitch;
		if (model.Xtree != NULL) delete [] model.Xtree;
}
void pvdfRelease (pvdf model)
{
	if (model.Xj != NULL) delete [] model.Xj;
	if (model.S != NULL) delete [] model.S;
}
void pvdfRelease (pvdf* model, int Size)
{
	//if (model.qdd != NULL) delete [] model.qdd;
	for (int i=0;i<Size;i++)
	{
		if (model[i].Xj != NULL) delete [] model[i].Xj;
		if (model[i].S != NULL) delete [] model[i].S;
	}
}