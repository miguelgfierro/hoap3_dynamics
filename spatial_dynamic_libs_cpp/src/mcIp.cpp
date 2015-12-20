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
/// file mcIp.cpp
//
//
//
//
//
// mcIp  planar rigid-body inertia from mass, CoM and rotational inertia.
// mcIp(m,c,I) calculates the planar inertia matrix of a rigid body from its
// mass, centre of mass (2D vector) and rotational inertia (scalar) about
// its centre of mass.

#include <iostream>
#include "PlanarVectorArithmetic.h"

using namespace std;

float* pva::mcIp (float m, float* c, float I)
{

	rbi = new float [9];

	float temp = c[0]*c[0]+c[1]*c[1];
	
	float RBI[9] = {
		I+m*temp, -m*c[1], m*c[0],
		-m*c[1],m,0,
		m*c[0],0,m,
	};

	for (i=0; i<9; i++) rbi[i] = RBI[i];
	return rbi;
}