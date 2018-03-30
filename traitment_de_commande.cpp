#include<clocale>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>

/******************************************************************************
/****************************Fonction gotoxy **********************************
/******************************************************************************/
void gotoxy(int x,int y)
{
  COORD pos={x,y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}  
/******************************************************************************
/***********************Les structures *****************************
/******************************************************************************/
typedef struct client
	                   {
                          	                      
	                      	char	numero_client[12],nom[15],prn[15],adr[20],tel[15];
							int Num;
							
	                   }CLIENT;
CLIENT cli;
typedef struct produit
	                   {
                        
	                       char ref[15],desination[15];
	       				   float pu;
	                   }PRODUIT;
PRODUIT pro;

typedef struct commande{
	
	    char date_commade[15];
        char numero_client[30];                  
	    int numero_cmd;
	   	float  total;
	
}commande;
commande  cmd;
typedef struct commander{
	
	      char ref[15];
          char numero_client[30];
		  int quantit;
          int numero_cmd;
       
		                
}commander;

commander com;

/******************************************************************************
/***********************Les pointeurs de fichiers *****************************
/******************************************************************************/
FILE *fc,*fnc;
FILE *fcom , *fncom;
FILE *fcmd , *fncmd;
FILE *fp,*fnp;
/******************************************************************************
/*********************Fonction interface d'une client ***********************
/******************************************************************************/
void interfaceClient()
{
		system("cls");
		gotoxy (24,5);		printf("Information sur la client");
        gotoxy (10,9);		printf("numero client			 ");
		gotoxy (10,13);		printf("Nom client				 ");
		gotoxy (10,17);		printf("Prénom clien			 ");
		gotoxy (10,21);		printf("Adresse					 ");
		gotoxy (10,25);		printf("Télephone				 ");
		gotoxy (10,29);
}
/******************************************************************************
/*************************** Fonction lecture *********************************
/******************************************************************************/
void lectureClient()
{
        gotoxy(26,9);	scanf("%s",cli.numero_client);
	    gotoxy(26,13);	scanf("%s",cli.nom);
	    gotoxy(26,17);	scanf("%s",cli.prn);
	    gotoxy(26,21);	scanf("%s",cli.adr);
	    gotoxy(26,25);	scanf("%s",cli.tel);
}                           
/******************************************************************************
/*********************Fonction enregistrer une client ***********************
/******************************************************************************/
void enregistrerClient(){
	int ch1,ch2;
	do
    {
	   interfaceClient();
	   lectureClient();
	   gotoxy(10,33);	printf("                             ");
       gotoxy(10,33);	printf("voulez vous enregistrer o/n?:");
	   ch1=getch();
	   if (toupper(ch1)=='O')
       {
		 fc=fopen("client.don","a");
		 fwrite(&cli,sizeof(cli),1,fc);
		 fclose(fc);
	   }
	  gotoxy(10,33);
      printf("voulez vous ajouter une autre client  o/n?:");
	  ch2=getch();
	}while(toupper(ch2)=='O');
 } 
/*******************************************************************************/
/***************************** Rechercher***************************************/
/*******************************************************************************/
void rechercherClient(){
	  char numc[15];	int tr=0;
      system("cls");
	  gotoxy(20,3);		printf("Numéro de la cient à rechercher :     ");
	  gotoxy(56,3);		scanf("%s",numc);
	  fc=fopen("client.don","r");
	  if(fc==NULL)
      { 
         gotoxy(22,12);printf("Fichier introuvable!!!");
      }
	  else
      {
	      do
          {
	         fread(&cli,sizeof(cli),1,fc);
             if (strcmp(numc,cli.numero_client)==0)
             {
	            interfaceClient();
	            gotoxy(26,9);printf("%s",cli.numero_client);
	            gotoxy(26,13);printf("%s",cli.nom);
	            gotoxy(26,17);printf("%s",cli.prn);
	            gotoxy(26,21);printf("%s",cli.adr);
                gotoxy(26,25);printf("%s",cli.tel);   
	            tr=1;
             }
       	  }while (!feof(fc)&&(strcmp(numc,cli.numero_client)!=0));
	   	  if (tr==0)
	      {
			    gotoxy(22,12);printf("Pas de client avec ce Numéro!!!");
		  }
    }
    gotoxy(15,33);	printf("Taper une touche pour revenir au menu principal  ");
    getch();
}
/*******************************************************************************/
/*************************** Fonction Supprimer ********************************/
/*******************************************************************************/
void supprimerClient(){
   int tr;
   char c[12],rep,ch1;
   do{
   		system("cls");
	    tr=0;
	    fc=fopen("client.don","r");
       	gotoxy(10,5);	printf("Numéro de client à supprimer :");
	   	scanf("%s",c);
       	fnc=fopen("newclient.don","a");
        if(fnc!=NULL)
        {
          while(!feof(fc))
          {
             fread(&cli,sizeof(cli),1,fc);
             if(!feof(fc))
             {
               if (strcmp(c,cli.numero_client)!=0)
                   fwrite(&cli,sizeof(cli),1,fnc);
               else 
               {
                interfaceClient();
	            gotoxy(26,9);printf("%s",cli.numero_client);
	            gotoxy(26,13);printf("%s",cli.nom);
	            gotoxy(26,17);printf("%s",cli.prn);
	            gotoxy(26,21);printf("%s",cli.adr);
                gotoxy(26,25);printf("%s",cli.tel);   
	            tr=1;
               }
          	}
      	 }
		   fclose(fc);
		   fclose(fnc);
		   if(tr==1)
	       {
	          gotoxy(15,33);printf("Voulez vous  supprimer cette client o/n?:");
	          ch1=getch();
		      if (toupper(ch1)=='O'){
	             remove("client.don");
		         rename("newclient.don","client.don");
		         gotoxy(15,33);printf("                                                ");
	       	     gotoxy(15,33);printf("La client est supprimée!");
	          }
		      else remove("newclient.don");
	       }
	       else{
	            remove("newclient.don");
		        gotoxy(15,33);printf("Numéro introuvable!");
		        getch();
	       }
		   gotoxy(15,35);printf("Autre client à supprimer o/n?:");
		   rep=getch();
    	}else gotoxy(15,33);printf("Fichier introuvable!");
	}while(toupper(rep)=='O');
   }
/***********************Fonction lister les client **************************
/******************************************************************************/
void listerClient()
{ 
      system("cls");
      int i=0;
	  gotoxy(29,5);
      printf("La liste des client");
	  gotoxy(4,8);
      printf("numero de client");
	  gotoxy(23,8);
      printf("Les noms");
	  gotoxy(36,8);
      printf("Prenoms");
	  gotoxy(46,8);
      printf("Adresses");
	  gotoxy(60,8);
      printf("Telephone");
	  fc=fopen("client.don","r");
	  do
      {
	     fread(&cli,sizeof(cli),1,fc);
	     if(!feof(fc))
         {
	                   i++;
	                   gotoxy(6,8+i*2); printf("%s",cli.numero_client);
	                   gotoxy(24,8+i*2);printf("%s",cli.nom);
	                   gotoxy(37,8+i*2);printf("%s",cli.prn);
	                   gotoxy(47,8+i*2);printf("%s",cli.adr);
	                   gotoxy(60,8+i*2);printf("%s",cli.tel);
	                 }
      }while(!feof(fc));
	  fclose(fc);
	  gotoxy(10,12+i*2);
      printf("Taper une touche pour revenir au menu principal : ");
	  gotoxy(60,12+i*2);
	  getch();
}
/*******************************************************************************/
/**************************** Fonction Modifier *********************************/
/*****************************************************************************/
void modifierClient()
{

   int pos,ln,q,tr=0;
   char ncc[12];
   do{
      system("cls");
     gotoxy(30,3);printf(" Modifier une client");
     gotoxy(16,6);printf("Numéro de la client à modifier :     ");
     gotoxy(50,6);scanf("%s",ncc);
     fc=fopen("client.don","r");
     if(fc==NULL)
     { 
                 gotoxy(22,9);
                 printf("Fichier introuvable!!!");
     }
     else
     {
       do{
          pos=ftell(fc);
          fread(&cli,sizeof(cli),1,fc);
	      if (strcmp(ncc,cli.numero_client)==0)
          {
	         interfaceClient();
             gotoxy(26,9);printf("%s",cli.numero_client);
             gotoxy(26,13);printf("%s",cli.nom);
             gotoxy(26,17);printf("%s",cli.prn);
             gotoxy(26,21);printf("%s",cli.adr);
             gotoxy(26,25);printf("%s",cli.tel);   
          
             tr=1;
       }
	}while (!feof(fc)&&(strcmp(ncc,cli.numero_client)!=0));
	if (tr==0){
	   gotoxy(16,9);printf("Pas de client avec ce Numéro!!!");
	}
	else{
	    fclose(fc);
	    do{
              gotoxy(16,33); printf("Numéro de la ligne à modifier:");
              gotoxy(48,33);scanf("%d",&ln);
	          switch(ln)
              {
		             case 1 :gotoxy(26,9);printf("                                ");gotoxy(26,9);scanf("%s",cli.numero_client);gotoxy(26,13);break;
		             case 2 :gotoxy(26,13);printf("                                ");gotoxy(26,13);scanf("%s",cli.nom);gotoxy(26,17);break;
		             case 3 :gotoxy(26,17);printf("                                ");gotoxy(26,17);scanf("%s",cli.prn);gotoxy(26,21);break;
		             case 4 :gotoxy(26,21);printf("                                ");gotoxy(26,21);scanf("%s",cli.adr);gotoxy(26,25);break;
		             case 5 :gotoxy(26,25);printf("                                ");gotoxy(26,25);scanf("%s",cli.tel);gotoxy(26,29);break;
               }
               gotoxy(16,33); printf("                                                      ");
               gotoxy(16,33); printf("Autre ligne à modifier o/n:");
               gotoxy(48,33);q=getch();
	     }while(toupper(q)=='O');
	     gotoxy(14,33); printf("                                                          ");
         gotoxy(14,33); printf("Voulez vous vraiment modifier cet enregistrement o/n?");
         q=getch();
         if(toupper(q)=='O')
         {
            fc=fopen("client.don","r+");
            fseek(fc,pos,0);
            fwrite(&cli,sizeof(cli),1,fc);
            fclose(fc);
         }
         }
         }
         gotoxy(14,33); printf("                                                          ");
         gotoxy(14,33); printf("modifier un autre enregistrement o/n?:");
         q=getch();
     }while(toupper(q)=='O');
     }



/******************************************************************************
/*********************Fonction interface d'une produit ***********************
/******************************************************************************/
void interfaceProduit()
{
		system("cls");
		gotoxy (24,5);
		printf("Information sur la produit");
        gotoxy (10,9);
		printf("referance");
		gotoxy (10,13);
		printf("designation");
		gotoxy (10,17);
		printf("prix unite");
		
}
/******************************************************************************
/*********************** Fonction lectureune produit *****************************
/******************************************************************************/
void lectureProduit()
{
        gotoxy(26,9);scanf("%s",pro.ref);
	    gotoxy(26,13);scanf("%s",pro.desination);
	    gotoxy(26,17);scanf("%f",&pro.pu); 
}                           
/******************************************************************************
/*********************Fonction enregistrer une produit ***********************
/******************************************************************************/
void enregistrerprodit(){
	int ch1,ch2;
	do
    {
	   interfaceProduit();
	   lectureProduit();
	   gotoxy(10,33);
	   printf("                                                 ");
       gotoxy(10,33);
	   printf("voulez vous enregistrer o/n?:");
	   ch1=getch();
	   if (toupper(ch1)=='O')
       {
		 fp=fopen("produit.don","a");
		 fwrite(&pro,sizeof(pro),1,fp);
		 fclose(fp);
	  }
	  gotoxy(10,33);
      printf("voulez vous ajouter une autre produit  o/n?:");
	  ch2=getch();
	  }while(toupper(ch2)=='O');
 } 
/*******************************************************************************/
/***************************** Rechercher***************************************/
/*******************************************************************************/
void rechercherprouduit(){
	  char refp[12];
      int tr=0;
      system("cls");
	  gotoxy(20,3);printf("referance de la produit à rechercher   ");
	  gotoxy(60,3);scanf("%s",refp);
	  fp=fopen("produit.don","r");
	  if(fp==NULL)
      { 
         gotoxy(22,12);printf("Fichier introuvable!!!");
      }
	  else
      {
	      do
          {
	         fread(&pro,sizeof(pro),1,fp);
             if (strcmp(refp,pro.ref)==0)
             {
	            interfaceProduit();
	            gotoxy(26,9);printf("%s",pro.ref);
	            gotoxy(26,13);printf("%s",pro.desination);
	            gotoxy(26,17);printf("%f",pro.pu);
	           
	            tr=1;
             }
       }while (!feof(fp)&&(strcmp(refp,pro.ref)!=0));
	   if (tr==0)
       {
		  gotoxy(22,12);printf("Pas de produit avec ce referance!!!");
	   }
    }
    gotoxy(15,33);printf("Taper une touche pour revenir au menu principal  ");
    getch();
}
/*******************************************************************************/
/*************************** Fonction Supprimer ********************************/
/*******************************************************************************/
void supprimerproduit(){
   int tr;
   char c[12],rep,ch1;
   do{
	tr=0;
	system("cls");
       gotoxy(10,5);
	   fp=fopen("produit.don","r");
	   printf("referance  de la produit à supprimer    ");
	   scanf("%s",c);
       fnp=fopen("newpro.don","a");
        if(fnp!=NULL)
        {
          while(!feof(fp))
          {
             fread(&pro,sizeof(pro),1,fp);
             if(!feof(fp))
             {
               if (strcmp(c,pro.ref)!=0)
                   fwrite(&pro,sizeof(pro),1,fnp);
               else 
               {
                interfaceProduit();
	            gotoxy(26,9);printf("%s",pro.ref);
	            gotoxy(26,13);printf("%s",pro.desination);
	            gotoxy(26,17);printf("%f",pro.pu);
	            
	            tr=1;
             }
          }
       }
	   fclose(fp);
	   fclose(fnp);
	   if(tr==1)
       {
          gotoxy(15,33);printf("Voulez vous  supprimer cette produit o/n?:");
          ch1=getch();
	      if (toupper(ch1)=='O'){
             remove("produit.don");
	         rename("newpro.don","produit.don");
	         gotoxy(15,33);printf("                                                ");
       	     gotoxy(15,33);printf("Le produit est supprimée!");
             //getch();
          }
	      else remove("newpro.don");
       }
       else{
            remove("newpro.don");
	        gotoxy(15,33);printf("Numéro introuvable!");
	        getch();
       }
	   gotoxy(15,35);printf("Autre produit à supprimer o/n?:");
	   rep=getch();
    }
    else
        gotoxy(15,33);printf("Fichier introuvable!");
	}while(toupper(rep)=='O');
   }
/***********************Fonction lister les produits **************************
/******************************************************************************/
void listerProduit()
{ 
		      system("cls");
		      int i=0;
			  gotoxy(29,5);
		      printf("La liste des produits");
			  gotoxy(4,8);
		      printf("referance");
			  gotoxy(23,8);
		      printf("designation");
			  gotoxy(36,8);
		      printf("prix unite");
			  
			  fp=fopen("produit.don","r");
			  do
		      {
			     fread(&pro,sizeof(pro),1,fp);
			     if(!feof(fp))
		         {
			                   i++;
			                   gotoxy(6,8+i*2); printf("%s",pro.ref);
			                   gotoxy(24,8+i*2);printf("%s",pro.desination);
			                   gotoxy(37,8+i*2);printf("%f",pro.pu);
			                 }
		      }while(!feof(fp));
			  fclose(fp);
			  gotoxy(10,12+i*2);
		      printf("Taper une touche pour revenir au menu principal : ");
			  gotoxy(60,12+i*2);
			  getch();
		}
		/*******************************************************************************/
		/**************************** Fonction Modifier *********************************/
		/*****************************************************************************/
		void modifierproduit()
		{
		
		   int pos,ln,q,tr=0;
		   char ncp[12];
		   do{
					      system("cls");
					     gotoxy(30,3);printf(" Modifier une produit");
					     gotoxy(16,6);printf("Referance de la produit à modifier");
					     gotoxy(60,6);scanf("%s",ncp);
					     fp=fopen("produit.don","r");
					     if(fp==NULL)
					     { 
					                 gotoxy(22,9);
					                 printf("Fichier introuvable!!!");
					     }else
					     {
					       do{
					          pos=ftell(fp);
					          fread(&pro,sizeof(pro),1,fp);
						      if (strcmp(ncp,pro.ref)==0)
					          {
						         interfaceProduit();
					             gotoxy(26,9);printf("%s",pro.ref);
					             gotoxy(26,13);printf("%s",pro.desination);
					             gotoxy(26,17);printf("%f",pro.pu);
					             
					             tr=1;
					       }
						}while (!feof(fp)&&(strcmp(ncp,pro.ref)!=0));
						if (tr==0){
						   gotoxy(16,9);printf("Pas de produit avec ce Numéro!!!");
						}
						else
						{
						    fclose(fp);
							    do{
						              gotoxy(16,33); printf("Numéro de la ligne à modifier:");
						              gotoxy(48,33);scanf("%d",&ln);
								          switch(ln)
							              {
									             case 1 :gotoxy(26,9);printf("                                ");gotoxy(26,9);scanf("%s",pro.ref);gotoxy(26,13);break;
									             case 2 :gotoxy(26,13);printf("                                ");gotoxy(26,13);scanf("%s",pro.desination);gotoxy(26,17);break;
									             case 3 :gotoxy(26,17);printf("                                ");gotoxy(26,17);scanf("%f",&pro.pu);gotoxy(26,21);break;
									      
							               }
						               gotoxy(16,33); printf("                                                      ");
						               gotoxy(16,33); printf("Autre ligne à modifier o/n:");
						               gotoxy(48,33);q=getch();
						         }while(toupper(q)=='O');
								 gotoxy(14,33); printf("                                                          ");
							     gotoxy(14,33); printf("Voulez vous vraiment modifier cet enregistrement o/n?");
							     q=getch();
						         if(toupper(q)=='O')
						         {
						            fp=fopen("produit.don","r+");
						            fseek(fp,pos,0);
						            fwrite(&pro,sizeof(pro),1,fp);
						            fclose(fp);
						         }
					    }
		         }
		         gotoxy(14,33); printf("                                                          ");
		         gotoxy(14,33); printf("modifier un autre enregistrement o/n?:");
		         q=getch();
			}while(toupper(q)=='O');
     }

/******************************************************************************
/*********************Fonction interface d'une commande ***********************
/******************************************************************************/
void interfaceCommande()
{
	system("cls");
	gotoxy(30,6);	
	printf("commande client");
	gotoxy(3,10);
	printf("le numero de client:");
	gotoxy(50,10);
	printf("nom client:");
	gotoxy(3,12);
	printf("prenom de client:");
	gotoxy(50,12);
	printf("adress client:");
	gotoxy(3,14);
	printf("telephone de client:");
	gotoxy(50,14);
	printf("numero de comande:");
	gotoxy(30,16);
	printf("date de comande:");
	
}
void lectureCommande()
{
     	interfaceCommande();
        gotoxy(30,10);scanf("%s",cmd.numero_client);
        /////////////////////
    	fc = fopen("client.don","r");
	  if(fc == NULL)
      { 
         gotoxy(22,12);printf(" Fichier introuvable!!! ");
      }
	  else
      {
	      do
          {
	         fread(&cli,sizeof(cli),1,fc);
	         
             if (strcmp(cmd.numero_client,cli.numero_client)==0)
             {
             	system("cls");
	            interfaceCommande();
	            gotoxy(30,10);printf("%s",cmd.numero_client);
	            gotoxy(75,10);printf("%s",cli.nom);
	            gotoxy(30,12);printf("%s",cli.prn);
	            gotoxy(75,12);printf("%s",cli.adr);
                gotoxy(30,14);printf("%s",cli.tel);   
	            
             }
             
          }while (!feof(fc)&&(strcmp(cmd.numero_client,cli.numero_client)!=0));
	   
    }
    gotoxy(75,14);scanf("%d",&cmd.numero_cmd);
    gotoxy(50,16);scanf("%s",cmd.date_commade);
        
} 
/******************************************************************************
/*********************Fonction interface d'une commander ***********************
/******************************************************************************/
void interfaceCommander()
{
	gotoxy(3,18);
	printf("referance");
	gotoxy(16,18);
	printf("destenation");
	gotoxy(29,18);
	printf("prix unite");
	gotoxy(42,18);
	printf("quntite");
	gotoxy(55,18);
	printf("montant"); 
}
void lectureCommander()
{
	char ch;
	int y=20;
	cmd.total=0;
	do
    {
            int x=3;
        	float pri=0 ;
        	interfaceCommander();
            gotoxy(x,y);scanf("%s",com.ref);
            fp=fopen("produit.don","r");
    	  if(fp==NULL)
          { 
             gotoxy(22,22);printf("Fichier introuvable!!!");
          }
	  else
      {
	      do
          {
	         fread(&pro,sizeof(pro),1,fp);
                 if (strcmp(com.ref,pro.ref)==0)
                 {
    	            gotoxy(x+=13,y);printf("%s",pro.desination);
    	            gotoxy(x+=13,y);printf("%f",pro.pu);
    	            pri=pro.pu;
                 }
          }while (!feof(fp)&&(strcmp(com.ref,pro.ref)!=0));
	   fclose(fp);
     }
    gotoxy(x+=13,y);scanf("%d",&com.quantit);
    
    
    float mon=com.quantit*pri;
    cmd.total+=mon;
    
    gotoxy(x+=13,y);	printf("%f",mon);
    
    com.numero_cmd = cmd.numero_cmd;
   	strcpy(com.numero_client , cmd.numero_client); 
  	  
	gotoxy(3,y+=2);		printf(" voulez vous ajouter une autre commander  o/n?: ");
	int posto= y+3;
	gotoxy(3,posto);	printf("total de commande %f",cmd.total);
    gotoxy(60,y); ch=getch();
	  
	  if(toupper(ch) == 'O'){
	  
	         fcom=fopen("commander.don","a");
			 fwrite(&com,sizeof(com),1,fcom);
			 fclose(fcom);
	
		  	 gotoxy(3,y);	printf("                                                      ");
			 gotoxy(3,posto);	printf("                                                      ");
				
	  }else{
		 fcom=fopen("commander.don","a");
		 fwrite(&com,sizeof(com),1,fcom);
		 fclose(fcom);
	  }
	  }while(toupper(ch)=='O');
	   
} 
void enregistrer_cmd_com(){
	int ch1;

		lectureCommande();
		lectureCommander();
	   gotoxy(10,33);
	   printf("                                                 ");
       gotoxy(10,33);
	   printf("voulez vous enregistrer o/n?:");
	   ch1=getch();
	   if (toupper(ch1)=='O')
       {
		 fcmd=fopen("commande.don","a");
		 fwrite(&cmd,sizeof(cmd),1,fcmd);
		 fclose(fcmd); 
	  }
	 fflush(stdin);
}	 
char cmdCli[30];
void recherchercommande(){
	  int cmdc;
      int tr=0;
      system("cls");
	  gotoxy(20,3);printf("Numéro de la commande à rechercher");
	  gotoxy(60,3);scanf("%d",&cmdc);
	  fcmd=fopen("commande.don","r");
	  fc = fopen("client.don","r");
	  if(fcmd==NULL || fc==NULL)
      { 
         gotoxy(22,12);printf("Fichier introuvable!!!");
      }
	 else 
	{
	      do
          {
	         fread(&cmd,sizeof(cmd),1,fcmd);
             if (cmdc==cmd.numero_cmd)
             {
             	
	            system("cls");
				gotoxy(30,6);	
				printf("commande client");
				gotoxy(3,10);
				printf("numero de comande:");
				gotoxy(50,10);
				printf("le numero de client:");
				gotoxy(3,12);
				printf("nom client:");
				gotoxy(50,12);
				printf("prenom de client:");
				gotoxy(3,14);
				printf("adress client:");
				gotoxy(50,14);
				printf("telephone de client:");
				gotoxy(30,16);
				printf("date de comande:");
				
	            do
				{	
					fread(&cli,sizeof(cli),1,fc);
		           	if (strcmp(cmd.numero_client,cli.numero_client)==0)
					   {	
				            gotoxy(30,10);printf("%d",cmd.numero_cmd);
				            gotoxy(75,10);printf("%s",cmd.numero_client);
				            gotoxy(30,12);printf("%s",cli.prn);
				            gotoxy(75,12);printf("%s",cli.nom);
			                gotoxy(30,14);printf("%s",cli.adr); 
			              	gotoxy(75,14);printf("%s",cli.tel);
						 
						}
	            }while(!feof(fc)&&(strcmp(cmd.numero_client,cli.numero_client)!=0));
	            fclose(fc);
	            gotoxy(55,16);printf("%s",cmd.date_commade);
	            fcom=fopen("commander.don","r");
	            int l=0;
	            do{
	            	fread(&com,sizeof(com),1,fcom);
	            	if(com.numero_cmd==cmdc)
					if(!feof(fcom)){
	            		interfaceCommander();
						gotoxy(3,20+l);printf("%s",com.ref);
						
							fp = fopen("produit.don","r");
										  if(fp==NULL)
											{ 
												gotoxy(22,22);printf("Fichier introuvable!!!");
											}
											else
											{
											  do
											    {
												  fread(&pro,sizeof(pro),1,fp);
											        if (strcmp(com.ref,pro.ref)==0)
											        {
												      gotoxy(16,20+l);printf("%s",pro.desination);
												      gotoxy(29,20+l);printf("%f",pro.pu);
												      gotoxy(42,20+l);printf("%d",com.quantit);
												      gotoxy(55,20+l);printf("%.2f",pro.pu*com.quantit);
											        }
											    }while(!feof(fc)&&(strcmp(com.ref,pro.ref)!=0));
												fclose(fp);	   
											}	
	            		l++;
					}	            	
				}while(!feof(fcom));
				fclose(fcom);
				gotoxy(3,22+l);printf("total de la commande : %.2f",cmd.total);
	            tr=1;
             }
      	 }while (!feof(fcmd)&&(cmdc!=cmd.numero_cmd));
      	 fclose(fcmd);
	 		 if (tr==0)
			 {
				  gotoxy(22,12);printf("Pas de client avec ce Numéro!!!");
			 }			 
     }   
     fflush(stdin);  
    gotoxy(15,33);printf("Taper une touche pour revenir au menu principal  ");   
    getch();
}
/***********************Fonction lister les commandes **************************
/******************************************************************************/
void listerCommande()
{ 
      system("cls");
      int i=0;
	  gotoxy(29,5);
      printf("La liste des commande");
	  gotoxy(4,8);
      printf("Numero de commande");
	  gotoxy(25,8);
      printf("date");
	  gotoxy(40,8);
      printf("Numero de client");
	  gotoxy(60,8);
      printf("Prenom et nom");
	  gotoxy(80,8);
      printf("Total");
	
	  fcmd=fopen("commande.don","r");
	  do
      {
	     fread(&cmd,sizeof(cmd),1,fcmd);
	     if(!feof(fcmd))
         {
	                   i++;
	                   gotoxy(6,8+i*2); printf("%d",cmd.numero_cmd);
	                   gotoxy(25,8+i*2);printf("%s",cmd.date_commade);
	                   
	                   fc = fopen("client.don","r");
										  if(fc==NULL)
											{ 
												gotoxy(22,22);printf("Fichier introuvable!!!");
											}
											else
											{
											  do
											    {
												  fread(&cli,sizeof(cli),1,fc);
											        if (strcmp(cmd.numero_client,cli.numero_client)==0)
											        {
												         gotoxy(40,8+i*2);printf("%s",cli.numero_client);
	                  									 gotoxy(60,8+i*2);printf("%s %s",cli.prn,cli.nom);
	                  									 gotoxy(80,8+i*2);printf("%.2f",cmd.total);
											        }
											    }while(!feof(fc)&&(strcmp(cmd.numero_client,cli.numero_client)!=0));
												fclose(fc);	   
	                						 }
	             }
      }while(!feof(fcmd));
	  fclose(fcmd);
	  fflush(stdin);
	  gotoxy(10,12+i*2);	printf("Taper une touche pour revenir au menu principal : ");
	  gotoxy(60,12+i*2);
	  getch();
}
/*******************************************************************************/
/*************************** Fonction Supprimer ********************************/
/*******************************************************************************/
void supprimerCmdCom()
{
   int tr,scmdn;
   char rep,ch1;
   do
   {
	    tr=0;
	    system("cls");
        gotoxy(10,5);
	    fcmd=fopen("commande.don","r");
	   
  	    printf("Numéro de commande à supprimer :");
	    scanf("%d",&scmdn);  
        fncmd=fopen("newcommande.don","w");
        fclose(fncmd);
         fncmd=fopen("newcommande.don","a");
        //fncom=fopen("newcommander.don","a");
        if(fcmd!=NULL)
        {
         do
          {
             fread(&cmd,sizeof(cmd),1,fcmd);
             //fread(&com,sizeof(com),1,fcom);
             if(!feof(fcmd))
             {
                   if (scmdn!=cmd.numero_cmd)
                   {
			   	      fwrite(&cmd,sizeof(cmd),1,fncmd);
                      //fwrite(&com,sizeof(com),1,fncom);
			       }
                   
                   else 
                   {
               	
               
				                system("cls");
								gotoxy(30,6);	
								printf("commande client");
								gotoxy(3,10);
								printf("numero de comande:");
								gotoxy(40,10);
								printf("le numero de client:");
								gotoxy(3,12);
								printf("nom client:");
								gotoxy(40,12);
								printf("prenom de client:");
								gotoxy(3,14);
								printf("adress client:");
								gotoxy(40,14);
								printf("telephone de client:");
								gotoxy(20,16);
								printf("date de comande:");
               		  
                		        gotoxy(30,10);printf("%d",cmd.numero_cmd);
				                gotoxy(75,10);printf("%s",cmd.numero_client);
				            
                			    fc = fopen("client.don","r");
			                    do
							    {	
								  fread(&cli,sizeof(cli),1,fc);
					           	  if (strcmp(cmd.numero_client,cli.numero_client)==0)
							      {	
							            
							            gotoxy(30,12);printf("%s",cli.prn);
							            gotoxy(75,12);printf("%s",cli.nom);
						                gotoxy(30,14);printf("%s",cli.adr); 
						              	gotoxy(75,14);printf("%s",cli.tel);
									 
	                              }
                               }while(!feof(fc)&&(strcmp(cmd.numero_client,cli.numero_client)!=0));
				               fclose(fc);
				               
				               gotoxy(55,16);printf("%s",cmd.date_commade);
				            	            
                               int l=0;
                               fcom = fopen("commander.don","r");
	                           do
                               {
					            	fread(&com,sizeof(com),1,fcom);
					            	if(com.numero_cmd==scmdn)
									if(!feof(fcom))
                                    {
       		                        interfaceCommander();
									gotoxy(3,20+l);printf("%s",com.ref);
										
									fp = fopen("produit.don","r");
							        if(fp==NULL)
									{ 
									  gotoxy(22,22);printf("Fichier introuvable!!!");
									}
									else
									{
							            do
					                    {
                                             fread(&pro,sizeof(pro),1,fp);
	                                         if (strcmp(com.ref,pro.ref) == 0)
	                                         {
                                               gotoxy(16,20+l);printf("%s",pro.desination);
			                                   gotoxy(29,20+l);printf("%f",pro.pu);
			                                   gotoxy(42,20+l);printf("%d",com.quantit);
			                                   gotoxy(55,20+l);printf("%.2f",pro.pu*com.quantit);
                                             }
                                         }while(!feof(fp)&&(strcmp(com.ref,pro.ref)!=0));
									     fclose(fp);	   
									}	
       		                        l++; 
                                    }     	
								}while(!feof(fcom));							
								fclose(fcom);							
								gotoxy(3,22+l);		printf("total de la commande : %.2f",cmd.total);
					            tr=1;
                   }
                }
           } while(!feof(fcmd));
  	  	  if(tr == 1)
          {
              
                 fcom=fopen("commander.don","r");
                  fncom=fopen("newcommander.don","a");
       			 
	                  while(!feof(fcom))
	                  {
	                         fread(&com,sizeof(com),1,fcom);
	                         //fread(&com,sizeof(com),1,fcom);
	                         if(!feof(fcom))
	                         {
	                             if (scmdn!=com.numero_cmd)
	                             {
				   	                fwrite(&com,sizeof(com),1,fncom);
	                             }
	                         }
	                    }
                		fclose(fcmd); fclose(fncmd);
	                    fclose(fcom); fclose(fncom);
	                    //fflush(stdin);
	                    gotoxy(15,33);printf("Voulez vous  supprimer cette commande o/n?:");
	                    ch1=getch();
		                if (toupper(ch1)=='O')
	                    {          
	                            remove("commande.don");
	                            rename("newcommande.don","commande.don");
		         
		                        remove("commander.don");
		                        rename("newcommander.don","commander.don");
		         
		                        gotoxy(15,33);printf("                                                ");
	       	                    gotoxy(15,33);printf("La commande est supprimée!");
	                    }             
		                else
	                    {
			                remove("newcommande.don");
		                    remove("newcommander.don");
     				    } 
           }
           else
           {      		
			         fclose(fcom); fclose(fncom);
                     remove("newcommande.don");
	                 remove("newcommander.don");
	        
	                 gotoxy(15,33);printf("Numéro introuvable dans commander!");
	                 getch();
		   }
	              gotoxy(15,35);printf("Autre commande à supprimer o/n?:");
	              rep=getch();
        }else
		{
			gotoxy(15,33);printf("Fichier introuvable!");
		} 
	}while(toupper(rep)=='O');
	fflush(stdin);
 }
/******************************************************************************
/************************Fonction menu principal ******************************
/******************************************************************************/
void menu()
 {
	int nm;
	do
		{
			system("cls");
			gotoxy(32,5);
			puts("Menu principal");
			gotoxy(8,7);
			puts("Client");
			gotoxy(5,8);
			puts("1: Enregister");
			gotoxy(5,9);
			puts("2: Rechercher");
			gotoxy(5,10);
			puts("3: Lister");
			gotoxy(5,11);
			puts("4: Modifier");
			gotoxy(5,12);
			puts("5: Supprimer");
			gotoxy(30,7);
			puts("Produit");
			gotoxy(27,8);
			puts("6: Enregister");
			gotoxy(27,9);
			puts("7: Rechercher");
			gotoxy(27,10);
			puts("8: Lister");
			gotoxy(27,11);
			puts("9: Modifier");
			gotoxy(27,12);
			puts("10:Supprimer");
			gotoxy(52,7);
			puts("Comande");
			gotoxy(49,8);
			puts("11:Enregister");
			gotoxy(49,9);
			puts("12:Rechercher");
			gotoxy(49,10);
			puts("13:Lister");
			gotoxy(49,11);
			puts("14:Supprimer ");
			gotoxy(49,12);
			puts("15:Quitter");
			
			do
			{
				gotoxy(10,15);
				puts("Entrer votre choix :            ");
				gotoxy(30,15);
				
				scanf("%d",&nm);fflush(stdin);
			}while((nm<1)||(nm>15));
			switch(nm)
			{
				case 1:		system("color f1");	enregistrerClient();	break;
				case 2:		system("color f2");		rechercherClient();		break;
				case 3:		system("color f3");		listerClient();			break;
				case 4:		system("color 1f");		modifierClient();		break;
				case 5:		system("color f5");		supprimerClient();		break;
				case 6:		system("color 6f");		enregistrerprodit();	break;
				case 7:		system("color 70");		rechercherprouduit();	break;
				case 8:		system("color fc");		listerProduit();		break;
				case 9:		system("color f9");		modifierproduit();		break;
				case 10:	system("color f2");	supprimerproduit();		break;
				case 11:	system("color f5");	enregistrer_cmd_com();	break;
				case 12:	system("color f3");	recherchercommande();	break;
				case 13:	system("color f1");	listerCommande();		break;
				case 14:	system("color 70");	supprimerCmdCom();		break;
			
			}
		} while(nm!=15);
 }
/******************************************************************************
/*********************Fonction principale main() ***********************
/******************************************************************************/
main()
{
	system("cls");
    setlocale( LC_CTYPE , "fra" ) ;
	menu();
}
