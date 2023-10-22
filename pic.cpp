#include <fstream>
#include <cstring>
#define MAX_N 70
#define MAX_K 40
#define MAXCIF_X 22
#define MAXCIF_V 22
#define LGMAX_X MAXCIF_X*2+1
#define LGMAX_V MAXCIF_V*2+1
using namespace std;
// fisiere citire/scriere
ifstream fin("pic.in");
ofstream fout("pic.out");
// constante globale
const int LGMAX = LGMAX_X > LGMAX_V ? LGMAX_X : LGMAX_V;
const int MAXCIF = MAXCIF_X > MAXCIF_V ? MAXCIF_X : MAXCIF_V;
// structuri abstracte
struct NrMare
{
	char cif[MAXCIF];
	int nrcif;
};
// functii ajutatoare
void eliminaToateAparitiileCaracteruluiDinSir(char, char*, int=LGMAX);
void creeazaNrMareDinSir(NrMare &, char*);
void afiseazaNrMare(NrMare);
void citesteDateIntrare(int &, int &, NrMare*, NrMare*);
void citesteNrMari(int, NrMare*);
// functia principala
int main()
{
	int n, k, i;
	NrMare x[MAX_N], v[MAX_K];
	citesteDateIntrare(n, k, x, v);
	for (i = 0; i < n; i++)
	{
		afiseazaNrMare(x[i]);
	}
	for (i = 0; i < k; i++)
	{
		afiseazaNrMare(v[i]);
	}
	return 0;
}
void citesteNrMari(int n, NrMare* x)
{
	char s[LGMAX];
	for (int i = 0; i < n; i++)
	{
		fin.getline(s, LGMAX);
		eliminaToateAparitiileCaracteruluiDinSir(' ', s);
		NrMare nr;
		creeazaNrMareDinSir(nr, s);
		x[i] = nr;
	}
}
void citesteDateIntrare(int & n, int & k, NrMare* x, NrMare* v)
{	
	fin >> n;
	fin.get();
	citesteNrMari(n, x);
	fin >> k;
	fin.get();
	citesteNrMari(k, v);
	fin.close();
}
void eliminaToateAparitiileCaracteruluiDinSir(char c, char* s, int LGMAX_SIR)
{
	char *p, q[LGMAX_SIR];
	while(p = strchr(s, c))
	{
		strcpy(q, p+1);
		*p = 0;
		strcat(s, q);
	}
}
void creeazaNrMareDinSir(NrMare & nr, char* s)
{
	int lg, i;
	lg = strlen(s);
	for (i = lg-1; i >= 0; i--)
	{
		nr.cif[lg-i-1] = s[i]-'0';
	}
	for (i = lg; i < MAXCIF; i++)
	{
		nr.cif[i] = 0;
	}
	nr.nrcif = lg;
}
void afiseazaNrMare(NrMare nr)
{
	for (int i = nr.nrcif-1; i >= 0; i--)
	{
		fout << (int)nr.cif[i];
	}
	fout << '\n';
}
