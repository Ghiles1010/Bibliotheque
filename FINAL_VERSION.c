#include<stdio.h>
#include<stdlib.h>
#include <string.h>
 



FILE *fichier;  



                                 ///**************LES   TYPES********************///

////////////////////////////////////////////////////////////
typedef struct emprunteur{

    char nom[16];
    char prenom[16];
    struct emprunteur *svt;

}emprunteur;

//////////////////////////////////////////////////////////

typedef struct Femprunteur{

    char nom[16];
    char prenom[16];

    struct Femprunteur *svt;
    struct Femprunteur *prcd;

}Femprunteur;

//////////////////////////////////////////////////////////
typedef struct E_BD_empr{

    struct Femprunteur *T_fempr;
    struct Femprunteur *Q_fempr;


}E_BD_emp;

//////////////////////////////////////////////////////////
typedef struct livre{

    char *titre;
    char *auteur;
    int nbtot;
    int nbdisp;

    struct emprunteur *Tempreunteur;
    struct E_BD_empr BD_empr;

    struct livre *svt;
    struct livre *prcd;

}livre;
//////////////////////////////////////////////////////////
typedef struct BD_lettre{

    struct livre *Ltete;
    struct livre *Lqueue;

}BD_lettre;



//////////////////////////////////////////////////////////




                 ///**************LES   FONCIONS********************///

//////////////////////////////////////////////////////////
livre *creer_livre(char titre[],char auteur [],int nbt,int nbd){
    livre *p;

    p=(livre*)malloc(sizeof(livre));

    if(p==NULL){
        printf("il ny a plus d'espace pour ajouter un livre.\n");

        exit(EXIT_FAILURE);




    }

    p->auteur=(char*)malloc(sizeof( strlen(auteur)));
    strcpy(p->auteur,auteur);

    //allocation dynamique du titre.


    p->titre=(char*)malloc(sizeof( strlen(titre)));
    strcpy(p->titre,titre);

    // lecture de nbdisp et nbtot


    p->nbtot=nbt;


    p->nbdisp=nbd;

    p->Tempreunteur=NULL;
    p->BD_empr.Q_fempr=NULL;
    p->BD_empr.T_fempr=NULL;


    return p;

}
///////////////////////////////////////////////////////////
int priorite_alpha(char x1[], char x2[]) { //retourne 1 si pri(x1)<pri(x2), 2 si = , 0 sinon;

    int i = 0;

    if (strcmp(x1, x2) == 0) {
        return 2;
    }

    while (x1[i] == x2[i]) {
        i++;
    }

    if ((x1[i] == '\0') || (x1[i] < x2[i])) {
        return 1;
    }

    if ((x2[i] == '\0') || (x2[i] < x1[i])) {
        return 0;
    }



}
//////////////////////////////////////////////////////////
void ajouter_livre_tete(BD_lettre *tq,livre *l){




    if(tq->Ltete==NULL){

        tq->Ltete=l;
        tq->Lqueue=l;

        l->svt=NULL;
        l->prcd=NULL;



    }
    else{

        l->svt=tq->Ltete;
        tq->Ltete->prcd=l;
        l->prcd=NULL;
        tq->Ltete=l;

    }

}
//////////////////////////////////////////////////////////
void ajouter_livre_apres(BD_lettre *tq,livre *l,livre *p){


    p->svt=l->svt;
    p->prcd=l;
    l->svt=p;

    if(p->svt==NULL){
        tq->Lqueue=p;

    }
    else{
        p->svt->prcd=p;
    }


}
////////////////////////////////////////////////////////
void inserer_livre_pos(BD_lettre v[],livre *l){
    int pos; char x[30]; livre *p;

    strcpy(x,l->titre);
    strlwr(x);

    pos=x[0]-97;

    p=v[pos].Ltete;

    if(v[pos].Ltete==NULL){
        ajouter_livre_tete(&v[pos],l);

    }

    else{                             //retourne 1 si pri(x1)<pri(x2), 2 si = , 0 sinon;

        while( (p!=NULL) && (priorite_alpha(x,p->titre)==0) ){
            p = p->svt;
        }
        if(p==NULL){
            ajouter_livre_apres(&v[pos],v[pos].Lqueue,l);

        }
        else {

            if (p == v[pos].Ltete) {
                ajouter_livre_tete(&v[pos], l);

            } else {

                ajouter_livre_apres(&v[pos], p->prcd, l);

            }
        }

    }
    printf("Livre ajoute avec succes!\n");
    printf("attention! vous devez quitter le programme en choisissant 7 dans le menu\npour que le livre se sauvegrade sur votre ordinateur\n\n");

}
/////////////////////////////////////////////////////////
void ajouter_nv_livre (BD_lettre v[] ){   //A=65...Z=90//a=97...z=122 en ascii
    char tit[30],aut[30]; int nbt,nbd,nbr,pos;



    livre*p;





        printf("Entrez le titre du livre: ");
        scanf("%s", tit);
        ///////////////////////////////
        strlwr(tit);
        pos = tit[0] - 97;
        p = v[pos].Ltete;

        while ((p != NULL) && (strcmp(tit, p->titre) != 0)) {
            p = p->svt;
        }

        if (p != NULL) {

            printf("ce livre existe deja vous pouvez ajouter une copie en choisissant 3 dans le menu\n");
            nbr=0;
        }

        else {


            ///////////////////////////////

            strlwr(tit);
            printf("Entrez l'auteur du livre: ");
            scanf("%s", aut);
            printf("Entrez le nombre total de copie de ce livre que vous voulez ajouter :");
            scanf("%d", &nbt);
            nbd = nbt;


            p = creer_livre(tit, aut, nbt, nbd);

            inserer_livre_pos(v, p);

            nbr = nbr - 1;


        }



}
////////////////////////////////////////////////////////
void ajouter_emprunteur (char name[],char prenom[],livre *l){

    emprunteur *e;
    e=(emprunteur*) malloc( sizeof(emprunteur));

    printf("%s",name);


    strcpy(e->nom,name);

    strcpy(e->prenom,prenom);

    e->svt=l->Tempreunteur;
    l->Tempreunteur=e;




}
//////////////////////////////////////////////////////////
void ajouter_copie_livre(BD_lettre v[]){

    char x[30]; int pos,n; livre *p; char c; Femprunteur *fe;

    printf("Entrez le titre de la copie du livre que vous voulez ajouter: "); scanf("%s",&x); strlwr(*x);
    printf("Entrez la quantite que vous voulez ajouter: "); scanf("%d",&n);
    pos=x[0]-97;

    p=v[pos].Ltete;

    while((p!=NULL)&&(strcmp(strlwr(x),p->titre)!=0)){
        p=p->svt;
    }
    if(p==NULL){

        printf("Ce livre n'existe pas dans votre bibliotheque.\n Voulez vous l'ajouter? (O/N): ");
        scanf("%c",&c);

        while((c!='o')&&(c!='O')&&(c!='N')&&(c!='n')){

            printf("repondez par 'O' pour dire ''OUI'' et 'N' pour dire ''NON'': ");
            scanf("%c",&c);

        }
        if((c=='O')||(c=='o')){
            system("cls");
            ajouter_nv_livre(v);

        }

    }
    else {

        p->nbtot = p->nbtot + n;

        if(p->nbdisp==0){
            printf("\nIl y a des personnes en liste d'attentepour emprunter ce livre.\n");
            printf("Ces personnes vont basculer de la listte d'attente a la liste d'emprunteur de ce livre\n");
            system("pause");

            while((n>0)&&(p->BD_empr.T_fempr!=NULL)) {

                ////on l'ajoute sur la liste d'emprunteur et on desemfile

                ajouter_emprunteur(p->BD_empr.T_fempr->nom, p->BD_empr.T_fempr->prenom, p);


                if (p->BD_empr.T_fempr == p->BD_empr.Q_fempr) {

                    fe = p->BD_empr.Q_fempr;
                    p->BD_empr.T_fempr = NULL;
                    p->BD_empr.Q_fempr = NULL;
                    free(fe);

                } else {
                    fe = p->BD_empr.T_fempr;
                    p->BD_empr.T_fempr = p->BD_empr.T_fempr->svt;
                    p->BD_empr.T_fempr->prcd = NULL;
                    free(fe);




                }
                n=n-1;
            }
        }

        p->nbdisp = p->nbdisp + n;
    }


}
//////////////////////////////////////////////////////////////////////////////////
void creer_struct (BD_lettre v[]){

    int nbd,nbt,i=0,j=0,pos;        livre *p;
    char aut[30],tit[30];

    fichier=fopen("BIB.txt","r");

    if(fichier!=NULL){


        while( !feof(fichier) ){



            //lecture et allocation dynamique de l'auteur.

            fscanf(fichier,"%s",tit);


            ///lecture du titre.

            fscanf(fichier,"%s",aut);


            /// lecture de nbdisp et nbtot

            fscanf(fichier,"%d",&nbt);


            fscanf(fichier,"%d",&nbd);

            ///creatoion du livre

            p=creer_livre(tit,aut,nbt,nbd);



            strlwr(tit);
            pos=tit[0]-97;



            if(v[pos].Ltete==NULL){

                v[pos].Lqueue=p;
                v[pos].Ltete=p;
                p->svt=NULL;
                p->prcd=NULL;


            }
            else{
                p->prcd=v[pos].Lqueue;
                p->svt=NULL;
                v[pos].Lqueue->svt=p;
                v[pos].Lqueue=p;
            }


        }
        fclose(fichier);





    }
}
/////////////////////////////////////////////////////////
void ajouter_liste_att(livre *l,char nom[],char prenom[]){

    Femprunteur *fe;
    fe=(Femprunteur*)malloc(sizeof(Femprunteur));

    strcpy(fe->nom,nom);
    strcpy(fe->prenom,prenom);



    if(l->BD_empr.T_fempr==NULL){

        l->BD_empr.T_fempr=fe;
        l->BD_empr.Q_fempr=fe;
        fe->svt=NULL;
        fe->prcd=NULL;

    }
    else{
        fe->svt=NULL;
        fe->prcd=l->BD_empr.Q_fempr;
        l->BD_empr.Q_fempr->svt=fe;
        l->BD_empr.Q_fempr=fe;

    }





}
//////////////////////////////////////////////////////////
void emprunter(BD_lettre v[]){
    char nom[20],prenom[15],x[10],c; int pos; livre *p; emprunteur *e;

    printf("Entrez le nom de l'emprunteur: "); scanf("%s",nom);
    printf("Entrez le prenom de l'emprunteur: "); scanf("%s",prenom);
    printf("Entrez le titre du livre que M.%s souhaite emprunter: ",nom); scanf("%s",x); strlwr(x);

    pos=x[0]-97;


    p=v[pos].Ltete;

    while((p!=NULL)&&(strcmp(x,p->titre)!=0)){
        p=p->svt;
    }

    if(p==NULL){
        printf("Ce livre n'existe pas dans votre bibliothque.\n");

    }

    else {
        e = p->Tempreunteur;

        while ((e != NULL) && ( (strcmp(e->nom, nom)!=0) || (strcmp(e->prenom, prenom)!= 0) ) ) {

            e = e->svt;

        }

        if (e != NULL) {
            printf("M.%s a deja emprunte ce livre, et il ne l'a pas encore rendu.\n", nom);
        }

        else {


            if (p->nbdisp == 0) {
                printf("Toutes les copies de ce livre ont ete empruntes.\n ");
                printf("Voulez-vous mettre M.%s en liste d'attente? (O/N)\n ", nom);
                scanf("%c", &c);

                while ((c != 'o') && (c != 'O') && (c != 'N') && (c != 'n')) {

                    printf("repondez par 'O' pour dire ''OUI'' et 'N' pour dire ''NON'': ");
                    scanf("%c", &c);

                }

                if ((c == 'O') || (c == 'o')) {
                    ajouter_liste_att(p, nom, prenom);
                    printf("M.%s a ete ajoute a la liste d'attente.\n", nom);

                }

            } else {
                p->nbdisp = p->nbdisp - 1;
                ajouter_emprunteur(nom, prenom, p);
                printf("M.%s a ete ajoute a la liste des emprunteurs.\n", nom);

            }
        }

    }







}
////////////////////////////////////////////////////////////////////////////
void rendre(BD_lettre v[]){
    char nom[15],prenom [15],titre [15]; int pos; livre * p; emprunteur *q,*prcd; Femprunteur *fe;

    printf("Donner le nom de l'emprunteur: "); scanf(" %s",nom);
    printf("Donner le prenom de l'emprunteur: "); scanf(" %s",prenom);
    printf("Donner le titre du livre que M.%s a emprunte: ",nom); scanf(" %s",titre);

    strlwr(titre);
    pos=titre[0]-97;

    p=v[pos].Ltete;

    while((p!=NULL)&&( strcmp(p->titre,titre)!=0) ) {
        p = p->svt;
    }

    if(p==NULL){
        printf("Ce livre n'existe pas dans votre bibliothque.\n");

    }
    else{

        q=p->Tempreunteur;
        prcd=q;

        while((q!=NULL)&&( (strcmp(prenom,q->prenom)!=0) || (strcmp(nom,q->nom)!=0) )){

            prcd=q;
            q=q->svt;

        }
        if(q==NULL){
            printf("M.%s n'a pas emprunte ce livre.\n",nom);

        }
        else{
            p->nbdisp=p->nbdisp+1;

            if(q==p->Tempreunteur){
                free(q);
                p->Tempreunteur=NULL;
            }

            else{
                prcd->svt=q->svt;
                free(q);
            }
            printf("livre rendu avec succes.\n");
            ///// on regarde si ya des gens sur la liste d'attente de ce livre.
            if(p->BD_empr.T_fempr!=NULL){
                ////on l'ajoute sur la liste d'emprunteur et on desemfile
                printf("une personne en lise d'attente va etre bascule en liste des empruneurs.\n\n");

                ajouter_emprunteur(p->BD_empr.T_fempr->nom,p->BD_empr.T_fempr->prenom,p);
                p->nbdisp=p->nbdisp-1;

                if(p->BD_empr.T_fempr==p->BD_empr.Q_fempr) {

                    fe = p->BD_empr.Q_fempr;
                    p->BD_empr.T_fempr = NULL;
                    p->BD_empr.Q_fempr = NULL;
                    free(fe);

                }
                else{

                    fe=p->BD_empr.T_fempr;
                    p->BD_empr.T_fempr= p->BD_empr.T_fempr->svt;
                    p->BD_empr.T_fempr->prcd=NULL;
                    free(fe);

                }
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////
void liberer_empre(emprunteur *tete){

    emprunteur *p;

    while(tete!=NULL){
        p=tete;
        tete=tete->svt;
        free(p);

    }
}
//////////////////////////////////////////////////////////////////////////////
void liberer_liste_att_empr(Femprunteur *tete){
    Femprunteur *p;

    while(tete!=NULL){

        p=tete;
        tete=tete->svt;
        free(p);

    }

}
//////////////////////////////////////////////////////////////////////////////
void ecrire_fichier_et_liberer(BD_lettre v[]){
    int i;     livre *l,*p;


    fichier=fopen("BIB.txt","w+");

    for (i = 0; i < 26; i++) {

        if(v[i].Ltete!=NULL){

            l=v[i].Ltete;

            while(l!=NULL) {

                liberer_empre(l->Tempreunteur);
                liberer_liste_att_empr(l->BD_empr.T_fempr);
                fprintf(fichier, "%s\n", l->titre);
                fprintf(fichier, "%s\n", l->auteur);
                fprintf(fichier, "%d\n", l->nbtot);
                fprintf(fichier, "%d\n", l->nbdisp);

                free(l->titre);
                free(l->auteur);

                p=l;
                l=l->svt;
                free(p);
            }


        }

    }
    fclose(fichier);


}
/////////////////////////////////////////////////////////////////////////////
void init_tab(BD_lettre v[]){

    int i;

    for(i=0;i<26;i++){
        v[i].Ltete=NULL;
        v[i].Lqueue=NULL;
    }
}
/////////////////////////////////////////////////////////////////////////////
void afficher(BD_lettre v[]){
    int i=0; livre *a, *b,*c, *d; emprunteur *e; Femprunteur *fe;
    char q='k';



    while(( (i+4) <= 28)&& (q!='q')) {

        a = v[i].Ltete;
        b = v[i + 1].Ltete;

        c=v[i+2].Ltete;
        d=v[i+3].Ltete;




        printf("|         %c         |         %c         |         %c         |         %c         |\n\n", i + 97, i + 98, i + 99,
               i + 100);
        while ((a != NULL) || (b != NULL) || (c != NULL) || (d != NULL)) {
            ////////////////////////////////////////

            if ((a != NULL)) {
                printf("      %s            ", a->titre);
                a = a->svt;
            } else {
                printf("                    ");

            }
            /////////////////////////////////////////
            if ((b != NULL)) {
                printf("      %s            ", b->titre);
                b = b->svt;
            } else {
                printf("                    ");

            }
            ///////////////////////////////////////////
            if (i < 24) {

                if (c != NULL) {
                    printf("      %s            ", c->titre);
                    c = c->svt;
                } else {
                    printf("                    ");
                }

                ///////////////////////////////////////////////////
                if (d != NULL) {
                    printf("      %s            \n", d->titre);
                    d = d->svt;
                } else {
                    printf("                     \n");
                }
            } else {
                c = NULL;
                d = NULL;
            }


        }



        printf("\n Appuyer sur 'Q' pour quitter, ou sur un autre pour afficher les 4 prochaines lettres.\n ");


        scanf(" %c",&q);





        i=i+4;


    }




}
//////////////////////////////////////////////////////////////////////////////
void recherche(BD_lettre v[]){



    emprunteur *e; Femprunteur *fe; livre *l; char x[20]; int pos;

    printf("entrez le titre du livre que vous recherchez: "); scanf("%s",x);
    strlwr(x);
    pos=x[0]-97;

    l=v[pos].Ltete;

    while((l!=NULL)&&(strcmp(l->titre,x)!=0)){

        l=l->svt;
    }
    if(l==NULL){
        printf("ce livre n'existe pas dans votre bibliothque.\n");

    }
    else{
        printf("voici les informations de ce livre: \n");
        e=l->Tempreunteur; fe=l->BD_empr.T_fempr;

        printf("|                          --                               \n\n");
        printf("|   Tirtre:....................%s                     \n",l->titre);
        printf("|   Auteur:....................%s                    \n",l->auteur);
        printf("|   Nombre totale de copies:...%d                    \n",l->nbtot);
        printf("|   Nombre disponible:.........%d                    \n",l->nbdisp);

        if(l->nbtot!=l->nbdisp) {

            printf("voici les emprunteur de ce livre: \n");

            while (e != NULL) {
                printf("|   M.%s %s                  |   \n", e->nom,e->prenom);
                e=e->svt;
            }

            if((l->nbdisp==0)&&(fe!=NULL)){
                printf("voici les personnes sur la liste d'attente de ce livre: \n");

                while (fe != NULL) {

                    printf("|   M.%s %s                  |   \n", fe->nom,fe->prenom);
                    fe=fe->svt;
                }

            }
        }

    }



}
///////////////////////////////////////////////////////////////////////////////
void presentation (){

    printf("\n\n\n          ********************************************************\n\n");
    printf("                                  BIENVENUE.               \n\n  ");
    printf("                        Ce programme gere une biblioteque.   \n\n\n\n\n");
    printf("                                                    realise par:\n");
    printf("                                                       Aghiles DJEBARA.\n");
    printf("                                                       Chakib HOUATI.\n");
    printf("          ********************************************************\n\n");
    system("pause");
    system("cls");
}
///////////////////////////////////////////////////////////////////////////////
void menu(char *x){
    char y; int s=0;



    printf("********************************************************************************\n\n");
    printf("          *************************--MENU--**********************\n\n");
    printf("           1- Affichage de tout les livres.\n");
    printf("           2- Rechercher un livre et ses informations.\n");
    printf("           3- Ajouter une copie d'un livre.\n");
    printf("           4- Ajouter un nouveau livre.\n");
    printf("           5- Emprunter un livre. \n");
    printf("           6- Rendre un livre.\n");
    printf("           7- Quitter.\n");
    printf("          ********************************************************\n\n");
    printf("********************************************************************************\n\n");

    printf("Veuillez Choisisir une option :\n");  scanf(" %c",&y);

    while(s==0) {

        switch (y) {
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                s=1;

                break;
            default:
                printf("Veuillez Choisisir une valeur correcte (1-7):\n");
                scanf(" %c",&y);

                break;
        }

    }


    (*x)=y;

}
/////////////////////////////////////////////////////////////////////////////
int main() {



    //////////////////////////////////////////////////////////////////////////////

    BD_lettre lettre[26]; //le tableau principal
    int z=0 ; char choix;



    ///////////////////////////initialisation du tableau/////////////////////////////
    init_tab(lettre);
    ///////////////////////////creation de la structure//////////////////////////////////
     creer_struct(lettre);

    /////////////// ///////////////////////////////////////////////////////////////////
    presentation();
    ////////////////////////////////////////////////////////////////////////////////


    while(z==0) {
        menu(&choix);

        switch (choix) {

            case '1':
                afficher(lettre);
                break;

            case '2':
                recherche(lettre);
                break;

            case '3':
                ajouter_copie_livre(lettre);
               
                break;

            case '4':
                ajouter_nv_livre(lettre);
        
                break;

            case '5':
                emprunter(lettre);
                
                break;

            case '6':
                rendre(lettre);
  
                break;

            case
            '7':
                z = 1;
                break;



        }
        system("pause");

        system("cls");
    }


        ecrire_fichier_et_liberer(lettre);

 




    printf("\n\n\n\n            ------------------------ Au revoir!!-------------------------\n\n\n\n");

    system("pause");
    return 0;
}

