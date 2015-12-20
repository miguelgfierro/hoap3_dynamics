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
///		file Matrix.h
///		class header 


#ifndef	_Matrix_H
#define _Matrix_H

using namespace std;


double det (const int size, const float*const src);

class matrix
{
public:
	float* C_sum;
	float* C_transponse;
	float* diag;
	float* eye_matrix;
	float dot_product;
	float* zeros;
	float* ones;
	float* C_VectorMulti;
	float* C_Vector_Div;
	float result;
	float* U;
	float* L;

	double* C_sum_d;

	matrix();
	float* Sum (float* A, float* B, int sign = 0);
	float* Sum (float* A, int SizeA, float* B, int sign = 0);
	void  Sum (float* dst, float* A, float* B, int sign);
	double* Sum (double* A, double* B, int sign = 0);
	double* Sum (double* A, int SizeA, double* B, int sign = 0);

	float* Multiplication (float* A, int SizeAr, int SizeAc, float* B, int SizeBr, int SizeBc, float* D = 0, int SizeDr = 0, int SizeDc = 0);
	void Multiplication (float* dst, float* A, int SizeAr, int SizeAc, float* B, int SizeBr, int SizeBc);

	float* MultiVecMat (float* A, int SizeAc, float* B, int SizeBr, int SizeBc);
	double* MultiVecMat (double* A, int SizeAc, double* B, int SizeBr, int SizeBc);

	float* Transponse (float* A, int SizeAr, int SizeAc);
	double* Transponse (double* A, int SizeAr, int SizeAc);

	void Display  (float* A, int SizeAr, int SizeAc);
	void Display  (double* A, int SizeAr, int SizeAc);

	float* ScalarMulti (float* A, int SizeAr, int SizeAc, float Scalar, int sign = 0);
	double* ScalarMulti (double* A, int SizeAr, int SizeAc, double Scalar, int sign = 0);

	float DotProduct (float* A, int SizeA, float* B, int SizeB);
	double DotProduct (double* A, int SizeA, double* B, int SizeB);

	float* Eye (int Size);

	float* DiagOfDiag (float* A, int SizeA);

	float* Zeros(int SizeAr, int SizeAc);

	float* Ones(int SizeAr, int SizeAc);

	float PowerScalar (float Scalar, int power);

	float Floor (float Scalar);

	float Ceil (float Scalar);

	float* VectorMulti (float* A, float* B);
	double* VectorMulti (double* A, double* B);

	float* VectorDivision (float* A, int SizeAr, int SizeAc, float* B, int SizeB);
	double* VectorDivision (double* A, int SizeAr, int SizeAc, double* B, int SizeB);

	float* ScalarAdd (float* A, int SizeA, float scalar, int sign = 0);
	double* ScalarAdd (double* A, int SizeA, double scalar, int sign = 0);

	float* VectorToMatrix (float* A, int SizeAr, float* B, int SizeBr);
	double* VectorToMatrix (double* A, int SizeAr, double* B, int SizeBr);

	void VectorToMatrix(float* dst, float *A, int SizeAr, float *B, int SizeBr);

	double Determinant(float* A, int Size);
	double Determinant(double* A, int Size);

	float* InvMat (float* A, int Size);
	double* InvMat (double* A, int Size);

	float* Minor(float* A, int row, int col, int Size);
	double* Minor(double* A, int row, int col, int Size);

	float* LeftDiv (float* A, int Size,float* B, int SizeBr, int SizeBc);
	double* LeftDiv (double* A, int Size,double* B, int SizeBr, int SizeBc);

	double* MultiE (double* A, double* B, int SizeBr, int SizeBc);

	float MultiVect (float* A, float* B, int SizeBr);

private:
	int i,j,k,p2,p1;
	double temp;
	float p;
	double p_d;
};

#endif 

