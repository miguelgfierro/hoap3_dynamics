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


#ifndef		_Hoap_H
#define		_Hoap_H

#include "ModelConstructors.h"

using namespace std;

void two_legs();
void two_legs_floating_base();
void second();
void second_floating_base();
void forward_walking();
void read(mc* HOAP, int SizeR, int SizeC, char* Name);
void read(double* hoap, int SizeR, int SizeC, char* Name);
void qd_diff(mc* stance, int SizeR, int SizeC, double Scalar);
void qdd_diff(mc* stance, int SizeR, int SizeC, double Scalar);
void mass_prop_HOAP (mc* body, mc* left_arm, mc* right_arm, mc* left_leg, mc* right_leg, mc* head);
void read_points(mc* HOAP);
void send(double* data,int SizeR, int SizeC, char* Name, int Var = 0);
void send(float* data,int SizeR, int SizeC, char* Name);
void send(double* data, int RowTotal, int ColToral, int Row1, int Col1,int Row2, int Col2, char* Name);

#endif