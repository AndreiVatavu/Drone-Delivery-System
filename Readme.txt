							Explicatii tema 3
							-----------------
	
Algoritmul lui Floyd
--------------------
	Pentru a calcula matricea drumurilor minime am folosit algoritmul lui Floyd.
Acest algoritm consta in faptul ca verifica daca intre doua noduri, exista un
nod intrermediar k. De asemenea in timp ce calculez matricea drumurilor minime
construiesc si o matrice care sa retina nodurile intermediare aflate intre doua
noduri astfel: drum[i][j] = nodul intermediar dintre i si j sau cu 0 daca exista
o cale directa.

Taskul 1
--------
	Am citit datele de intrare, am creat graful initial, dupa care am aplicat
algoritml lui Floyd. Iau fiecare comanda in ordine si afisez nodurile
intermediare intre ferma si client, apoi intre client si ferma ( avand in vedere
faptul ca exista o singura ferma )

Taskul 2
--------
	Dupa ce creez matricea drumurilor minime afisez nodurile intre ferma de
start si primul client, apoi aflu care este cea mai apropiata ferma de nodul
in care ma aflu si afisez nodurile prin care trebuie sa treaca drona pentru
a ajunge la ferma. Procedeul se repeta pana cand sunt finalizate toate comenzile.

Taskul 3
--------
	Pentru a rezolva taskul 3 am folosit o strategie de tipul backtracking.
Initial am creat o structura ce retine un nod si tipul acestuia, dupa care
mi-am creat un vector de tipul acestei structuri. Daca nodul este client
voi pune tipul fermei de unde poate primi comanda cu semnul minus, iar daca
e ferma, voi lasa tipul fermei pozitiv. In functia backtracking parcurg acest
vector si adaug cate un element, verific daca indeplineste conditiile de
validare, iar daca este o solutie mai buna decat cea curenta o memorez.
Conditiile de validare sunt: sa nu fie doua noduri identice pe pozitii consecu-
tive, de la ultimul punct de interes si pana la cel curent, drona sa nu treaca
de doua ori prin acelasi nod.
