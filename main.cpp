#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
class Sommet{
    private :
        int m_num;
        int m_couleur;
        Sommet* m_predecesseur;
        ///chaque sommet possède la liste de ses successeurs (un vecteur de pointeurs sur Sommet)
        std::vector< Sommet*> m_successeurs;

    public :
        /*constructeur*/
        Sommet(int num):m_num{num},m_couleur(0){};
        /*accesseurs*/
        int getNum()const{return m_num;}
        int getCouleur()const{return m_couleur;}
        Sommet* getPredecesseur()const{return m_predecesseur;}
        void setCouleur(int couleur){m_couleur=couleur;}
        void setPredecesseur(Sommet* predecesseur){m_predecesseur=predecesseur;}
        ///accesseur : pour la liste des successeurs
        const std::vector< Sommet*>& getSuccesseurs()const {return m_successeurs;}
        /* pour ajouter un successeur à la liste*/
        void ajouterSucc( Sommet*s){
            m_successeurs.push_back(s);
        }
        /* méthode d'affichage*/
        void afficher() const{
            std::cout<<"     sommet "<<m_num<<" : ";
            for (auto s : m_successeurs)
            {
                std::cout<<s->getNum()<<" ";
            }
        }

};
class Graphe{
    private :
        ///liste des sommets (vecteur de pointeurs sur Sommet)
        std::vector<Sommet*> m_sommets;
        int m_orientation;
    public :
        /* La construction du réseau peut se faire à partir d'un fichier
         dont le nom est passé en paramètre
        Le fichier contient : orientation (0 ou 1), ordre, taille, liste des arcs */
        Graphe(std::string nomFichier)
        {
            std::ifstream ifs{nomFichier};
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
            ifs >> m_orientation;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture orientation du graphe");
            int ordre;
            ifs >> ordre;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");
            int taille;
            ifs >> taille;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture taille du graphe");
            for (int i=0; i<ordre; ++i)
                m_sommets.push_back( new Sommet{i} );
            int num1,num2;
            for (int i=0;i<taille;++i){
                ifs>>num1>>num2;
                if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture arc");
                m_sommets[num1]->ajouterSucc(m_sommets[num2]);
                ///si le graphe n'est pas orienté
                ///si num2 est successeur de num1, num1 est successeur de num2
                if(!m_orientation) m_sommets[num2]->ajouterSucc(m_sommets[num1]);
            }
        }
        /*destructeur*/
        ~Graphe()
        {
            for (auto s : m_sommets)
                delete s;
        }
        /*méthode d'affichage*/
        void afficher() const{
            std::cout<<std::endl<<"graphe ";
            if(m_orientation) std::cout<<"oriente"<<std::endl<<"  ";
            else std::cout<<"non oriente"<<std::endl<<"  ";
            std::cout<<"ordre = "<<m_sommets.size()<<std::endl<<"  ";
            std::cout<<"listes d'adjacence :"<<std::endl;
            for (auto s : m_sommets){
                    s->afficher();
                    std::cout<<std::endl;
            }
        }
        void Initilisation()
        {
            int initial;
            std::queue<Sommet*>file;
            std::stack<Sommet*>pile;

            std::cout<<"Saisir le sommet initial : ";
            std::cin>>initial;
            std::cout<<"Le sommet initial est : "<<initial<<std::endl;



            m_sommets[initial]->afficher();
            m_sommets[initial]->setCouleur(1);
            m_sommets[initial]->setPredecesseur(NULL);
            file.push(m_sommets[initial]);
            pile.push(m_sommets[initial]);

            DFS(pile);
            BFS(file);

            for (auto s : m_sommets){
            if(s->getCouleur()==2)
            {
                std::cout<<std::endl;
                Resultat(s);
            }
    }

        }
        void BFS(std::queue<Sommet*>file)
        {
            for(auto elem:file.front()->getSuccesseurs())
            {
                if(elem->getCouleur()==0)
                {
                    elem->setCouleur(1);
                    elem->setPredecesseur(file.front());
                    file.push(elem);
                }
            }
            file.front()->setCouleur(2);
            std::cout<<file.front()->getNum()<<" ";
            file.pop();

            if(!file.empty())
               BFS(file);
        }
        void DFS(std::stack<Sommet*>pile)
        {
            Sommet*stockage;
            pile.top()->setCouleur(2);
            std::cout<<pile.top()->getNum();
            stockage=pile.top();
            pile.pop();

            for(auto elem:stockage->getSuccesseurs())
            {
                if(elem->getCouleur()==0)
                {
                    elem->setCouleur(1);
                    elem->setPredecesseur(stockage);
                    pile.push(elem);
                }
            }
            if(!pile.empty())
               DFS(pile);
        }

        void Resultat(Sommet* sommet)
        {
            std::cout<<sommet->getNum();
            if(sommet->getPredecesseur()!=NULL)
            {
                std::cout<<"<--";
                Resultat(sommet->getPredecesseur());
            }
        }

        void Connexe()
        {
            std::queue<Sommet*>file;
            for(auto elem: m_sommets)
            {
                if(elem->getCouleur()!=2)
                {
                    file.push(elem);
                    std::cout<<"Composante connexe : ";
                    BFS(file);
                    std::cout<<std::endl;
                    file.pop();
                }
            }
        }
};

int main()
{
    Graphe g{"graphe1_TP2.txt"};
    ///appel de la méthode pour afficher le graphe

    //g.Initilisation();
    g.Connexe();
    /// afficher le graphe
    g.afficher();

    return 0;
}
