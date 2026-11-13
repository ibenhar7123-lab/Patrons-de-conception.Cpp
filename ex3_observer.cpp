// Exercice 3 : Patron Observateur - station météo
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// Interface : le sujet ne connaît que cette abstraction
class Observateur {
public:
    virtual void mettreAJour(float temperature, float humidite, float pression) = 0;
    virtual ~Observateur() = default;
};

class StationMeteo {
private:
    vector<Observateur*> observateurs;                          // approche classique
    vector<function<void(float, float, float)>> abonnes;        // alternative moderne
    float temperature = 0, humidite = 0, pression = 0;

    void notifier() {
        for (auto* o : observateurs) o->mettreAJour(temperature, humidite, pression);
        for (auto& f : abonnes) f(temperature, humidite, pression);
    }

public:
    void ajouter(Observateur* o) { observateurs.push_back(o); }
    void retirer(Observateur* o) {
        observateurs.erase(remove(observateurs.begin(), observateurs.end(), o), observateurs.end());
    }
    void abonner(function<void(float, float, float)> f) { abonnes.push_back(move(f)); }

    void setMesures(float t, float h, float p) {
        temperature = t; humidite = h; pression = p;
        notifier();
    }
};

class AffichageTemperature : public Observateur {
public:
    void mettreAJour(float t, float, float) override {
        cout << "[Temperature] " << t << " C" << endl;
    }
};
class AffichageHumidite : public Observateur {
public:
    void mettreAJour(float, float h, float) override {
        cout << "[Humidite]    " << h << " %" << endl;
    }
};
class AffichagePression : public Observateur {
public:
    void mettreAJour(float, float, float p) override {
        cout << "[Pression]    " << p << " hPa" << endl;
    }
};

int main() {
    StationMeteo station;
    AffichageTemperature aT;
    AffichageHumidite aH;
    AffichagePression aP;

    station.ajouter(&aT);
    station.ajouter(&aH);
    station.ajouter(&aP);

    cout << "--- Mesure 1 ---" << endl;
    station.setMesures(25.5f, 60.0f, 1013.0f);

    cout << "\n--- On retire l'affichage humidite ---" << endl;
    station.retirer(&aH);
    station.setMesures(27.0f, 55.0f, 1010.0f);

    cout << "\n--- Abonne moderne (lambda / std::function) ---" << endl;
    station.abonner([](float t, float, float) {
        if (t > 30) cout << "[Alerte] Canicule !" << endl;
        else cout << "[Lambda] Temperature normale (" << t << ")" << endl;
    });
    station.setMesures(35.0f, 40.0f, 1005.0f);
    return 0;
}
