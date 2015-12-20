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
#include <fstream>
#include "hoap.h"

using namespace std;

void read(mc* HOAP, int SizeR, int SizeC, char* Name)
{
	ifstream file (Name);
	
	int b=0;

	if (file.is_open() == NULL)
	{
		cout <<"file " << Name << " cannot be opened!";
	}
	else
	{ 

		cout <<"file " << Name << " opened properly" << endl;
		for (int j=0; j<SizeR*SizeC; j++)
		{
			for (int i=0; i<SizeC; i++)
			{
				file >> HOAP[0].q[b];
				b++;
			}
		}
	}
	//file.close;
}

void read(double* hoap, int SizeR, int SizeC, char* Name)
{
	ifstream file (Name);
	
	int b=0;

	if (file.is_open() == NULL)
	{
		cout <<"file cannot be opened!";
	}
	else
	{ 
		cout <<"file " << Name << " opened properly" << endl;
		for (int j=0; j<SizeR*SizeC; j++)
		{
			for (int i=0; i<SizeC; i++)
			{
				file >> hoap[b];
				b++;
			}
		}
	}
	//file.close;
}