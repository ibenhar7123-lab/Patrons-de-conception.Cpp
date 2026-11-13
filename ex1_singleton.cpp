// Exercice 1 : Patron Singleton - classe Configuration
#include <iostream>
#include <string>
using namespace std;

class Configuration {
private:
    string cheminFichier;
    string utilisateur;
    string motDePasse;

    // Constructeur privé : personne d'autre ne peut créer d'instance
    Configuration()
        : cheminFichier("/etc/app/config.ini"), utilisateur("admin"), motDePasse("secret") {
        cout << "(Configuration creee)" << endl;
    }

public:
    // Suppression de la copie et de l'affectation
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    // Singleton de Meyers : variable statique locale.
    // Depuis C++11, son initialisation est garantie thread-safe.
    static Configuration& getInstance() {
        static Configuration instance;
        return instance;
    }

    void setCheminFichier(const string& c) { cheminFichier = c; }
    void setUtilisateur(const string& u) { utilisateur = u; }
    void setMotDePasse(const string& m) { motDePasse = m; }

    void afficherParametres() const {
        cout << "Fichier     : " << cheminFichier << endl;
        cout << "Utilisateur : " << utilisateur << endl;
        cout << "Mot de passe: " << string(motDePasse.size(), '*') << endl;
    }
};

int main() {
    Configuration& c1 = Configuration::getInstance();
    c1.afficherParametres();

    Configuration& c2 = Configuration::getInstance();
    c2.setUtilisateur("khalid");   // modifié via c2...
    cout << "\nApres modification via c2 :" << endl;
    c1.afficherParametres();       // ...visible via c1

    cout << "\nMeme instance ? " << (&c1 == &c2 ? "oui" : "non") << endl;

    // Configuration c3;                 // ERREUR : constructeur privé
    // Configuration c4 = c1;            // ERREUR : copie supprimée
    return 0;
}
