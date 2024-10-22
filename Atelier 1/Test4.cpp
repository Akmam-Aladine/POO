#include<iostream>
using namespace std;

int main()
{
        int A, B, C, D,max,min;
    cout << "Entrez l'entier A : ";
    cin >> A;
    cout << "Entrez l'entier B : ";
    cin >> B;
    cout << "Entrez l'entier C : ";
    cin >> C;
    cout << "Entrez l'entier D : ";
    cin >> D;
    
     max=(A> C) ?A:C;
     min=(B< D)?B:D;
    if(min>max){
     cout<<"l'intersection des deux intervalles est:["<<max<<","<<min<<"]";
    }
    else{
        cout<<"il n y a pas d'intersection";
    }
    
return 0;
}

