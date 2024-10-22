#include<iostream>
using namespace std;
 
const int N=10;
 
int main()
{
int t[N],i,a,ct;
 
for(i=0;i<N;i++)
{cout<<"Veuillez rentrez le numero : "<<i<<endl;
cin>>t[i];
}
 
do
        {
        a=0;
        for(i=0;i<N-1;i++)
                if(t[i]>t[i+1])
                        {
                        ct=t[i];t[i]=t[i+1];t[i+1]=ct;
                        a++;
                        }
        }while(a!=0);
 
cout<<"VOICI LE TABLEAU TRIE :"<<endl;
for(i=0;i<N;i++)cout<<"a["<<i<<"]="<<t[i]<<endl;
 
return 0;
}