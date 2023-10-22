#include <fstream>
#include <cstring>
#include <algorithm>
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
bool compar(NrMare, NrMare);
int comparaNrMari(NrMare, NrMare);
void initializeazaNrMare(NrMare &, int=MAXCIF);
NrMare sumaNrMari(NrMare, NrMare);
NrMare diferentaNrMari(NrMare, NrMare);
// functia principala
int main()
{
	int n, k, i;
	NrMare x[MAX_N], v[MAX_K], s;
	citesteDateIntrare(n, k, x, v);
	initializeazaNrMare(s, MAXCIF+2);
	for (i = 0; i < n; i++)
	{
		s = sumaNrMari(x[i], s); // s += x[i]
	}
	sort(v, v+k, compar);
	for (i = 0; i < k && comparaNrMari(s, v[i]) >= 0; i++)
	{
		s = diferentaNrMari(s, v[i]); // s -= v[i]
	}
	fout << i;
	return 0;
}
NrMare diferentaNrMari(NrMare a, NrMare b)
{
	// d = a - b
	int i, t, val;
	NrMare d;
	for (i = b.nrcif; i < a.nrcif; i++)
	{
		b.cif[i] = 0;
	}
	for (t = i = 0; i < a.nrcif; i++)
	{
		val = a.cif[i]-b.cif[i]+t;
		if (val < 0)
		{
			d.cif[i] = val+10;
			t = -1;
		}
		else
		{
			d.cif[i] = val;
			t = 0;
		}
	}
	// ignor zerourile nesemnificative si actualizez nr. de cifre al lui d
	for (d.nrcif = a.nrcif; d.nrcif > 1 && d.cif[d.nrcif-1] == 0; d.nrcif--);
	return d;
}
NrMare sumaNrMari(NrMare a, NrMare b)
{
	// s = a + b 
	int i, t, val;
	NrMare s;
	// completeaza numarul cel mai mic cu zerouri nesemnificative
	if (a.nrcif < b.nrcif)
	{
		for (i = a.nrcif; i < b.nrcif; i++)
		{
			a.cif[i] = 0;
		}
		s.nrcif = b.nrcif;
	}
	else
	{
		for (i = b.nrcif; i < a.nrcif; i++)
		{
			b.cif[i] = 0;
		}
		s.nrcif = a.nrcif;
	}
	// aduna cele doua numere si retine rezultatul in s
	for (t = i = 0; i < s.nrcif; i++)
	{
		val = a.cif[i]+b.cif[i]+t;
		s.cif[i] = val%10;
		t = val/10;
	}
	if (t)
	{
		s.cif[s.nrcif++] = t;
	}
	return s;
}
void initializeazaNrMare(NrMare & a, int NRMAXCIF)
{
	a.nrcif = 1;
	for (int i = 0; i < NRMAXCIF; i++)
	{
		a.cif[i] = 0;
	}
}
int comparaNrMari(NrMare a, NrMare b)
{
	if (a.nrcif < b.nrcif)
	{
		return -1;
	}
	if (a.nrcif > b.nrcif)
	{
		return 1;
	}
	int i;
	for (i = a.nrcif-1; i >= 0 && a.cif[i] == b.cif[i]; i--);
	if (i < 0)
	{
		return 0;
	}
	if (a.cif[i] < b.cif[i])
	{
		return -1;
	}
	return 1;
}
bool compar(NrMare a, NrMare b)
{
	return comparaNrMari(a, b) < 0;
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
// scor 90
