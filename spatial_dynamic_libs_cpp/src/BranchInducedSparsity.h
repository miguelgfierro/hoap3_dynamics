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


#ifndef _Branch_Induced_Sparsity_H
#define _Branch_Induced_Sparsity_H

class bis
{
public:
	float* newLambda;
	float* L_ltl;
	float* L_ltdl;
	float* D_ltdl;
	float* y_mpyH;
	float* y_mpyL;
	float* y_mpyLt;
	float* y_mpyLi;
	float* y_mpyLit;


	bis();
	float* expandLambda (float* lambda, int SizeLambda, float* nf, int SizeNF);
	float* LTL (float* H, int SizeH, float* lambda);
	void LTDL (float* H, int SizeH, float*lambda);
	float* mpyH (float* H, int SizeH, float* lambda, float* x, int SizeX);
	float* mpyL (float* L, int SizeL, float* lambda, float* x, int SizeX);
	float* mpyLt (float* L, int SizeL, float* lambda, float* x, int SizeX);
	float* mpyLi (float* L, int SizeL, float* lambda, float* x, int SizeX);
	float* mpyLit (float* L, int SizeL, float* lambda, float* x, int SizeX);

private:
	int n, i,j,k, *map;
	float a;
};



#endif