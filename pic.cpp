#include <fstream>
#include <algorithm>
#define MAX_CIFRE 30
#define MAX_BUTOAIE 40
using namespace std;
ifstream fin("pic.in");
ofstream fout("pic.out");
struct NrMare { int nrCifre, cifre[MAX_CIFRE]; };
void citesteNrMare(NrMare&);
void initializeazaNrMareCuZero(NrMare&);
void adunaNrMari(NrMare, NrMare, NrMare&);
void scadeNrMari(NrMare, NrMare, NrMare&);
int comparaNrMari(NrMare, NrMare);
bool comparaButoaie(NrMare, NrMare);
int main()
{
	int i, nrVase, nrButoaie, nrMaxim;
	NrMare vas, picaturi, butoaie[MAX_BUTOAIE];
	initializeazaNrMareCuZero(picaturi);
	fin >> nrVase;
	for (i = 0; i < nrVase; i++)
	{
		citesteNrMare(vas);
		adunaNrMari(picaturi, vas, picaturi);
	}
	fin >> nrButoaie;
	for (i = 0; i < nrButoaie; i++)
		citesteNrMare(butoaie[i]);
	fin.close();
	sort(butoaie, butoaie + nrButoaie, comparaButoaie);
	for (nrMaxim = i = 0; i < nrButoaie; i++)
		if (comparaNrMari(picaturi, butoaie[i]) >= 0)
		{
			nrMaxim++;
			scadeNrMari(picaturi, butoaie[i], picaturi);
		}
		else
			break;
	fout << nrMaxim;
	fout.close();
	return 0;
}
void scadeNrMari(NrMare a, NrMare b, NrMare& d)
{
	int i, t, val;
	d.nrCifre = a.nrCifre > b.nrCifre ? a.nrCifre : b.nrCifre;
	if (a.nrCifre < b.nrCifre)
		for (i = a.nrCifre; i < b.nrCifre; i++)
			a.cifre[i] = 0;
	else if (b.nrCifre < a.nrCifre)
		for (i = b.nrCifre; i < a.nrCifre; i++)
			b.cifre[i] = 0;
	for (t = i = 0; i < d.nrCifre; i++)
	{
		val = a.cifre[i]-b.cifre[i]-t;
		if (val < 0)
			val += 10, t = 1;
		else
			t = 0;
		d.cifre[i] = val;
	}
	for (i = d.nrCifre-1; i > 0 && d.cifre[i] == 0; i--);
	d.nrCifre = i+1;
}

void initializeazaNrMareCuZero(NrMare& a)
{
	a.nrCifre = 1;
	a.cifre[0] = 0;
}
int comparaNrMari(NrMare a, NrMare b)
{
	int i;
	if (a.nrCifre < b.nrCifre)
		return -1;
	if (a.nrCifre > b.nrCifre)
		return 1;
	for (i = a.nrCifre-1; i >= 0 && a.cifre[i] == b.cifre[i]; i--);
	if (i < 0)
		return 0;
	if (a.cifre[i] < b.cifre[i])
		return -1;
	return 1;
}
bool comparaButoaie(NrMare a, NrMare b)
{
	if (comparaNrMari(a, b) < 0)
		return 1;
	return 0;
}
void adunaNrMari(NrMare a, NrMare b, NrMare& s)
{
	int i, t, val;
	s.nrCifre = a.nrCifre > b.nrCifre ? a.nrCifre : b.nrCifre;
	if (a.nrCifre < b.nrCifre)
		for (i = a.nrCifre; i < b.nrCifre; i++)
			a.cifre[i] = 0;
	else if (b.nrCifre < a.nrCifre)
		for (i = b.nrCifre; i < a.nrCifre; i++)
			b.cifre[i] = 0;
	for (t = i = 0; i < s.nrCifre; i++)
	{
		val = a.cifre[i]+b.cifre[i]+t;
		s.cifre[i] = val%10;
		t = val/10;
	}
	if (t)
		s.cifre[s.nrCifre++] = t;
}
void citesteNrMare(NrMare& a)
{
	fin >> a.nrCifre;
	for (int i = 0; i < a.nrCifre; i++)
		fin >> a.cifre[a.nrCifre-i-1];
}
