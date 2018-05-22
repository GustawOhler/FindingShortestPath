#include <iostream>
#include <limits>
#include <stdio.h>

using namespace std;

class Wierzcholek {
public:
	Wierzcholek **tablica;
	int *odleglosc;
	int ilmoz;
	int najkrotsza;
	//Wierzcholek *powrotny;
	int powrotny;
	bool przerobiony;
	Wierzcholek() {
		this->ilmoz = 0;
		this->najkrotsza = numeric_limits<int>::max();
		this->powrotny = -1;
		przerobiony = false;
	}
	void dodaj(Wierzcholek *nastepny, int droga) {
		if (ilmoz == 0) {
			odleglosc = new int[1];
			odleglosc[0] = droga;
			tablica = new Wierzcholek*[1];
			tablica[0] = nastepny;
			ilmoz++;
		}
		else {
			Wierzcholek **nowatablica = new Wierzcholek*[ilmoz + 1];
			int *noweodleglosci = new int[ilmoz + 1];
			for (int i = 0; i < ilmoz; i++) {
				nowatablica[i] = tablica[i];
				noweodleglosci[i] = odleglosc[i];
			}
			nowatablica[ilmoz] = nastepny;
			noweodleglosci[ilmoz] = droga;
			delete[] tablica;
			delete[] odleglosc;
			tablica = nowatablica;
			odleglosc = noweodleglosci;
			ilmoz++;
		}
	}
};

void znajdzdroge(Wierzcholek *wierzcholki, int lskrzyz) {
	wierzcholki[0].najkrotsza = 0;
	for (int i = 0; i < lskrzyz-1; i++) {
		int min = numeric_limits<int>::max();
		Wierzcholek* wybrany = NULL;
		for (int j = 0; j < lskrzyz-1; j++) {
			if (wierzcholki[j].przerobiony == false) {
				if (wierzcholki[j].najkrotsza < min) {
					min = wierzcholki[j].najkrotsza;
					wybrany = &wierzcholki[j];
				}
			}
		}
		if (wybrany == NULL) break;
		for (int j = 0; j < wybrany->ilmoz; j++) {
			if (wybrany->tablica[j]->najkrotsza > wybrany->najkrotsza + wybrany->odleglosc[j]) {
				wybrany->tablica[j]->najkrotsza = wybrany->najkrotsza + wybrany->odleglosc[j];
				for (int k = 0; k < wybrany->tablica[j]->ilmoz; k++) {
					if (wybrany->odleglosc[j] == wybrany->tablica[j]->odleglosc[k] && wybrany->tablica[j]->tablica[k] == wybrany) {
						wybrany->tablica[j]->powrotny = k;
						break;
					}
				}
				//wybrany->tablica[j]->powrotny = wybrany;
			}
		}
		wybrany->przerobiony = true;
	}
	Wierzcholek *tyl = &wierzcholki[lskrzyz-1];
	Wierzcholek *nastepny = NULL;
	int min2 = numeric_limits<int>::max();
	/*while (tyl != &wierzcholki[0]) {
		for (int i = 0; i < tyl->ilmoz; i++) {
			if (tyl->tablica[i] != nastepny && tyl->tablica[i] != tyl->powrotny && tyl->tablica[i]->powrotny != tyl) {
				if (tyl->tablica[i]->najkrotsza + tyl->odleglosc[i] + (wierzcholki[lskrzyz - 1].najkrotsza - tyl->najkrotsza) < min2) {
					min2 = tyl->tablica[i]->najkrotsza + tyl->odleglosc[i] + (wierzcholki[lskrzyz - 1].najkrotsza - tyl->najkrotsza);
				}
			}
		}
		nastepny = tyl;
		tyl = tyl->powrotny;
	}*/
	while (tyl != &wierzcholki[0]) {
		for (int i = 0; i < tyl->ilmoz; i++) {
			if (tyl->tablica[i] != nastepny && i != tyl->powrotny && tyl->tablica[i]->tablica[tyl->tablica[i]->powrotny] != tyl) {
				if (tyl->tablica[i]->najkrotsza + tyl->odleglosc[i] + (wierzcholki[lskrzyz - 1].najkrotsza - tyl->najkrotsza) < min2) {
					min2 = tyl->tablica[i]->najkrotsza + tyl->odleglosc[i] + (wierzcholki[lskrzyz - 1].najkrotsza - tyl->najkrotsza);
				}
			}
		}
		nastepny = tyl;
		tyl = tyl->tablica[tyl->powrotny];
	}
	if (min2 < numeric_limits<int>::max() && wierzcholki[lskrzyz - 1].najkrotsza < numeric_limits<int>::max())
		printf("%d %d", wierzcholki[lskrzyz - 1].najkrotsza, min2);
	else
		printf("#");
}

int main()
{
	int lskrzyz, ldrog;
	scanf_s("%d", &lskrzyz);
	scanf_s("%d", &ldrog);
	Wierzcholek *tablica = new Wierzcholek[lskrzyz];
	for (int i = 0; i < ldrog; i++) {
		int wierz1, wierz2, odl;
		scanf_s("%d", &wierz1);
		scanf_s("%d", &wierz2);
		scanf_s("%d", &odl);
		tablica[wierz1].dodaj(&tablica[wierz2], odl);
		tablica[wierz2].dodaj(&tablica[wierz1], odl);
	}
	znajdzdroge(tablica, lskrzyz);
    return 0;
}