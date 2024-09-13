# Checker Tema  - 2024
Checker-ul este o aplicație de testare automată a temelor. Este un produs open-source realizat de către și pentru studenții din Facultatea de Automatică și Calculatoare - UPB, și este menit atât să usureze munca asistenților de a corecta teme cât și sa ofere studenților o evaluare cât mai obiectivă.

## Rularea checker-ului
Pentru a verifica functionarea checker-ului va trebui sa descarcati tot depozitul de mai sus, dupa aceasta deschideti un terminal in folderul in care se afla depozitul descarcat si scrieti urmatoarea comanda:
```shell
./checker.sh
````
Acest proiect presupune implementarea unui algoritm care gestioneaza o competitie intre echipe, folosind mai multe structuri de date pentru a organiza si procesa echipele in functie de punctajul lor. Procesul este impartit in mai multe etape.

Pasi principali:
Crearea listei initiale de echipe:

Se creeaza o lista de echipe citite dintr-un fisier, adaugand elementele la inceputul listei pentru o complexitate de O(1).
Eliminarea echipelor cu punctaj mic:

Echipele cu cel mai mic punctaj sunt eliminate din lista astfel incat sa ramana n echipe, unde n este o putere a lui 2.
Daca mai multe echipe au acelasi punctaj, se elimina prima echipa gasita.
Organizarea meciurilor:

Se formeaza o coada de meciuri intre echipe in ordinea in care acestea apar in lista (primele doua echipe formeaza primul meci si asa mai departe).
Gestionarea invinsilor si castigatorilor:

Se creeaza doua stive: una pentru echipele invinse si una pentru castigatori.
Echipele castigatoare primesc un punct in plus.
Daca doua echipe au acelasi punctaj in cadrul unui meci, castiga prima echipa adaugata.
Dupa fiecare runda, echipele din stiva invinsilor sunt eliminate, iar castigatorii sunt introdusi in urmatoarea runda de meciuri.
Continuarea meciurilor pana la ramanerea a 8 echipe:

Procesul continua pana raman 8 echipe in competitie, care sunt salvate intr-o lista separata.
Clasamentul final (BST):

Cele 8 echipe ramase sunt introduse intr-un Binary Search Tree (BST), ordonat dupa punctaj.
Clasamentul final este afisat in ordine descrescatoare. Daca doua echipe au acelasi punctaj, acestea se ordoneaza alfabetic, in ordine descrescatoare dupa nume.
Structuri de date folosite:
Lista simplu inlantuita: Pentru organizarea echipelor.
Coada: Pentru formarea si gestionarea meciurilor.
Stive: Pentru separarea castigatorilor si invinsilor dupa fiecare runda.
Arbore binar de cautare (BST): Pentru afisarea clasamentului final al ultimelor 8 echipe.
Acest proiect pune accent pe manipularea structurilor de date si pe algoritmi de organizare si filtrare a echipelor, gestionand eficient competitiile pana la determinarea castigatorului.


addToList:
Rol: Adauga o echipa la inceputul unei liste de echipe.

read:
Rol: Citeste datele despre echipe si jucatori dintr-un fisier si le stocheaza intr-o lista.

write:
Rol: Scrie numele echipelor intr-un fisier.

countTeams:
Rol: Numara echipele din fisier.

power:
Rol: Calculeaza urmatoarea putere a lui 2 peste numarul de echipe.

searchPosition:
Rol: Gaseste pozitia echipei cu cel mai mic numar de puncte in lista de echipe.

eliminate:
Rol: Elimina jumatate din echipe, incepand cu cele cu cele mai putine puncte.

initQueue:
Rol: Initializeaza o coada de meciuri.

isEmpty:
Rol: Verifica daca coada de meciuri este goala.

enqueue:
Rol: Adauga un meci la coada.

clearQueue:
Rol: Goleste o coada de meciuri.

initStack:
Rol: Initializeaza o stiva de echipe.

isEmptyStack:
Rol: Verifica daca stiva de echipe este goala.

pop:
Rol: Scoate o echipa din varful stivei.

clearStack:
Rol: Goleste o stiva de echipe.

push:
Rol: Adauga o echipa la varful stivei.

eliminateWhitespace:
Rol: Elimina spatiile albe dintr-un sir de caractere.

printQueue:
Rol: Tipareste coada de meciuri intr-un fisier.

printStack:
Rol: Tipareste stiva de echipe intr-un fisier.

createMatches:
Rol: Creeaza meciuri pe baza echipei disponibile intr-o runda si le adauga in coada.

decideWinner:
Rol: Determina echipa castigatoare a fiecarui meci si le adauga in stiva castigatorilor si a perdantilor.

refillQueueFromStack:
Rol: Reimprospateaza coada de meciuri cu echipele castigatoare ale rundei anterioare.

sizeQueue:
Rol: Calculeaza dimensiunea cozii de meciuri.

processMatches:
Rol: Proceseaza meciurile in fiecare runda si decide echipele castigatoare.

insertInBST:
Rol: Insereaza o echipa intr-un arbore binar de cautare.

ListToBST:
Rol: Transforma o lista de echipe intr-un arbore binar de cautare.

printBST:
Rol: Tipareste arborele binar de cautare intr-un fisier.
