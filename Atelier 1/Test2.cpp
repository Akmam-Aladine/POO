#include<iostream>
using namespace std;

int main()
{
const char c = '*' ; //caractère de remplissage 
int nl; // nombre total de lignes 
int l; // compteur de ligne 
int np ; //nombre d'espaces précédant une étoile 
int j ;
cout << "combien de lignes ? " ;
cin >> nl ;
for (l=0 ; l<nl ; l++)
{ np = nl - l - 1 ;
for (j=0 ; j<np ; j++) cout << ' ' ;
for (j=0 ; j<2*l+1 ; j++) cout << c ;
cout << '\n' ;
}
    return 0;
}