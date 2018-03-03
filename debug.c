#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define dim_max 50
#define inf 999999
#define ruta_directa -1

int** Floyd ( int** graf, int n )
{
	int i, j, k;
	// Matricea in care voi retine nodurile intermediare
	int** drum = ( int** ) calloc ( n, sizeof ( int* ) );
	for ( i = 0; i < n; i++ )
		drum[i] = ( int* ) calloc ( n, sizeof ( int ) );
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			drum[i][j] = ruta_directa;

	// Aplic algoritmul lui Floyd
	// Verific daca intre oricare doua noduri exista un drum intermediar
	// Daca exista verific daca costul acelui drum eeste mai mic decat costul drumului curent
	for ( k = 0; k < n; k++ )
		for ( i = 0; i < n; i++ )
			for ( j = 0; j < n; j++ )
				if ( graf[i][k] != inf && graf[k][j] != inf && i != j && 
					 graf[i][k] + graf[k][j] < graf[i][j] )
				{
					drum[i][j] = k;
					graf[i][j] = graf[i][k] + graf[k][j];
				}			
	return drum;
}

void noduri_intermediare ( FILE* output, int** drum, int x, int y )
{
	// Nodul intermediar dintre x si y
	int k;
	k = drum[x][y];
	if ( k != ruta_directa )
	{
		noduri_intermediare ( output, drum, x, k );
		fprintf ( output, "%d ", k );
		noduri_intermediare ( output, drum, k, y );
	}
}

void afiseaza ( int** graf, int n )
{
	int i, j;
	for ( i = 0; i < n; i++ )
	{
		for ( j = 0; j < n; j++ )
			printf ( "%d ", graf[i][j] );
		printf ( "\n" );
	}
}

void task1 ( FILE* input, FILE* output )
{
	int n;
	fscanf ( input, "%d\n", &n );
	int i, j;
	// Citesc tipul puctelor de interes
	char buffer[100];
	fgets ( buffer, 100, input );
	int ferma;
	for ( i = 0; i < strlen ( buffer ); i += 2 )
	{
		if ( buffer[i] == '1' )
		{
			ferma = i / 2;
			break;
		}
	}
	// Matricea asociata grafului ( graf[i][j] = distanta dintre i si j )
	int** graf = ( int** ) malloc ( n * sizeof ( int* ) );
	for ( i = 0; i < n; i++ )
		graf[i] = ( int* ) malloc ( n * sizeof ( int ) );
	// Initializez fiecare distanta cu inf
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			graf[i][j] = inf;
	// Citesc numarul de culuare aeriene
	int nr_culoare;
	fscanf ( input, "%d\n", &nr_culoare );
	// Citesc disatantele intre punctele de interes
	for ( i = 0; i < nr_culoare; i++ )
	{
		int x, y, cost;
		fscanf ( input, "%d %d %d\n", &x, &y, &cost );
		graf[x][y] = cost;
	}
	// Numarul de comenzi
	int nr_comenzi;
	fscanf ( input, "%d\n", &nr_comenzi );
	
	// Citesc fiecare comanda
	int** comenzi = ( int** ) malloc ( nr_comenzi * sizeof ( int* ) );
	for ( i = 0; i < nr_comenzi; i++ )
	{
		comenzi[i] = ( int* ) malloc ( 2 * sizeof ( int ) );
		fscanf ( input, "%d %d\n", &comenzi[i][0], &comenzi[i][1] );
	}

	// Matricea drumurilor minime
	int** drum = Floyd ( graf, n );
	int cost = 0;
	// Prelucrez fiecare comanda
	for ( i = 0; i < nr_comenzi; i++ )
	{
		cost += graf[ferma][ comenzi[i][1] ];
		cost += graf[ comenzi[i][1] ][ferma];
		fprintf ( output, "%d ", ferma );
		noduri_intermediare ( output, drum, ferma, comenzi[i][1] );
		fprintf ( output, "%d ", comenzi[i][1] );
		noduri_intermediare ( output, drum, comenzi[i][1], ferma );
	}
	fprintf ( output, "%d\n%d\n", ferma, cost );

	// Eliberarea memoriei
	for ( i = 0; i < n; i++ )
	{
		free ( drum[i] );
		free ( graf[i] );
	}
	free ( graf );
	free ( drum );

	for ( i = 0; i < nr_comenzi; i++ )
		free ( comenzi[i] );
	free ( comenzi );

}

void task2 ( FILE* input, FILE* output )
{
	int n;
	fscanf ( input, "%d\n", &n );
	int i, j;
	// Citesc tipul puctelor de interes
	char buffer[100];
	fgets ( buffer, 100, input );
	int* ferma = ( int* ) malloc ( n * sizeof ( int ) );
	int k = 0;
	for ( i = 0; i < strlen ( buffer ); i += 2 )
	{
		if ( buffer[i] == '1' )
		{
			ferma[k] = i / 2;
			k++;
		}
	}
	// Matricea asociata grafului ( graf[i][j] = distanta dintre i si j )
	int** graf = ( int** ) malloc ( n * sizeof ( int* ) );
	for ( i = 0; i < n; i++ )
		graf[i] = ( int* ) malloc ( n * sizeof ( int ) );
	// Initializez fiecare distanta cu inf
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			graf[i][j] = inf;
	// Citesc numarul de culuare aeriene
	int nr_culoare;
	fscanf ( input, "%d\n", &nr_culoare );
	// Citesc disatantele intre punctele de interes
	for ( i = 0; i < nr_culoare; i++ )
	{
		int x, y, cost;
		fscanf ( input, "%d %d %d\n", &x, &y, &cost );
		graf[x][y] = cost;
	}
	// Numarul de comenzi
	int nr_comenzi;
	fscanf ( input, "%d\n", &nr_comenzi );
	
	// Citesc fiecare comanda
	int** comenzi = ( int** ) malloc ( nr_comenzi * sizeof ( int* ) );
	for ( i = 0; i < nr_comenzi; i++ )
	{
		comenzi[i] = ( int* ) malloc ( 2 * sizeof ( int ) );
		fscanf ( input, "%d %d\n", &comenzi[i][0], &comenzi[i][1] );
	}
	// Ferma de start
	int start;
	fscanf ( input, "%d", &start );

	// Matricea drumurilor minime
	int** drum = Floyd ( graf, n );
	int cost = 0;
	// Prelucrez fiecare comanda
	for ( i = 0; i < nr_comenzi; i++ )
	{
		cost += graf[start][ comenzi[i][1] ];
		fprintf ( output, "%d ", start );
		noduri_intermediare ( output, drum, start, comenzi[i][1] );
		fprintf ( output, "%d ", comenzi[i][1] );
		int min = inf;
		// Aflu cel mai mic drum pana la o ferma + urmatorul nod
		for ( j = 0; j < k; j++ )
		{
			if ( i != nr_comenzi - 1 )
			{
				if ( graf[ comenzi[i][1] ][ ferma[j] ] + graf[ ferma[j] ][ comenzi[ i + 1 ][1] ] < min )
				{
					min = graf[ comenzi[i][1] ][ ferma[j] ] + graf[ferma[j]][ comenzi[ i + 1 ][1] ];
					start = ferma[j];
				}
			}
			else
				if ( graf[ comenzi[i][1] ][ ferma[j] ] < min )
				{
					min = graf[ comenzi[i][1] ][ ferma[j] ];
					start = ferma[j];
				}
		}

		noduri_intermediare ( output, drum, comenzi[i][1], start );

		cost += graf[ comenzi[i][1] ][start];
	}
	fprintf ( output, "%d\n%d\n", start, cost );

	// Eliberarea memoriei
	for ( i = 0; i < n; i++ )
	{
		free ( drum[i] );
		free ( graf[i] );
	}
	free ( graf );
	free ( drum );

	for ( i = 0; i < nr_comenzi; i++ )
		free ( comenzi[i] );
	free ( comenzi );

	free ( ferma );
}

int v[100], w[100], n, min = inf, dim;
int** graf;
int* tip_nod;

// Functia ce verifica daca noul element introdus in vector
// cu ajutorul metodei backtracking este valid
int valid ( int k )
{
	if ( graf[ v[k - 1] ][ v[k] ] != inf && v[k - 1] != v[k] )
	{
		int i, x;
		for ( x = k; x >= 0; x-- )
			if ( tip_nod[ v[x] ] <= 0 )
				break;
		for ( i = x + 1; i < k; i++ )
			if ( v[i] == v[k] || tip_nod[ v[i] ] == tip_nod[ v[k] ] )
				return 0;
		return 1;
	}

	return 0;
}

// Verifica daca sau efectuat toate comenzile
int solutie ( int k )
{
	for ( int i = 0; i < n; i++ )
		if ( tip_nod[i] < 0 )
			return 0;
	return 1;
}

// Scrie in fisier rezultatul obtinut
void tipar ( int v[100], int k, FILE* output, int** drum )
{
	int i, cost = 0;
	for ( i = 0; i < k; i++ )
	{
		cost += graf[ v[i] ][ v[ i + 1 ] ];
		fprintf ( output, "%d ", v[i] );
		noduri_intermediare ( output, drum, v[i], v[i + 1] );
	}
	fprintf( output, "%d\n%d\n", v[k], cost);
}

typedef struct node
{
	int nod;
	int type;
}node;

// Metoda backtracking
void backtracking ( node list[100], int nr, int k, int nod_curent, int cost )
{
	// Verific daca costul curent este mai mare decat cea mai buna solutie de pana acum
	// Daca este mai mare se renunta la aceasta varianta
	if ( cost > min )
		return;
	int i;
	// Se parcurge multimea nodurilor de interes
	for ( i = 0; i < nr; i++ )
	{
		// Verific daca nodul curent a fost parcurs si daca exista drum intre el
		// si intre nodul anterior
		if ( list[i].type != 0 && graf[ v[ k - 1 ] ][list[i].nod] != inf )
		{
			// Actualizez costul
			cost += graf[ v[k - 1] ][ list[i].nod ];
			// Daca costul depaseste minimul, se renunta la aceasta posibilitate
			if ( cost > min )
			{
				cost -= graf[ v[k - 1] ][ list[i].nod ];
				continue;
			}
			// Daca nodul curent este un client
			if ( list[i].type < 0 && tip_nod[nod_curent] == -list[i].type )
			{
				// Se adauga in vector
				v[k] = list[i].nod;
				int aux = list[i].type;
				// Se marcheaza comanda ca fiind finalizata
				list[i].type = 0;
				tip_nod[list[i].nod] = 0;
				if ( valid ( k ) )
				{
					if ( solutie ( k ) )
					{
						// Aflu care ferma este cea mai aproape
						int min2 = inf, nod_terminal;
						for ( int j = 0; j < nr; j++ )
							if ( list[j].type > 0 )
								if ( min2 > graf[list[i].nod][list[j].nod] )
								{
									min2 = graf[list[i].nod][list[j].nod];
									nod_terminal = list[j].nod;
								}
						// Adaug aceasta distanta la cost
						cost += min2;
						// Daca costul este mai mic decat minimul curent, se actulizeaza minimimul
						// si se salveaza solutia
						if ( cost < min )
						{
							min = cost;
							k++;
							v[k] = nod_terminal;
							dim = k;
							for ( int q = 0; q <= dim; q++ )
								w[q] = v[q];
							k--;
						}
						cost -= min2;

					}
					else
						// Se apeleaza functia in mod recursiv pentru a trece la pasul urmator
						backtracking ( list, nr, k + 1, list[i].nod, cost );
				}
				tip_nod[list[i].nod] = aux;
				list[i].type = aux;
			}
			// Daca nodul curent este o ferma
			if ( list[i].type > 0 && list[i].type != tip_nod[nod_curent] )
			{
				// Aceleasi operatii ca si in cazul in care nodul este un client
				// doar ca ferma nu se marcheaza cu 0
				v[k] = list[i].nod;
				if ( valid ( k ) )
				{
					if ( solutie ( k ) )
					{
						int min2 = inf, nod_terminal;
						for ( int j = 0; j < nr; j++ )
							if ( list[j].type > 0 )
								if ( min2 > graf[list[i].nod][list[j].nod] )
								{
									min2 = graf[list[i].nod][list[j].nod];
									nod_terminal = list[j].nod;
								}
						cost += min2;
						if ( cost < min )
						{
							min = cost;
							k++;
							v[k] = nod_terminal;
							dim = k;
							for ( int q = 0; q <= dim; q++ )
								w[q] = v[q];
							k--;
						}
						cost -= min2;
					}
					else
						backtracking ( list, nr, k + 1, list[i].nod, cost );
				}
			}
			cost -= graf[ v[k - 1] ][ list[i].nod ];
		}
	}
}

void task3 ( FILE* input, FILE* output )
{
	fscanf ( input, "%d\n", &n );
	int i, j;
	// Citesc tipul puctelor de interes
	char buffer[100];
	fgets ( buffer, 100, input );
	tip_nod = ( int* ) malloc ( n * sizeof ( int ) );
	int k = 0;
	for ( i = 0; i < strlen ( buffer ); i += 2 )
	{
		tip_nod[k] = buffer[i] - 48;
		k++;
	}

	// Matricea asociata grafului ( graf[i][j] = distanta dintre i si j )
	graf = ( int** ) malloc ( n * sizeof ( int* ) );
	for ( i = 0; i < n; i++ )
		graf[i] = ( int* ) malloc ( n * sizeof ( int ) );
	// Initializez fiecare distanta cu inf
	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
			graf[i][j] = inf;
	// Citesc numarul de culuare aeriene
	int nr_culoare;
	fscanf ( input, "%d\n", &nr_culoare );
	// Citesc disatantele intre punctele de interes
	for ( i = 0; i < nr_culoare; i++ )
	{
		int x, y, cost;
		fscanf ( input, "%d %d %d\n", &x, &y, &cost );
		graf[x][y] = cost;
	}
	// Numarul de comenzi
	int nr_comenzi;
	fscanf ( input, "%d\n", &nr_comenzi );
	
	// Citesc fiecare comanda
	for ( i = 0; i < nr_comenzi; i++ )
	{
		int tip_ferma, client;
		fscanf ( input, "%d %d\n", &tip_ferma, &client );
		tip_nod[client] = -tip_ferma;
	}

	node list[100];
	int nr = 0;
	for ( i = 0; i < k; i++ )
		if ( tip_nod[i] != 0 )
		{
			list[nr].nod = i;
			list[nr].type = tip_nod[i];
			nr++;
		}

	// Ferma de start
	int start;
	fscanf ( input, "%d", &start );

	// Matricea drumurilor minime
	int** drum = Floyd ( graf, n );
	int cost = 0;
	v[0] = start;
	backtracking ( list, nr, 1, start, cost );
	tipar ( w, dim, output, drum );

	// Eliberarea memoriei
	for ( i = 0; i < n; i++ )
	{
		free ( drum[i] );
		free ( graf[i] );
	}
	free ( graf );
	free ( drum );

	
	free ( tip_nod );
}

int main ( int argc, char** argv )
{
	FILE *input, *output;

	input = fopen ( argv[1], "r" );
	if ( !input )
		return 1;
	output = fopen ( argv[2], "w" );

	int task;
	fscanf ( input, "%d\n", &task );

	switch ( task )
	{
		case 1:
			task1 ( input, output );
			break;
		case 2:
			task2 ( input, output );
			break;
		case 3:
			task3 ( input, output );
			break;
	}

	fclose ( input );
	fclose ( output );

	return 0;
}