#include <iostream>
#include <thread>
#include <chrono>
#include <queue>
#include <vector>
#include <map>

class Salle{
    private:
        int id;
        std::string nom;
        int capacite;
        int nb_fourmis;

    public:
        Salle(int id_s, const char* n, int cap) : id(id_s), nom(n), capacite(cap), nb_fourmis(0) {} // Constructeur par défaut

        int getid(){
            return id;
        }

        std::string getnom(){
            return nom;
        }

        int getcapacite(){
            return capacite;
        }

        int getnb_fourmis(){
            return nb_fourmis;
        }

        void ajouter_fourmi(){
            nb_fourmis++;
        }

        void retirer_fourmi(){
            nb_fourmis--;
        }
};

class Chemin{
    private:
        int id;
        Salle* salle1;
        Salle* salle2;

    public:
        Chemin(int id_c, Salle* s1, Salle* s2) : id(id_c), salle1(s1), salle2(s2) {}

        Salle* getsalle1(){
            return salle1;
        }

        Salle* getsalle2(){
            return salle2;
        }

        int getid(){
            return id;
        }
};

class Fourmi{
    private:
        int id;
        int position;
        Salle* salle;
    
    public:
        Fourmi(int id_f) : id(id_f), position(0), salle(nullptr) {} // Constructeur par défaut

        int getid(){
            return id;
        }

        int getposition(){
            return position;
        }

        void avancerPosition() {
            position++;
        }

        int changerSalle(Salle* nouvelleSalle, Chemin* chemins[], int nbChemins) {
            // Si la fourmi n'est dans aucune salle, on l'ajoute directement
            if (salle == nullptr) {
                nouvelleSalle->ajouter_fourmi();
                salle = nouvelleSalle;
                std::cout << "Fourmi" << id << "placée dans la salle initiale." << std::endl;
                return 1;
            }
            else {
                // Sinon, on vérifie l'existence d'un chemin
                bool cheminExiste = false;
                for (int i = 0; i < nbChemins; ++i) {
                    if ((chemins[i]->getsalle1() == salle && chemins[i]->getsalle2() == nouvelleSalle) ||
                        (chemins[i]->getsalle2() == salle && chemins[i]->getsalle1() == nouvelleSalle)) {
                        cheminExiste = true;
                        break;
                    }
                }
                if (!cheminExiste) {
                    return 0;
                }
                if (nouvelleSalle->getnb_fourmis() >= nouvelleSalle->getcapacite()) {
                    return 0;
                }
                if (salle != nullptr) {
                    salle->retirer_fourmi();
                }
                nouvelleSalle->ajouter_fourmi();
                salle = nouvelleSalle;
                std::cout << "Fourmi" << id << "déplacée dans la salle : " << nouvelleSalle->getnom() << std::endl;
                return 1;
            }
        }

        Salle* getsalle() { return salle; }
};

std::vector<Salle*> trouverParcours(Salle* depart, Salle* arrivee, Chemin* chemins[], int nbChemins) {
    std::queue<Salle*> q;
    std::map<Salle*, Salle*> precedent;
    q.push(depart);
    precedent[depart] = nullptr;

    while (!q.empty()) {
        Salle* courant = q.front();
        q.pop();

        if (courant == arrivee) break;

        for (int i = 0; i < nbChemins; ++i) {
            Salle* voisin = nullptr;
            if (chemins[i]->getsalle1() == courant)
                voisin = chemins[i]->getsalle2();
            else if (chemins[i]->getsalle2() == courant)
                voisin = chemins[i]->getsalle1();

            if (voisin && precedent.find(voisin) == precedent.end()) {
                precedent[voisin] = courant;
                q.push(voisin);
            }
        }
    }

    // Reconstruire le chemin
    std::vector<Salle*> parcours;
    Salle* courant = arrivee;
    while (courant && courant != depart) {
        parcours.insert(parcours.begin(), courant);
        courant = precedent[courant];
    }
    if (courant == depart)
        parcours.insert(parcours.begin(), depart);

    return parcours;
}

int main(){
    int fourmis = 3;
    int n = 1;

    // Création des salles
    Salle sv(1, "Sv", 50);
    Salle s2(2, "S1", 1);
    Salle s3(3, "S2", 1);
    Salle sd(4, "Sd", 50);

    // Création des chemins
    Chemin c1(1, &sv, &s2);
    Chemin c2(2, &sv, &s3);
    Chemin c3(3, &s2, &sd);
    Chemin c4(4, &s3, &sd);

    Chemin* chemins[] = { &c1, &c2, &c3, &c4};

    Fourmi f1(1);
    Fourmi f2(2);
    Fourmi f3(3);

    Fourmi* fourmisTab[] = { &f1, &f2, &f3 };  

    for (int i = 0; i < fourmis; i++) {
        fourmisTab[i]->changerSalle(&sv, chemins, 3);
    }

    // Tableau des étapes à suivre pour chaque fourmi
    std::vector<Salle*> parcours = trouverParcours(&sv, &sd, chemins, 4);

    while (sd.getnb_fourmis() < fourmis) {
        std::cout << "+++++Etape" << n << "+++++" << std::endl;
        for (int i = 0; i < fourmis; i++) {
            // Calculer le chemin optimal depuis la salle actuelle de la fourmi
            std::vector<Salle*> parcours = trouverParcours(fourmisTab[i]->getsalle(), &sd, chemins, 4);
            if (parcours.size() > 1) {
                // Essayer la salle optimale d'abord
                Salle* prochaineSalle = parcours[1];
                if (fourmisTab[i]->changerSalle(prochaineSalle, chemins, 4) == 1) {
                    fourmisTab[i]->avancerPosition();
                    continue;
                }
                // Sinon, essayer les autres voisines qui rapprochent du dortoir
                Salle* salleActuelle = fourmisTab[i]->getsalle();
                for (int j = 0; j < 4; j++) {
                    Salle* voisin = nullptr;
                    if (chemins[j]->getsalle1() == salleActuelle)
                        voisin = chemins[j]->getsalle2();
                    else if (chemins[j]->getsalle2() == salleActuelle)
                        voisin = chemins[j]->getsalle1();

                    // Vérifie que le voisin est sur un chemin vers le dortoir et n'est pas la salle actuelle
                    std::vector<Salle*> parcoursVoisin = trouverParcours(voisin, &sd, chemins, 4);
                    if (voisin && voisin != salleActuelle && parcoursVoisin.size() > 0) {
                        if (fourmisTab[i]->changerSalle(voisin, chemins, 4) == 1) {
                            fourmisTab[i]->avancerPosition();
                            break;
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        n++;
    }

    return 0;
}

//Penser a ajouter une fonction pour vérifier le chemin le plus optimiser vers le dortoir (Sd) depuis une salle

// Placement initial dans la salle A
//    f1.changerSalle(&s1, chemins, 3);
//    f2.changerSalle(&s1, chemins, 3);
//    f3.changerSalle(&s1, chemins, 3);

    // Étape 1 : Salle A -> Salle B
//    f1.changerSalle(&s2, chemins, 3);
//    f2.changerSalle(&s2, chemins, 3);
//    f3.changerSalle(&s2, chemins, 3);

    // Étape 2 : Salle B -> Salle C
//    f1.changerSalle(&s3, chemins, 3);
//    f2.changerSalle(&s3, chemins, 3);
//    f3.changerSalle(&s3, chemins, 3);

    // Étape 3 : Salle C -> Dortoir
//    f1.changerSalle(&s4, chemins, 3);
//    f2.changerSalle(&s4, chemins, 3);
//    f3.changerSalle(&s4, chemins, 3);