#include<iostream>
using namespace std;

int f1(int n){
if(n%2) 
return 0;
else return 1;
}
int f2(int n){
if(n%3)  return 0;
else return 1;

}

int main(){
int n;
cout<<"entrez une valeur "<<endl;
cin>>n;
int f1(int);
int f2(int);
if(f1(n))
{
    cout<<"il est pair"<<endl;
}
if(f2(n)){
    cout<<"il est multiple de 3"<<endl;
}
if(n%6==0)
{
    cout<<"il est divisible par 6"<<endl;
}
    return 0;
}