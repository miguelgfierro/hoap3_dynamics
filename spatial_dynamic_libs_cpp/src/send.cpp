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

void send(double* data, int SizeR, int SizeC, char* Name, int Var)
{
	ofstream file (Name);
	
	int b=0;

	if (Var == 0)
	{
		if (file.is_open() == NULL)
		{
			cout <<"file cannot be generated!";
		}
		else
		{ 
			for (int j=0; j<SizeR; j++)
			{
				for (int i=0; i<SizeC; i++)
				{
					if (i == 0)
					{
						//if (j == 0) file << 0 << "\t";
						//else 
						//{
							float aux = j;
							file << aux/SizeR << "\t";
						//}
					}

					file << data[j*SizeC + i] << "\t";
				}
				file << endl << endl;
			}
		}
	}
	else
	{
		if (file.is_open() == NULL)
		{
			cout <<"file cannot be generated!";
		}
		else
		{ 
			for (int j=0; j<SizeR; j+=2)
			{
				for (int i=0; i<SizeC; i++)
				{
					if (i == 0)
					{
						//if (j == 0) file << 0 << "\t";
						//else 
						//{
							//float aux = j;
							file << j << "\t";
						//}
					}
					file << data[j*SizeC + i] << "\t";
				}
				file << endl << endl;
			}
		}
	}


}
void send(float* data,int SizeR, int SizeC, char* Name)
{
	ofstream file (Name);
	
	int b=0;

	if (file.is_open() == NULL)
	{
		cout <<"file cannot be generated!";
	}
	else
	{ 
		for (int j=0; j<SizeR; j++)
		{
			for (int i=0; i<SizeC; i++)
			{
				file << data[j*SizeC + i] << "\t";
			}
			file << endl << endl;
		}
	}
}
void send(double* data, int RowTotal, int ColToral, int Row1, int Col1,int Row2, int Col2, char* Name)
{
	ofstream file (Name);
	
	if (file.is_open() == NULL)
	{
		cout <<"file cannot be generated!";
	}
	else
	{ 
		for (int j=Row1 - 1; j<Row2; j++)
		{
			for (int i = Col1 - 1; i<Col2; i++)
			{
				file << data[j*ColToral + i] << "\t";
			}
			file << endl << endl;
			//cout << "!!!!";
		}
	}
}