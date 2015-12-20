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
/// file crmp.cpp
//
//
//
// crmp  planar cross-product operator (motion).
// crmp(v) calculates the 3x3 matrix such that the expression crmp(v)*m is
// the cross product of the planar motion vectors v and m.


#include <iostream>
#include "PlanarVectorArithmetic.h"

using namespace std;

float* pva::crmp (float* v)
{
	vcross_crmp = new float [3*3];

	float vcross [9] = {
		0,0,0,
		v[2],0,-v[0],
		-v[1],v[0],0
		};

	for (i=0; i<9; i++) vcross_crmp[i] = vcross[i];
	
	return vcross_crmp;
}