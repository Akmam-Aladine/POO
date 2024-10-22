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

    // Constructeur avec paramètres
    Voiture(string m, string mod, int a, float km, float v) {
        marque = m;
        modele = mod;
        annee = a;
        kilometrage = km;
        vitesse = v;
    }

    // Méthode pour accélérer
    void accelerer(float valeur) {
        vitesse += valeur;
    }

    // Méthode pour freiner
    void freiner(float valeur) {
        if (vitesse - valeur >= 0) {
            vitesse -= valeur;
        } else {
            vitesse = 0;
        }
    }

    // Méthode pour afficher les informations
    void afficherInfo() const {
        cout << "Marque: " << marque << endl;
        cout << "Modèle: " << modele << endl;
        cout << "Année: " << annee << endl;
        cout << "Kilométrage: " << kilometrage << " km" << endl;
        cout << "Vitesse: " << vitesse << " km/h" << endl;
    }

    // Méthode pour avancer
    void avancer(float distance) {
        kilometrage += distance;
    }

    // Destructeur
    ~Voiture() {
        cout << "La voiture " << marque << " " << modele << " est détruite." << endl;
    }
};

int main() {
    // Création d'une voiture avec le constructeur par défaut
    Voiture voiture1;
    voiture1.afficherInfo();

    // Création d'une voiture avec des paramètres
    Voiture voiture2("Toyota", "Corolla", 2020, 10000, 120);
    voiture2.afficherInfo();

    // Accélérer et freiner la voiture
    voiture2.accelerer(20);
    voiture2.afficherInfo();

    voiture2.freiner(50);
    voiture2.afficherInfo();

    // Avancer la voiture
    voiture2.avancer(500);
    voiture2.afficherInfo();

    return 0;
}
