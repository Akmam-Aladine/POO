#include<iostream>
using namespace std;
class Personne{
private:
string nom;
string prenom;
int date_nais;
public:
Personne(string n,string pre,int date)
:nom(n),prenom(pre),date_nais(date)
{}
  virtual void affiche() const{
    cout<<"le nom  :"<<nom<<" ,le prenom  :"<<prenom<< ",la date de naissance  : "<<date_nais;

}
};
class Employe:public Personne{
private:
double salaire;
public:
Employe(string n,string pre,int date,double sal)
:Personne(n,pre,date),salaire(sal)
{}
void affiche() const override {
        Personne::affiche();
cout<<"le salire:  "<<salaire<<"DH"<<endl;
}
};
class Chef:public Employe{
private:
string service;
public:
Chef(string n,string pre,int date,double sal,string serv)
:Employe(n,pre,date,sal),service(serv)
{}
void affiche() const override {
        Employe::affiche();
cout<<"le service:"<<service<<endl;
}
};
class Directeur:public Chef{
private:
string societe;
public:
Directeur(string n,string pre,int date,double sal,string serv,string soc)
:Chef(n,pre,date,sal,serv),societe(soc)
{}
void affiche() const override {
        Chef::affiche();
cout<<" a société: "<<societe<<endl;
}
};

int main() {
    Personne personne("ALI", "SAID", 1998);
    Employe employe("Abdou", "chabane", 1992, 5000);
    Chef chef("fatima", "mohamed", 1990, 6000, "Chef de cellule");
    Directeur directeur("alice", "aldine", 1985, 10000, "Responsable ", "NETIS");

    personne.affiche();
    cout << "------------------" << endl;
    employe.affiche();
    cout << "------------------" << endl;
    chef.affiche();
    cout << "------------------" << endl;
    directeur.affiche();

    return 0;
}

