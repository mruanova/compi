
// PROCESADORES DE LENGUAJES
// Mai SQL
// Mauricio Ruanova 44703 mruanova@yahoo.com
// Carlos Camino    59999 ccamino1@yahoo.com

#include<iostream.h> // para cout cin
#include<fstream.h>
#include<iomanip.h>
#include<stdio.h>    // para getchar, getc
#include<except.h>   // para terminate
#include<fstream.h>  // para archivos
#include<ctype.h>    // para isalpha, isdigit, isalnum, toupper
#include<conio.h>    // para gotoxy
#include<string.h>   // para strcpy
#include<cstring.h>   // para string
#include<stdlib.h>   // para randoms, abs

struct tabla1 //PALABAS RESERVADAS
{
	char pal[15];
	int token;
};

struct reg //registro
{
	void *valor;
	reg *sigreg;
	reg *abajo;
};

struct nodo      //campo
{
	char nombre[20];
	int tipo;
	int tamano;
	int id;
//	void *valor;
	nodo *sig;
};

struct apuntc // apunt char
{
	char info[20];
	apuntc *sig;
};

struct apuntv  // apuntador a memoria
{
	void *info;
	apuntv *sig;
	float tipo;
//	int temp;
};

struct apunti // apunt int
{
	int info;
	apunti *sig;
};

struct apuntn // apunt nodo
{
	nodo *info;
	int tabla;
	apuntn *sig;
};

struct cuadruplo
{
	float operador;
	apuntv *uno;
	apuntv *dos;
	apuntv *tres;
	cuadruplo *sig;
};

struct apunts // apunt saltos
{
	cuadruplo *info;
	apunts *sig;
};

struct celda //para guardar las tablas
{
	char nombre[20];
	int actualreg;
	int cuentareg;
	nodo *sig;
	reg *sigreg;
};

struct celda2 //para guardar las constantes
{
	float valor;
};

struct celda3 //para guardar los strings
{
	char valor[50];
};

//cuadruplos
void genera();
void generacuadno();//no(a=a)
void generacuadcampos1(int tabla);
void generacuadcampos2();
void generacuadtoma(int cual);
void generacuadcopia();
void imprimecuad(cuadruplo *cuad);
void ejecuta();//ejecuta el top
void ejecutatodos();

//FILAS
int sacatipo();//fila de tipos crea y tipodato, y vacia
void metetipo(int &valor);

char* sacacampos();
void metecampos();

void metereg(reg *r);//agrega un reg a la fila
void metefilareg(int tabla);//agrega la fila de reg a la tabla

//PILAS
void pushreg(reg *r);
reg* popreg();

void pushcampos(nodo *n,int tabla);
void popcampos();

void pushsaltos(cuadruplo *cuad);
cuadruplo* popsaltos();

int popoperadores();
void pushoperadores(int valor);

void popoperandos();
void pushoperandos(int tipo,int posctes,int posstrs);
void pushoperando(apuntv *aux,int tipo);

// otros
int gettabla(nodo *campo);
void creacampos123();
void insertacampo123(nodo *n);
void inicializarcuadruplos();
void verificaid(int tabla);
void imprimeoperador(int tipo);
int conviertetipo(int tipo);
void llenarinfo(apuntc *apunt);
void abreycargatabla(int nocreate);
void vacia(int tabla);
int compatibles(int x, int y);
void sort(apuntn *campo,int ascendente);
void swap(int a,int b);
void borra(nodo *campo);
int numdecampo(nodo *campo);
void meteregs(apuntn *campo);  //mete los reg del campo a operandos

//funciones
int cuenta(nodo *campo);
float suma(nodo *campo);
float min(nodo *campo);
float max(nodo *campo);
char* minstr(nodo *campo);
char* maxstr(nodo *campo);

//registros
int regvalorint(nodo *campo,int posicion);
float regvalorfloat(nodo *campo,int posicion);
char* regvalorchar(nodo *campo,int posicion);
reg* regposicion(nodo *campo,int posicion);

//editor de texto
void ayuda(void);
void compilar(void);
void exist(void);
void newfile(void);
void printfile(void);

//lexico
int gettoken();
int diferentemayormenor();
int comentario();
int enteroreal();
int esstring();
int reservadavariable();
int esdelimitador(char cha);
int checareservada();
void palabrasreservadas();

//sintaxis
void prcAgrega();
void prcCampo();
void prcCampos();
void prcCrea();
void prcDefine();
void prcElimina();
void prcExpresion();
void prcExpBooleana();
void prcFactor();
void prcFuncion();
void prcID();
void prcInicial();
void prcInstruccion();
void prcLimpia();
void prcOrdena();
void prcRenombra();
void prcSelecciona();
void prcSubSelecciona();
void prcTabla();
void prcTablas();
void prcTermino();
void prcTablas();
void prcTermino();
void prcTipoDato();

//variables globales
char ch;
char salida;
ifstream afile;
int cha;
int nohagonada=-4;
int errordecadena=-5;     //estado no aceptor
int auxtoken=0;
int token=0;
int len;
int linea=1; // contador de lineas

char cadena[20];
tabla1 palabra[150];  // 150 palabras reserbadas maximo
celda matriz[20];   // matriz con las tablas;
int topmatriz=0;
int actualtabla=1;
celda2 ctes[20]; //constantes
int topctes=0;
celda3 strs[20]; //strings
int topstrs=0;
//int cuentaregs=0;

//pilas
apunts *topsaltos;
reg *topreg=NULL;
reg *inicioreg=NULL;
apuntn *topcampos=NULL;
apuntc *iniciocampos=NULL;
apunti *iniciotipos=NULL;
apunti *topoperadores=NULL;
apuntv *topoperandos=NULL; //no tiene tipo
apuntc *auxc=NULL;
cuadruplo *topcuadruplos=NULL;
cuadruplo *cuadcontmas1=NULL;
cuadruplo *actualcuad=NULL;
apuntv *buffer=NULL;

ofstream fcuads;//achivo donde se imprimen los cuadruplos

void main() //---------------------------------------------------------VOID MAIN
{
	inicio:
	clrscr();
	int i;
	for(i=2;i<=75;i++)
	{
		gotoxy(i,2);  cout<<char(95);
	}
	for(i=2;i<=75;i++)
	{
		gotoxy(i,6);  cout<<char(95);
	}
	gotoxy(28,4);  cout<<"MaiSQL";
	gotoxy(10,8);  cout<<"Procesadores de lenguajes";
	gotoxy(10,14); cout<<"Mauricio Ruanova ................... 44703";
	gotoxy(10,16); cout<<"Carlos Camino ...................... 59999";
	gotoxy(15,22); cout<<"Presione ENTER ... ";
	getch();
	compilar();
	if((salida!='s')&&(salida!='S'))
	{
		goto inicio;
	}
}//main

void compilar()   //----------------------------------------------------COMPILAR
{
	char name[200];
	clrscr();
	cout<<"NOMBRE DEL ARCHIVO A COMPILAR.\n";
	gets(name);
	fflush(stdin);
	clrscr();
	afile.open(name,ios::in);
	if(!afile)
	{
		cout<<"ERROR AL ABRIR ARCHIVO !!! \n";
		terminate();
	}
	else
	{
		auxtoken=0;        // leo el primer char
	}
	palabrasreservadas();    // Construye la tabla de palabras
	inicializarcuadruplos();

	strcpy(cadena,""); // Inicializo la cadena
	while((afile)&&(ch!='�'))       // mientras no sea EOF
	{
		auxtoken=0;
		afile.get(ch);      // saco el primer char del archivo
		cha=ch;
		/*Checo primero comentario,entero,real,reservada,variable,string */
		token=gettoken();
		prcInicial();
	}
	fcuads<<"---separador-de-prueba---"<<'\n';
	fcuads.close();
	afile.close();
	int i;
	for(i=2;i<=75;i++)
	{
		gotoxy(i,2);  cout<<char(95);
	}
	for(i=2;i<=75;i++)
	{
		gotoxy(i,6);  cout<<char(95);
	}
	gotoxy(28,4);  cout<<"MaiSQL";
	gotoxy(10,8);  cout<<"Compilaci�n exitosa";
	gotoxy(15,22); cout<<"Salir? (S/N) ...";
	cin>>salida;
}//compilar

int gettoken()   //-------------------------------------- LEXICO ------GET TOKEN
{
	int aux=0;
	cout<<"";
	while((aux<=0)&&(afile)) // hasta q devuelva un token valido
	{
		//automata diferente !=   menor que <=  mayor que >=
		if((cha==33)||(cha==60)||(cha==62))  //   !  <  >
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			aux=diferentemayormenor();
		}
		else if(cha==47) //automata comentario /
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			aux=comentario();
		}
		else if(isdigit(ch)) //automata de enteros y reales
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			aux=enteroreal();
		}
		else if(isalpha(ch)) //automata palabras reservadas y variables
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			aux=reservadavariable();
		}
		else if(cha==39) //automata 'string'
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			aux=esstring();
		}
		else //delimitadores operadores
		{
			memset(cadena, 0, sizeof(cadena)); //cadena="";  // limpio cadena
			auxtoken=esdelimitador(ch);
			if(auxtoken>0)
			{
				aux=auxtoken;
				afile.get(ch);
				cha=ch;
			}
			else if(auxtoken==0)
			{
				cout<<"Linea: "<<linea<<"Error: No reconocido! "<<ch;
				terminate();
			}
			else  // espacio enter tab
			{
				afile.get(ch);
				cha=ch;
			}
		}
	}//while
	return aux;
}//gettoken

int diferentemayormenor()  //------------------------------------------AUTOMATAS
{
	int auxtoken;
	auxtoken=esdelimitador(ch); // si no entra en ninguno se queda con este token
	if(cha==33)      // !
	{
		afile.get(ch);
		cha=ch;
		if(cha==61)  //el igual =
		{
			auxtoken=63;  // !=
			afile.get(ch);
			cha=ch;
		}
	}
	else if(cha==60)       // <
	{
		afile.get(ch);
		cha=ch;
		if(cha==61)  //el igual =
		{
			auxtoken=64;    // <=
			afile.get(ch);
			cha=ch;
		}
	}
	else if(cha==62)      // >
	{
		afile.get(ch);
		cha=ch;
		if(cha==61)  //el igual =
		{
			auxtoken=65;    // >=
			afile.get(ch);
			cha=ch;
		}
	}
	return auxtoken;
}//diferentemayormenor

int comentario()     //------------------------------------------------AUTOMATAS
{
	auxtoken=esdelimitador(ch); //si no fue comentario regresa el token del /
	afile.get(ch);
	cha=ch;
	if(cha==47)  //comentario //
	{
		auxtoken=0;
		while((ch!='\n')&&(afile))
		{
			afile.get(ch);
		}
      linea++;
		afile.get(ch);
		cha=ch;
	}
	return auxtoken;
}

int enteroreal()      //-----------------------------------------------AUTOMATAS
{
	auxtoken=67;
	len=strlen(cadena);   //calculo el tope de la cadena
	cadena[len]=ch; // guardo el char en el string
	afile.get(ch);
	cha=ch;
	cout<<""; //no hace nada pero si lo quitar no jala !!!
	while(isdigit(ch))
	{
		auxtoken=67;
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		afile.get(ch);
		cha=ch;
	}
	if(ch=='^')
	{
		auxtoken=errordecadena;
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		afile.get(ch);
		cha=ch;
		if((ch=='-')||(ch=='+'))
		{
			auxtoken=errordecadena;
			len=strlen(cadena);   //calculo el tope de la cadena
			cadena[len]=ch; // guardo el char en el string
			afile.get(ch);
			cha=ch;
		}
		if(isdigit(ch))
		{
			while(isdigit(ch))
			{
				auxtoken=67; //enter
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]=ch; // guardo el char en el string
				afile.get(ch);
				cha=ch;
			}
		}
	}
	if(ch=='.')
	{
		auxtoken=errordecadena;
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		afile.get(ch);
		cha=ch;
		{
			while(isdigit(ch))
			{
				auxtoken=68;
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]=ch; // guardo el char en el string
				afile.get(ch);
				cha=ch;
			}
			if(ch=='^')
			{
				auxtoken=errordecadena;
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]=ch; // guardo el char en el string
				afile.get(ch);
				cha=ch;
			}
			if((ch=='-')||(ch=='+'))
			{
				auxtoken=errordecadena;
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]=ch; // guardo el char en el string
				afile.get(ch);
				cha=ch;
			}
			if(isdigit(ch))
			{
				while(isdigit(ch))
				{
					auxtoken=68;//real
					len=strlen(cadena);   //calculo el tope de la cadena
					cadena[len]=ch; // guardo el char en el string
					afile.get(ch);
					cha=ch;
				}
			}
		}
	}
	if(auxtoken==errordecadena)  //Error(bandera);
	{
		cout<<"Linea: "<<linea<<"Error de lexico en entero-real";
		terminate();
	}
	return auxtoken;
}//reales

int reservadavariable() //---------- Automata de palabras reservadas y variables
{
	while(isalpha(ch))
	{
		auxtoken=66;
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		afile.get(ch);
		cha=ch;
	}
	int fueunderscore=0;  //inicializo en false
	while(((isalnum(ch))||(ch=='_'))&&(auxtoken==66)) //var
	//mientras num,letra,underscore y que no haya sido palabra reservada
	{
		auxtoken=66; //var
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		if(ch=='_')
		{
			fueunderscore=1;
		}
		else
		{
			fueunderscore=0;
		}
		afile.get(ch);
		cha=ch;
	}//termina de leer variable
	if(fueunderscore==1)
	{
		auxtoken=errordecadena;//variable que termina en underscore
		cout<<"Linea: "<<linea<<"Error: variable termina en _";
		terminate();
	}
	if(checareservada()!=0)  //checo si fue palabra reservada
	{
		auxtoken=checareservada();
	}
	return auxtoken;
}//variables y palabras reservadas

int esstring() // --------------------------------------------Automata de string
{
	auxtoken=errordecadena; // no guardo el char '
	afile.get(ch);
	cha=ch;     //to ascii
	cout<<"";  //<- no hace nada pero si se quita ya no jala, lo juro!!
	while((cha!=39)&&(ch!='\n')&&(afile))//hasta el otro 39 (ascii del ') o enter
	{
		auxtoken=errordecadena;
		len=strlen(cadena);   //calculo el tope de la cadena
		cadena[len]=ch; // guardo el char en el string
		afile.get(ch);
		cha=ch;     //to ascii
	}
	if(cha==39)        //ni meto el ultimo '
	{
		auxtoken=69;//token string
		afile.get(ch);
		cha=ch;
	}
	else     //fue ENTER o EOF
	{
		auxtoken=errordecadena;
		cout<<"Linea: "<<linea<<" Error: String muy largo";
		terminate();
	}
	return auxtoken;
}//'string'

void error(char valor)   //------------------------------------------------ERROR
{
	cout<<"Linea: "<<linea<<" Error: Se esperaba "<<valor;
	terminate();
}

void palabrasreservadas() //---------------------------------palabras reservadas
{
	strcpy(palabra[1].pal,"A");				palabra[1].token=1;
	strcpy(palabra[2].pal,"AGREGA");    	palabra[2].token=2;
	strcpy(palabra[3].pal,"ASCENDENTE");	palabra[3].token=3;
	strcpy(palabra[4].pal,"CAMPOS");			palabra[4].token=4;
	strcpy(palabra[5].pal,"CHAR");         palabra[5].token=5;
	strcpy(palabra[6].pal,"COMO");         palabra[6].token=6;
	strcpy(palabra[7].pal,"CON");          palabra[7].token=7;
	strcpy(palabra[8].pal,"CREA");         palabra[8].token=8;
	strcpy(palabra[9].pal,"CUANDO");       palabra[9].token=9;//del case
	strcpy(palabra[10].pal,"CUENTA");      palabra[10].token=10;
	strcpy(palabra[11].pal,"DE");          palabra[11].token=11;
	strcpy(palabra[12].pal,"DEFINE");      palabra[12].token=12;
	strcpy(palabra[13].pal,"DESCENDENTE"); palabra[13].token=13;
	strcpy(palabra[14].pal,"DISTINTO");    palabra[14].token=14;
	strcpy(palabra[15].pal,"DONDE");       palabra[15].token=15;
	strcpy(palabra[16].pal,"ELIMINA");     palabra[16].token=16;
	strcpy(palabra[17].pal,"EN");          palabra[17].token=17;
	strcpy(palabra[18].pal,"ENTERO");      palabra[18].token=18;
	strcpy(palabra[19].pal,"PROM");			palabra[19].token=19;//(ENTONCES)
	strcpy(palabra[20].pal,"EXISTE");      palabra[20].token=20;
	strcpy(palabra[21].pal,"FIN");         palabra[21].token=21;//del case
	strcpy(palabra[22].pal,"IDENT");       palabra[22].token=22;
	strcpy(palabra[23].pal,"IDTABLA");     palabra[23].token=23;
	strcpy(palabra[24].pal,"LIMPIA");      palabra[24].token=24;
	strcpy(palabra[25].pal,"LOGICO");		palabra[25].token=25;
	strcpy(palabra[26].pal,"MAX");         palabra[26].token=26;
	strcpy(palabra[27].pal,"MIN");         palabra[27].token=27;
	strcpy(palabra[28].pal,"NULO");        palabra[28].token=28;
	strcpy(palabra[29].pal,"ORDENA");      palabra[29].token=29;
	strcpy(palabra[30].pal,"OTRO");        palabra[30].token=30;//del case
	strcpy(palabra[31].pal,"POR");         palabra[31].token=31;
	strcpy(palabra[32].pal,"REAL");        palabra[32].token=32;
	strcpy(palabra[33].pal,"REGISTROS");   palabra[33].token=33;
	strcpy(palabra[34].pal,"RENOMBRA");    palabra[34].token=34;
	strcpy(palabra[35].pal,"SELECCIONA");  palabra[35].token=35;
	strcpy(palabra[36].pal,"SUMA");        palabra[36].token=36;
	strcpy(palabra[37].pal,"TABLA");       palabra[37].token=37;
	strcpy(palabra[38].pal,"TIPO");        palabra[38].token=38;
	strcpy(palabra[39].pal,"VALORES");     palabra[39].token=39;
	strcpy(palabra[40].pal,"Y");           palabra[40].token=40;
	strcpy(palabra[41].pal,"O");           palabra[41].token=41;
	strcpy(palabra[42].pal,"NO");          palabra[42].token=42;
	strcpy(palabra[43].pal,"CASO");	      palabra[43].token=43;//del case
	strcpy(palabra[44].pal,"VERDADERO");   palabra[44].token=44;
	strcpy(palabra[45].pal,"FALSO");       palabra[45].token=45;
}

int esdelimitador(char ch)   //------------------------------------DELIMITADORES
{
	int cha;
	int token=0;

	if(ch=='\n')
	{
		cha=13;  // el enter lo agarra raro asi q lo manipulamos
		linea++;  //si es <ENTER> incrementa linea
	}
	else
	{
		cha=ch;      // saco el ascii del char
	}
	switch(cha)       // segun el ascii regreso el token
	{
		case 32: // ESPACIO
			token=-1;
		break;
		case 13: // ENTER
			token=-2;
		break;
		case 9: // TAB
			token=-3;
		break;
		case 46: // .
			token=61;
		break;
		case 59: // ;
			token=62;
		break;
		case 40: // (
			token=46;
		break;
		case 41: // )
			token=47;
		break;
		case 91: // [
			token=48;
		break;
		case 93: // ]
			token=49;
		break;
		case 60: // <
			token=50;
		break;
		case 62: // >
			token=51;
		break;
		case 43: // +
			token=52;
		break;
		case 45: // -
			token=53;
		break;
		case 42: // *
			token=54;
		break;
		case 47: // /
			token=55;
		break;
		case 37: // %
			token=56;
		break;
		case 39: // '    comita sencilla
			token=57;
		break;
		case 44: // ,    COMA
			token=58;
		break;
		case 33: // !
			token=59;
		break;
		case 61: //  =
			token=60;
		break;
	}
	return token;
}

int checareservada()  //-----------------------------------------checa reservada
{
	int i,tope;
	tope=strlen(cadena)-1;   //calculo el tope de la cadena
	for (i=0; i<=tope; i++)   //convierto a mayusculas la cadena
	{
		cadena[i] = toupper(cadena[i]);
	}
	int aux=0; //inicializo en 0 q significa error, si la encuentra se pone en 1
	for(i=1;i<=45;i++) // de 1 a 45
	{
		if(strlen(cadena)==strlen(palabra[i].pal))//q sean del tama�o, mas rapido
		{
			if(strcmp(cadena,palabra[i].pal)==0) // compara strings
			{
				aux=palabra[i].token;  // regresa el token
			}
		}
	}
	return aux;
}

//----------------SINTAXIS-SEMANTICA-ACCIONES-----------------------------------

void prcAgrega()    //----------------------------------------------------AGREGA
{
	int tabla;//indice de la matriz
	if(token==2)     // AGREGA
	{
		token=gettoken(); //avanzo
		if(token==1)     // A
		{
			token=gettoken(); //avanzo
			prcTabla();//Esta lo abre y carga
			tabla=topmatriz;
			if(token==39)     // VALORES
			{
				//accion push todos a la pila
				nodo *q;
				q=matriz[tabla].sig;				//me posiciono
				while(q!=NULL)
				{
					pushcampos(q,topmatriz);
					q=q->sig;
				}
				token=gettoken(); //avanzo
			}
			else if(token==46) // (
			{
				token=gettoken(); //avanzo
				prcCampos();
				if(token==47) // )
				{
					token=gettoken(); //avanzo
				}
				else
				{
					error(')');
				}
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: VALORES";
				terminate();
			}
			if(token==46) // (
			{
				do
				{
					token=gettoken(); //avanzo
					prcExpBooleana();
					ejecutatodos();//<--no se si va aqui
				}
				while(token==58);  //  ,
				if(token==47) // )
				{
					token=gettoken(); //avanzo

					//AGREGO al nodo n el pop n
					nodo *n;
					while((topcampos!=NULL)&&(topoperandos!=NULL))
					{
						//cargo valor
						n=topcampos->info;
						int x=n->tipo;
						int y=(int)topoperandos->tipo;
						//CHECO EL TIPO
						if(!compatibles(x,y)) // 0 es false
						{
							cout<<"Linea: "<<linea<<" Error: Type Mismatch";
							terminate();
						}
						//checo el tama�o
						if(y==69)//string
						{
							char aux[50];
							strcpy(aux,(char *)topoperandos->info);
							len=strlen(aux);   //calculo el tope de la cadena
							if(len>n->tamano)
							{
								cout<<"Linea: "<<linea<<" Error: Sobrepasa el ";
								cout<<"tama�o del arreglo";
								terminate();
							}
						}
						//agregas registros
						reg *r=new reg;
						r->valor=topoperandos->info;//se usa y
						r->sigreg=NULL;
						r->abajo=NULL;
						pushreg(r);//meto a pila

						popoperandos();//se tira
						popcampos();
					}//while
					reg *aux;
					while(topreg!=NULL) //vacio pila en fila
					{
						aux=popreg();//saco de la pila
						metereg(aux);//meto a la fila
					}
					metefilareg(tabla); //agrega la pila a la tabla
				}
				else
				{
					error(')');
				}
			}
			else
			{
				prcSubSelecciona();
				//accion q agrega los campos   NO HICE VERIF SEMANTICA
				reg *r;
				if(matriz[tabla].sigreg!=NULL)
				{
					r=matriz[tabla].sigreg;
					while(r->abajo!=NULL)
					{
						r=r->abajo;
					}
					r->abajo=matriz[topmatriz].sigreg;
				}
				else
				{
					matriz[tabla].sigreg=matriz[topmatriz].sigreg;
				}
			}
			//vacias al archivo
			vacia(tabla);
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: A";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: AGREGA";
		terminate();
	}
}//AGREGA

void prcCampo()     //-----------------------------------------------------CAMPO
{
	char name[20];
	if(token==23) // IDTABLA
	{
		token=gettoken(); //avanzo
		if(token==46) // (
		{
			token=gettoken(); //avanzo
			prcTabla();
			if(token==47) // )
			{
				//accion IDTABLA
				nodo *q;
				q=matriz[actualtabla].sig;
				while((q!=NULL)&&(q->id!=1))
				{
					q=q->sig;
				}
				if(!q)
				{
					cout<<"Linea: "<<linea<<" Error: Tabla sin campo identificador";
					terminate();
				}
				pushcampos(q,actualtabla);
				token=gettoken(); //avanzo
			}
			else
			{
				error(')');
			}
		}
		else
		{
			error('(');
		}
	}
	else 	if(token==66)   // VAR
	{
		strcpy(name,cadena);
		token=gettoken(); //avanzo
		if(token==61) // .
		{
			token=gettoken(); //avanzo
			if(token==66) // VAR
			{
				//ACCION
				//busco el campo
				nodo *q;
				int i;
				for(i=1;i<=topmatriz;i++)
				{
					if(strcmp(name,matriz[i].nombre)==0)
					{
						q=matriz[i].sig;
						while((q!=NULL)&&(strcmp(cadena,q->nombre)!=0))
						{
							q=q->sig;
						}
					}
				}
				if(q!=NULL)//encontro el campo
				{
					actualtabla=i;
					pushcampos(q,actualtabla);//le mando el indice de la tabla
				}
				else
				{
					cout<<"Linea: "<<linea<<" Error: no se encontro campo"<<cadena;
					terminate();
				}
				token=gettoken(); //avanzo
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: VARIABLE";
				terminate();
			}
		}
		else		//EPSILON
		{
			nodo *q;
			int aux,i;
			int encontrado=0;       
			i=1;
			while((i<=topmatriz)&&(encontrado==0))
			{
				q=matriz[i].sig;		//me posiciono en el 1�
				aux=strcmp(q->nombre,name);
				while((q!=NULL)&&(aux!=0))
				{
					q=q->sig;
					if(q!=NULL)
					{
						aux=strcmp(q->nombre,name);
					}
				}
				if(q!=NULL)
				{
					encontrado=1;
				}
				i++;
			}
			if(encontrado==1)
			{
				pushcampos(q,i-1);
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: Campo no declarado";
				terminate();
			}
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: Variable o IDTabla";
		terminate();
	}
}//CAMPO

void prcCampos()    //----------------------------------------------------CAMPOS
{
	if(token==23) // IDTABLA
	{    //no le hago get token sino q lo mando directamente a CAMPO
		do
		{
			prcCampo();
		}
		while(token==58); // ,
	}
	else if(token==66) //VAR
	{
		char name[20];
		strcpy(name,cadena);
		token=gettoken();  //avanzo
		if(token==61)   // .
		{
			token=gettoken();  //avanzo
			if(token==54) // *
			{
				//accion push todos a la pila
				nodo *q;
				q=matriz[actualtabla].sig;
				//me posiciono
				while(q!=NULL)
				{
					pushcampos(q,actualtabla);
					q=q->sig;
				}
				token=gettoken();  //avanzo
			}
			else if(token==66) // VAR
			{
				//ACCION
				//busco el campo
				nodo *q;
				int i;
				for(i=1;i<=topmatriz;i++)
				{
					if(strcmp(name,matriz[i].nombre)==0)
					{
						q=matriz[i].sig;
						while((q!=NULL)&&(strcmp(cadena,q->nombre)!=0))
						{
							q=q->sig;
						}
					}
				}
				if(q!=NULL)//encontro el campo
				{
					actualtabla=i;
					pushcampos(q,actualtabla);//le mando el indice de la tabla
				}
				else
				{
					cout<<"Linea: "<<linea<<" Error: no se encontro campo"<<cadena;
					terminate();
				}
				token=gettoken(); //avanzo cadena
				while(token==58) // ,
				{
					token=gettoken();  //avanzo
					prcCampo();
				}
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: *, Variable";
				terminate();
			}
		}
		else // epsilon
		{
			nodo *q;
			q=matriz[topmatriz].sig;		//me posiciono
			int aux=strcmp(q->nombre,name);
			cout<<"";
			while((q!=NULL)&&(aux!=0))   //avanzo hasta q lo ancuentre
			{
				cout<<"";
				q=q->sig;
				if(q!=NULL)
				{
					aux=strcmp(q->nombre,name);
				}
			}
			if(q!=NULL)
			{
				pushcampos(q,topmatriz);
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: Campo no declarado";
				terminate();
			}
			while(token==58) // ,
			{
				token=gettoken();  //avanzo
				prcCampo();
			}
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: Variable o IDTabla";
		terminate();
	}
}//CAMPOS

void prcCrea()    //--------------------------------------------------------CREA
{
	int cont=0;
	ofstream afile;
	if(token==8)     // CREA
	{
		token=gettoken();    //avanzo
		if(token==66)   // VAR
		{
			//accion - crea archivo
			fflush(stdin);
			len=strlen(cadena);   //calculo el tope de la cadena
			cadena[len]='.'; // guardo el .txt en el string
			len=strlen(cadena);
			cadena[len]='t'; //
			len=strlen(cadena);
			cadena[len]='x'; //
			len=strlen(cadena);
			cadena[len]='t'; //
			//verificacion semantica VARIABLE DUPLICADA
/*
			ifstream x;
			x.open(cadena,ios::nocreate);
			if(x)   // si ya existia el archivo
			{
				x.close();
				cout<<"Linea: "<<linea<<" ERROR: Tabla duplicada !!! \n";
				terminate();
			}
*/
			afile.open(cadena); //cadena contiene la variable capturada en lexico
			if(!afile)
			{
				cout<<"Linea: "<<linea<<" ERROR AL CREAR ARCHIVO !!! \n";
				terminate();
			}
			token=gettoken(); //avanzo
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: VARIABLE";
			terminate();
		}
		if(token==7)        // CON
		{
			do
			{
				token=gettoken();   //avanzo
				if(token==66)   // Variable campo
				{
					//accion	 push(campos,cadena)
					metecampos();
					cont++; // cont es local
					token=gettoken();    //avanzo
				}
				else
				{
					cout<<"Linea: "<<linea<<" Error: se esperaba: VARIABLE";
					terminate();
				}
				if(token==38) //TIPO
				{
					token=gettoken();  //avanzo
					prcTipoDato();
				}
				else
				{
					cout<<"Linea: "<<linea<<" Error: se esperaba: TIPO";
					terminate();
				}
			}
			while(token==58);  //  ,
			while(cont>0)
			{
				//accion inserta tabla: pop(campos),pop(tipos),tamano,id
				char nombre[20];
				int tipo;
				int tamano;
				int id;
				cout<<"";
				strcpy(nombre,sacacampos());//instancia.nombre=popcampos();
				cout<<"";
				tipo=sacatipo();
				cout<<"";
				if(tipo==69)//STRING
				{
					int x=*(float *)topoperandos->info;//se usa con casting
					tamano=int(x);
					popoperandos();   // y se tira
				}
				else
				{
					tamano=0; //no fue CHAR, no usa tama�o
				}
				id=0;//por default ninguna es ID
				afile<<nombre<<','<<tipo<<','<<tamano<<','<<id<<';';
				cont--;
			}
			afile.put('\n');
			afile.close();
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: CON";
			terminate();
		}
	}
	else
	{
			cout<<"Linea: "<<linea<<" Error: se esperaba: CREA";
			terminate();
	}
}//CREA

void prcDefine()      //--------------------------------------------------DEFINE
{
	if(token==12)     // DEFINE
	{
		token=gettoken(); //avanzo
		if(token==22) // IDENT
		{
			token=gettoken(); //avanzo
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: IDENT";
			terminate();
		}
		prcTabla();
		if(token==6)        // COMO
		{
			token=gettoken(); //avanzo
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: COMO";
			terminate();
		}
		prcCampo();//SE POSICIONA EN EL CAMPO
		nodo *n;
		n=topcampos->info;
		n->id=1;
		vacia(1);
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: DEFINE";
		terminate();
	}
}//DEFINE

void prcElimina()   //---------------------------------------------------ELIMINA
{
	if(token==16)     // ELIMINA
	{
		token=gettoken(); //avanzo
		if(token==33) // REGISTROS
		{
			token=gettoken(); //avanzo
			if(token==11) // DE
			{
				token=gettoken(); //avanzo
				prcTablas();
				if(token==15) // DONDE
				{
					token=gettoken(); //avanzo
					prcExpBooleana();
					ejecutatodos();//<--no se si va aqui
					while((token==40)||(token==41))
					{
						token=gettoken(); //avanzo
						prcExpBooleana();
						ejecutatodos();//<--no se si va aqui
					}
				}
				else
				{
					cout<<"Linea: "<<linea<<" Error: se esperaba: DONDE";
					terminate();
				}
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: DE";
				terminate();
			}
		}
		else if(token==11) // DE
		{
			token=gettoken(); //avanzo
			prcTabla();
			if(token==4) // CAMPOS
			{
				token=gettoken(); //avanzo
				prcCampos();
				//accion
				while(topcampos!=NULL)
				{
					borra(topcampos->info);
					popcampos();
				}
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: DE";
				terminate();
			}
		}
		else if(token==37) // TABLA
		{
			token=gettoken(); //avanzo
			if(token==66)// variable
			{
				//borra
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]='.'; // guardo el .txt en el string
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]='t'; //
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]='x'; //
				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]='t'; //
				int x=remove(cadena);
				if(x!=0)
				{
					cout<<"Linea: "<<linea<<" Error: Tabla no declarada";
					terminate();
				}
				token=gettoken(); //avanzo
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: Se esperaba tabla";
				terminate();
			}
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: TABLA/CAMPOS/REGISTROS";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: ELIMINA";
		terminate();
	}
	vacia(topmatriz);
}//ELIMINA

void prcExpresion()   //-----------------------------------------------EXPRESION
{
	cout<<"";
	inicio:
	cout<<"";
	prcTermino();
	cout<<"";
	//accion 4
	if(topoperadores!=NULL)
	if((topoperadores->info==52)||(topoperadores->info==53)
	||(topoperadores->info==41)) // +, -, o
	{
		//generar cuadruplo(+,pop(operandos),pop(operadores),t1)
		genera();
	}
	cout<<"";
	if((token==52)||(token==53)||(token==41)) // +, -, o
	{
		cout<<"";
		pushoperadores(token);
		cout<<"";
		token=gettoken(); //avanzo
		cout<<"";
		goto inicio;
	}
}//EXPRESION

void prcExpBooleana()   // -----------------------------------EXPRESION BOOLEANA
{
	if(token==20) //EXISTE
	{
		token=gettoken(); //avanzo
		if(token==46) // (
		{
			token=gettoken(); //avanzo
			prcSubSelecciona();
			//accion :  si hay al menos un registro -> meto un true
			int aux;
			if(matriz[topmatriz].sigreg!=NULL)
			{
				aux=1;//true
			}
			else
			{
				aux=0;//false
			}
			ctes[topctes].valor=aux;
			pushoperandos(25,topctes,-1);  // 25 = logico
			topctes++;

			if(token==47) // )
			{
				token=gettoken(); //avanzo
			}
			else
			{
				error(')');
			}
		}
		else
		{
			error('(');
		}
	}
	else         // no empieza con  no,existe
	{
		prcExpresion();
		if(token==17) // EN
		{
			token=gettoken(); //avanzo
			if(token==46) // (
			{
				token=gettoken(); //avanzo
				prcSubSelecciona();
				//accion lo busca en tabla auxiliar 123
//inicio TODO ESTO ES UN PARCHE PA Q JALE
			ctes[topctes].valor=1;//true
			pushoperandos(25,topctes,-1);  // 25 = logico
			topctes++;
//fin TODO ESTO ES UN PARCHE PA Q JALE
				if(token==47) // )
				{
					token=gettoken(); //avanzo
				}
				else
				{
					error(')');
				}
			}
			else
			{
				error('(');
			}
		}
		else if((token==60)||(token==63)||(token==50)
				||(token==51)||(token==64)||(token==65))//operadores booleanos                                              6
		{
			// accion 8
			pushoperadores(token);
			token=gettoken(); //avanzo
			prcExpresion();
			// accion 9    si topoperadores es operador booleano
			if((topoperadores->info==60)||(topoperadores->info==63)
			||(topoperadores->info==50)||(topoperadores->info==51)
			||(topoperadores->info==64)||(topoperadores->info==65))
			{
				//generar cuadruplo(=,pop(operandos),pop(operadores),t1)
				genera();
			}
		}
		else
		{
			//epsilon
		}
	}
}//EXPRESION BOOLEANA

void prcFactor() //-------------------------------------------------------FACTOR
{
	if(token==42)//NO
	{
		//push NO
		pushoperadores(token);
		token=gettoken(); //avanzo
		if(token==46) // (
		{
			//PUSH MARCA
			//accion 6 PUSH MARCA (
			pushoperadores(token);
			token=gettoken(); //avanzo
			prcExpBooleana();
			if(token==47) // )
			{
				//POP MARCA (
				token=popoperadores();//tiro el pop reusando token
				//genera curdruplo - t t
				generacuadno();//no(a=a)
				token=gettoken(); //avanzo
			}
			else
			{
				error(')');
			}
		}
		else
		{
			error('(');
		}
	}
	else if(token==46) // (
	{

		//accion 6 PUSH MARCA
		pushoperadores(token);
		token=gettoken(); //avanzo
		prcExpBooleana();
		if(token==47) // )
		{
			//POP MARCA
			token=popoperadores();//tiro el pop reusando token
			token=gettoken(); //avanzo
		}
		else
		{
			error(')');
		}
	}
	else
	{
		prcID();
	}
}//FACTOR

void prcFuncion()   //---------------------------------------------------FUNCION
{
	if((token==36)||(token==10)||(token==27)||(token==26)||(token==19))
	{//Suma,Cuenta,Min,Max,prom
		pushoperadores(token);
		token=gettoken(); //avanzo
		if(token==46) // (
		{
			token=gettoken(); //avanzo
			prcCampo();
			if(token==47) // )
			{
				token=gettoken(); //avanzo
				//accion
				int t;
				t=popoperadores();
				if(t==36) //suma
				{
					ctes[topctes].valor=suma(topcampos->info);
					pushoperandos(topcampos->info->tipo,topctes,-1);    //tipo *
					topctes++;
					popcampos();
				}
				else if(t==10)   //cuenta
				{
					ctes[topctes].valor=cuenta(topcampos->info);
					pushoperandos(topcampos->info->tipo,topctes,-1);    //tipo entero
					topctes++;
					popcampos();
				}
				else if(t==27) //min
				{
					if (topcampos->info->tipo==69)  // si es string
					{
						char aux[50];
						strcpy(aux,minstr(topcampos->info));
						strcpy(strs[topstrs].valor,aux);
						pushoperandos(topcampos->info->tipo,-1,topstrs);
						topstrs++;
						popcampos();
					}
					else // es numerico
					{
						ctes[topctes].valor=min(topcampos->info);
						pushoperandos(topcampos->info->tipo,topctes,-1);//tipo
						topctes++;
						popcampos();
					}
				}
				else if(t==26) //max
				{
					if (topcampos->info->tipo==69)  // si es string
					{
						char aux[50];
						strcpy(aux,maxstr(topcampos->info));
						strcpy(strs[topstrs].valor,aux);
						pushoperandos(topcampos->info->tipo,-1,topstrs);
						topstrs++;
						popcampos();
					}
					else // es numerico
					{
						ctes[topctes].valor=max(topcampos->info);
						pushoperandos(topcampos->info->tipo,topctes,-1);//tipo
						topctes++;
						popcampos();
					}
				}
				else if (t==19) // promedio
				{
					float s,c,p;
					s=suma(topcampos->info);
					c=cuenta(topcampos->info);
					p=s/c;
					ctes[topctes].valor=p;
					topctes++;
					pushoperandos(topcampos->info->tipo,topctes,-1);
					popcampos();
				}
			}
			else
			{
				error(')');
			}
		}
		else
		{
			error('(');
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: Funcion";
		terminate();
	}
}//FUNCION

void prcID()       //---------------------------------------------------------ID
{
	if((token==67)||(token==68)||(token==44)||(token==45)||(token==28)
	|| (token==69)) // Entero, Real ,verdadero, falso,nulo, string
	{
		//accion 1
		if(token==69)//string
		{
			strcpy(strs[topstrs].valor,cadena);
			pushoperandos(token,-1,topstrs);
			topstrs++;
		}
		else if(token==44)//verdadero
		{
			ctes[topctes].valor=1;
			pushoperandos(25,topctes,-1);  // 25 = logico
			topctes++;
		}
		else if(token==45)//falso
		{
			ctes[topctes].valor=0;
			pushoperandos(25,topctes,-1); // 25 = logico
			topctes++;
		}
		else if(token==28)//nulo
		{
			ctes[topctes].valor=NULL;
			pushoperandos(token,topctes,-1);
			topctes++;
		}
		else      //entero real
		{
			ctes[topctes].valor=atof(cadena);
			pushoperandos(token,topctes,-1);
			topctes++;
		}
		token=gettoken(); //avanzo
	}
	else
	{
		if((token==36)||(token==10)||(token==27)||(token==26)||(token==19))
		{//Sum,Cuent,Min,Max
			prcFuncion();
		}
		else
		{
			prcCampo();
			//accion
			apuntv *auxv=new apuntv;
			auxv->info=topcampos->info;   //apunta al campo
			auxv->sig=NULL;
			pushoperando(auxv,4);//tipo=CAMPOS
		}
	}
}//ID

void prcInicial()    //--------------------------------------------------INICIAL
{
	prcInstruccion();
	while((token==11)||(token==29)||(token==12)||(token==2)||(token==16)
	||(token==8)||(token==34)||(token==24))
	{ // Los Firsts de Instruccion
		prcInstruccion();
	}
	if(token!=0)   // si no sigue un EOF
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba fin de archivo";
		terminate();
	}
}//INICIAL

void prcInstruccion()      //----------------------------------------INSTRUCCION
{
	if(token==11)//DE
	{
		prcSelecciona();
	}
	else if(token==29)
	{
		prcOrdena();
	}
	else if(token==12)
	{
		prcDefine();
	}
	else if(token==2)
	{
		prcAgrega();
	}
	else if(token==16)
	{
		prcElimina();
	}
	else if(token==8)
	{
		prcCrea();
	}
	else if(token==34)
	{
		prcRenombra();
	}
	else if(token==24)
	{
		prcLimpia();
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba una instruccion";
		terminate();
	}
	if(token==62) // ;
	{
		token=gettoken(); //avanzo
		//accion libera memoria
		for(int i=topmatriz;i>0;i--)
		{
			nodo *x;
			nodo *y;
			x=matriz[i].sig;
			y=x;
			while(y!=NULL)
			{
				y=x->sig;
				delete x;
				x=y;
			}
			matriz[i].sig=NULL;
			memset(matriz[i].nombre, 0, sizeof(matriz[i].nombre));//limpia
		}
		topmatriz=0;
	}
	else
	{
		error(';');
	}
}//INSTRUCCION

void prcLimpia()       //-------------------------------------------------LIMPIA
{
	if(token==24)     // LIMPIA
	{
		token=gettoken();
		prcTabla();
		if(token==1)        // A
		{
			token=gettoken();
			if(token==66)        // VAR
			{
				//renombra
				char anterior[20];
				memset(anterior, 0, sizeof(anterior)); // limpio cadena
				strcpy(anterior,matriz[topmatriz].nombre);
				len=strlen(anterior);   //calculo el tope de la cadena
				anterior[len]='.'; // guardo el .txt en el string
				len=strlen(anterior);   //calculo el tope de la cadena
				anterior[len]='t'; //
				len=strlen(anterior);   //calculo el tope de la cadena
				anterior[len]='x'; //
				len=strlen(anterior);   //calculo el tope de la cadena
				anterior[len]='t'; //

				len=strlen(cadena);   //calculo el tope de la cadena
				cadena[len]='.'; // guardo el .txt en el string
				len=strlen(cadena);
				cadena[len]='t'; //
				len=strlen(cadena);
				cadena[len]='x'; //
				len=strlen(cadena);
				cadena[len]='t'; //
				int x=rename(anterior,cadena);
				if(x!=0)
				{
					cout<<"Linea: "<<linea<<" Error: No se puede limpiar a ";
					cout<<"tabla ya existente";
					terminate();
				}
				token=gettoken();
			}
		}
		else // epsilon
		{
			//borra
			char name[20];
			memset(name, 0, sizeof(name)); // limpio cadena
			strcpy(name,matriz[topmatriz].nombre);
			len=strlen(name);   //calculo el tope de la cadena
			name[len]='.'; // guardo el .txt en el string
			len=strlen(name);   //calculo el tope de la cadena
			name[len]='t'; //
			len=strlen(name);   //calculo el tope de la cadena
			name[len]='x'; //
			len=strlen(name);   //calculo el tope de la cadena
			name[len]='t'; //

			ofstream x;
			x.open(name);
			x<<"";
			if(!x)
			{
				cout<<"Linea: "<<linea<<" Error: Tabla no declarada";
				terminate();
			}
			x.close();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: LIMPIA";
		terminate();
	}
}//LIMPIA

void prcOrdena()   //-----------------------------------------------------ORDENA
{
	if(token==29)     // ORDENA
	{
		token=gettoken();    //avanzo
		prcTabla();
		if(token==31)        // POR
		{
			topcampos=NULL;
			do
			{
				token=gettoken();   //avanzo
				prcCampo();
				if((token==3)||(token==13)) // ASCENDENTE, DESCENDENTE
				{
					pushoperadores(token);
					token=gettoken();  //avanzo
				}
				else
				{
					pushoperadores(3);//default es ascendente
				}
			}
			while(token==58);  //  ,
			//accion ordena
			while(topcampos!=NULL)
			{
				sort(topcampos,popoperadores());
				popcampos();
			}
			//vacias al archivo
			vacia(topmatriz);
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: POR";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: ORDENA";
		terminate();
	}
}//ORDENA

void prcRenombra()  //--------------------------------------------------RENOMBRA
{
	if(token==34)     // RENOMBRA
	{
		token=gettoken(); //avanzo
		prcTabla();//esta checa q exista
		if(token==1)        // A
		{
			token=gettoken(); //avanzo
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: A";
			terminate();
		}
		if(token==66)        // var
		{
			char anterior[20];
			memset(anterior, 0, sizeof(anterior)); // limpio cadena
			strcpy(anterior,matriz[topmatriz].nombre);
			len=strlen(anterior);   //calculo el tope de la cadena
			anterior[len]='.'; // guardo el .txt en el string
			len=strlen(anterior);   //calculo el tope de la cadena
			anterior[len]='t'; //
			len=strlen(anterior);   //calculo el tope de la cadena
			anterior[len]='x'; //
			len=strlen(anterior);   //calculo el tope de la cadena
			anterior[len]='t'; //

			len=strlen(cadena);   //calculo el tope de la cadena
			cadena[len]='.'; // guardo el .txt en el string
			len=strlen(cadena);
			cadena[len]='t'; //
			len=strlen(cadena);
			cadena[len]='x'; //
			len=strlen(cadena);
			cadena[len]='t'; //
			int x=rename(anterior,cadena);
			if(x!=0)
			{
				cout<<"Linea: "<<linea<<" Error: No se puede renombrar a tabla ";
				cout<<"ya existente";
				terminate();
			}
			token=gettoken(); //avanzo
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: A";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: RENOMBRA";
		terminate();
	}
}//RENOMBRA

void prcSelecciona()  //----------------------------------------------SELECCIONA
{
	if(token==11)     //DE
	{
		token=gettoken();  //avanzo
		prcTablas();
		if (token==35) // selecciona
		{
			token=gettoken();  //avanzo
			if (token==54) // *
			{
				//accion push todos a la pila
				nodo *q;
				for(int i=topmatriz;i>0;i--)//for(i=1;i<=topmatriz;i++)
				{
					q=matriz[i].sig;				//me posiciono
					while(q!=NULL)
					{
						pushcampos(q,i);
						q=q->sig;
					}
				}
				token=gettoken(); //avanzo
			}
			else
			{
				prcCampos();
			}
			//generas cuads
			for(int i=1;i<=topmatriz;i++)
			{
				generacuadcampos1(i);//sig y gotov por cada tabla
			}
			//creas tabla auxiliar 123
			topmatriz++;
			strcpy(matriz[topmatriz].nombre,"123");

			//copia los campos a tabla aux 123
			creacampos123();
			if(token==15) // DONDE
			{
				cout<<"";
				token=gettoken();  //avanzo
				cout<<"";
				prcExpBooleana();
			}
			else //epsilon
			{
				//meto un true
				ctes[topctes].valor=1;
				pushoperandos(25,topctes,-1);  // 25 = logico
				topctes++;
			}
			//accion
			if(topsaltos!=NULL)
			{
				//copio
				generacuadcopia();
			}
			while(topsaltos!=NULL)
			{
				generacuadcampos2();
			}
			//ejecuta los cuadruplos
			ejecutatodos();
			if(token==1) // A
			{
				token=gettoken();  //avanzo
				if(token==66) // VAR
				{
					char name[50];
					strcpy(name,cadena);
					token=gettoken();  //avanzo
					if(token==14) // DISTINTO
					{
						//accion borra registros iguales
						/*

						*/
						token=gettoken();  //avanzo
					}
					//renombras tabla
					strcpy(matriz[topmatriz].nombre,name);
					//vacias tabla
					vacia(topmatriz);
				}
			}
			else
			{
				cout<<"Linea: "<<linea<<" Error: se esperaba: A";
				terminate();
			}
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: DE";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: SELECCIONA";
		terminate();
	}
}//SELECCIONA

void prcSubSelecciona()        //----------------------------------SUBSELECCIONA
{
	if(token==11)     //DE
	{
		token=gettoken();  //avanzo
		prcTablas();
		if (token==35) // selecciona
		{
			token=gettoken();  //avanzo
			if(token==54) // *
			{
//
				//accion push todos a la pila
				nodo *q;
				for(int i=topmatriz;i>0;i--)//for(i=1;i<=topmatriz;i++)
				{
					q=matriz[i].sig;				//me posiciono
					while(q!=NULL)
					{
						pushcampos(q,i);
						q=q->sig;
					}
				}
//
				token=gettoken();  //avanzo
			}
			else
			{
				cout<<"";
				prcID();
				cout<<"";
				while(token==58) // ,
				{
					token=gettoken();  //avanzo
					prcID();
				}
			}
//
			//generas cuads
			for(int i=1;i<=topmatriz;i++)
			{
				generacuadcampos1(i);//sig y gotov por cada tabla
			}
			//creas tabla auxiliar 123
			topmatriz++;
			strcpy(matriz[topmatriz].nombre,"123");

			//copia los campos a tabla aux 123
			creacampos123();
//
			if(token==15) // DONDE
			{
				cout<<"";
				token=gettoken();  //avanzo
				cout<<"";
				prcExpBooleana();
				cout<<"";
				while((token==40)||(token==41))    // y o
				{
					token=gettoken(); //avanzo
					prcExpBooleana();
				}
			}
			else //epsilon
			{
//
				//meto un true
				ctes[topctes].valor=1;
				pushoperandos(25,topctes,-1);  // 25 = logico
				topctes++;
//
			}
//
			//accion
			if(topsaltos!=NULL)
			{
				//copio
				generacuadcopia();
			}
			while(topsaltos!=NULL)
			{
				generacuadcampos2();
			}
			//ejecuta los cuadruplos
			ejecutatodos();
//
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: se esperaba: DE";
			terminate();
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: SELECCIONA";
		terminate();
	}
}//SUBSELECCIONA

void prcTabla()         //-------------------------------------------------TABLA
{
	if(token==66)   // VAR
	{
		if(topmatriz>0)
		{
			int encontrado=0;
			for(int i=topmatriz;i>0;i--)
			{
				if(strcmp(cadena,matriz[i].nombre)==0)
				{
					encontrado=i;
				}
			}
			if(encontrado==0)//encontro el campo
			{
				abreycargatabla(1);//y tablen valida q exista (1), que tal eh?
				actualtabla=topmatriz;
			}
			else
			{
				actualtabla=encontrado;
			}
		}
		else
		{
			abreycargatabla(1);//y tablen valida q exista (1), que tal eh?
			actualtabla=topmatriz;
		}
		token=gettoken(); //avanzo
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: Tabla";
		terminate();
	}
}//TABLA

void prcTablas()  //------------------------------------------------------TABLAS
{
	inicio:
	prcTabla();
	if(token==58)   // ,
	{
		token=gettoken();  //avanzo
		goto inicio;
	}
}//TABLAS

void prcTermino()  //----------------------------------------------------TERMINO
{
	inicio:
	prcFactor();
	//accion 4
	if(topoperadores!=NULL)
	if((topoperadores->info==54)||(topoperadores->info==55)
	||(topoperadores->info==56)||(topoperadores->info==40))
	{  // *, /,%, y
		//generar cuadruplo(*,pop(operandos),pop(operadores),t1)
		genera();
	}
	if((token==54)||(token==55)||(token==56)||(token==40)) // *, /,%, y
	{
		pushoperadores(token);
		token=gettoken(); //avanzo
		goto inicio;
	}
}//TERMINO

void prcTipoDato()    //--------------------------------------------TIPO DE DATO
{
	if((token==18)||(token==32)||(token==25)) // Entero, Real, Logico
	{
		//accion
		metetipo(token);
		token=gettoken(); //avanzo
	}
	else if(token==5) //char
	{

		//accion
		metetipo(token);
		token=gettoken(); //avanzo
		if(token==48) // corchete [
		{
			token=gettoken(); //avanzo
			prcExpresion();
			ejecutatodos();//<--no se si va aqui
			//verificacion semantica
			if(topoperandos->tipo!=67)
			{
				cout<<"Linea: "<<linea<<" Error: TypeMismatch";
				terminate();
			}
			if(token==49) // corchete ]
			{
				token=gettoken(); //avanzo
			}
			else
			{
				error(']');
			}
		}
		else
		{
			error('[');
		}
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: se esperaba: Tipo de Dato";
		terminate();
	}
}//TIPO DE DATO

//-------------------------------------------------------------------------FILAS
int sacatipo()
{
	apunti *auxi;
	int a;
	auxi=iniciotipos;
	if(iniciotipos==NULL)
	{
		cout<<"FILA toptipos VACIA\n";
		a=-1;
	}
	else
	{
		a=auxi->info;
		iniciotipos=auxi->sig;
		delete auxi;
	}
	return a;
}

void metetipo(int &valor)
{
	apunti *auxi;
	apunti *q;
	q=new apunti;
	auxi=new apunti;

	auxi->info=conviertetipo(valor);
	auxi->sig=NULL;
	q=iniciotipos;
	if(iniciotipos!=NULL)
	{
		while(q->sig!=NULL)
		{
			q=q->sig;
		}
		q->sig=auxi;
	}
	else
	{
		iniciotipos=auxi;
	}
}

void metecampos()//mete fila
{
	apuntc *q;
	apuntc *auxc;
	q=new apuntc;
	auxc=new apuntc;

	llenarinfo(auxc);//auxc->info=cadena;
	auxc->sig=NULL;
	q=iniciocampos;
	if(iniciocampos!=NULL)
	{
		while(q->sig!=NULL)
		{
			q=q->sig;
		}
		q->sig=auxc;
	}
	else
	{
		iniciocampos=auxc;
	}
}

char* sacacampos()//fila
{
	char* a;
	apuntc *auxc;
	auxc=iniciocampos;
	if(iniciocampos==NULL)
	{
		cout<<"PILA CAMPOS VACIA\n";
		a="-1";
	}
	else
	{
		a=auxc->info;
		iniciocampos=auxc->sig;
		delete auxc;
	}
	return a;
}

void metereg(reg *r)//agrega un reg al campo
{
	reg *q;
	q=inicioreg;
	if(inicioreg!=NULL)
	{
		while(q->sigreg!=NULL)
		{
			q=q->sigreg;
		}
		q->sigreg=r;
	}
	else
	{
		inicioreg=r;
	}
}

void metefilareg(int tabla)//agrega la pila de reg's a la tabla
{
	//recorro hasta el ultimo registro
	reg *r;
	verificaid(tabla);
	if(matriz[tabla].sigreg!=NULL)
	{
		r=matriz[tabla].sigreg;
		while(NULL!=r->abajo)
		{
			r=r->abajo;
		}
		r->abajo=inicioreg;
		inicioreg=r;
	}
	else
	{
		matriz[tabla].sigreg=inicioreg;
	}
	inicioreg=NULL;
}

//-------------------------------------------------------------------------PILAS
void pushreg(reg *aux)
{
	aux->sigreg=topreg;
	topreg=aux;
}

reg* popreg()
{
	reg *a=NULL; //valor q regresa
	if(topreg==NULL)
	{
		cout<<"PILA registros VACIA\n";
	}
	else
	{
		a=topreg;
		topreg=a->sigreg;
		a->sigreg=NULL;
	}
	return a;
}

void popcampos() // nada mas borra uno pero no devuelve nada
{
	apuntn *n;
	if (topcampos==NULL)
	{
		cout<<"PILA campos VACIA\n";
	}
	else
	{
		n=topcampos;
		//a=*n;//info       NO devuelve nada para permitir casting
		topcampos=n->sig;
		delete n;
	}
}

void pushcampos(nodo *n,int tabla)
{
	apuntn *aux=new apuntn;
	aux->info=n;
	aux->tabla=tabla;
	aux->sig=topcampos;
	topcampos=aux;
}

int popoperadores()
{
	int a=-1 ;
	apunti *auxi;
	if(topoperadores==NULL)
	{
		cout<<"PILA operadores VACIA\n";
	}
	else
	{
		auxi=topoperadores;
		a=auxi->info;
		topoperadores=auxi->sig;
		delete auxi;
	}
	return a;
}

void pushoperadores(int valor)
{
	apunti *auxi;
	auxi=new apunti;
	auxi->sig=topoperadores;
	auxi->info=valor;
	topoperadores=auxi;
}

void popoperandos() // nada mas borra uno pero no devuelve nada
{
	apuntv *auxv;
	if (topoperandos==NULL)
	{
		cout<<"PILA OPERANDOS VACIA\n";
	}
	else
	{
		auxv=topoperandos;
		//a=*auxc;//info       NO devuelve nada para permitir casting
		topoperandos=auxv->sig;
		delete auxv;
	}
}

void pushoperandos(int tipo,int posctes,int posstrs)
{
	apuntv *auxv;
	auxv=new apuntv;
	auxv->sig=topoperandos;
	auxv->tipo=tipo;
	if(posctes>=0) //es constante
	{
		auxv->info=&ctes[posctes].valor;
	}
	else // es string
	{
		auxv->info=&strs[posstrs].valor;
	}
	topoperandos=auxv;
}

void pushoperando(apuntv *aux,int tipo)
{
	aux->tipo=tipo;
	aux->sig=topoperandos;
	topoperandos=aux;
}

void pushsaltos(cuadruplo *cuad)
{
	apunts *auxs=new apunts;
	auxs->info=cuad;
	auxs->sig=topsaltos;
	topsaltos=auxs;
}

cuadruplo* popsaltos()
{
	cuadruplo *a=NULL ;
	apunts *auxs;
	if(topsaltos==NULL)
	{
		cout<<"PILA saltos VACIA\n";
	}
	else
	{
		auxs=topsaltos;
		a=auxs->info;
		topsaltos=auxs->sig;
		delete auxs;
	}
	return a;
}

//--------------------------------------------------------cuadruplos y ejecucion
void inicializarcuadruplos()
{
	fcuads.open("cuads.txt",ios::ate);//abre archivo de cuads
	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	topcuadruplos=cuadcontmas1;
}

void genera()    //-------------------------------------------------------GENERA
{
	//generar cuadruplo(=*-/+,pop(operandos),pop(operadores),t1)

	//si hay un campo en la pila hago un TOMA
	if(topoperandos->tipo==4)
	{
		generacuadtoma(2);
	}
	if(topoperandos->sig->tipo==4)
	{
		generacuadtoma(1);
	}
	int tipo1,tipo2,tipo;
	apuntv *temp=new apuntv;
	apuntv *buffer=new apuntv;
	cuadruplo *cuad;
	cuad=cuadcontmas1;
	cuad->operador=popoperadores();

	cuad->dos->info=topoperandos->info;//apunta a donde apuntaba info
	cuad->dos->tipo=topoperandos->tipo;
	popoperandos();//si era temp falta el dispose

	cuad->uno->info=topoperandos->info;
	cuad->uno->tipo=topoperandos->tipo;
	popoperandos();//si era temp falta el dispose

	tipo1=cuad->uno->tipo;
	if(tipo1==4)
	{
		nodo *n;
		n=(nodo *)cuad->uno->info;
		tipo1=n->tipo;
	}
	tipo2=cuad->dos->tipo;
	if(tipo2==4)
	{
		nodo *n;
		n=(nodo *)cuad->dos->info;
		tipo1=n->tipo;
	}
	if((cuad->operador==60)||(cuad->operador==63)
	||(cuad->operador==50)||(cuad->operador==51)
	||(cuad->operador==64)||(cuad->operador==65))
	{
		tipo=25;//boolean
	}
	else if((tipo1==68)||(tipo2==68))//real
	{
		tipo=68;
	}
	else if(tipo1==tipo2)
	{
		tipo=cuad->dos->tipo;
	}
	else
	{
		cout<<"Linea: "<<linea<<" Error: Type mismatch";
		terminate();
	}
	temp->info=&buffer->tipo;//este temp se va a la pila
	temp->sig=NULL;
	//	temp->temp=1;
	cuad->tres->info=&buffer->tipo; //TEMP
	cuad->tres->tipo=tipo;
	cuad->tres->sig=buffer;
	pushoperando(temp,tipo);

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuad->sig=cuadcontmas1;
}

void generacuadno()    //no(a=a)
{
	//genera cuardruplo - t t
	int tipo;
	apuntv *temp=new apuntv;
	apuntv *buffer=new apuntv;
	cuadruplo *cuad;
	cuad=cuadcontmas1;

	cuad->operador=popoperadores();//42 = NO

	cuad->uno->info=topoperandos->info;
	tipo=topoperandos->tipo;
	popoperandos();//si era temp falta el dispose

	temp->info=&buffer->tipo;//este temp se va a la pila
	temp->sig=NULL;
//	temp->temp=1;

	cuad->dos->info=&buffer->tipo; //TEMP
	cuad->dos->sig=buffer;

	cuad->tres->info=NULL;
	pushoperando(temp,tipo);

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;
}

void generacuadcampos1(int tabla) //------cuadruplos de--------------SIG y GOTOV
{
	apuntv *temp;
	apuntv *buffer;

	cuadruplo *cuad;

	//init, incializa
	cuad=cuadcontmas1;
	cuad->operador=72;//init

	cuad->uno->info=NULL;
	cuad->uno->tipo=tabla;

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;


	//sig reg: tabla, ---, eof
	cuad=cuadcontmas1;
	cuad->operador=73;//sig reg

	cuad->uno->info=NULL;
	cuad->uno->tipo=tabla;
	cuad->dos->info=NULL;//no se usa
	cuad->dos->tipo=0;
	temp=new apuntv;
	buffer=new apuntv;
	temp->info=&buffer->tipo;//este temp se va a la pila
	temp->sig=NULL;
	/*	temp->temp=1; */
	cuad->tres->info=&buffer->tipo; //TEMP
	cuad->tres->tipo=25;//booleano
	cuad->tres->sig=buffer;
	pushoperando(temp,25);//booleano

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;

	pushsaltos(cuad);


	//GOTOV: pop, popsaltos(o ultimo cuad)
	cuad=cuadcontmas1;
	cuad->operador=74;//gotov
	cuad->uno->info=topoperandos->info;
	popoperandos();
	cuad->uno->tipo=25;//booleano
//	cuad->dos->info=topoperandos->info;

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;
}

void generacuadcampos2()//cuadruplos de ------------------------------------GOTO
{
	//copia registro

	//GOTO, popsaltos
	cuadruplo *cuad;
	cuadruplo *auxc;
	cuad=cuadcontmas1;

	cuad->operador=70;//goto
//	apunts *q;
	auxc=popsaltos();
//	q->info=auxc;
	cuad->uno->info=auxc; //q->info;

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;

	//relleno con cont+1
	auxc=auxc->sig;
	auxc->dos->info=cuadcontmas1;
}

void generacuadtoma(int cual)//---------------------------------------------toma
{
	//toma: tabla, campo
	cuadruplo *cuad;
	cuad=cuadcontmas1;
	nodo *n;
	cuad->operador=75;//toma
	cuad->uno->info=NULL;
	if(cual==2)
	{
		n=(nodo *)topoperandos->info;   //(topcampos->info);
	}
	else if(cual==1)
	{
		n=(nodo *)topoperandos->sig->info;
	}
	cuad->uno->tipo=gettabla(n);
	cuad->dos->info=n;
	cuad->dos->tipo=n->tipo;
	cuad->tres->tipo=cual;

	popcampos();

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;
}

void generacuadcopia()//---------------------------------------------------copia
{
	//toma: tabla, campo
	cuadruplo *cuad;
	cuad=cuadcontmas1;
	cuad->operador=76;//copia

	cuad->uno->info=topoperandos->info;//si es true, hace copia
	cuad->uno->tipo=topoperandos->tipo;//si es true, hace copia
	popoperandos();

	cuadcontmas1=new cuadruplo;
	cuadcontmas1->operador=-1;
	cuadcontmas1->uno=new apuntv;
	cuadcontmas1->dos=new apuntv;
	cuadcontmas1->tres=new apuntv;
	cuadcontmas1->sig=NULL;
	cuad->sig=cuadcontmas1;
}

void ejecutatodos()  //--------------------------------------------EJECUTA TODOS
{
	actualcuad=topcuadruplos;
	while((actualcuad!=NULL)&&(actualcuad->operador>0))//-1 es el cuadcontmas1
	{
		ejecuta();//solito avanza
	}
}

void ejecuta()  // ------------------------------------------------------ejecuta
{
	//ejecuta el top
	if(actualcuad->operador==52)//+
	{
		if((actualcuad->uno->tipo==67)&&(actualcuad->dos->tipo==67))//entero
		{
			int uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(int)uno+(int)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(int)tres;//actualiza valor del buffer
		}
		else    //reales
		{
			float uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(float)uno+(float)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(float)tres;//actualiza valor del buffer
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==53)//-
	{
		if((actualcuad->uno->tipo==67)&&(actualcuad->dos->tipo==67))//entero
		{
			int uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(int)uno-(int)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(int)tres;//actualiza valor del buffer
		}
		else    //reales
		{
			float uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(float)uno-(float)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(float)tres;//actualiza valor del buffer
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==54)//*
	{
		if((actualcuad->uno->tipo==67)&&(actualcuad->dos->tipo==67))//entero
		{
			int uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(int)uno*(int)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(int)tres;//actualiza valor del buffer
		}
		else    //reales
		{
			float uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(float)uno*(float)dos;
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(float)tres;//actualiza valor del buffer
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==55)// /
	{
		float uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		if(dos==0)
		{
			cout<<"Linea: "<<linea<<" Error: division entre cero";
			terminate();
		}
		tres=uno/dos;
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==60)// =
	{
		if(actualcuad->uno->tipo!=69)//no string
		{
			int uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(uno==dos);
			apuntv *q;//=new apuntv  //(int)
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=tres;//actualiza valor del buffer
		}
		else
		{
			char uno[50];
			char dos[50];
			int tres;
			strcpy(uno,(char *)actualcuad->uno->info);
			strcpy(dos,(char *)actualcuad->dos->info);
			tres=strcmp(uno,dos);
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			if(tres==0)
			{
				q->tipo=0;//actualiza valor del buffer
			}
			else
			{
				q->tipo=1;//actualiza valor del buffer
			}
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==63)// !=
	{
		if(actualcuad->uno->tipo!=69)//string
		{
			int uno,dos,tres;
			uno=*(float *)actualcuad->uno->info;
			dos=*(float *)actualcuad->dos->info;
			tres=(uno!=dos);
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=(int)tres;//actualiza valor del buffer
		}
		else
		{
			char uno[50];
			char dos[50];
			int tres;
			strcpy(uno,(char *)actualcuad->uno->info);
			strcpy(dos,(char *)actualcuad->dos->info);
			tres=strcmp(uno,dos);
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			if(tres==0)
			{
				q->tipo=1;//actualiza valor del buffer
			}
			else
			{
				q->tipo=0;//actualiza valor del buffer
			}
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==50)// <
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno<dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==51)// >
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno>dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==64)// <=
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno<=dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==65)// >=
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno>=dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==56)// %
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno%dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==42)// NO
	{
		int uno,dos;
		uno=*(float *)actualcuad->uno->info;
		dos=(!uno);
		apuntv *q;
		q=actualcuad->dos->sig;//toma la direccion
		q->tipo=(int)dos;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==40)// Y
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno&&dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==41)// O
	{
		int uno,dos,tres;
		uno=*(float *)actualcuad->uno->info;
		dos=*(float *)actualcuad->dos->info;
		tres=(uno||dos);
		apuntv *q;
		q=actualcuad->tres->sig;//toma la direccion
		q->tipo=(int)tres;//actualiza valor del buffer

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==70)//GOTO, direc
	{
		imprimecuad(actualcuad);
		actualcuad=(cuadruplo *)actualcuad->uno->info;
	}
	if(actualcuad->operador==71)//GOTOF, direc
	{
	/* No se usan*/
	}
	if(actualcuad->operador==72)//INIT inicializa
	{
		int tabla;
		tabla=actualcuad->uno->tipo;
		matriz[tabla].actualreg=0;

		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==73)//sig reg: tabla, ---, eof
	{
		int tabla;
		tabla=actualcuad->uno->tipo;
		matriz[tabla].actualreg++;
		if(matriz[tabla].actualreg>matriz[tabla].cuentareg)
		{
			int tres=1;//true
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=tres;//actualiza valor del buffer
		}
		else
		{
			int tres=0;//true
			apuntv *q;
			q=actualcuad->tres->sig;//toma la direccion
			q->tipo=tres;//actualiza valor del buffer
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==74)//GOTOV, pop 'eof', 2 cuads abajo
	{
		int eof;
		eof=*(float *)actualcuad->uno->info;
		//popoperandos();
		imprimecuad(actualcuad);//*******

		if(eof==1)//true : salto 2 cuadruplos
		{
			while((actualcuad!=NULL)&&(actualcuad->operador!=-1))//brinco todos
			{
				actualcuad=actualcuad->sig;
			}
		}
		else
		{
			actualcuad=actualcuad->sig;
		}
	}
	if(actualcuad->operador==75)//toma: tabla, campo
	{
		if(actualcuad->tres->tipo==1)    //toma1
		{
			int tabla;
			nodo *n;
			reg *r;
			n=(nodo *)actualcuad->dos->info;
			tabla=actualcuad->uno->tipo;
			actualcuad->sig->uno->tipo=n->tipo;
			r=regposicion(n,matriz[tabla].actualreg);
			actualcuad->sig->uno->info=r->valor;
		}
		else if(actualcuad->tres->tipo==2)  //toma2
		{
			int tabla;
			nodo *n;
			reg *r;
			n=(nodo *)actualcuad->dos->info;
			tabla=actualcuad->uno->tipo;
			actualcuad->sig->sig->dos->tipo=n->tipo;
			r=regposicion(n,matriz[tabla].actualreg);
			actualcuad->sig->sig->dos->info=r->valor;
		}
		imprimecuad(actualcuad);
		actualcuad=actualcuad->sig;
	}
	if(actualcuad->operador==76)//copio
	{
		reg *r;
		reg *aux;
		apuntn *q;
		int tabla;
		int auxi;
		int cont=0;
		q=topcampos;
		auxi=*(float *)actualcuad->uno->info;
		if(auxi==1)
		{
			while(q!=NULL)//ciclo de campos
			{
				//copio
				cont++;
				tabla=gettabla(q->info);
				//aux=regposicion(q->info,tabla);
            aux=regposicion(q->info,matriz[tabla].actualreg);
				r=new reg;
				r->valor=aux->valor;
				r->sigreg=NULL;
				r->abajo=NULL;
				metereg(r);//meto a la fila
				q=q->sig;
			}
			metefilareg(topmatriz); //agrega la pila a la tabla
		}
//		imprimecuad(actualcuad);  <- no jala con esto  << BUG DE C++ >>
		fcuads<<"COPIO "<<auxi<<'\n';//  <- asi q lo hago a mano
		actualcuad=actualcuad->sig;
	}
}

void imprimecuad(cuadruplo *cuad)//----------------------------IMPRIME CUADRUPLO
{
	float x;
	int op;
	op=cuad->operador;
	imprimeoperador(op);

	if(cuad->operador<70)//cuadruplo normales
	{
		x=*(float *)cuad->uno->info;
		fcuads<<x;
		fcuads.put(' ');

		x=*(float *)cuad->dos->info;
		fcuads<<x;
		fcuads.put(' ');

		if(cuad->tres->info!=NULL)
		{
			x=*(float *)cuad->tres->info;
			fcuads<<x;
		}
	}
	else if(cuad->operador==70)//GOTO
	{
   //NO SE IMPRIME LA DIRECC
	}
	else if(cuad->operador==71)//GOTOF
	{
		x=*(float *)cuad->uno->info; //eof
		fcuads<<x;
		fcuads.put(' ');
	}
	else if(cuad->operador==72)//INIT
	{
		x=cuad->uno->tipo; //eof
		fcuads<<x;
		fcuads.put(' ');
	}
	else if(cuad->operador==73)//SIG REG
	{
		int x;
		char cad[50];
		x=cuad->uno->tipo; //tabla
		strcpy(cad,matriz[x].nombre);
		fcuads<<cad;
		fcuads.put(' ');

		x=*(float *)cuad->tres->info;//eof
		fcuads<<x;
		fcuads.put(' ');
	}
	else if(cuad->operador==74)//GOTOV
	{
		x=*(float *)cuad->uno->info; //eof
		fcuads<<x;
		fcuads.put(' ');
	}
	else if(cuad->operador==75)//toma
	{
		char cad[50];
		nodo *n;
		n=(nodo *)actualcuad->dos->info;
		strcpy(cad,n->nombre);
		fcuads<<cad;
		fcuads.put(' ');
	}
	else if(cuad->operador==76)//copia
	{
		x=*(float *)cuad->uno->info; //eof
		fcuads<<x;
		fcuads.put(' ');
	}
	fcuads.put('\n');
}

void imprimeoperador(int tipo) // ------------------------------IMPRIME OPERADOR
{
	// devuelve el char para imprimir en archivo
	if(tipo==52)
	{
		fcuads<<"+ ";
	}
	else if(tipo==53)
	{
		fcuads<<"- ";
	}
	else if(tipo==54)
	{
		fcuads<<"* ";
	}
	else if(tipo==55)
	{
		fcuads<<"/ ";
	}
	else if(tipo==56)
	{
		fcuads<<"% ";
	}
	else if(tipo==60)
	{
		fcuads<<"= ";
	}
	else if(tipo==63)
	{
		fcuads<<"!= ";
	}
	else if(tipo==50)
	{
		fcuads<<"< ";
	}
	else if(tipo==51)
	{
		fcuads<<"> ";
	}
	else if(tipo==64)
	{
		fcuads<<"<= ";
	}
	else if(tipo==65)
	{
		fcuads<<">= ";
	}
	else if(tipo==42)
	{
		fcuads<<"NO ";
	}
	else if(tipo==40)
	{
		fcuads<<"Y ";
	}
	else if(tipo==41)
	{
		fcuads<<"O ";
	}
	else if(tipo==70)
	{
		fcuads<<"GOTO ";
	}
	else if(tipo==71)
	{
		fcuads<<"GOTOF ";
	}
	else if(tipo==72)
	{
		fcuads<<"INIT ";
	}
	else if(tipo==73)
	{
		fcuads<<"SIG ";
	}
	else if(tipo==74)
	{
		fcuads<<"GOTOV ";
	}
	else if(tipo==75)
	{
		fcuads<<"TOMA ";
	}
	else if(tipo==76)
	{
		fcuads<<"COPIO ";
	}
	else
	{
		cout<<"no reconcio "<<tipo;
	}
}

int conviertetipo(int tipo)  // ----------------------------------CONVIERTE TIPO
{
	// cambia ENTERO por el token de entero
	if(tipo==5)  //CHAR
	{
		return 69;//string
	}
	else if(tipo==18)//ENTERO
	{
		return 67;//entero
	}
	else if(tipo==32)//REAL
	{
		return 68;//real
	}
	else
	{
		return tipo;
	}
}

//----------------------------------------------------------procedimientos otros
void creacampos123()
{
	apuntn *q;
	q=topcampos;
	nodo *n;
	nodo *aux;
	while(q!=NULL)
	{
		n=new nodo;
		aux=q->info;
		strcpy(n->nombre,aux->nombre);
		n->tipo=aux->tipo;
		n->tamano=aux->tamano;
		n->id=aux->id;
		n->sig=NULL;
		insertacampo123(n);
		q=q->sig;
	}
}

void insertacampo123(nodo *n)
{
	if(matriz[topmatriz].sig==NULL)
	{
		matriz[topmatriz].sig=n;
	}
	else
	{
		nodo *q;
		q=matriz[topmatriz].sig;
		if(strcmp(q->nombre,n->nombre)==0)
		{
			cout<<"Linea: "<<linea<<" Error: campo duplicado "<<n->nombre;
			terminate();
		}
		while(q->sig!=NULL)
		{
			q=q->sig;
			if(strcmp(q->nombre,n->nombre)==0)
			{
				cout<<"Linea: "<<linea<<" Error: campo duplicado "<<n->nombre;
				terminate();
			}
		}
		q->sig=n;
	}
}

void verificaid(int tabla)
{
	//verifica que los id no se repitan
	//busca el campo id
	//busca sus valores
	//checa en inicioreg si existe y marca error
}

void llenarinfo(apuntc *apunt)// ------------------------------------LLENAR INFO
{
	for(int i=0;cadena[i]!='\0';i++)
	{
		apunt->info[i]=cadena[i];
	}
	apunt->info[i]=cadena[i];
}

int compatibles(int x, int y) // ------------------------------------COMPATIBLES
{
	// 25=logico 67=entero 68=real 69=string
	int aux;
	if(((x==68)&&(y==67))||((x==68)&&(y==67)))   // real=entero;
	{
		aux=1;
	}
	else if(x==y) //mismo tipo
	{
		aux=1;
	}
	else     //tipos no compatibles
	{
		aux=0;
	}
	return aux;
}

void abreycargatabla(int nocreate)// -------------------------------ABRE Y CARGA
{
	//semantica, valida que exista
	char name[20];
	topmatriz++;
	memset(name, 0, sizeof(name)); //limpio
	strcpy(name,cadena);
	fflush(stdin);// aun no se que hace esto pero lo tenia el editor
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='.'; // guardo el .txt en el string
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='t'; //
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='x'; //
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='t'; //
	char nombre[20];
	int tipo;
	int tamano;
	int id;
	ifstream afile;
	if(nocreate==1)
	{
		afile.open(name,ios::nocreate);//este valida q exista
	}
	else
	{
		afile.open(name); //lo crea, exista o no
	}
	if(!afile)
	{
		cout<<"Linea: "<<linea<<" Error: tabla no declarada "<<cadena;
		terminate();
	}
	//cargo tabla a memoria
	strcpy(matriz[topmatriz].nombre,cadena); //guardas nombre de tabla en matriz
	matriz[topmatriz].sig=NULL;
	matriz[topmatriz].sigreg=NULL;
	matriz[topmatriz].actualreg=0;
	matriz[topmatriz].cuentareg=0;
	char ch=NULL;
	afile>>ch;
	while((afile)&&(ch!='\n'))
	{
		nodo *n = new nodo;
		memset(nombre, 0, sizeof(nombre)); //limpio
		while(ch!=',')       //leo el nombre char x char hasta la coma
		{
			len=strlen(nombre); //calculo el tope
			nombre[len]=ch; //le agrego el char
			afile>>ch;
		}
		afile>>tipo>>ch>>tamano>>ch>>id>>ch;
		strcpy(n->nombre,nombre);
		n->tipo=tipo;
		n->tamano=tamano;
		n->id=id;
		n->sig=NULL;
		//inserta
		if(matriz[topmatriz].sig!=NULL) //inserto al final
		{
			nodo *aux;
			aux=matriz[topmatriz].sig;
			while(aux->sig!=NULL)//recorro hasta el final
			{
				aux=aux->sig;
			}
			aux->sig=n; //n queda al final de la lista
		}
		else
		{
			matriz[topmatriz].sig=n;
		}
		afile.get(ch);//leo el separador @ o la primera letra
	}//while

	//cargo los reg's
	nodo *n;
	int cuenta=0;
	reg *r;
	reg *vertical;
	reg *horizontal;
	afile.get(ch);//leo el eof o el inicio del reg
	while(afile)
	{
		n=matriz[topmatriz].sig;//pongo n en inicio
		r=new reg;
		if(!matriz[topmatriz].sigreg)  //NULL
		{
			matriz[topmatriz].sigreg=r;
			horizontal=r;
			vertical=r;
			cuenta++;
		}
		else
		{
			vertical->abajo=r;
			vertical=vertical->abajo;
			horizontal=vertical;
			cuenta++;
		}
		r->sigreg=NULL;
		r->valor=NULL;
		r->abajo=NULL;
		if((n->tipo==25)||(n->tipo==67))//logico,entero
		{
			int val;
			afile>>val>>ch;
			ctes[topctes].valor=val;
			r->valor=&ctes[topctes].valor;
			topctes++;
		}
		else if(n->tipo==69)//string
		{
			char val[50];
			while((ch!=';')&&(ch!='\n'))  //leo char x char hasta ';'
			{
				len=strlen(val); //calculo el tope
				val[len]=ch; //le agrego el char
				afile>>ch;
			}
			strcpy(strs[topstrs].valor,val);
			r->valor=&strs[topstrs].valor;
			topstrs++;
		}
		else if(n->tipo==68)//real
		{
			float val;
			afile>>val>>ch;
			ctes[topctes].valor=val;
			r->valor=&ctes[topctes].valor;
			topctes++;
		}
		n=n->sig;

		while(n!=NULL)//ciclo q recorre los campos (headers)
		{
			r=new reg;
			if(!vertical)  //NULL
			{
				vertical->sigreg=r;
				horizontal=r;
				horizontal=horizontal->sigreg;
			}
			else
			{
				horizontal->sigreg=r;
				horizontal=horizontal->sigreg;
			}
			r->sigreg=NULL;
			r->valor=NULL;
			r->abajo=NULL;

			if((n->tipo==25)||(n->tipo==67))//logico,entero
			{
				int val;
				afile>>val>>ch;
				ctes[topctes].valor=val;
				r->valor=&ctes[topctes].valor;
				topctes++;
			}
			else if(n->tipo==69)//string
			{
				char val[50];
				memset(val, 0, sizeof(val)); //limpio
				afile>>ch;
				while((ch!=';')&&(ch!=',')&&(ch!='\n'))//leo char x char hasta ';'
				{
					len=strlen(val); //calculo el tope
					val[len]=ch; //le agrego el char
					afile>>ch;
				}
				strcpy(strs[topstrs].valor,val);
				r->valor=&strs[topstrs].valor;
				topstrs++;
			}
			else if(n->tipo==68)//real
			{
				float val;
				afile>>val>>ch;
				ctes[topctes].valor=val;
				r->valor=&ctes[topctes].valor;
				topctes++;
			}
			n=n->sig;
		}//while de campos (header)
	}//while de afile
	afile.close();
	matriz[topmatriz].cuentareg=cuenta;
}

void vacia(int tabla)//----------------------------------------------------VACIA
{
	char nombre[20];
	int tipo;
	int tamano;
	int id;
	ofstream file;
	char name[20];
	nodo *n;
	reg *r;
	reg *horizontal;
	reg *vertical;

	n=matriz[tabla].sig;
	r=matriz[tabla].sigreg;

	//abres archivo
	memset(name, 0, sizeof(name)); //limpio
	strcpy(name,matriz[tabla].nombre);
	fflush(stdin);// aun no se que hace esto pero lo tenia el editor
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='.'; // guardo el .txt en el string
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='t'; //
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='x'; //
	len=strlen(name);   //calculo el tope de la cadena
	name[len]='t'; //
	file.open(name); //,ios::nocreate);
	if(!file)
	{
		cout<<"Linea: "<<linea<<" Error: El archivo no se pudo abrir";
		terminate();
	}
	//escribes header y creas una fila con los tipos
	iniciotipos=NULL;
	while(n!=NULL)
	{
		strcpy(nombre,n->nombre);
		tipo=n->tipo;
		metetipo(tipo);
		tamano=n->tamano;
		id=n->id;
		file<<nombre<<','<<tipo<<','<<tamano<<','<<id<<';';
		n=n->sig;
		if(!n)
		{
			file<<'\n';  //fin de header
		}
	}
	//escribes registros con casting
	r=NULL;
	horizontal=matriz[tabla].sigreg;
	vertical=matriz[tabla].sigreg;
	while(vertical!=NULL)
	{
		while(horizontal!=NULL)
		{
			tipo=sacatipo(); //lo saco
			metetipo(tipo); //y lo mando al ultimo
			r=horizontal;
			//escribes n  con casting
			if(tipo==69)//string
			{
				file<<";"<<(char *)r->valor;
			}
			else if(tipo==67)//entero
			{
				int x=*(float *)r->valor;
				file<<";"<<x;
			}
			else if(tipo==68)//real
			{
				float x=*(float *)r->valor;
				file<<";"<<x;
			}
			else //logico
			{
				int x=*(float *)r->valor;
				file<<";"<<x;
			}
			//avanzo la horizontal
			horizontal=horizontal->sigreg;
		}
		//avanzo la vertical
		file<<'\n';
		vertical=vertical->abajo;
		horizontal=vertical;
	}
	//cierras archivo
	file.close();
	//vacia la fila tipos
	while(iniciotipos!=NULL)
	{
		tipo=sacatipo();
	}
	//liberas reg's
	horizontal=matriz[tabla].sigreg;
	vertical=matriz[tabla].sigreg;
	while(vertical!=NULL) //ciclo q borra las horizontales
	{
		r=horizontal->sigreg;
		while(r!=NULL)
		{
			horizontal=r->sigreg;
			delete r;
			r=horizontal;
		}
		//avanzo la vertical
		vertical=vertical->abajo;
		horizontal=vertical;
	}
	vertical=matriz[tabla].sigreg;
	r=matriz[tabla].sigreg;
	while(r!=NULL)  //ciclo q borra las verticales
	{
		vertical=r->abajo;
		delete r;
		r=vertical;
	}
	//liberas nodos
	nodo *aux;
	n=matriz[tabla].sig;
	while(n!=NULL)
	{
		aux=n->sig;
		delete n;
		n=aux;
	}
	matriz[tabla].sig=NULL;
	//limpias matriz
	memset(matriz[tabla].nombre, 0, sizeof(matriz[tabla].nombre));//limpia
}

void swap(int conta,int contb)//--------------------------------------------SWAP
{  // abajo   ok
	reg *a;
	reg *b;
	if((conta==1)&&(contb==2))
	{
		a=matriz[topmatriz].sigreg;//posiciono A
		b=a->abajo;//posiciono b
		a->abajo=b->abajo;//swap
		b->abajo=a;//swap
		matriz[topmatriz].sigreg=b;//swap
	}
	else
	{
		int i;
		reg *padre;
		padre=matriz[topmatriz].sigreg;
		for(i=1;i<(conta-1);i++)
		{
			padre=padre->abajo;
		}
		a=padre->abajo;//posiciono A
		b=a->abajo;//posiciono B
		a->abajo=b->abajo;//swap
		b->abajo=a;//swap
		padre->abajo=b;//swap
	}
}

void sort(apuntn *n,int ascendente)  // -----------------------------BUBBLE SORT
{
	int ok;
	int x;
	int tipo;
	nodo *campo;
	campo=n->info;
	x=cuenta(campo);
	tipo=campo->tipo;  //67 entero, 68 real, 69 string, 25 logico.
	if ((tipo==67) || (tipo==25))
	{
		do
		{
			ok=1;
			for(int i=1;i<=x-1;i++)
			{
				if(ascendente==3)
				{
					if (regvalorint(campo,i)>regvalorint(campo,i+1))
					{
						swap(i,i+1);
						ok=0;
					}
				}
				else //descendente 13
				{
					if (regvalorint(campo,i)<regvalorint(campo,i+1))
					{
						swap(i,i+1);
						ok=0;
					}
				}
			}
		}
		while(!ok);
	}
	else if(tipo==68) // reales
	{
		do
		{
			ok=1;
			for(int i=1;i<=x-1;i++)
			{
				if (ascendente==3)
				{
					if (regvalorfloat(campo,i)>regvalorfloat(campo,i+1))
					{
						swap(i,i+1);
						ok=0;
					}
				}
				else
				{
					if (regvalorfloat(campo,i)<regvalorfloat(campo,i+1))
					{
						swap(i,i+1);
						ok=0;
					}
				}
			}
		}
		while(!ok);
	}
	else if(tipo==69)//string
	{
		do
		{
			ok=1;
			for(int i=1;i<=x-1;i++)
			{
				if (ascendente==3)
				{
					if(strcmp(regvalorchar(campo,i),regvalorchar(campo,i+1))>0)
					{
						swap(i,i+1);
						ok=0;
					}
				}
				else
				{
					if (strcmp(regvalorchar(campo,i),regvalorchar(campo,i+1))<0)
					{
						swap(i,i+1);
						ok=0;
					}
				}
			}
		}
		while(!ok);
	}
	else
	{
		cout<<"Error, tipo no valido";
	}
}

int regvalorint(nodo *campo,int posicion)
{
	int i,cont=0;
	nodo *n;
	reg *r;
	int tabla;
	tabla=gettabla(campo);
	n=matriz[tabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
	{
		n=n->sig;
		cont++;
	}
	r= matriz[tabla].sigreg;// registro
	for(i=1;i<posicion;i++)
	{
		if(r->abajo!=NULL)
		{
		 r=r->abajo;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	for(i=0;i<cont;i++)
	{
		if(r->sigreg!=NULL)
		{
			r=r->sigreg;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	cont=*(float *)r->valor;
	return cont;
}

float regvalorfloat(nodo *campo,int posicion)
{
	int i,cont=0;
	nodo *n;
	reg *r;
	int tabla;
	tabla=gettabla(campo);
	n=matriz[tabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
	{
		n=n->sig;
		cont++;
	}
	r= matriz[tabla].sigreg;// registro
	for(i=1;i<posicion;i++)
	{
		if(r->abajo!=NULL)
		{
		 r=r->abajo;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	for(i=0;i<cont;i++)
	{
		if(r->sigreg!=NULL)
		{
			r=r->sigreg;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	float aux;
	aux=*(float *)r->valor;
	return aux;
}

char* regvalorchar(nodo *campo,int posicion)
{
	int i,cont=0;
	nodo *n;
	reg *r;
	int tabla;
	tabla=gettabla(campo);
	n=matriz[tabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
	{
		n=n->sig;
		cont++;
	}
	r= matriz[tabla].sigreg;// registro
	for(i=1;i<posicion;i++)    //vertical
	{
		if(r->abajo!=NULL)
		{
		 r=r->abajo;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	for(i=0;i<cont;i++)  //horizontal
	{
		if(r->sigreg!=NULL)
		{
			r=r->sigreg;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	return (char *)r->valor;
}

reg* regposicion(nodo *campo,int posicion)
{
	int tabla;
	tabla=gettabla(campo);
	int i,cont=0;
	nodo *n;
	reg *r;
	n=matriz[tabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
	{
		n=n->sig;
		cont++;
	}
	r= matriz[tabla].sigreg;// registro
	for(i=1;i<posicion;i++)
	{
		if(r->abajo!=NULL)
		{
		 r=r->abajo;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	for(i=0;i<cont;i++)
	{
		if(r->sigreg!=NULL)
		{
			r=r->sigreg;
		}
		else
		{
			cout<<"posicion no valida";
		}
	}
	return r;
}

int cuenta(nodo *campo)
{
	int tabla;
	tabla=gettabla(campo);
	int cont=0;
	nodo *n;
	reg *r;
	n=matriz[tabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
	{
		n=n->sig;
	}
	if(n!=NULL)
	{
		r= matriz[tabla].sigreg;// registro
		while(r!=NULL)
		{
			cont++;
			r=r->abajo;
		}
		return cont;
	}
	else
	{
		return 0;
	}
}

int gettabla(nodo *campo)
{
	int aux=0;
	nodo *n;
	int encontrado=0;
	int i=1;
	while((i<=topmatriz)&&(encontrado==0))
	{
		n=matriz[i].sig;// nodo
		while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))
		{
			n=n->sig;
		}
		if(n!=NULL)
		{
			encontrado=1;
			aux=i;
		}
		i++;
	}
	if(encontrado==0)
	{
		cout<<"Linea: "<<linea<<" Error: Campo no declarado";
		terminate();
	}
	return aux;
}

float suma(nodo *campo)
{
	float acum=0;
	int tipo;
	int x;
	x=cuenta(campo);
	tipo=campo->tipo;
	for (int i=1;i<=x;i++)
	{
		if (tipo==67) // si es entero
		{
			acum+=regvalorint(campo,i);
		}
		else if (tipo==68) //si es float
		{
			acum+=regvalorfloat(campo,i);
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: No se puede sumar ese tipo";
			terminate();
		}
	}
	return acum;
}

float min(nodo *campo)
{
	int tipo;
	float menor;
	menor=99999;
	int x=cuenta(campo);
	tipo=campo->tipo;
	float aux;
	for (int i=1;i<=x;i++)
	{
		if (tipo==67)// si es entero
		{
			aux=regvalorint(campo,i);
		}
		else if (tipo==68)// si es float
		{
			aux=regvalorfloat(campo,i);
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: No se puede sumar ese tipo";
			terminate();
		}

		if (aux<menor)
		{
			menor=aux;
		}
	}
	return menor;
}

float max(nodo *campo)
{
	int tipo;
	float mayor;
	mayor=-99999;
	int x=cuenta(campo);
	tipo=campo->tipo;
	float aux;
	for (int i=1;i<=x;i++)
	{
		if (tipo==67)// si es entero
		{
			aux=regvalorint(campo,i);
		}
		else if (tipo==68)// si es float
		{
			aux=regvalorfloat(campo,i);
		}
		else
		{
			cout<<"Linea: "<<linea<<" Error: No se puede sumar ese tipo";
			terminate();
		}

		if (aux>mayor)
		{
			mayor=aux;
		}
	}
	return mayor;
}

char* minstr(nodo *campo)
{
	char menor[50];
	int x=cuenta(campo);
	char aux[50];
	strcpy(menor,"zzzzz");
	int comparacion;
	for (int i=1;i<=x;i++)
	{
		strcpy(aux,regvalorchar(campo,i));
		comparacion=strcmp(aux,menor);
		if(comparacion<0)
		{
			strcpy(menor,aux);
		}
	}
	return menor;
}

char* maxstr(nodo *campo)
{
	char mayor[50];
	int x=cuenta(campo);
	char aux[50];
	int comparacion;
	strcpy(mayor,"aaaa");
	for (int i=1;i<=x;i++)
	{
		strcpy(aux,regvalorchar(campo,i));
		comparacion=strcmp(aux,mayor);
		if(comparacion>0)
		{
			strcpy(mayor,aux);
		}
	}
	return mayor;
}

void borra(nodo *campo)// borra los reg's y luego el campo
{
	nodo *n; nodo *m;
	reg *r; reg *horizontal; reg *vertical; reg *q;
	int cont,i;
	cont=numdecampo(campo);
	r=matriz[topmatriz].sigreg;//reg
	if(cont==0)//si quiere borrar el primer campo
	{
		//borra registros
		if(matriz[topmatriz].sigreg!=NULL)
		{
			matriz[topmatriz].sigreg=r->sigreg;
			q=matriz[topmatriz].sigreg;
			while(r!=NULL)
			{
				vertical=r;
				r=r->abajo;
				if(r!=NULL)
				{
					q->abajo=r->sigreg;
				}
				delete vertical;
				q=q->abajo;
			}
		}
		//borrar el campo
		n=matriz[topmatriz].sig;
		matriz[topmatriz].sig=n->sig;
		delete n;
	}
	else  //no es el primer campo
	{
		//borra registros
		if(matriz[topmatriz].sigreg==NULL)
		{
			horizontal=r;
			vertical=r;
			while(vertical!=NULL)
			{
				for(i=0;i<cont;i++)
				{
					horizontal=r;//queda uno antes
					r=r->sigreg;
				}
				horizontal->sigreg=r->sigreg;
				delete r;
				vertical=vertical->abajo;
			}
		}
		//borro el campo
		n=matriz[topmatriz].sig;
		for(i=0;i<cont;i++)
		{
			m=n;//queda uno antes
			n=n->sig;
		}
		m->sig=n->sig;
		delete n;
	}
}

int numdecampo(nodo *campo)// borra los reg's y luego el campo
{
	int cont=0;
	nodo *n;
/*
	int tabla;
	tabla=gettabla(campo);
*/
	n=matriz[actualtabla].sig;// nodo
	while((n!=NULL)&&(strcmp(n->nombre,campo->nombre)!=0))//cuenta la horizontal
	{
		n=n->sig;
		cont++;
	}
	if(n!=NULL)
	{
		return cont;
	}
	else
	{
		return -1;
	}
}

void meteregs(apuntn *campo)  //mete los reg del campo a operandos
{
	apuntv *auxv;
	nodo *n;
	int x,y,tipo;
	reg *r; reg *aux;
	int tabla;
	tabla=campo->tabla;
	n=(nodo *)campo->info;
	aux=matriz[tabla].sigreg;
	x=numdecampo(campo->info);
	y=cuenta(campo->info);
	for(int i=1;i<y;i++)
	{
		r=aux;
		for(int i=1;i<x;i++)
		{
			r=r->sigreg;
		}
		auxv=new apuntv;
		auxv->info=r->valor;
		//	int temp;
		tipo=n->tipo;
		pushoperando(auxv,tipo);
		aux=aux->abajo;
	}
}

/*
COMENTARIOS
DISPOSE A TEMPS
*/


