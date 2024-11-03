#include <iostream>
#include <cmath>
using namespace std;

class Vector3d {
private:
    float x, y, z;

public:
    // Constructeur avec valeurs par défaut
    Vector3d(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}

    // Fonction d'affichage
    void display() const {
        cout << "Les composantes du vecteur : (" << x << ", " << y << ", " << z << ")" << endl;
    }

    // Fonction pour la somme de deux vecteurs
    Vector3d operator+(const Vector3d& vect) const {
        return Vector3d(x + vect.x, y + vect.y, z + vect.z);
    }

    // Produit scalaire de deux vecteurs
    float produit_scal(const Vector3d& vect) const {
        return x * vect.x + y * vect.y + z * vect.z;
    }

    // Fonction pour vérifier si deux vecteurs ont les mêmes composantes
    bool coincide(const Vector3d& vect) const {
        return (x == vect.x && y == vect.y && z == vect.z);
    }

    // Calcul de la norme du vecteur
    float norme() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Norme maximale par valeur
    Vector3d normax_val(const Vector3d& vect) const {
        return (this->norme() > vect.norme()) ? *this : vect;
    }

    // Norme maximale par adresse
    const Vector3d* normax_adr(const Vector3d* vect) const {
        return (this->norme() > vect->norme()) ? this : vect;
    }

    // Norme maximale par référence
    const Vector3d& normax_ref(const Vector3d& vect) const {
        return (this->norme() > vect.norme()) ? *this : vect;
    }
};

int main() {
    Vector3d vect1(1.0, 2.0, 3.0);
    Vector3d vect2(4.0, 5.0, 6.0);

    cout << "Vecteur vect1 : ";
    vect1.display();

    cout << "Vecteur vect2 : ";
    vect2.display();

    // Somme des vecteurs
    Vector3d somme = vect1 + vect2;
    cout << "Somme de vect1 et vect2 : ";
    somme.display();

    // Produit scalaire
    cout << "Produit scalaire de vect1 et vect2 : " << vect1.produit_scal(vect2) << endl;

    // Vérification de la coïncidence
    cout << "vect1 et vect2 ont les mêmes composantes ? " << (vect1.coincide(vect2) ? "Oui" : "Non") << endl;

    // Normes des vecteurs
    cout << "Norme de vect1 : " << vect1.norme() << endl;
    cout << "Norme de vect2 : " << vect2.norme() << endl;

    // Norme maximale par valeur
    Vector3d normax_val = vect1.normax_val(vect2);
    cout << "Vecteur avec la plus grande norme (par valeur) : ";
    normax_val.display();

    // Norme maximale par adresse
    const Vector3d* normax_adresse = vect1.normax_adr(&vect2);
    cout << "Vecteur avec la plus grande norme (par adresse) : ";
    normax_adresse->display();

    // Norme maximale par référence
    const Vector3d& normax_reference = vect1.normax_ref(vect2);
    cout << "Vecteur avec la plus grande norme (par référence) : ";
    normax_reference.display();

    return 0;
}