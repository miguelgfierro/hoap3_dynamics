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



#ifndef		_Planar_Vector_Arithmetic_H
#define		_Planar_Vector_Arithmetic_H

class pva
{
public:
	float *v, *X, *rbi, *vcross_crmp, *vcross_crfp;

	pva();
	float* XtoVp (float* X);
	float* Xpln (double theta, float* r);
	float* mcIp (float m, float* c, float I);
	float* crmp (float* v);
	float* crfp (float* v);

private:
	double s,c;
	int i;
};


#endif