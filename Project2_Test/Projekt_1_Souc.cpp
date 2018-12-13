	#define _CRT_SECURE_NO_DEPRECATE
	#define _CRT_SECURE_NO_WARNINGS
	#define _CRT_NONSTDC_NO_DEPRECATE
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	struct osoba
	{
		char meno[50];
		char pohlavie;
		int rok_narodenia;
		char spz[7];
		int typ_priestupku;
		int vyska_pokuty;
		int datum_priestupku;
	};

	int zisti_pocet(const char *meno_suboru) {
		int pocet_riadkov, pocet_prvkov = 0;
		FILE *subor;
		subor = fopen(meno_suboru, "r");
		if (subor) {
			while ((pocet_riadkov = getc(subor)) != EOF) {
				if (pocet_riadkov == '\n')
					pocet_prvkov++;
			}
		}
		pocet_prvkov /= 7;
		fclose(subor);
		return pocet_prvkov;
	}

	int je_palindrom(char* vstup_spz) {
		char porovnavaci[8];
		strcpy(porovnavaci, vstup_spz);
		strrev(porovnavaci);
		if (strcmp(vstup_spz, porovnavaci) == 0) 
			return 1;
		return 0;
	}

	void vypis_palindrom_spz(int kolko, osoba *ktore_pole) {
		for (int i = 1; i <= kolko; i++) {
			if (je_palindrom(ktore_pole->spz)==1)
				printf("%s%s\n", ktore_pole->meno, ktore_pole->spz);
			ktore_pole++;
		}
	}


	void aktualne_pokuty(int kolko, osoba *ktore_pole) {
		int datum;
		scanf("%d", &datum);
		for (int i = 1; i <= kolko; i++) {
			if (datum / 10000 == ktore_pole->datum_priestupku / 10000)
				printf("\nMeno priezvisko: %sSPZ: %s\nDatum priestupku: %d\n", ktore_pole->meno, ktore_pole->spz, ktore_pole->datum_priestupku);
			ktore_pole++;
		}
	}

	void mesacna_odmena(int pocet_prvkov, osoba *ktore_pole) {
		int datum;
		double pokuta = 0;
		scanf("%d", &datum);
		for (int i = 1; i <= pocet_prvkov; i++) {
			if (datum / 100 == ktore_pole->datum_priestupku / 100) {
				if (ktore_pole->typ_priestupku) {
					pokuta += ((ktore_pole->vyska_pokuty)*0.052);
				}
				else
					pokuta += ((ktore_pole->vyska_pokuty)*0.038);
			}
			ktore_pole++;
		}
		printf("Pokuta za aktualny mesiac: %.2lf\n", pokuta);
	}

	void vypis_pole(int pocet_prvkov, osoba *ktore_pole) {
		for (int i = 1; i <= pocet_prvkov; i++) {
			printf("\nMeno priezvisko: %sPohlavie: %c\nRok narodenia: %d\nSPZ: %s\nTyp priestupku: %d\nVyska pokuty: %d\nDatum priestupku: %d\n", ktore_pole->meno, ktore_pole->pohlavie, ktore_pole->rok_narodenia, ktore_pole->spz, ktore_pole->typ_priestupku, ktore_pole->vyska_pokuty, ktore_pole->datum_priestupku);
			ktore_pole++;
		}
	}

	void napln_osoby(osoba **r_osoby, const char *nazov_suboru, int*pocet_zaznamy) {

		FILE *subor;
		osoba *p_osoby, *osoby;
		osoby = (osoba*)calloc(zisti_pocet(nazov_suboru), sizeof(osoba));
		int poradie_polozka = 1;
		char *string, *temp_string, aktualny_znak;
		subor = fopen(nazov_suboru, "r");
		string = (char*)calloc(50, sizeof(char));
		temp_string = string;
		p_osoby = osoby;
		*pocet_zaznamy = 0;

		if (subor) {
			while ((aktualny_znak = getc(subor)) != EOF) {
				*temp_string = aktualny_znak;
				if (aktualny_znak == '\n') {
					//printf("%s %d\n", string, poradie_polozka);
					if (poradie_polozka == 1) { 
						memcpy((char*)p_osoby->meno, (const char*)string, 50);
						free(string);
					}
					if (poradie_polozka == 2) { 
						p_osoby->pohlavie = *string;
						free(string);
					}
					if (poradie_polozka == 3) { 
						p_osoby->rok_narodenia = atoi(string);
						free(string);
					}
					if (poradie_polozka == 4) { 
						memcpy((char*)p_osoby->spz, (const char*)string, 7);
						free(string);
					}
					if (poradie_polozka == 5) { 
						p_osoby->typ_priestupku = atoi(string);
						free(string);
					}
					if (poradie_polozka == 6) { 
						p_osoby->vyska_pokuty = atoi(string);
						free(string);
					}
					if (poradie_polozka == 7) { 
						p_osoby->datum_priestupku = atoi(string);
						(*pocet_zaznamy)++;
						free(string);
					}
					if (poradie_polozka < 8) { 
						string = (char*)calloc(50, sizeof(char));
						temp_string = string;
					}
					poradie_polozka++;
					if (poradie_polozka > 8) {
						poradie_polozka = 1;
						p_osoby++;
					}
				}
				else {
					temp_string++;
				}
			}
			fclose(subor);
		}
		*r_osoby = osoby;
	}

	int main() {
	
		osoba *osoby=NULL;
		int ktory_prikaz, pocet_zaznamy;

		while ((ktory_prikaz = getchar()) != 'k') {
			if (ktory_prikaz == 'o'){
				napln_osoby(&osoby, "priestupky.txt", &pocet_zaznamy);
			}
			else if (ktory_prikaz == 'v'){
				if(osoby != NULL)	
					vypis_pole(pocet_zaznamy, osoby);
			}
			else if (ktory_prikaz == 'x') {
				if (osoby != NULL)
					aktualne_pokuty(pocet_zaznamy, osoby);
			}
			else if (ktory_prikaz == 'r') {
				if (osoby != NULL)
					mesacna_odmena(pocet_zaznamy, osoby);
			}
			else if (ktory_prikaz == 'p') {
				if (osoby != NULL)
					vypis_palindrom_spz(pocet_zaznamy, osoby);
			}
		}	
		return 0;
		}