#include <iostream>
#include <vector>
using namespace std;

class Traitement {
private:
    vector<int> vecteur; // Attribut pour stocker les 15 entiers pairs

public:
    // Méthode pour initialiser le vecteur
    void Initialise() {
        int nombre;
        cout << "Veuillez entrer 15 entiers pairs (non nuls) :\n";

        while (vecteur.size() < 15) {
            cout << "Entrez un entier : ";
            cin >> nombre;

            // Vérification de l'entrée
            if (cin.fail()) {
                cin.clear(); // Effacer l'état d'erreur de cin
                cin.ignore(10000000000, '\n'); // Ignorer l'entrée incorrecte
                cout << "Erreur : Veuillez entrer un nombre entier.\n";
                continue;
            }

            if (nombre % 2 == 0 && nombre != 0) { // Vérification si le nombre est pair et non nul
                vecteur.push_back(nombre);
            } else {
                cout << "Erreur : Veuillez entrer un nombre entier pair non nul.\n";
            }
        }
    }

    // Méthode récursive pour afficher les éléments du vecteur
    void show(int index = 0) const {
        if (index < vecteur.size()) {
            cout << vecteur[index] << " ";
            show(index + 1); // Appel récursif
        } else {
            cout << endl;
        }
    }

    // Méthode amie pour calculer la moyenne
    friend double moyenne(const Traitement& t) {
        if (t.vecteur.empty()) return 0.0;

        double somme = 0;
        for (int nombre : t.vecteur) {
            somme += nombre;
        }
        return somme / t.vecteur.size();
    }

    // Méthode amie pour calculer la médiane
    friend double median(const Traitement& t) {
        if (t.vecteur.empty()) return 0.0;

        vector<int> copie = t.vecteur; // Faire une copie du vecteur pour trier
        for (size_t i = 0; i < copie.size() - 1; ++i) { // Tri simple par sélection
            for (size_t j = i + 1; j < copie.size(); ++j) {
                if (copie[i] > copie[j]) {
                    swap(copie[i], copie[j]);
                }
            }
        }

        size_t taille = copie.size();
        if (taille % 2 == 0) {
            // Si le nombre d'éléments est pair, la médiane est la moyenne des deux éléments centraux
            return (copie[taille / 2 - 1] + copie[taille / 2]) / 2.0;
        } else {
            // Si le nombre d'éléments est impair, la médiane est l'élément central
            return copie[taille / 2];
        }
    }
};

int main() {
    Traitement t;
    t.Initialise(); // Initialisation du vecteur

    cout << "Les éléments du vecteur sont : ";
    t.show(); // Affichage récursif des éléments

    // Calcul et affichage de la moyenne et de la médiane
    cout << "Moyenne : " << moyenne(t) << endl;
    cout << "Médiane : " << median(t) << endl;

    return 0;
}