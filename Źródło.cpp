#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

const int wys = 50;
const int dlu = 50;
const int miasta = 1000;

struct Miasto
{
	int x;
	int y;
};

bool stos_check(int x, int y, int n, int m, Miasto stos[miasta]);
void wypis(int mapa[wys][dlu], int n, int m);
void zeruj(Miasto stos[miasta]);
void randomise(int o, int i, int n, int m, Miasto stos[miasta], int mapa[wys][dlu], bool done);
bool spojnosc(int n, int m, Miasto stos[miasta]);
void kanal(bool polaczenie, Miasto stos[miasta], int akt, int licz, int mapa[wys][dlu], int n, int m, int suma);

int main()
{
	Miasto stos[miasta];
	int connected[wys][dlu];
	int n, m;
	srand(time(0));
	int random = rand() % 2;
	int mapa[wys][dlu];
	int ulice[wys][dlu];
	cin >> n >> m;
	int suma = n * m;
	n = n * 2 - 1;
	m = m * 2 - 1;
	for (int i = 0; i < n; i++)
	{
		for (int o = 0; o < m; o++)
		{
			connected[i][o] = 0;
			if (i % 2 == 0 && o % 2 == 0)
			{
				mapa[i][o] = 2;
			}
			else
			{
				if (i % 2 == 1 && o % 2 == 1)
				{
					mapa[i][o] = 0;
				}
				else
				{
					random = rand() % 2;
					if (random == 1)
					{
						mapa[i][o] = 1;
					}
					else
					{
						mapa[i][o] = 0;
					}
				}
			}
		}
	}
	random = rand() % 2;
	if (random % 2 == 0)
	{
		mapa[0][1] = 1;
	}
	else
	{
		mapa[1][0] = 1;
	}
	wypis(mapa, n, m);
	int konieci = 0;
	bool done = 0;
	int licz = 0;
	int akt = 0;
	stos[0].x = 0;
	stos[0].y = 0;
	bool polaczenie = 0;
	bool koniec = 0;
	while (1)
	{
		if (spojnosc(n, m, stos) == 1)
		{
			cout << "spojne" << endl;
			wypis(mapa, n, m);
			break;
		}
		zeruj(stos);
		done = 0;
		akt = 0;
		licz = 0;
		polaczenie = 0;
		while (polaczenie == 0)
		{
			if (stos[akt].y < 0 && stos[akt].x < 0)
			{
				break;
			}
			konieci = 0;
			if (stos[akt].y > 0)
			{
				if (mapa[stos[akt].y - 1][stos[akt].x] == 1)
				{
					if (stos_check(stos[akt].x, stos[akt].y - 2, n, m, stos) == 0)
					{
						licz++;
						stos[licz].y = stos[akt].y - 2;
						stos[licz].x = stos[akt].x;
						//cout << stos[licz].x << " " << stos[licz].y << endl;
					}
					else konieci++;
				}
			}
			else konieci++;
			if (mapa[stos[akt].y + 1][stos[akt].x] == 1)
			{
				if (stos_check(stos[akt].x, stos[akt].y + 2, n, m, stos) == 0)
				{
					licz++;
					stos[licz].y = stos[akt].y + 2;
					stos[licz].x = stos[akt].x;
					//cout << stos[licz].x << " " << stos[licz].y << endl;
				}
				else konieci++;
			}
			if (stos[akt].x > 0)
			{
				if (mapa[stos[akt].y][stos[akt].x - 1] == 1)
				{
					if (stos_check(stos[akt].x - 2, stos[akt].y, n, m, stos) == 0)
					{
						licz++;
						stos[licz].y = stos[akt].y;
						stos[licz].x = stos[akt].x - 2;
						//cout << stos[licz].x << " " << stos[licz].y << endl;
					}
					else konieci++;
				}
			}
			else konieci++;
			if (mapa[stos[akt].y][stos[akt].x + 1] == 1)
			{
				if (stos_check(stos[akt].x + 2, stos[akt].y, n, m, stos) == 0)
				{
					licz++;
					stos[licz].y = stos[akt].y;
					stos[licz].x = stos[akt].x + 2;
					//cout << stos[licz].x << " " << stos[licz].y << endl;
				}
				else konieci++;
			}
			if (stos[akt].y == 0 && stos[akt].x == 0 && akt!=0)
			{
				polaczenie = 1;
			}
			if (akt > suma)
			{
				polaczenie = 1;
			}
			akt++;
		}
		for (int i = 0; i < n; i += 2)
		{
			for (int o = 0; o < m; o += 2)
			{
				if (stos_check(o, i, n, m, stos) == 0)
				{
					randomise(o, i, n, m, stos, mapa, done);
					if (done == 1) break;
				}
			}
			if (done == 1)
			{
				break;
			}
			
		}
	}
	zeruj(stos);
	done = 0;
	akt = 0;
	licz = 0;
	polaczenie = 0;
	kanal(polaczenie, stos, akt, licz, mapa, n, m, suma);
	wypis(mapa, n, m);
	return 0;
}

bool stos_check(int x, int y, int n, int m, Miasto stos[miasta])
{
	for (int z = 0; z < miasta; z++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int o = 0; o < m; o++)
			{
				if (stos[z].x == x && stos[z].y == y)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void wypis(int mapa[wys][dlu], int n, int m)
{
	char kanal = 176;
	for (int i = 0; i < n; i++)
	{
		for (int o = 0; o < m; o++)
		{
			if (mapa[i][o] == 2)
			{
				cout << "X";
			}
			if (mapa[i][o] == 0)
			{
				if (o % 2 == 0 && i % 2 == 1)
				{
					cout << " ";
				}
				else
				{
					cout << "    ";
				}
			}
			if (mapa[i][o] == 1)
			{
				if (i % 2 == 0)
				{
					cout << "----";
				}
				else
				{
					cout << "|";

				}
			}
			if (mapa[i][o] == 3)
			{
				if (i % 2 == 0)
				{
					cout << "====";
				}
				else
				{
					cout << kanal;

				}
			}
		}
		cout << endl ;
		
	}
	cout << "#########################################################################################################################" << endl;
}

void zeruj(Miasto stos[miasta])
{
	for (int i = 0; i < miasta; i++)
	{
		stos[i].x = 0;
		stos[i].y = 0;
	}
}

void randomise(int o, int i, int n, int m, Miasto stos[miasta], int mapa[wys][dlu], bool done)
{
	int losowanie[4] = { 5,5,5,5 };
	int los = rand() % 4 + 1;
	losowanie[0] = los;
	bool koniec = 0;
	for (int z = 1; z <= 3; z++)
	{
		koniec = 0;
		while (koniec == 0)
		{
			los = rand() % 4 + 1;
			if (los != losowanie[0] && los != losowanie[1] && los != losowanie[2] && los != losowanie[3])
			{
				losowanie[z] = los;
				koniec = 1;
			}
		}
	}
	for (int z = 0; z < 4; z++)
	{
		if (o > 0 && losowanie[z] == 1)
		{
			if (stos_check(o - 2, i, n, m, stos) == 1)
			{
				mapa[i][o - 1] = 1;
				done = 1;
			}
		}
		if (i > 0 && losowanie[z] == 2)
		{
			if (stos_check(o, i - 2, n, m, stos) == 1 && done != 1)
			{
				mapa[i - 1][o] = 1;
				done = 1;
			}
		}
		if (stos_check(o, i + 2, n, m, stos) == 1 && done != 1 && losowanie[z] == 3)
		{
			mapa[i + 1][o] = 1;
			done = 1;
		}
		if (stos_check(o + 2, i, n, m, stos) == 1 && done != 1 && losowanie[z] == 4)
		{
			mapa[i][o + 1] = 1;
			done = 1;
		}
	}
}

bool spojnosc(int n, int m, Miasto stos[miasta])
{
	bool dobrze = 0;
	int licz = 0;
	for (int z = 0; z < miasta; z++)
	{
		for (int i = 0; i < n; i+=2)
		{
			for (int o = 0; o < m; o+=2)
			{
				if (stos[z].x == o && stos[z].y == i)
				{
					if (stos[z].x == 0 && stos[z].y == 0)
					{
						if (z == 0)
						{
							licz++;
						}
					}
					else
					{
						licz++;
					}
				}
			}
		}
	}
	if (licz == (n + 1) / 2 * (m + 1) / 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void kanal(bool polaczenie, Miasto stos[miasta], int akt, int licz, int mapa[wys][dlu], int n, int m, int suma)
{
	while (polaczenie == 0)
	{
		if (stos[akt].y < 0 && stos[akt].x < 0)
		{
			break;
		}
		if (stos[akt].y > 0)
		{
			if (mapa[stos[akt].y - 1][stos[akt].x] == 1)
			{
				if (stos_check(stos[akt].x, stos[akt].y - 2, n, m, stos) == 0)
				{
					licz++;
					stos[licz].y = stos[akt].y - 2;
					stos[licz].x = stos[akt].x;
					mapa[stos[akt].y - 1][stos[akt].x] = 3;
					//cout << stos[licz].x << " " << stos[licz].y << endl;
				}
			}
			//else konieci++;
		}
		if (mapa[stos[akt].y + 1][stos[akt].x] == 1)
		{
			if (stos_check(stos[akt].x, stos[akt].y + 2, n, m, stos) == 0)
			{
				licz++;
				stos[licz].y = stos[akt].y + 2;
				stos[licz].x = stos[akt].x;
				mapa[stos[akt].y + 1][stos[akt].x] = 3;
				//cout << stos[licz].x << " " << stos[licz].y << endl;
			}
		}
		if (stos[akt].x > 0)
		{
			if (mapa[stos[akt].y][stos[akt].x - 1] == 1)
			{
				if (stos_check(stos[akt].x - 2, stos[akt].y, n, m, stos) == 0)
				{
					licz++;
					stos[licz].y = stos[akt].y;
					stos[licz].x = stos[akt].x - 2;
					//cout << stos[licz].x << " " << stos[licz].y << endl;
					mapa[stos[akt].y][stos[akt].x - 1] = 3;
				}
			}
			//else konieci++;
		}
		if (mapa[stos[akt].y][stos[akt].x + 1] == 1)
		{
			if (stos_check(stos[akt].x + 2, stos[akt].y, n, m, stos) == 0)
			{
				licz++;
				stos[licz].y = stos[akt].y;
				stos[licz].x = stos[akt].x + 2;
				//cout << stos[licz].x << " " << stos[licz].y << endl;
				mapa[stos[akt].y][stos[akt].x + 1] = 3;
			}
		}
		if (stos[akt].y == 0 && stos[akt].x == 0 && akt != 0)
		{
			polaczenie = 1;
		}
		if (akt > suma)
		{
			polaczenie = 1;
		}
		akt++;
	}
}
