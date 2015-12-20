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
/// file SparialVectorArithmetic.h
/// class header
///



#ifndef _Spatial_Vector_Arithmetic_H
#define _Spatial_Vector_Arithmetic_H

class sva
{
public:
	float *vcross_crf, *vcross_crm, *x_rotx, *x_roty, *x_rotz, *v, *x_trans, *rbi;
	double *vcross_crf_d, *vcross_crm_d, *v_d, *x_trans_d, *rbi_d, *x_rotx_d, *x_roty_d, *x_rotz_d;


	//sva();
	float* crm (float* v);
	void crm (float* dst, float* v);
	float* crf (float* v);
	void crf (float* dst, float* v);
	float* mcI (float m, float* c, float* I);
	float* Xrotx (double theta);
	float* Xroty (double theta);
	float* Xrotz (double theta);
	float* Xtov (float *X);
	float* Xtrans (float* r);

	double* crm (double* v);
	double* crf (double* v);
	double* mcI (double m, double* c, double* I);
	double* Xrotx_d (double theta);
	double* Xroty_d (double theta);
	double* Xrotz_d (double theta);
	double* Xtov (double *X);
	double* Xtrans (double* r);
	void svaDelete (sva model);

private:
	int i;
};

#endif