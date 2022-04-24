#include <iostream>
#include <fstream>
#include <stdio.h>
//CERINTA!
//Se dau n puncte in coordonate XoY. Sa se determine daca poligonul format din aceste puncte este convex
//REZOLVARE
//Daca punctele au acelasi sens (trigonometric sau invers trigonometric) poligonul este convex. Daca exita un punct care are sensul diferit fata de celalalte, poligonul este concav

using namespace std;

ifstream load("coordonate_puncte.txt");
int numar_puncte;

//structura in care sunt introduse coordonatele punctelor
struct points
{
	int x;
	int y;
};

points p;
points lista[10]; //initializam un vector de puncte cu capacitatea de 10 elemente

//pentru verificarea sensului punctelor se foloseste ecuatia dreptei prin determinant :
//Fie A,B,C 3 puncte, pe prima linie A.x  A.y  1, pe a doua B.x  B.y  1, iar pe ultima C.x  C.y  1;
// Daca determinantul > 0, punctele sunt invers trigonometiric, determinantul < 0 punctele sunt in sens trigonometric, iar daca determinantul == 0 sunt coliniare

//functia determinant returneaza 1 daca determinantul > 0, -1 daca deteminantul < 0 iar  0 pentru determinant = 0 
int determinant(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int determinant;
	determinant = x1 * y2 + x2 * y3 + x3 * y1 - x3 * y2 - x1 * y3 - x2 * y1;
	if (determinant < 0)
		return -1;
	if (determinant > 0)
		return 1;
	return 0;
}

int main()
{
	int i;
	load >> numar_puncte;
	if (numar_puncte == 0) // daca nu se introduc puncte nu se poate forma un poligon
		cout << "Nu se poate forma un poligon! Nu exista puncte";
	if (numar_puncte < 4 && numar_puncte != 0) // pentru mai putin de 4 puncte , poligonul format nu poate sa fie decat convex
		cout << "Poligonul este convex";
	if (numar_puncte >= 4)
	{
		for (i = 0; i < numar_puncte; i++) // se citesc din fisier coordonatele punctelor si se adauga punctul in vector
		{
			load >> p.x;
			load >> p.y;
			lista[i] = p;
		}

		int a = 0, b = 0, c = 0; //indicii celor 3 puncte care vor fii verificate
		bool valid = true; //folosim valid pentru a marca prima trecere prin for, trecerea care seteaza sensul punctelor 
		bool convex = true; 
		int unghi = 0; //variabila unghi memoreaza sensul punctelor 

		//cele trei puncte trebuie sa fie consecutive astfel, a = 0, b = 1, c = 2 etc..
		for (a = 0; a < numar_puncte && convex == true; a++)
		{
			b = a + 1;
			if (b > numar_puncte - 1) // pentru a se verifica toate perechile de 3 puncte, cand a ajunge la finalul vectorului, b devine indicele primului element
			{
				b = b % numar_puncte;
			}
			c = a + 2;
			if (c > numar_puncte - 1)// pentru a se verifica toate perechile de 3 puncte, cand a ajunge la finalul vectorului, c devine indicele celui de al doilea element
			{
				c = c % numar_puncte;
			}
			//intrarea in acest if se va intampla o singura data pentru a seta sensul punctelor 

			//la prima trecere, daca determinantul este diferit de 0 ( daca deteinantul = 0 punctele sunt coliniare deci nu se poate afla sensul punctelor) variabila unghi salveaza sensul punctelor iar valid == false
			if (valid == true && determinant(lista[a].x, lista[a].y, lista[b].x, lista[b].y, lista[c].x, lista[c].y) != 0)
			{
				unghi = determinant(lista[a].x, lista[a].y, lista[b].x, lista[b].y, lista[c].x, lista[c].y);
				valid = false;
			}
			//aici se verifica daca restul perechilor de 3 puncte au acelasi sens

			//daca deteminantul este diferit de 0 si diferit de valoarea lui unghi, atunci poligonul nu mai este convex ==> se iese din for
			if (valid == false)
			{
				if (determinant(lista[a].x, lista[a].y, lista[b].x, lista[b].y, lista[c].x, lista[c].y) != 0 && determinant(lista[a].x, lista[a].y, lista[b].x, lista[b].y, lista[c].x, lista[c].y) != unghi)
					convex = false;
			}
		}
		if (convex == true)
			cout << "Punctele formeaza un poligon convex!";
		else
			cout << "Punctele nu formeaza un poligon convex!";
	}
	return 0;
}