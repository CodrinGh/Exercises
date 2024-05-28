#include<iostream>
#include <stdlib.h>

int x = 10; // this should have a static duration, hence why the static storage

int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int b[10];
void* calloc(size_t nelem, size_t elsize)
{
	return 0;
}
void free(void* ptr)
{

}


int f()
{
	int y = 10; // this should have automatic duration, hence why auto storage
	return y;
}

int main()
{
	static int k = 3;
	return 0;
}

/*
Sunt 3 moduri de a crea activation frames
1. Alocare statica -> arata activation frame ul la compilare
2. Alocare dinamica pe heap -> crearea activation frame ului pe heap la runtime
3. Alocare dinamica pe system stack -> la fel ca inainte, doar ca e pe system stack in loc de heap. ce plm e asta?

E folosita a 3 a varianta, pentru ca asa se reda controlul la executarea functiilor mai bine. Activation frame ul este pus pe system stack,
astfel creandu se recursivitate

*/

//realloc may create dangling pointers
//alloc poate failui daca nu are suficienta memorie, daca se cere prea multa memorie, sau sistemul care aloca memoria are bug uri
//am putea spune ca sectiunea de date statica este una data de compilator, unde se stocheaza informatiile globale, statice si instructiunile
//de executie pentru program
//alocarea dinamica preia memoria data de manager si eventual o imparte in segmente mai mici, acolo unde e nevoie
//motiv pentru care free poate si sa faca join la zonele de memorie eliberate


//ACTIVATION FRAME -> data stracture, adica structura de date unde se salveaza toate datele necesare pentru rularea unei functii
// //se foloseste low address a spatiului nefolosit, low putand insemna ca se pune de jos in sus, adica de la mai mare la mai mic, din ce zic astia
// apoi, dupa cum urmeaza: variabilele statice se pun in static data region a memoriei programului, iar dynamic data se pun in regiunea de dynamic data
// interesant, compiler ul include instructiuni prin care sa se transforme tipurile de data in cod binar
//
// struct ul are un padding astfel incat sa poata citi un machine word, sa nu intercaleze datele
// fetch is reading
//
// adresele ca si literal se folosesc cand se fac operatii de intrare/iesire cu systemul
//  
// When the linking starts, firstly it start with rellocation where the library is linked into the ombject module, putting the machine code after the
// first machinde code, and the initialized data section after the initialized data section
//addreses => actually offsets for symbols from the beginning of the object module(or seciton)
//start execution function x => start executing instruction at address y
//Object module structure
//--------
//HEADER SECTION
//--------
//MACHINE CODE SECTION (a.k.a text section)
//--------
//INITIALIZED DATA SECTION
//--------
//SYMBOL TABLE SECTION
//--------
//RELOCATION INFORMATION SECTION
//--------


/*
HEADER SECTION
0 124 -> number of bytes of machine code execution
4 44 -> number of bytes of initialized data section
8 40 -> number of bytes of uninitialized data section(b)
? ? -> ??
12 60 -> number of bytes of Relocation information section
Machine code execution (124 bytes)
20 x code for
 - - -
Initialized data section(start of 144 because 20+ 124 = 144)
144 - 0 beggining of array a[]


Symbol table section(start of 188 because 144 + 44 = 188)
188 X -> arra a[]: offset 0 in initialized data section -> meaning that it s from offset 0 starting the initialized data section->makes sense
Relocation information section(44 bytes)
248 X -> relocation information

*/

//un interpreter doar interpreteaza limbajul, fara a l compila, motiv pentru care e portabil
//un interpreter de C++ ar fi dificil pentru ca are nevoie sa lucreze cu atat de multe adrese/pointeri
//un interpreter ar trebui sa aiba instructiuni specifice in functie de platforma pe care ruleaza, motiv pentru ca nu foloseste
//pentru ca toata ideea unui interpreter e de a fi portabil, nu de a l face platform specific
//calloc is malloc which clears

//
// Function stack
//-- Return value
//-- Actual arguments
//-- Optional access link -> alte date care nu sunt locale, puse in alte stack uri, dar probabil sunt referinte
//-- Optional control link -> link catre activation frame ul de la caller
//-- Saved machine status -> are valori are registrilor de sistem. ca exemplu e program counter, ce plm e ala
//-- Local data -> datele locale
//-- Temporaries -> valori temporare, ca de ex rezultate ale expresiilor