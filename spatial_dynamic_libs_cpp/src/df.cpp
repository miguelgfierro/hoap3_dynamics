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
/// file df.cpp
///
///
///
///
/// constructor

#include <iostream>
#include "DynamicsFunctions.h"

using namespace std;

df::df()
{
	Xj = NULL; S = NULL;  tau = NULL;  a_grav = NULL ; a_grav_n = NULL;  f = NULL; X = NULL; v = NULL; c = NULL; a = NULL; q = NULL; qd = NULL; qdd = NULL;
	IA = NULL; pA = NULL; U = NULL; u1 = NULL;  u = NULL;  d = NULL; Xup = NULL; pa = NULL; Ia = NULL; vJ = NULL; IAfb = NULL; pAfb = NULL; afb = NULL; avp = NULL;
	fvp = NULL; C = NULL; H = NULL; IC = NULL; ICfb = NULL;  pCfb = NULL; pC = NULL; fh = NULL; qdd_out = NULL;  tau_out = NULL; f_ext = NULL;

	Xj_d = NULL;  S_d = NULL;  tau_d = NULL; a_grav_d = NULL;  a_grav_n_d = NULL;  f_d = NULL;  X_d = NULL; v_d = NULL; c_d = NULL; a_d = NULL; q_d = NULL; qd_d = NULL;
	qdd_d = NULL; IA_d = NULL; pA_d = NULL; U_d = NULL; u1_d = NULL;  u_d = NULL;  d_d = NULL; Xup_d = NULL; pa_d = NULL; Ia_d = NULL; vJ_d = NULL; IAfb_d = NULL; pAfb_d = NULL;
	afb_d = NULL; avp_d = NULL; fvp_d = NULL; C_d = NULL; H_d = NULL; IC_d = NULL; ICfb_d = NULL;  pCfb_d = NULL; pC_d = NULL; fh_d = NULL; qdd_out_d = NULL;  tau_out_d = NULL; f_ext_d = NULL;
}