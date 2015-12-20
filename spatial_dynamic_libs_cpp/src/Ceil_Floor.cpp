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

//using namespace std;


float matrix::Ceil (float Scalar)
{
	float Ceil_scalar = Scalar;
	if (Scalar > 0)
	{
		while (Scalar > 0)
		{
			Scalar--; 
		}
		Scalar++;
		Ceil_scalar -= Scalar - 1;
	}
	else if (Scalar == 0) Ceil_scalar = 0;
	else if (Scalar < 0)
	{
		while (Scalar < 0)
		{
			Scalar++; 
		}
		Scalar--;
		Ceil_scalar -= Scalar;
	}

	return Ceil_scalar;
}

float matrix::Floor (float Scalar)
{
	float Floor_scalar = Scalar;
	if (Scalar > 0)
	{
		while (Scalar > 0)
		{
			Scalar--; 
		}
		Scalar++;
		Floor_scalar -= Scalar;
	}
	else if (Scalar == 0) Floor_scalar = 0;
	else if (Scalar < 0)
	{
		while (Scalar < 0)
		{
			Scalar++; 
		}
		Scalar--;
		Floor_scalar -= Scalar + 1;
	}
	return Floor_scalar;
}


