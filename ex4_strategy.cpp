// Exercice 4 : Patron Stratégie - tri de chaînes
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class StrategieTri {
public:
    virtual void trier(vector<string>& v) const = 0;
    virtual string nom() const = 0;
    virtual ~StrategieTri() = default;
};

class TriCroissant : public StrategieTri {
public:
    void trier(vector<string>& v) const override { sort(v.begin(), v.end()); }
    string nom() const override { return "Croissant"; }
};
class TriDecroissant : public StrategieTri {
public:
    void trier(vector<string>& v) const override { sort(v.begin(), v.end(), greater<string>()); }
    string nom() const override { return "Decroissant"; }
};
class TriParLongueur : public StrategieTri {
public:
    void trier(vector<string>& v) const override {
        stable_sort(v.begin(), v.end(),
                    [](const string& a, const string& b) { return a.size() < b.size(); });
    }
    string nom() const override { return "Par longueur"; }
};

class GestionnaireTri {
private:
    unique_ptr<StrategieTri> strategie;
public:
    explicit GestionnaireTri(unique_ptr<StrategieTri> s) : strategie(move(s)) {}
    void setStrategie(unique_ptr<StrategieTri> s) { strategie = move(s); } // changement à l'exécution

    void executer(vector<string> donnees) const {   // copie : l'original reste intact
        strategie->trier(donnees);
        cout << strategie->nom() << " : ";
        for (const auto& s : donnees) cout << s << " ";
        cout << endl;
    }
};

int main() {
    vector<string> mots = {"banane", "kiwi", "pomme", "fraise", "fig", "abricot"};
    cout << "Original     : ";
    for (const auto& m : mots) cout << m << " ";
    cout << "\n\n";

    GestionnaireTri g(make_unique<TriCroissant>());
    g.executer(mots);
    g.setStrategie(make_unique<TriDecroissant>());
    g.executer(mots);
    g.setStrategie(make_unique<TriParLongueur>());
    g.executer(mots);
    return 0;
}
