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

#ifndef _Model_Constructors_H
#define _Model_Constructors_H

class mc
{
public:
	int NB;
	float pitch;
	int parent;
	float* Xtree;
	float* model;
	float* I;
	float mass;
	float* CoG;
	double* encoder;
	double* qdd;
	double* qd;
	double* q;
	double* tau;
	double* Fx;
	double* Fz;
	double* Fy;
	double* qdd_aba;
	double* qdd_crba;
	double* qdd_fdf;
	double* afb;


	//float* len;

	mc();
	mc* autoTree (int nb, int bf = 1, int skew = 0, int taper = 1);
	mc* floatbase (mc* model);
	mc* planarN (int n);
	mc* test(int x);
	

private:
	float len;
	float* CoM;
	float* Icm;
	int i;
};





#endif