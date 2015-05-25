#include<iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<conio.h>

//FAV
/*
-lista dublu inlantuita circulara
-flaero.txt
-identificator unic: idAeronava
*/

//-----STRUCTURA AERONAVA--------------------------------------------------------------------------

enum TipAeronava { PAS, CAR };

struct Aeronava {
	char* idAeronava;
	TipAeronava tipAero;
	short int nrLocuri;
	double greutateMaxima;
};

void afisareAeronava(Aeronava aero) {
	printf("IdAeronava: %s\n",aero.idAeronava);
	if(aero.tipAero == TipAeronava::PAS) {
		printf("TipAeronava: Pasageri\n");
	} else {
		printf("TipAeronava: Cargo\n");
	}
	printf("NrLocuriAeronava: %d\n",aero.nrLocuri);
	printf("GreutateMaximaAeronava: %5.2lf\n",aero.greutateMaxima);
}

Aeronava creareAeronava(char* idAeronava, char* tipAero, char* nrLocuri, char* greutateMaxima) {
	Aeronava aero;
	aero.idAeronava = new char[strlen(idAeronava)+1];
	strcpy(aero.idAeronava,idAeronava);
	if(strcmp(tipAero,"pas")) {
		aero.tipAero = TipAeronava::PAS;
	} else if(strcmp(tipAero,"car")) {
		aero.tipAero = TipAeronava::CAR;
	}
	aero.nrLocuri = atoi(nrLocuri);
	aero.greutateMaxima = atof(greutateMaxima);
	return aero;
}

//-----END STRUCTURA AERONAVA-----------------------------------------------------------------------



//-----STRUCTURA LISTA DUBLU INLANTUITA CIRCULARA---------------------------------------------------

struct NodAeronava {
	Aeronava aero;
	NodAeronava *next, *back;
};

void afisareAeronavePrimUltim(NodAeronava *prim, NodAeronava *ultim) {
	printf("\n-----AFISARE AERONAVE-----\n");
	while(prim != NULL) {
		afisareAeronava(prim->aero);
		printf("\n");
		if(prim == ultim) {
			prim = NULL;
		} else {
			prim = prim->next;
		}
	}
}

void afisareAeronaveUltimPrim(NodAeronava *prim, NodAeronava *ultim) {
	while(ultim != NULL) {
		afisareAeronava(ultim->aero);
		if(prim == ultim) {
			ultim = NULL;
		} else {
			ultim = ultim->back;
		}
	}
}

void inserareAeronavaInceput(NodAeronava* &prim, NodAeronava* &ultim, Aeronava aero) {
	NodAeronava *nou = new NodAeronava;
	nou->aero = aero;
	if(prim == NULL) {
		prim = ultim = nou;
		nou->next = ultim;
		nou->back = prim;
	} else if(prim == ultim) {
		nou->next = ultim;
		nou->back = ultim;
		prim = nou;
		ultim->next = nou;
		ultim->back  = nou;
	} else {
		nou->next = prim;
		prim->back = nou;
		nou->back = ultim;
		ultim->next = nou;
		prim = nou;
	}
}

void inserareAeronavaSfarsit(NodAeronava* &prim, NodAeronava* &ultim, Aeronava aero) {
	NodAeronava *nou = new NodAeronava;
	nou->aero = aero;
	if(prim == NULL) {
		prim = ultim = nou;
		nou->next = nou;
		nou->back = nou;
	} else if(prim == ultim) {
		nou->next = prim;
		nou->back = prim;
		prim->next = nou;
		prim->back = nou;
		ultim = nou;
	} else {
		nou->back = ultim;
		ultim->next = nou;
		nou->next = ultim;
		ultim = nou;
		prim->back = ultim;
	}
}

void inserareAeronavaInainteDeNod(NodAeronava* &prim, NodAeronava* &ultim, Aeronava aero, NodAeronava* poz) {
	NodAeronava *nou = new NodAeronava;
	nou->aero = aero;
	if(prim == NULL) {
		prim = ultim = nou;
		nou->next = nou;
		nou->back = nou;
	}
	else if(prim == poz) {
		nou->next = prim;
		nou->back = ultim;
		prim->back = nou;		
		prim = nou;
		prim->next = prim;
	}
	else {
		nou->next = poz;
		nou->back = poz->back;
		nou->back->next = nou;
		poz->back = nou;
	}
}

void inserareAeronavaDupaNod(NodAeronava* &prim, NodAeronava* &ultim, Aeronava aero, NodAeronava* poz) {
	NodAeronava *nou = new NodAeronava;
	nou->aero = aero;
	if(prim == NULL) {
		prim = ultim = nou;
		nou->next = nou;
		nou->back = nou;
	} else if(ultim == poz) {
		nou->back = ultim;
		ultim->next = nou;
		nou->next = prim;
		ultim = nou;
		prim->back = ultim;
	} else {
		nou->back = poz;
		nou->next = poz->next;
		poz->next = nou;
		nou->back->next = nou;
	}
}

NodAeronava* cautaNodAeronavaDupaId(NodAeronava *prim, NodAeronava *ultim, char *idAeronava) {
	while(prim != NULL) {

		if(strcmp(prim->aero.idAeronava,idAeronava) == 0) {
			return prim;
		}

		if(prim == ultim) {
			prim = NULL;
		} else {
			prim = prim->next;
		}
	}
	return NULL;
}

int getPozitieNodAeronava(NodAeronava *prim, NodAeronava *ultim, NodAeronava *nod) {
	int poz = 0;
	while(prim != NULL) {

		if(strcmp(nod->aero.idAeronava, nod->aero.idAeronava) == 0) {
			return poz;
		}

		if(prim == ultim) {
			prim = NULL;
		} else {
			prim = prim->next;
			poz++;
		}
	}
	return -1;
}

NodAeronava *cautaNodAeronavaDupaPozitie(NodAeronava *prim, NodAeronava *ultim, int poz) {
	int i = 0;
	while(prim != NULL && i < poz) {
		prim = (prim->next == ultim->next ? NULL : prim->next);
		i++;
	}

	if(i == poz) {
		return prim;
	} else {
		return NULL;
	}
}

void modificaNodAeronavaDupaId(NodAeronava *&prim, NodAeronava *&ultim, char* idAeronava, char* tipAero, char* nrLocuri, char* greutateMaxima) {
	while(prim != NULL) {

		if(strcmp(prim->aero.idAeronava,idAeronava) == 0) {
			prim->aero = creareAeronava(idAeronava, tipAero, nrLocuri, greutateMaxima);
			return;
		}

		if(prim == ultim) {
			prim = NULL;
		} else {
			prim = prim->next;
		}
	}
}

void stergeNodAeronavaDupaId(NodAeronava *&prim, NodAeronava *&ultim, char *idAeronava) {

	if(prim == NULL) {
		return;
	} else {
		int poz = getPozitieNodAeronava(prim, ultim, prim);
		if(poz == 0 && strcmp(prim->aero.idAeronava, idAeronava) == 0) {
			NodAeronava* nodDeSters1 = prim;
			prim = prim->next;
			prim->back = ultim;
			delete nodDeSters1;
		} else {		
			NodAeronava* nodCautat = cautaNodAeronavaDupaId(prim, ultim, idAeronava);
			if(nodCautat == ultim && strcmp(nodCautat->aero.idAeronava, idAeronava) == 0) {			 
				NodAeronava *nodDeSters2 = ultim;
				ultim = ultim->back;
				ultim->next = prim;
				prim->back = ultim;
				delete nodDeSters2;
			} else {
				if(nodCautat != NULL && strcmp(nodCautat->aero.idAeronava, idAeronava) == 0) {
					nodCautat->next->back = nodCautat->back;
					nodCautat->back->next = nodCautat->next;
					delete nodCautat; 
				}
			}
		}
	}
}

//-----END STRUCTURA LISTA DUBLU INLANTUITA CIRCULARA-----------------------------------------------



//RUZ
/*
-program.txt
-tabela de dispersie
-id alfanumeric zbor
-maxim 20 zboruti saptamanal

*/

//-----STRUCTURA ZBOR-------------------------------------------------------------------------------

struct Zbor {
	char* idZbor;
	char* idAeronava;
	double costuriTotaleRuta;
};

Zbor creareZbor(char* idZbor, char* idAeronava, char* costuri) {
	Zbor zbor;
	zbor.idZbor = new char[strlen(idZbor)+1];
	strcpy(zbor.idZbor, idZbor);
	zbor.idAeronava = new char[strlen(idAeronava)+1];
	strcpy(zbor.idAeronava, idAeronava);
	zbor.costuriTotaleRuta = atof(costuri);
	return zbor;
}

void afisareZbor(Zbor zbor) {
	printf("IdZbor: %s\n", zbor.idZbor);
	printf("IdAeronava: %s\n", zbor.idAeronava);
	printf("CoturiTotaleRuta: %5.2f\n",zbor.costuriTotaleRuta);
}

//-----END STRUCTURA ZBOR---------------------------------------------------------------------------


//-----STRUCTURA LISTA SIMPLU INLANTUITA------------------------------------------------------------

struct NodZbor {
	Zbor zbor;
	NodZbor *next;
};

void inserareZborInceput(NodZbor* &capat, Zbor zbor) {
	NodZbor *nou = new NodZbor;
	nou->zbor = zbor;
	nou->next = NULL;
	if(capat == NULL) {
		capat = nou;
	} else{
		nou->next = capat;
		capat = nou;
	}
}

void afisareListaZboruri(NodZbor* capat) {
	if(capat != NULL) {
		NodZbor* temp = capat;
		while(temp != NULL) {
			afisareZbor(temp->zbor);
			printf("\n");
			temp = temp->next;
		}
	}
}

int getNrNoduriNodZbor(NodZbor* capat) {
	int poz = 0;
	if(capat != NULL) {
		NodZbor* temp = capat;
		while(temp != NULL) {
			temp = temp->next;
			poz++;
		}
	}
	return poz;
}

int getPozitieNodZbor(NodZbor* capat, NodZbor *nod) {
	int poz = 0;
	if(capat != NULL) {
		NodZbor* temp = capat;
		while(temp != NULL) {

			if(strcmp(temp->zbor.idZbor,nod->zbor.idZbor) == 0) {
				return poz;
			}

			temp = temp->next;
			poz++;
		}
	}
	return 0;
}

//-----END STRUCTURA LISTA SIMPLU INLANTUITA--------------------------------------------------------



//-----STRUCTURA TABELA DE DISPERSIE CHAINING-------------------------------------------------------

struct TabelaDispersie {
	(NodZbor*) *zboruri;
	int dimTabela;
};

int functieHT(char idZbor[50], int dimTabela) {
	int suma = 0;
	for(int i=0; i<strlen(idZbor); i++) {
		suma += idZbor[i];
	}
	return suma % dimTabela;
}

TabelaDispersie initialiareTabelaDispersie(int dimTabela) {
	TabelaDispersie tabela;
	tabela.dimTabela = dimTabela;
	tabela.zboruri = new NodZbor*[dimTabela];
	for(int i=0; i<dimTabela; i++)
		tabela.zboruri[i] = NULL;
	return tabela;
}

TabelaDispersie inserareZborTabelaDispersie(TabelaDispersie &tabela, Zbor zbor) {
	int i = functieHT(zbor.idZbor, tabela.dimTabela);
	NodZbor *stiva = tabela.zboruri[i]; 
	inserareZborInceput(stiva,zbor);
	tabela.zboruri[i] = stiva;
	return tabela;
}

void afisareZboruriTabelaDispersie(TabelaDispersie tabela) {
	printf("\n-----AFISARE ZBORURI-----\n");
	for(int i=0; i < tabela.dimTabela; i++) {
		if(tabela.zboruri[i] != NULL) {
			afisareListaZboruri(tabela.zboruri[i]);
		}
	}
}

NodZbor* cautaNodZborDupaId(TabelaDispersie tabela, char idZbor[30]) {
	int i = functieHT(idZbor, tabela.dimTabela);
	NodZbor* temp = tabela.zboruri[i];
	if(temp != NULL) {
		while(temp != NULL){
			if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
				return temp;
			} else {
				temp = temp->next;
			}
		}
	}
	return NULL;
}

void modificaNodZborDupaId(TabelaDispersie &tabela, char* idZbor, char* idAeronava, char* cost) {
	int i = functieHT(idZbor, tabela.dimTabela);
	NodZbor* temp = tabela.zboruri[i];
	if(temp != NULL) {
		while(temp != NULL) {
			if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
				temp->zbor = creareZbor(idZbor, idAeronava, cost);
				return;
			} else {
				temp = temp->next;
			}
		}
	}
}

void stergeNodZborDupaId(TabelaDispersie &tabela, char *idZbor) {
	int i = functieHT(idZbor, tabela.dimTabela);
	NodZbor* temp = tabela.zboruri[i];
	if(temp != NULL) {
		if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
			NodZbor* nodDeSters1 = temp;
			temp = temp->next;
			tabela.zboruri[i] = temp;
			delete nodDeSters1;
			return;
		} 
		while(temp->next != NULL && strcmp(temp->next->zbor.idZbor,idZbor) != 0) {
			temp = temp->next; 
		}
		if(temp->next != NULL) {
			NodZbor* nodDeSters2 = temp->next;
			temp->next = temp->next->next;
			delete nodDeSters2; 
		} 

		/*while(temp != NULL) {
		int nrNoduri = getNrNoduriNodZbor(tabela.zboruri[i]);
		int poz = getPozitieNodZbor(tabela.zboruri[i], temp);

		if(poz == 0 && strcmp(temp->zbor.idZbor,idZbor) == 0) {

		NodZbor* nodDeSters2 = temp;
		temp = NULL;
		delete nodDeSters2;
		return; 

		} else if(poz == nrNoduri-1 && strcmp(temp->zbor.idZbor,idZbor) == 0) {

		NodZbor* nodDeSters = temp;
		temp = temp->next;
		delete nodDeSters;
		return; 

		} else if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
		NodZbor* nodDeSters2 = temp->next;
		nodDeSters2->next = nodDeSters2->next->next;
		delete nodDeSters2;
		return;
		}
		temp = temp->next;
		}*/
	}
}

void afisareNodZbor(NodZbor* nod) {
	if(nod == NULL) {
		printf("Nu exista zborul cu id-ul dat!\n");
	} else {
		afisareZbor(nod->zbor);
	}
}

//-----END STRUCTURA TABELA DE DISPERSIE CHAINING---------------------------------------------------



//REP
/*
-lista de liste
*/


//-----STRUCTURA PASAGER----------------------------------------------------------------------------

struct Pasager {
	char* idRezervare;
	char* idZbor;
	char* nume;
	char* prenume;
	double costBilet;
	bool isChecked;
};

void afisarePasager(Pasager pas) {
	printf("IdRezervare: %s\n",pas.idRezervare);
	printf("IdZbor: %s\n",pas.idZbor);
	printf("Nume: %s\n",pas.nume);
	printf("Prenume: %s\n",pas.prenume);
	printf("CostBilet: %5.2lf lei\n",pas.costBilet);
	if(pas.isChecked) {
		printf("Check: Da\n");
	} else {
		printf("Check: Nu\n");
	}
}

Pasager crearePasager(char* idRezervare, char* idZbor, char* nume, char* prenume, char* costBilet, char* isChecked) {
	Pasager pas;
	pas.idRezervare = new char[strlen(idRezervare)+1];
	strcpy(pas.idRezervare,idRezervare);
	pas.idZbor = new char[strlen(idZbor)+1];
	strcpy(pas.idZbor,idZbor);
	pas.nume = new char[strlen(nume)+1];
	strcpy(pas.nume,nume);
	pas.prenume = new char[strlen(prenume)+1];
	strcpy(pas.prenume,prenume);
	pas.costBilet = atof(costBilet);
	int valCheck = atoi(isChecked);
	if(valCheck == 1) {
		pas.isChecked = true;
	} else {
		pas.isChecked = false;
	}
	return pas;
}

struct NodPasager {
	Pasager pas;
	NodPasager *next;
};

void inserarePasagerSfarsit(NodPasager* &capat, Pasager pas) {
	NodPasager *nou = new NodPasager;
	nou->pas = pas;
	nou->next = NULL;
	if(capat == NULL) {
		capat = nou;
	} else{
		NodPasager *temp = capat;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

void afisareListaNodPasager(NodPasager *capat) {
	if(capat != NULL) {
		NodPasager* temp = capat;
		while(temp != NULL) {
			afisarePasager(temp->pas);
			temp = temp->next;
		}
	}
}

//-----END STRUCTURA PASAGER------------------------------------------------------------------------



//-----STRUCTURA LISTA DE LISTE---------------------------------------------------------------------

struct NodZborPasageri {
	Zbor zbor;
	NodPasager *listaPasageri;
	NodZborPasageri *next;
};

void inserareZborPasageriSfarsit(NodZborPasageri* &capat, Zbor zbor) {
	NodZborPasageri *nou = new NodZborPasageri;
	nou->zbor = zbor;
	nou->listaPasageri = NULL;
	nou->next = NULL;
	if(capat == NULL) {
		capat = nou;
	} else{
		NodZborPasageri *temp = capat;
		while(temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nou;
	}
}

NodZborPasageri* creareListaDeListe(TabelaDispersie tabela) {
	NodZborPasageri *capat = NULL;
	if(tabela.dimTabela > 0) {
		for(int i=0; i < tabela.dimTabela; i++) {
			if(tabela.zboruri[i] != NULL) {
				NodZbor *temp = tabela.zboruri[i];
				while(temp != NULL) {
					inserareZborPasageriSfarsit(capat,temp->zbor);
					temp=temp->next;		
				}
			}
		}
	}
	return capat;
}

void inserarePasagerListaDeListe(NodZborPasageri *&capat, Pasager pas) {
	if(capat != NULL) {//daca exista zboruri
		NodZborPasageri *temp = capat;
		while(temp != NULL) {//parcurgem lista
			if(strcmp(temp->zbor.idZbor, pas.idZbor) == 0) {//verificam daca corespund id-urile zborului
				inserarePasagerSfarsit(temp->listaPasageri, pas);//inseram pasagerul
				break; //iesim fortat dupa ce s-a inserat (nu mai are sens sa continuam)
			}
			temp = temp->next;//trecem la urmatorul nod de liste cu pasageri
		}
	}
}

NodPasager* cautaNodPasagerDupaId(NodZborPasageri *capat, char* idRezervare) {
	if(capat != NULL) {
		NodZborPasageri *temp = capat;
		while(temp != NULL) {
			NodPasager *temp2 = temp->listaPasageri;
			while (temp2 != NULL) {
				if(strcmp(temp2->pas.idRezervare, idRezervare) == 0) {
					return temp2;
				}
				temp2 = temp2->next;
			}
			temp = temp->next;
		}
	}
	return NULL;
}

void modificaNodPasagerDupaId(NodZborPasageri *&capat, char* idRezervare, char* idZbor, char* nume, char* prenume, char* costBilet, char* isChecked) {
	if(capat != NULL) {
		NodZborPasageri *temp = capat;
		while(temp != NULL) {

			if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
				NodPasager *temp2 = temp->listaPasageri;
				while (temp2 != NULL) {
					if(strcmp(temp2->pas.idRezervare, idRezervare) == 0) {
						temp2->pas = crearePasager(idRezervare, idZbor, nume, prenume, costBilet, isChecked);
					}
					temp2 = temp2->next;
				}
			}
			temp = temp->next;
		}
	}
}

void afisarePasageriListaDeListe(NodZborPasageri *capat) {
	if(capat != NULL) {
		printf("\n-----AFISARE PASAGERI-----\n");
		NodZborPasageri *temp = capat;
		while(temp != NULL) {
			afisareListaNodPasager(temp->listaPasageri);
			printf("\n");
			temp = temp->next;
		}
	}
}

void stergeNodPasagerDupaId(NodZborPasageri *&capat, char* idRezervare) {
	if(capat != NULL) {
		NodZborPasageri *temp = capat;
		while(temp != NULL) {
			NodPasager *temp2 = temp->listaPasageri;
			if(strcmp(temp2->pas.idRezervare,idRezervare) == 0) {
				NodPasager* nodDeSters1 = temp2;
				temp2 = temp2->next;
				temp->listaPasageri = temp2;
				delete nodDeSters1;
				return;
			}
			while(temp2->next != NULL && strcmp(temp2->next->pas.idRezervare,idRezervare) == 0) {
				temp2 = temp2->next;
			}
			if(temp2->next != NULL) {
				NodPasager* nodDeSters2 = temp2->next;
				temp2->next = temp2->next->next;
				delete nodDeSters2; 
			}
		}
	}
}

void checkInPasageri(NodZborPasageri *capat, char *idZbor) {
	int locuriDisp = 20;
	if(capat != NULL) {
		NodZborPasageri *temp = capat;
		bool isChechInAll = true;
		while(temp != NULL) {
			if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
				NodPasager* temp2 = temp->listaPasageri;
				while(temp2 != NULL) {
					locuriDisp--;
					if(!temp2->pas.isChecked) {
						isChechInAll = false;
					}
					temp2 = temp2->next;
				}
			}
			temp = temp->next;
		}
		if(isChechInAll) {
			printf("Toti pasagerii acestui zbor au dat check in\n");
		} else {
			printf("Exista inca persoane care nu si-au dat check in!\n");
		}
		printf("Numarul de locuri disponibile: %d\n",locuriDisp);
	}
}

void costsPasageri(NodZborPasageri *capat, char *idZbor) {
	int locuriDisp = 20;
	if(capat != NULL) {
		NodZborPasageri *temp = capat;
		double venitBilete = 0;
		while(temp != NULL) {
			if(strcmp(temp->zbor.idZbor,idZbor) == 0) {
				NodPasager* temp2 = temp->listaPasageri;
				while(temp2 != NULL) {
					venitBilete += temp2->pas.costBilet;
					temp2 = temp2->next;
				}
				if(venitBilete - temp->zbor.costuriTotaleRuta >= 0) {
					printf("Profit: %5.2f lei\n", venitBilete - temp->zbor.costuriTotaleRuta);	
				} else {
					printf("Pierdere: %5.2f lei\n", venitBilete - temp->zbor.costuriTotaleRuta);	
				}
			}
			temp = temp->next;
		}
	}
}

//-----END STRUCTURA LISTA DE LISTE-----------------------------------------------------------------



//CAR
/*
-arbore avl
-marfuri.txt
*/

//-----STRUCTURA MARFA------------------------------------------------------------------------------

struct Marfa {
	char* idRezervare;
	char* idZbor;
	double greutateMarfa;
	int nivelRisc;
	float tarifUnitar;
	double costTotal;
};

void calculareCostTotalMarfa(Marfa &car) {
	car.tarifUnitar = 7;
	car.costTotal = car.greutateMarfa * car.nivelRisc * car.tarifUnitar;
}

Marfa creareMarfa(char* idRezervare, char* idZbor, char* greutateMaxima, char* nivelRisc) {
	Marfa car;
	car.idRezervare = new char[strlen(idRezervare)+1];
	strcpy(car.idRezervare,idRezervare);
	car.idZbor = new char[strlen(idZbor)+1];
	strcpy(car.idZbor,idZbor);
	car.greutateMarfa = atof(greutateMaxima);
	car.nivelRisc = atoi(nivelRisc);
	calculareCostTotalMarfa(car);
	return car;
}


void afisareMarfa(Marfa car) {
	printf("IdRezervare: %s\n",car.idRezervare);
	printf("IdZbor: %s\n",car.idZbor);
	printf("GreutateMarfa: %5.2f\n",car.greutateMarfa);
	printf("NivelRisc: %d\n",car.nivelRisc);
	printf("CostTotal: %5.2f\n",car.costTotal);
	printf("\n");
}

//-----END STRUCTURA LISTA DE LISTE-----------------------------------------------------------------



//-----STRUCTURA ARBORE AVL-------------------------------------------------------------------------

struct NodMarfa{
	Marfa car;
	NodMarfa *stanga;
	NodMarfa *dreapta;
};

int max(int a, int b){
	if(a>b) {
		return a;
	} else {
		return b;
	}
}

int inaltime(NodMarfa *rad) {
	if(rad != NULL) {
		return 1 + max(inaltime(rad->stanga),inaltime(rad->dreapta));
	} else {
		return 0;
	}
}

int gradEchilibru(NodMarfa *rad) {
	return inaltime(rad->dreapta) - inaltime(rad->stanga);
}

#pragma region Rotatii

NodMarfa* rotatieSimplaDreapta(NodMarfa *pivot, NodMarfa *fiuStanga) {
	pivot->stanga = fiuStanga->dreapta;
	fiuStanga->dreapta = pivot;
	return fiuStanga;
}

NodMarfa* rotatieSimplaStanga(NodMarfa *pivot, NodMarfa *fiuDreapta) {
	pivot->dreapta = fiuDreapta->stanga;
	fiuDreapta->stanga = pivot;
	return fiuDreapta;
}

NodMarfa* rotatieDublaStangaDreapta(NodMarfa *pivot, NodMarfa* fiuStanga) {
	pivot->stanga = rotatieSimplaStanga(fiuStanga, fiuStanga->dreapta);
	fiuStanga = pivot->stanga;
	fiuStanga = rotatieSimplaDreapta(pivot, fiuStanga);
	return fiuStanga;
}

NodMarfa* rotatieDublaDreaptaStanga(NodMarfa *pivot, NodMarfa *fiuDreapta) {
	pivot->dreapta = rotatieSimplaDreapta(fiuDreapta, fiuDreapta->stanga);
	fiuDreapta = pivot->dreapta;
	fiuDreapta = rotatieSimplaStanga(pivot, fiuDreapta);
	return fiuDreapta;
}

#pragma endregion

NodMarfa *creareNodMarfa(Marfa car) {
	NodMarfa *nou = new NodMarfa;
	nou->car = car;
	nou->stanga = nou->dreapta = NULL;
	return nou;
}

void inserareMarfa(NodMarfa *&rad, NodMarfa *nou) {
	if(rad == NULL) { 
		rad = nou;
		return;
	}

	if(strcmp(nou->car.idRezervare, rad->car.idRezervare) < 0) {
		inserareMarfa(rad->stanga, nou);
	} else if(strcmp(nou->car.idRezervare, rad->car.idRezervare) > 0) {
		inserareMarfa(rad->dreapta, nou);
	} else if(strcmp(nou->car.idRezervare, rad->car.idRezervare) == 0) {
		return;
	}

	if(gradEchilibru(rad) == 2) {
		if(gradEchilibru(rad->dreapta) == -1) {
			rad = rotatieDublaDreaptaStanga(rad, rad->dreapta);
		} else {
			rad = rotatieSimplaStanga(rad, rad->dreapta);
		}
	} else if(gradEchilibru(rad) == -2) {
		if(gradEchilibru(rad->stanga) == 1) {
			rad = rotatieDublaStangaDreapta(rad, rad->stanga);
		} else {
			rad = rotatieSimplaDreapta(rad, rad->stanga);
		}
	}
}

void afisareSrdMarfuri(NodMarfa *rad) {
	if(rad != NULL) {
		afisareSrdMarfuri(rad->stanga);
		afisareMarfa(rad->car);
		afisareSrdMarfuri(rad->dreapta);
	}
}

NodMarfa* cautaNodMarfaDupaId(NodMarfa *rad, char* idRezervare) {
	if(rad != NULL) {
		cautaNodMarfaDupaId(rad->stanga, idRezervare);
		if(strcmp(rad->car.idRezervare,idRezervare) == 0) {
			return rad;
		}
		cautaNodMarfaDupaId(rad->dreapta, idRezervare);
	} else {
		return NULL;
	}
}

void inserareMarfaArbore(NodAeronava *prim, NodAeronava *ultim, TabelaDispersie tabela, NodMarfa *&rad, Marfa car) {
	if(tabela.dimTabela > 0) { //daca exista zboruri in tabela de dispersie
		for(int i=0; i < tabela.dimTabela; i++) {//atunci parcurg vectorul de liste de zboruri
			if(tabela.zboruri[i] != NULL) {//daca lista de pe poz i nu e nula
				NodZbor *temp = tabela.zboruri[i];
				while(temp != NULL) {//atunci parcurg colectia de zboruri
					if(strcmp(temp->zbor.idZbor, car.idZbor) == 0) {//daca marfa corespunde zborului
						while(prim != NULL) {//atunci parcurg lista dubla de aeronave
							//daca aeronava corespunde zborului
							if(strcmp(prim->aero.idAeronava, temp->zbor.idAeronava) == 0) {
								//daca aeronava este de tip cargo
								if(prim->aero.tipAero == TipAeronava::CAR) {
									//are sens sa fac inserarea in arborele avl
									inserareMarfa(rad, creareNodMarfa(car));
									return;
								}//altfel nu inserez marfa
							}	
							//altfel avansez la urmatoarea aeronava
							if(prim == ultim) {
								prim = NULL;
							} else {
								prim = prim->next;
							}
						}
					}
					temp=temp->next;//atfel avansez la urmatorul nod zbor		
				}
			}
		}
	}
}

void modificaNodMarfaDupaId(NodMarfa *&rad, char* idRezervare, char* idZbor, char* greutateMaxima, char* nivelRisc) {
	if(rad != NULL) {
		NodMarfa *nod = cautaNodMarfaDupaId(rad,idRezervare);
		if(nod) {
			nod->car = creareMarfa(idRezervare, idZbor, greutateMaxima, nivelRisc);
		}
	}
}

void checkInMarfuri(NodMarfa *&rad, char *idZbor, double &totalGreutate) {
	if(rad != NULL) {
		checkInMarfuri(rad->stanga, idZbor, totalGreutate);
		if(strcmp(rad->car.idZbor, idZbor) == 0) {
			totalGreutate += rad->car.greutateMarfa;
		}
		checkInMarfuri(rad->dreapta, idZbor, totalGreutate);
	}
}

void costsMarfuri(NodMarfa *&rad, char *idZbor, double &venit) {
	if(rad != NULL) {
		checkInMarfuri(rad->stanga, idZbor, venit);
		if(strcmp(rad->car.idZbor, idZbor) == 0) {
			venit += rad->car.costTotal;
		}
		checkInMarfuri(rad->dreapta, idZbor, venit);
	}
}

//-----END STRUCTURA ARBORE AVL---------------------------------------------------------------------



//-----STRUCTURA COMANDA----------------------------------------------------------------------------

struct Comanda {
	char **parametri;
	int nrParametri;
	char timestamp[32];
};

char* timestampCurent() {
	time_t ltime = time(NULL);
	return asctime(localtime(&ltime));
}

Comanda creareComanda(char consola[1024]) {
	char *temp1 = new char[strlen(consola)+1];
	char *temp2 = new char[strlen(consola)+1];
	strcpy(temp1,consola);
	strcpy(temp2,consola);
	char sep[5] = " ,.-";

	//Calculez numarul parametrilor
	int nrParametri = 0;
	char *tok = strtok(temp1, sep);
	while(tok != NULL) {
		tok = strtok(NULL, sep);
		nrParametri++;
	}

	//Salvez parametru cu parametru
	char** parametri = new char*[nrParametri];
	tok = strtok(temp2, sep);
	for(int i = 0; (i<nrParametri) && (tok != NULL); i++) {
		parametri[i] = new char[strlen(tok)+1];
		strcpy(parametri[i],tok);
		tok = strtok(NULL, sep);
	}

	Comanda cmd;
	//Creez comanda
	if(nrParametri != 0) {
		cmd.nrParametri = nrParametri;
		cmd.parametri = new char*[nrParametri];
		for(int i = 0; i<nrParametri; i++) {
			cmd.parametri[i] = new char[strlen(parametri[i])+1];
			strcpy(cmd.parametri[i],parametri[i]);
		}
		strcpy(cmd.timestamp, timestampCurent()); //Pune un \n in plus
		cmd.timestamp[strlen(cmd.timestamp)-1] = '\0'; //Scap de acest caracter punand terminatorul de sir de caractere

	} else {
		cmd.nrParametri = 0;
		cmd.parametri = NULL;
		strcpy(cmd.timestamp, timestampCurent());
	}
	return cmd;
}

void afisareComanda(Comanda cmd) {
	for(int i=0; i<cmd.nrParametri; i++) {
		printf("%s ",cmd.parametri[i]);
	}
	printf("%s\n",cmd.timestamp);
}

void salvareComandaFisierTxt(Comanda cmd) {
	FILE *fisier = NULL;
	fisier = fopen("logs.txt","at");
	if(fisier != NULL) {
		fprintf(fisier,"%s ",cmd.timestamp);
		for(int i=0; i<cmd.nrParametri; i++) {
			fprintf(fisier,"%s ",cmd.parametri[i]);
		}
		fprintf(fisier,"\n");
	}
	fclose(fisier);
}

//-----END STRUCTURA COMANDA------------------------------------------------------------------------



//-----STRUCTURA LISTA SIMPLU INLANTUITA (COADA)----------------------------------------------------

struct NodComanda {
	Comanda cmd;
	NodComanda *next;
};

void inserareComandaSfarsit(NodComanda* &capat, Comanda cmd) {
	NodComanda *nou = new NodComanda;
	nou->cmd = cmd;
	nou->next = NULL;
	if(capat == NULL) {
		capat = nou;
	} else{
		NodComanda *temp = capat;
		while(temp->next != NULL) {
			temp=temp->next;
		}
		temp->next = nou;
	}
}

void afisareListaComenzi(NodComanda* capat) {
	if(capat != NULL) {
		NodComanda* temp = capat;
		while(temp != NULL) {
			afisareComanda(temp->cmd);
			temp = temp->next;
		}
	}
}

//-----END STRUCTURA LISTA SIMPLU INLANTUITA (COADA)------------------------------------------------



//-----INCARCARE STRUCTURI DIN FISIERE--------------------------------------------------------------

void citireAeronaveFisierTxt(NodAeronava *&prim, NodAeronava *&ultim) {
	prim = ultim = NULL;
	FILE *fisier = NULL;
	fisier = fopen("flaero.txt","rt");
	if(fisier != NULL) {
		while(!feof(fisier)) {
			Aeronava aero;
			char buffer[50];
			fscanf(fisier,"%s",buffer);
			aero.idAeronava = new char[strlen(buffer)+1];
			strcpy(aero.idAeronava,buffer);
			fscanf(fisier,"%s",buffer);
			if(strcmp(buffer,"pas")==0 || strcmp(buffer,"PAS")==0) {
				aero.tipAero = TipAeronava::PAS;
			} else if(strcmp(buffer,"car")==0 || strcmp(buffer,"CAR")==0){
				aero.tipAero = TipAeronava::CAR;
			}
			fscanf(fisier,"%s",buffer);
			aero.nrLocuri = atoi(buffer);
			fscanf(fisier,"%s",buffer);
			aero.greutateMaxima = atof(buffer);
			inserareAeronavaSfarsit(prim, ultim, aero);
		}
	} 
}

void citireZboruriFisierTxt(TabelaDispersie &tabela) {
	FILE *fisier = NULL;
	fisier = fopen("program.txt","rt");
	if(fisier != NULL) {
		while(!feof(fisier)) {
			Zbor zbor;
			char buffer[50];
			fscanf(fisier,"%s",buffer);
			zbor.idZbor = new char[strlen(buffer)+1];
			strcpy(zbor.idZbor,buffer);
			fscanf(fisier,"%s",buffer);
			zbor.idAeronava = new char[strlen(buffer)+1];
			strcpy(zbor.idAeronava,buffer);
			fscanf(fisier,"%s",buffer);
			zbor.costuriTotaleRuta = atof(buffer);
			inserareZborTabelaDispersie(tabela, zbor);
		}
	}
}

void citirePasageriFisierTxt(NodZborPasageri *&capat) {
	FILE *fisier = NULL;
	fisier = fopen("pasageri.txt","rt");
	if(fisier != NULL) {
		while(!feof(fisier)) {
			Pasager pas;
			char buffer[50];
			fscanf(fisier,"%s",buffer);
			pas.idRezervare = new char[strlen(buffer)+1];
			strcpy(pas.idRezervare,buffer);
			fscanf(fisier,"%s",buffer);
			pas.idZbor = new char[strlen(buffer)+1];
			strcpy(pas.idZbor,buffer);
			fscanf(fisier,"%s",buffer);
			pas.nume = new char[strlen(buffer)+1];
			strcpy(pas.nume,buffer);
			fscanf(fisier,"%s",buffer);
			pas.prenume = new char[strlen(buffer)+1];
			strcpy(pas.prenume,buffer);
			fscanf(fisier,"%s",buffer);
			pas.costBilet = atof(buffer);
			fscanf(fisier,"%s",buffer);
			if(atoi(buffer) == 1) {
				pas.isChecked = true;
			} else {
				pas.isChecked = false;
			}
			inserarePasagerListaDeListe(capat, pas);
		}
	}
}

void citireMarfuriFisierTxt(NodAeronava *prim, NodAeronava *ultim, TabelaDispersie tabela, NodMarfa *&rad) {
	FILE *fisier = NULL;
	fisier = fopen("marfuri.txt","rt");
	if(fisier != NULL) {
		while(!feof(fisier)) {
			Marfa car;
			char buffer[50];
			fscanf(fisier,"%s",buffer);
			car.idRezervare = new char[strlen(buffer)+1];
			strcpy(car.idRezervare,buffer);
			fscanf(fisier,"%s",buffer);
			car.idZbor = new char[strlen(buffer)+1];
			strcpy(car.idZbor,buffer);
			fscanf(fisier,"%s",buffer);
			car.greutateMarfa = atof(buffer);
			fscanf(fisier,"%s",buffer);
			car.nivelRisc = atoi(buffer);
			calculareCostTotalMarfa(car);
			inserareMarfaArbore(prim, ultim, tabela, rad, car);
		}
	}
}

//-----END INCARCARE STRUCTURI DIN FISIERE----------------------------------------------------------

void main() {

	//Primul si ultimul nod din lista dubla circulara de noduri Aeronava
	NodAeronava *primListaDblCircAeronave, *ultimListaDblCircAeronave = NULL;
	//Tabela de dispersie ce contine noduri Zbor
	//dimensiunea = 20 x cate aeronave exista in lista dubla
	TabelaDispersie tabDispZboruri = initialiareTabelaDispersie(20);
	//Lista de liste de noduri Pasager
	NodZborPasageri *listaPasageri = NULL;
	//Arbore AVL de noduri Marfa
	NodMarfa *arbMarfuri = NULL;

	//Incarcarea cu date din fisiere a structurilor de mai sus
	citireAeronaveFisierTxt(primListaDblCircAeronave, ultimListaDblCircAeronave);
	citireZboruriFisierTxt(tabDispZboruri);
	listaPasageri = creareListaDeListe(tabDispZboruri);
	citirePasageriFisierTxt(listaPasageri);
	citireMarfuriFisierTxt(primListaDblCircAeronave,ultimListaDblCircAeronave,tabDispZboruri,arbMarfuri);

	//Preluarea datelor de intrare ale comenzilor
	NodComanda *listaComenzi = NULL;
	while(true) {
		char consola[1024];
		printf("cmd> ");
		gets(consola);

		if(strcmp(consola, "exit") == 0) {

			//salvare modificari tabela dispersie in fisier
			break;
		}

		Comanda cmd = creareComanda(consola);
		inserareComandaSfarsit(listaComenzi, cmd);
	}

	//Parcurgere coada comenzi si procesarea parametrilor acesteia 
	if(listaComenzi != NULL) {
		NodComanda* temp = listaComenzi;
		while(temp != NULL) {
			bool eValida = true;
			char mesaj[100];
			//-----------------------------ADD------------------------------------------------------
			if(strcmp(temp->cmd.parametri[0], "add") == 0) {
				//-----------------------------ADD FAV----------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "fav") == 0) {

					Aeronava aero = creareAeronava(
						temp->cmd.parametri[2],
						temp->cmd.parametri[3],
						temp->cmd.parametri[4],
						temp->cmd.parametri[5]
					);
					inserareAeronavaSfarsit(primListaDblCircAeronave,ultimListaDblCircAeronave,aero);
					printf("Aeronava a fost adaugata cu succes.\n");

					//-----------------------------ADD RUZ----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1],"ruz") == 0) {
					if(cautaNodAeronavaDupaId(primListaDblCircAeronave, ultimListaDblCircAeronave, temp->cmd.parametri[3]) != NULL) {
						Zbor zbor = creareZbor(
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4]
						);
						inserareZborTabelaDispersie(tabDispZboruri, zbor);
						printf("Zborul a fost adaugat cu succes.\n");
					} else {
						printf("Aeronava cu id-ul introdus nu exista!\n");
					}
					//-----------------------------ADD REP----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri, temp->cmd.parametri[3]) != NULL) {
						Pasager pas = crearePasager(
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4],
							temp->cmd.parametri[5],
							temp->cmd.parametri[6],
							temp->cmd.parametri[7]
						);
						inserarePasagerListaDeListe(listaPasageri,pas);
						printf("Pasagerul a fost adaugat cu succes.\n");
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------ADD CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri, temp->cmd.parametri[3]) != NULL) {
						Marfa car = creareMarfa(
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4],
							temp->cmd.parametri[5]
						);
						NodMarfa* nodCar = creareNodMarfa(car);
						inserareMarfa(arbMarfuri, nodCar);
						printf("Marfa a fost adaugata cu succes.\n");
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
				//-----------------------------UPDATE------------------------------------------------------
			} else if(strcmp(temp->cmd.parametri[0],"update") == 0) {
				//-----------------------------UPDATE FAV--------------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "fav") == 0) {

					if(cautaNodAeronavaDupaId(primListaDblCircAeronave, ultimListaDblCircAeronave, temp->cmd.parametri[2]) != NULL) {
						modificaNodAeronavaDupaId(
							primListaDblCircAeronave,
							ultimListaDblCircAeronave,
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4],
							temp->cmd.parametri[5]
						);
						printf("Aeronava a fost modificata cu succes\n");
					} else {
						printf("Aeronava cu id-ul introdus nu exista!\n");
					}

					//-----------------------------UPDATE RUZ----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1],"ruz") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						modificaNodZborDupaId(
							tabDispZboruri,
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4]
						);
						printf("Zborul a fost modificat cu succes\n");
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------UPDATE REP----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					if(cautaNodPasagerDupaId(listaPasageri,temp->cmd.parametri[2]) != NULL) {
						modificaNodPasagerDupaId(
							listaPasageri,
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4],
							temp->cmd.parametri[5],
							temp->cmd.parametri[6],
							temp->cmd.parametri[7]
						);
						printf("Pasagerul a fost modificat cu succes\n");
					} else {
						printf("Pasagerul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------UPDATE CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					if(cautaNodMarfaDupaId(arbMarfuri,temp->cmd.parametri[2]) != NULL) {
						modificaNodMarfaDupaId(
							arbMarfuri,
							temp->cmd.parametri[2],
							temp->cmd.parametri[3],
							temp->cmd.parametri[4],
							temp->cmd.parametri[5]
						);
						printf("Marfa a fost modificata cu succes\n");
					} else {
						printf("Marfa cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
				//-----------------------------FIND------------------------------------------------------
			} else if(strcmp(temp->cmd.parametri[0],"find") == 0) {
				//-----------------------------FIND FAV--------------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "fav") == 0) {

					NodAeronava *nodCautat = cautaNodAeronavaDupaId(primListaDblCircAeronave, ultimListaDblCircAeronave, temp->cmd.parametri[2]);
					if(nodCautat != NULL) {
						afisareAeronava(nodCautat->aero);
					} else {
						printf("Aeronava cu id-ul introdus nu exista!\n");
					}

					//-----------------------------FIND RUZ----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1],"ruz") == 0) {

					NodZbor *nodCautat = cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]);
					if(nodCautat != NULL) {
						afisareZbor(nodCautat->zbor);
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------FIND REP----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					NodPasager *nodCautat = cautaNodPasagerDupaId(listaPasageri,temp->cmd.parametri[2]);
					if(nodCautat != NULL) {
						afisarePasager(nodCautat->pas);
					} else {
						printf("Pasagerul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------FIND CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					NodMarfa *nodCautat = cautaNodMarfaDupaId(arbMarfuri,temp->cmd.parametri[2]);
					if(nodCautat != NULL) {
						afisareMarfa(nodCautat->car);
					} else {
						printf("Marfa cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
				//-----------------------------DELETE------------------------------------------------------
			} else if(strcmp(temp->cmd.parametri[0],"delete") == 0) {
				//-----------------------------DELETE FAV----------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "fav") == 0) {

					if(cautaNodAeronavaDupaId(primListaDblCircAeronave, ultimListaDblCircAeronave, temp->cmd.parametri[2]) != NULL) {
						stergeNodAeronavaDupaId(primListaDblCircAeronave, ultimListaDblCircAeronave, temp->cmd.parametri[2]);
						printf("Aeronava a fost stearsa cu succes.\n");
					} else {
						printf("Aeronava cu id-ul introdus nu exista!\n");
					}

					//-----------------------------DELETE RUZ----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1],"ruz") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						stergeNodZborDupaId(tabDispZboruri, temp->cmd.parametri[2]);
						printf("Zborul a fost stears cu succes.\n");
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------DELETE REP----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					if(cautaNodPasagerDupaId(listaPasageri,temp->cmd.parametri[2]) != NULL) {
						stergeNodPasagerDupaId(listaPasageri, temp->cmd.parametri[2]);
						printf("Pasagerul a fost stears cu succes.\n");
					} else {
						printf("Pasagerul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------DELETE CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					if(cautaNodMarfaDupaId(arbMarfuri,temp->cmd.parametri[2]) != NULL) {
						//stergere nod marfa din arborele avl
						printf("Marfa a fost stearsa cu succes.\n");
					} else {
						printf("Marfa cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
				//-----------------------------CHECK------------------------------------------------------
			} else if(strcmp(temp->cmd.parametri[0],"check") == 0) {
				//-----------------------------CHECK REP-------------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						checkInPasageri(listaPasageri, temp->cmd.parametri[2]);
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------CHECK CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						double totalGreutate = 0;
						checkInMarfuri(arbMarfuri, temp->cmd.parametri[2], totalGreutate);
						printf("Total greutate zbor: %5.2lf\n",totalGreutate);
					} else {
						printf("Marfa cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
				//-----------------------------COSTS------------------------------------------------------
			} else if(strcmp(temp->cmd.parametri[0],"costs") == 0) {
				//-----------------------------COSTS REP-------------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "rep") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						costsPasageri(listaPasageri, temp->cmd.parametri[2]);
					} else {
						printf("Zborul cu id-ul introdus nu exista!\n");
					}

					//-----------------------------COSTS CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {

					if(cautaNodZborDupaId(tabDispZboruri,temp->cmd.parametri[2]) != NULL) {
						double venit = 0;
						Zbor zbor = cautaNodZborDupaId(tabDispZboruri, temp->cmd.parametri[2])->zbor;
						costsMarfuri(arbMarfuri, temp->cmd.parametri[2], venit);

						if(venit - zbor.costuriTotaleRuta >= 0) {
							printf("Profit: %5.2f lei\n", venit - zbor.costuriTotaleRuta);
						} else {
							printf("Pierdere: %5.2f lei\n", venit - zbor.costuriTotaleRuta);
						}

					} else {
						printf("Marfa cu id-ul introdus nu exista!\n");
					}

				} else {
					eValida = false;
				}
			}  //-----------------------------SELECT------------------------------------------------------
			else if(strcmp(temp->cmd.parametri[0], "select") == 0) {
				//-----------------------------SELECT FAV----------------------------------------------
				if(strcmp(temp->cmd.parametri[1], "fav") == 0) {
					afisareAeronavePrimUltim(primListaDblCircAeronave, ultimListaDblCircAeronave);
					//-----------------------------SELECT RUZ----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1],"ruz") == 0) {
					afisareZboruriTabelaDispersie(tabDispZboruri);
					//-----------------------------SELECT REP----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "rep") == 0) {
					afisarePasageriListaDeListe(listaPasageri);
					//-----------------------------SELECT CAR----------------------------------------------
				} else if(strcmp(temp->cmd.parametri[1], "car") == 0) {
					printf("\n-----AFISARE MARFURI-----\n");
					afisareSrdMarfuri(arbMarfuri);
				} else {
					eValida = false;
				}
				//-----------------------------UPDATE------------------------------------------------------
			}

			if(eValida) {
				salvareComandaFisierTxt(temp->cmd);
			}

			temp = temp->next;
		}
	}

	getch();
}