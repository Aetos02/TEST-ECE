#include <iostream>

using namespace std;

int main()
{
    bool VouF=false;
    std::string MdP="25042002",Id="Bapt",Login,Password;

    do
    {
        std::cout<< std::endl << "Saisir Identifiant : " ;
        std::cin >> Login;
        std::cout << std::endl<< "Saisir mot de passe : ";
        std::cin >> Password;
        if(Password==MdP&&Id==Login)
        {
            VouF=true;
            std::cout << "Acces autorise";
        }
        else
        {
            VouF=false;
            std::cout << "Acces refuse";
        }
    }while(VouF!=true);

    return 0;

}
