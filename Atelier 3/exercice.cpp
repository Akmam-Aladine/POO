#include <iostream>
#include <string>
using namespace std;

class Voiture {
private:
    string marque;
    string modele;
    int annee;
    float kilometrage;
    float vitesse;

public:
    Voiture() {
        marque = "Inconnue";
        modele = "Inconnu";
        annee = 0;
        kilometrage = 0.0;
        vitesse = 0.0;
    }

    Voiture(string m, string mod, int a, float km, float v) {
        marque = m;
        modele = mod;
        annee = a;
        kilometrage = km;
        vitesse = v;
    }
    void accelerer(float valeur) {
        vitesse += valeur;
    }

    void freiner(float valeur) {
        if (vitesse - valeur >= 0) {
            vitesse -= valeur;
        } else {
            vitesse = 0;
        }
    }
    void afficherInfo() const {
        cout << "Marque: " << marque << endl;
        cout << "Modèle: " << modele << endl;
        cout << "Année: " << annee << endl;
        cout << "Kilométrage: " << kilometrage << " km" << endl;
        cout << "Vitesse: " << vitesse << " km/h" << endl;
    }
    void avancer(float distance) {
        kilometrage += distance;
    }

    ~Voiture() {
        cout << "La voiture " << marque << " " << modele << " est détruite." << endl;
    }
};

int main() {
    Voiture voiture1;
    voiture1.afficherInfo();

    Voiture voiture2("Toyota", "Corolla", 2020, 10000, 120);
    voiture2.afficherInfo();

    voiture2.accelerer(20);
    voiture2.afficherInfo();

    voiture2.freiner(50);
    voiture2.afficherInfo();

    voiture2.avancer(500);
    voiture2.afficherInfo();

    return 0;
}
