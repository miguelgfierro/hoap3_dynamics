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
//// file crfp.cpp
//
//
//
//
// crfp  planar cross-product operator (force).
// crfp(v) calculates the 3x3 matrix such that the expression crfp(v)*f is
// the cross product of the planar motion vector v with the planar force
// vector f.

#include <iostream>
#include "PlanarVectorArithmetic.h"


float* pva::crfp (float* v)
{
	vcross_crfp = new float [9];

	float vcross[9] = {
		0,-v[2],v[1],
		0,0,-v[0],
		0,v[0],0,
	};
	
	for (i=0;i<9;i++) vcross_crfp[i] = vcross[i];

	return vcross_crfp;
}
