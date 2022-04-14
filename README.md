# Tema 1 - Momente disperate

0.  General
    a) Commandline
comanda o citesc cuvânt cu cuvânt (scanf), iar pentru a fi eficient din punct de vedere al memoriei și să nu folosesc un vector static, am folosit o funcție în care îmi alocă 256 biți, ca apoi să iau cu strlen + 1 pentru a lua fix mărimea cuvântului pe care-l citesc.

    b) Data
Datele le citesc cu o funcție create_data(), care-mi stochează datele introduse într-o structură ca apoi să le introduc cu funcția add_last / add_at.

    c) Length array
Am o funcție care calculează și returnează lungimea vectorului dinamic în biți, pentru a mă ajuta să aloc cât este nevoie pentru vectorii următori.

1. add_last/insert
    Am creat un array auxiliar (*aux), pentru a stoca datele în el, ca apoi să-l introducem în șirul *arr, pe lângă asta voi avea și un aux_len, care mă va ajuta să parcurg șirul, în același timp având și lungimea șirului în bytes, pentru a realoca vectorul mare *arr.

    Verific dacă șirul în care vom stoca la final este gol sau nu, pentru a ști ce funcție să folosim, malloc/realloc.
    Apoi pur și simplu îl introduc la sfârșit.

2. add_at/insert_at
    Avem un caz când index este mai mare sau egal decât numărul de elemente din vector, dacă da, atunci acesta inserează la sfârșitul vectorului cu funcția de mai sus.

    Pentru celălalt caz, parcurgem șirul, știind câte elemente are și ne oprim când ajunge iteratorul == index, în acelați timp va fi o variabilă len_aux, care calculează câți biți am parcurs, că dacă ajungem la elementul index, începutul lui va fi len_aux - data_aux->header->len. data_aux ia valorile în for, ca după să le folosim mai ușor.

    len_initial se duce la primul bit al elementului cu numărul index
    apoi introduc într-un șir auxiliar datele pe care le introducem.
    apoi mut biții pentru a face loc datelor pentru a le introduce, apoi copiem în poziția len_initial.

3. find
    Aceeași iterație ca la add_at, unde avem un len_aux, pe care-l avem ca să obținem datele din șir, când ajunge la index, avem un len_aux = 0 și un șir arr, pentru a folosi funcțiile print și add_last

4. delete_at
    Aceeași iterație ca la find, add_at, care ia datele din fiecare element, pentru ca apoi, să putem ajunge la începutul elementului care vrem să-l ștergem și să suprascriem ce e după element prin variabila len_aux, care a fost crescută în iterație.

5. print
    Aceeași iterație ca la delete_at/find/add_at, care tot trece prin toate elementele, dar în această iterație avem în plus că afișăm aceste elemente, prin niște if care ne ajută să știm dacă e de tip 1 , 2 sau 3.
    Am folosit un pointer care să mă ajute să parcurg șirul prin incrementare.
