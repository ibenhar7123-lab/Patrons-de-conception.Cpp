// Exercice 2 : Patron Fabrique (Factory Method)
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class Forme {
public:
    virtual void afficher() const = 0;
    virtual ~Forme() = default;
};

class Cercle : public Forme {
public:
    void afficher() const override { cout << "Je suis un Cercle" << endl; }
};
class Carre : public Forme {
public:
    void afficher() const override { cout << "Je suis un Carre" << endl; }
};
class Triangle : public Forme {
public:
    void afficher() const override { cout << "Je suis un Triangle" << endl; }
};

// ---- Fabrique simple : choix selon un paramètre ----
class FabriqueForme {
public:
    static unique_ptr<Forme> creer(const string& type) {
        if (type == "cercle")   return make_unique<Cercle>();
        if (type == "carre")    return make_unique<Carre>();
        if (type == "triangle") return make_unique<Triangle>();
        throw invalid_argument("Forme inconnue : " + type);
    }
};

// ---- Version modulaire : fabrique abstraite (Factory Method classique) ----
class FabriqueAbstraite {
public:
    virtual unique_ptr<Forme> creer() const = 0;
    virtual ~FabriqueAbstraite() = default;
};
class FabriqueCercle : public FabriqueAbstraite {
public:
    unique_ptr<Forme> creer() const override { return make_unique<Cercle>(); }
};
class FabriqueCarre : public FabriqueAbstraite {
public:
    unique_ptr<Forme> creer() const override { return make_unique<Carre>(); }
};
class FabriqueTriangle : public FabriqueAbstraite {
public:
    unique_ptr<Forme> creer() const override { return make_unique<Triangle>(); }
};

int main() {
    cout << "--- Fabrique simple ---" << endl;
    for (string t : {"cercle", "carre", "triangle", "hexagone"}) {
        try {
            FabriqueForme::creer(t)->afficher();
        } catch (const exception& e) {
            cout << "Erreur : " << e.what() << endl;
        }
    }

    cout << "\n--- Fabrique abstraite ---" << endl;
    vector<unique_ptr<FabriqueAbstraite>> fabriques;
    fabriques.push_back(make_unique<FabriqueCercle>());
    fabriques.push_back(make_unique<FabriqueCarre>());
    fabriques.push_back(make_unique<FabriqueTriangle>());
    for (const auto& f : fabriques) f->creer()->afficher();
    return 0;
}
