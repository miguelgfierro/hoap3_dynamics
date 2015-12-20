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
#include "Matrix.h"


using namespace std;

void read_points(mc* HOAP)
{
	//matrix matrix_aux;

	ifstream file ("test.txt");
	
//	HOAP[0].encoder = new float [20*17901];
	//float* a = new float[20*17901];
	int b=0;
	int* trash = new int [20*17901];

	if (file.is_open() == NULL)
	{
		cout <<"file cannot be opened!";
		//cout <<"asd";
	}
	else
	{ 
		for (int j=0; j<17901; j++)
		{
			for (int i=0; i<25; i++)
			{
				
				if (i>1 && i<22)
				{
					file >> HOAP[0].encoder[b];

					//cout << a[b];
					b++;
				}
				else 
				{
					file >> trash[i];
				}
			}
		}
		//file.close;
	}

	//for (int i=0; i<20*17901; i++)
	//{
	//	HOAP[0].encoder[i] = a[i];
	//}

	//detele[] a;
	//detele[] trash;
	//matrix_aux.Display (HOAP[0].encoder,0,20);

}