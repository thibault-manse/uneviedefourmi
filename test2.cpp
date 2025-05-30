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

        int changerSalle(Salle* nouvelleSalle, Chemin* chemins[], int nbChemins, Salle* salleDepart) {
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
                std::cout << "f" << id << " - " << salle->getnom() << " - " << nouvelleSalle->getnom() << std::endl;
                nouvelleSalle->ajouter_fourmi();
                salle = nouvelleSalle;
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
    int fourmis = 50;
    int n = 1;

    // Création des salles
    Salle sv(1, "Sv", 50);
    Salle s1(2, "S1", 8);
    Salle s2(3, "S2", 4);
    Salle s3(4, "S3", 2);
    Salle s4(5, "S4", 4);
    Salle s5(6, "S5", 2);
    Salle s6(7, "S6", 4);
    Salle s7(8, "S7", 2);
    Salle s8(9, "S8", 5);
    Salle s9(10, "S9", 1);
    Salle s10(11, "S10", 1);
    Salle s11(12, "S11", 1);
    Salle s12(13, "S12", 1);
    Salle s13(14, "S13", 4);
    Salle s14(15, "S14", 2);
    Salle sd(16, "Sd", 50);

    // Création des chemins
    Chemin c1(1, &s1, &s2);
    Chemin c2(2, &s2, &s3);
    Chemin c3(3, &s3, &s4);
    Chemin c4(4, &s4, &sd);
    Chemin c5(5, &sv, &s1);
    Chemin c6(6, &s2, &s5);
    Chemin c7(7, &s5, &s4);
    Chemin c8(8, &s13, &sd);
    Chemin c9(9, &s8, &s12);
    Chemin c10(10, &s12, &s13);
    Chemin c11(11, &s6, &s7);
    Chemin c12(12, &s7, &s9);
    Chemin c13(13, &s9, &s14);
    Chemin c14(14, &s14, &sd);
    Chemin c15(15, &s7, &s10);
    Chemin c16(16, &s10, &s14);
    Chemin c17(17, &s1, &s6);
    Chemin c18(18, &s6, &s8);
    Chemin c19(19, &s8, &s11);
    Chemin c20(20, &s11, &s13);

    Chemin* chemins[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10,
                          &c11, &c12, &c13, &c14, &c15, &c16, &c17, &c18, &c19, &c20 };

    Fourmi** fourmisTab = new Fourmi*[fourmis];
    for (int nb = 0; nb < fourmis; nb++){
        fourmisTab[nb] = new Fourmi(nb + 1);
    }

    for (int i = 0; i < fourmis; i++) {
        fourmisTab[i]->changerSalle(&sv, chemins, 20, &sv);
    }

    // Tableau des étapes à suivre pour chaque fourmi
    std::vector<Salle*> parcours = trouverParcours(&sv, &sd, chemins, 20);

    while (sd.getnb_fourmis() < fourmis) {
        std::cout << "+++++Etape" << n << "+++++" << std::endl;
        for (int i = 0; i < fourmis; i++) {
            // Calculer le chemin optimal depuis la salle actuelle de la fourmi
            std::vector<Salle*> parcours = trouverParcours(fourmisTab[i]->getsalle(), &sd, chemins, 20);
            if (parcours.size() > 1) {
                // Essayer la salle optimale d'abord
                Salle* prochaineSalle = parcours[1];
                if (fourmisTab[i]->changerSalle(prochaineSalle, chemins, 20, &sv) == 1) {
                    fourmisTab[i]->avancerPosition();
                    continue;
                }
                // Sinon, essayer les autres voisines qui rapprochent du dortoir
                Salle* salleActuelle = fourmisTab[i]->getsalle();
                for (int j = 0; j < 20; j++) {
                    Salle* voisin = nullptr;
                    if (chemins[j]->getsalle1() == salleActuelle)
                        voisin = chemins[j]->getsalle2();
                    else if (chemins[j]->getsalle2() == salleActuelle)
                        voisin = chemins[j]->getsalle1();

                    // Vérifie que le voisin est sur un chemin vers le dortoir et n'est pas la salle actuelle
                    std::vector<Salle*> parcoursVoisin = trouverParcours(voisin, &sd, chemins, 4);
                    if (voisin && voisin != salleActuelle && voisin != &sv && parcoursVoisin.size() > 0) {
                        if (fourmisTab[i]->changerSalle(voisin, chemins, 20, &sv) == 1) {
                            fourmisTab[i]->avancerPosition();
                            break;
                        }
                    }
                }
            }
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        n++;
    }

    return 0;
}