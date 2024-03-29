/*************************************************************************
   Stats  -  Classe gérant les statistiques de l'analyse de logs apache
                             -------------------
début                : 21/01/2020
copyright            : (C) 2020 par GRAVEY Thibaut & CHEN Gong
e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Stats> (fichier Stats.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Stats::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

void Stats::AjouterInfo (Informations & info)
// Algorithme : Utilisation de deux maps et une paire comme une structure de donnees
// pour stock les cibles et les referers et le nombres de hits correspondants.
{
    MapCibles[info.URL].MapReferers[info.referer]++;
    MapCibles[info.URL].NbHitTotal++;
}


void Stats::AffichageTop10()
// Algorithme : on cherche le NbHitTotal max dans le map MapCibles,
//  on l'enregistre dans un tableau, ensuite on remplace le NbHitTotal par 0,
//  a la fin de l'execution, on remet les valeurs  de NbHitTotal
//  but: eviter de verifier chaque fois si l'element existe deja dans myTop10 (complexité)
{
    CiblesTop10 myTop10(10);
    Map_Cibles_Pairs::iterator it;
    int NbHitTotalTop10  [10]= {0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 10; i++){
        for(it = MapCibles.begin(); it != MapCibles.end(); it++){
            if(it->Pair.NbHitTotal > NbHitTotalTop10[i]){
                myTop10[i] = it->NameCible;
                NbHitTotalTop10[i] = it->Pair.NbHitTotal;
            }
        }
        MapCibles[ myTop10[i] ].NbHitTotal = -1;
    }

    for(int j = 0; j < 10; j++){
       MapCibles[myTop10[j]].NbHitTotal = NbHitTotalTop10[j];
   }


    int n = 0;

    cout<<"Top 10 targets :"<<endl;
    for(int i = 0; i < 10 ; i++){
        if(NbHitTotalTop10[i] == 0 ){
            cout<<"No more targets in this case"<<endl;
            break;
        }
        n++;
        cout<<n<<"° :  "<<myTop10[i]<<"    (Total hits : "<<NbHitTotalTop10[i]<<" ) "<<endl;
    }
}

//------------------------------------------------- Surcharge d'opérateurs
Stats & Stats::operator = ( const Stats & unStats )
// Algorithme :
// Utilisation de l'opérateur d'affectation de la map de STL. Fourni une copie.
{
    if(this!=&unStats)
    {
        MapCibles.clear();
        MapCibles = unStats.MapCibles;
    }
    return *this;
} //----- Fin de operator =

ostream & operator << (ostream & os, Stats & unStats)
// Algorithme :
// Utilisation de l'opérateur << de l'ostream en utilisant des iterateurs pour parcourir notre structure
{
    Map_Cibles_Pairs::iterator IterCibles;
    Map_Referers_NbHit::iterator IterReferers;
    int n = 0;
    for(IterCibles =unStats.GetMapCibles().begin(); IterCibles !=unStats.GetMapCibles().end(); IterCibles++ ){
        os <<"*************************Cible et son nombre de hit total*************************" <<endl;
        os << "****** \"" << IterCibles->NameCible << "\"   \" Nombre de hit total: "  << IterCibles->Pair.NbHitTotal  << "\" ******"<<endl;
        os <<"*************************Referers correspondant - debut*************************" <<endl;
            for(IterReferers=IterCibles->Pair.MapReferers.begin(); IterReferers != IterCibles->Pair.MapReferers.end(); IterReferers++ ){
                n++;
               os<< "\"le "<<n<<"° referer: "<< IterReferers->NameRefere << "\" "<<"Nombre de hit correspondant: "<<  IterReferers->NbHit << "\""<<endl;
            }
        os <<"*************************Referers correspondant - fin*************************" <<endl;
        n = 0;
        os<<endl<<endl;
    }
    return os;
} //----- Fin de operator <<

Map_Cibles_Pairs & Stats::GetMapCibles(){
    return MapCibles;
}

//-------------------------------------------- Constructeurs - destructeur
Stats::Stats (const Stats & unStats )
// Algorithme :
// Utilisation de l'opérateur d'affectation de la map STL (fait bien une copie)
{

    MapCibles=unStats.MapCibles;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Stats>" << endl;
#endif
} //----- Fin de Stats (constructeur de copie)


Stats::Stats ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Stats>" << endl;
#endif
} //----- Fin de Stats


Stats::~Stats ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin de Stats

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
