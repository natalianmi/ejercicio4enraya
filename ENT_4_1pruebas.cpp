//TURNO 24-GRUPO 03.
//ENTREGABLE 4 – EJERCICIO 1.
//María Arrojo Naveira.
//Natalia Martín Íñiguez.



#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define FILAS 6
#define COLUMNAS 7
#define RAYA 4
#define MAX_PARTIDAS 3

struct partida
{
	char ficha_comienzo;
	int fichas;
	int ganador;
	int secuencia [FILAS*COLUMNAS];
};

void menu(void);
void menu2(void);
void inicializar_partida(struct partida [MAX_PARTIDAS]);
void dibuja_superior(void);
void dibuja_inferior(void);
void dibujar_tablero(char [FILAS][COLUMNAS]);
int rellenar_columnas(char [FILAS][COLUMNAS],char,int,struct partida *,char [FILAS][COLUMNAS]);
int buscar_ganador(char [FILAS][COLUMNAS],char,char,struct partida [MAX_PARTIDAS], int,char[FILAS][COLUMNAS]);


main()
{
	int i,j,m,l,n,o,p,q; //Variables utilizadas por los for
	int partidas_jugadas = 0;
	struct partida partidas[MAX_PARTIDAS];
	char opcion, opcion2;
	char tablero[FILAS][COLUMNAS];
	char tablero_copia[FILAS][COLUMNAS];		
	int col_escogida;	 //Variable de la columna escogida por el usuario.
	char ficha1;
	char ficha2;
	int champion=0;
	int partidas_grabadas=0;
	int partida_elegida=0;
	FILE*fichero;
	char nombre[20];
	int fichas_ganador;
	float fichas_totales=0;
	int columnas_introducidas[COLUMNAS];
	int contador_columnas[COLUMNAS];
	int columna_introducida;
	int mayor=0;
	int menor=0;
	//	int contador=0; //Contador utilizado en el for para contar las veces que se introduce cada columna
	
	//Inicio del encabezado del programa.
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191);
	printf("%c ENTREGABLE 4 - EJERCICIO 1 %c\n",179,179);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217);
	//Fin del encabezado.
	
	inicializar_partida(partidas);
	for(o=0;o<COLUMNAS;o++) //Bucle for que inicializa la matriz columnas_introducidas, 
		{					//la cual cuenta cuántas veces se selecciona una columna a 0 para poder utilizarla en el caso 3. 
			contador_columnas[o]=0; //EN CADA POSICION O SE VA A SUMAR ++ CUANDO SE INTRODUZCA ESA COLUMNA.  
		}
	//Bucle que se ejecuta hasta que la opción introducida sea 4.
	do
	{
		/*
		Bucle for que se repite hasta que se haya alcanzado el valor de max_partidas establecido al 
		inicio del entregable o hasta que se seleccione la opción 4.
		*/
		for(m=0; m<MAX_PARTIDAS;m++)
		{	
			
			do{
				printf ("\nEscoge una opci%cn",162);
				menu();//Llamada a la función menu.
				opcion = getch();
				printf ("\n\nOpci%cn escogida: %c", 162, opcion);
				
				if(opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4') 
					printf("\nOpci%cn incorrecta\n",162); 
				
			}while(opcion != '1' && opcion != '2'&&opcion != '3' && opcion != '4');
		
			switch(opcion)
			{
				case'1':
				{	
					
					if (partidas_jugadas >= MAX_PARTIDAS) 
					{
						printf("\n El n%cmero m%cximo de partidas jugadas ha sido alcanzado", 163,160);
						break; //Vuelve al menú principal.
					}
						
					
					else 
					{		
						//Se inicializa la matriz tablero y la tablero_copia a - .
						for(i=1 ; i<=FILAS ; i++) 
						{
							for(j=1 ; j<=COLUMNAS ; j++)
							{
								tablero[i][j] = '-';
								tablero_copia[i][j] = '-';
							}
						}
						dibujar_tablero(tablero);
						
						do  //Bucle que se repite hasta que la ficha sea correcta.
						{ 
							printf("\n\n%cCon qu%c ficha quiere comenzar a jugar?(x / o):", 168,130);
							ficha1 = getche();
							ficha1=tolower(ficha1); //Pone el caracter escogido en minúscula.
						}
						while (ficha1 != 'x' && ficha1 != 'o');
						
						//partidas[partidas_jugadas].ficha_comienzo = ficha1;
						
						
						switch (ficha1)// Adjudica la ficha al jugador 2 en función de la escogida por el jugador 1.
						{
							case 'x': ficha2 = 'o'; break;
							case 'o': ficha2 = 'x'; break;
						}
						do{ //Bucle que se ejecuta hasta que se encuentre un ganador o el tablero esté completo.
						
							
					
							//partidas[partidas_jugadas].fichas++; //Suma 1 al campo fichas de la estructura.
							
							printf("\nElige la columna en la que quiere introducir la ficha,jugador 1:");
							
							col_escogida = rellenar_columnas(tablero, ficha1, partidas[partidas_jugadas].fichas - 1 ,&partidas[partidas_jugadas],tablero_copia);
							
							contador_columnas[col_escogida-1]++;
							
							champion = buscar_ganador(tablero,ficha1,ficha2, partidas,partidas_jugadas,tablero_copia);
						//	printf("ficha 1 partida %d: %c", partidas_jugadas, partidas[partidas_jugadas].ficha_comienzo);
							if (champion == 1) // Champion=1 a si la función ha encontrado un ganador.
							{ 
								dibujar_tablero(tablero_copia); 
								break;	
							}
							
							if(partidas[partidas_jugadas].fichas == FILAS*COLUMNAS) //Analiza si el tablero está completo.
							{
								printf("\n Empate");
								dibujar_tablero(tablero);break;
							}
							
							printf("\nPulse tabulador para mostrar tablero o enter para continuar");
							
							switch(getch()) 
							{
								case 9: //tabulador
								{
									dibujar_tablero(tablero);
									break; 
								}	
								case 10: // enter.
									break; 
							}
							
							partidas[partidas_jugadas].fichas++;//Suma 1 a las fichas almacenadas en la estructura.
							
							printf("\nElige la columna en la que quiere introducir la ficha,jugador 2:");
							
							col_escogida = rellenar_columnas(tablero,ficha2, partidas[partidas_jugadas].fichas - 1, &partidas[partidas_jugadas],tablero_copia);
						
							contador_columnas[col_escogida-1]++;
						
							champion = buscar_ganador(tablero,ficha1,ficha2, partidas,partidas_jugadas,tablero_copia);
						//	printf("ficha 1 partida %d: %c", partidas_jugadas, partidas[partidas_jugadas].ficha_comienzo);
							if (champion == 1)  // Champion=1 a si la función ha encontrado un ganador.
							{
								dibujar_tablero(tablero_copia); 
								break;
							}
							
							if(partidas[partidas_jugadas].fichas == FILAS*COLUMNAS) //Analiza si el tablero está completo. 
							{
								printf("\n Empate");
								dibujar_tablero(tablero);
								break;
							}
							
							printf("\nPulse tabulador para mostrar tablero o enter para continuar");
							
							switch(getch())
							{
								case 9: dibujar_tablero(tablero);break; //tabulador.
								case 10:break; //enter
							}
							
						} while (partidas[partidas_jugadas].fichas<=FILAS*COLUMNAS || champion!=1);
							
							partidas[partidas_jugadas].ficha_comienzo = ficha1;
							
							partidas_jugadas++;
							
					
					} break; // Vuelve al menú principal.
				}
				case '2':
					{
						if (partidas_jugadas == 0) 
						//Si no hay partidas jugadas almacenadas se sale del case 2 
						//imprimiendo un mensaje de error y mostrando el menú de nuevo.
						{
							printf("\nNo hay partidas grabadas.");	
							break;
						}
						
						else
						{
							do //Pregunta por la partida que se desea grabar hasta que esta sea correcta.
							{
								printf("\nIndique la partida que desea guardar: "); 
								
								scanf("%d", &partida_elegida);
								
								if(partida_elegida <= 0 || partida_elegida > partidas_jugadas)
								{
									 printf("\nLa partida escogida no existe");
								}
							} while(partida_elegida <= 0 || partida_elegida > partidas_jugadas);
							
							printf("\nIndica el nombre del fichero:");
							
							gets(nombre);//Escanea el nombre del fichero.
							
							strcat(nombre,".txt");
							
							fichero = fopen(nombre,"a");//Abre el fichero.
							
							if(fichero != NULL) 
							{
								printf("\nEl fichero se ha abierto con %cxito",130);
							}
							fprintf(fichero,"\nPARTIDA %d - Tablero de %d filas y %d columnas - Jugador 1 comienza con '%c'",partida_elegida, FILAS, COLUMNAS, partidas[partida_elegida-1].ficha_comienzo);
						
							for(i=0 ; i<partidas[partida_elegida-1].fichas ; i++)
							{
								//Imprime en el fichero la secuencia de columnas introducidas.
								if (i%2 == 0) 
									fprintf(fichero, "\n%d. Jugador 1 Columna %d", i+1, partidas[partida_elegida-1].secuencia[i]); 	
								else if(i%2 != 0) 
									fprintf(fichero, "\n%d. Jugador 2 Columna %d", i+1, partidas[partida_elegida-1].secuencia[i]); 
							}
						
							if ((partidas[partida_elegida-1].ganador) == 1 || (partidas[partida_elegida-1].ganador) == 2) 
							{
								//Si localiza que algún jugador ha ganado lo guarda en la estructura y lo imprime en el fichero.
								if ((partidas[partida_elegida-1].fichas)%2==0) fichas_ganador=(partidas[partida_elegida-1].fichas)/2;
								
								else if((partidas[partida_elegida-1].fichas)%2!=0) fichas_ganador=(partidas[partida_elegida-1].fichas+1)/2;
								
								fprintf(fichero, "\nHa ganado el Jugador %d después de haber introducido %d fichas",partidas[partida_elegida-1].ganador, fichas_ganador);	
							}
							else if ((partidas[partida_elegida-1].ganador) == 0) 
							{
								fprintf(fichero, "\nLa partida ha terminado en empate con %d fichas", partidas[partida_elegida-1].fichas); 
							}
								
							fclose(fichero);
							
							if(fclose(fichero) != 0) 
								printf("\nEl fichero se ha cerrado con %cxito",130); 
						} break;
					
					}
				case '3': 
					{
						
						if(partidas_jugadas == 0) //Vuelve a mostrar el menú si no hay partidas grabadas.
						{
							printf("\nNo hay partidas jugadas/grabadas.");	break;
						}
						else 
						{
							do { //Bucle del que se ejecuta hasta que se pulsa la opción d.
							
								do{ //Bucle que se ejecuta si la opción escogida es incorrecta.
									printf("\nEscoge una opci%cn",162);
									menu2();
									opcion2 = getch();
									opcion2 = tolower(opcion2); //Convierte en minúscula la letra pulsada, para que en el caso de que se ponga sin querer en mayúsculas también recoja el carácter.
									printf("\n\nOpci%cn escogida: %c", 162, opcion2);
									if(opcion2 != 'a' && opcion2 != 'b' && opcion2 != 'c' && opcion2 != 'd') 
									{
										printf("\nOpci%cn incorrecta\n",162);
									}
								
								}while(opcion2 != 'a' && opcion2 != 'b' && opcion2 != 'c' && opcion2 != 'd');
							
								switch(opcion2)
								{
									case 'a': // Opción que muestra el promedio de fichas.
										{
											for(i=0;i<partidas_jugadas;i++) 
											{
												//Almacena las fichas totales de las partidas jugadas.
												fichas_totales=fichas_totales+partidas[i].fichas;
											}
											printf("\nEl promedio de fichas introducidas es: %1.1f",fichas_totales/partidas_jugadas); //Imprime el promedio de fichas.
											
											break; 
										}
										
									case 'b': //Opción que muestra en qué columna se han introducido más fichas.
										{ 
											for(i=1;i<COLUMNAS;i++) //Va comparando el número de fichas que hay en cada columna de todas las partidas jugadas 
											{	
												if(contador_columnas[mayor]<contador_columnas[i]) 
												{
													mayor=i;
												}
											} 
											printf("\nLa columna %d es en la que m%cs fichas se han introducido con %d fichas en total", mayor+1,160,contador_columnas[mayor]); 
										
											break;
										}
									case 'c': //Opción que muestra la columna en la que se han introducido menos fichas.
										{ 
											for(i=1;i<COLUMNAS;i++) //Va comparando el número de fichas que hay en cada columna de todas las partidas jugadas 
											{	
												if(contador_columnas[menor]>contador_columnas[i]) 
												{
													menor=i;
												}	
											}
											printf("\nLa columna %d es en la que menos fichas se han introducido con %d fichas en total",menor+1, contador_columnas[menor]); 
										
											break;	
										}
									case 'd': //Sale del bucle y se vuelve a imprimir el menu principal.
										break; 
								}
							} while(opcion2!='d');
						}
					}
				
				case '4': //Finaliza el programa.
					{ 
						m=MAX_PARTIDAS; 
						
						if (opcion==4) 
							printf("\n Fin del programa. Gracias.");
							
						break; 
					} 
			}
		}	
		
	}while(opcion!='4');
}
	

void menu(void) //Imprime el menú1.
{
	printf("\n1. Jugar partida");
	printf("\n2. Exportar partida");
	printf("\n3. Estad%csticas",161);
	printf("\n4. Salir del programa");
}

void menu2(void) //Imprime el menú 2.
{
	printf("\na. Promedio de fichas introducidas por partida");
	printf("\nb. Columna en que m%cs fichas se introducen",160);
	printf("\nc. Columna en que menos fichas se introducen",161);
	printf("\nd. Volver al men%c anterior",163);
}

void inicializar_partida(struct partida partidas[MAX_PARTIDAS]) //Inicializa la estructura.
{
	int i, j;
	for(j=0 ; j < MAX_PARTIDAS ; j++)
	{
		partidas[j].ficha_comienzo = ' ';
		
		partidas[j].fichas = 0; //Inicializa el campo fichas de la estructura a 0.
		
		partidas[j].ganador = 0; //Inicializa el campo ganador a 0.
		
		for(i = 0; i < FILAS*COLUMNAS; i++)
		{
			partidas[j].secuencia[i] = -1; //Inicializa la matriz secuencia a -1, indicando que no se ha introducido ninguna ficha.
		}
	}
	
	
}

void dibuja_superior(void) //Imprime la parte de arriba de la tabla.
{
	int j,i;
	printf("\n%c",201);// Imprime la esquina superior izquierda de la tabla.
	
	for(j=0 ; j<COLUMNAS-1 ; j++)//Imprime la parte de arriba de la tabla(menos la última casilla).
	{ 
	   	printf("%c%c%c%c",205,205,205,203);//Imprime las separaciones de columna de la parte superior de la tabla.
	}
	printf("%c%c%c%c \n",205,205,205,187);//Imprime la última casilla.

}

void dibuja_inferior(void) //Imprime la parte de abajo de la tabla.
{
	int i , j;
	printf("\n%c",200);
	for(j=1 ; j<COLUMNAS ; j++) //Imprime la parte de abajo de la tabla menos la última casilla.
	{  
   		printf("%c%c%c%c",205,205,205,202);
	}	
	printf("%c%c%c%c",205,205,205,188);//Imprime la última casilla y la esquina inferior derecha.
}

void dibujar_tablero( char tablero[FILAS][COLUMNAS]) //Imprime el tablero.
{
	int i,j; 
	
	dibuja_superior();
	
	for(i=1;i<=FILAS;i++)
	{	
		do{
			printf("%c",186); //Imprime la primera barra vertical de cada fila.
			
			for(j=1;j<=COLUMNAS;j++)
			{ 
				if (tablero[i][j]=='-') printf("   %c",186);
				else printf(" %c %c",tablero[i][j],186);
			}
			printf("\n%c",204); //Salta a la línea siguiente introduciendo la separación inicial de fila.
			
			for(j=1;j<=COLUMNAS-1;j++)
			{ 
				printf("%c%c%c",205,205,205); //Imprime las barras horizontales.
				printf("%c",206); //Imprime las crucetas que separan las casillas.
			}
			// última columna.
			printf("%c%c%c",205,205,205); //Imprime la barra horizontal.
			
			printf("%c\n",185); //Imprime la separación final de fila.
			
			i++;
		} while(i<FILAS);
		
		//Última fila.
		printf("%c",186); //Imprime la primera barra vertical de la fila.
		for(j=1;j<=COLUMNAS;j++)//For que se ejecuta hasta que la variable alcanza el valor de columnas introducido.
		{ 
			if (tablero[i][j]=='-') printf("   %c",186);
			else printf(" %c %c",tablero[i][j],186);			
		}	
	
	}
	
	dibuja_inferior();
} 

int rellenar_columnas(char tablero[FILAS][COLUMNAS],char ficha1,int ficha,struct partida *a,char tablero_copia [FILAS][COLUMNAS]) 
{	//Rellena las columnas del tablero con los datos introducidos para el jugador 1.
	int i,j;
	int col_escogida;
	do{ // Se ejecuta hasta que la columna introducida sea correcta.
		
		scanf("%d", &col_escogida);
		
		if(col_escogida > COLUMNAS || col_escogida < 1) 
			printf("\nColumna no v%clida, introduzca una distinta.",160);
	}
	while((col_escogida > COLUMNAS || col_escogida < 1));
	
	if(tablero[1][col_escogida] == 'x' || tablero[1][col_escogida] == 'o') //Se ejecuta si la columna está llena.
	{
		do{ // Se ejecuta hasta que la columna escogida sea correcta.
			printf("\nColumna llena, introduzca una distinta.");
			scanf("%d",&col_escogida);
		} while((col_escogida > COLUMNAS || col_escogida <= 0) && tablero[1][col_escogida]!= '-');
	}
	
	for (i=(FILAS) ; i>=1 ; i--)
	{
			if (tablero[i][col_escogida]=='-') 
			{	//Si no hay ninguna ficha introducida en la posición la introduce.
			 	tablero[i][col_escogida]=ficha1;
			 	//tablero_copia[i][col_escogida] == ficha1;
				i=0;
			}			
	}
	//a->secuencia[ficha] = col_escogida; //Guarda la columna en el apartado secuencia de la estructura
	return col_escogida;
}


int buscar_ganador(char tablero[FILAS][COLUMNAS],char ficha1,char ficha2,struct partida a[MAX_PARTIDAS],int partidas_jugadas,char tablero_copia [FILAS][COLUMNAS])  
{	//Recorre la matriz buscando algún ganador. 

	int length=0; // Longitud de la secuencia encontrada.
	int i,j,c,f,k,l;
	int winner=0;
	char simb=' ';//Variable que compara los caracteres de la tabla para buscar las rayas.
	int fila_anterior;
	
	//Buscar en horizontal.
	if (winner==0) // Si no se ha encontrado un ganador.
	{
		for(i=0 ; i<FILAS ; i++)
		{
			length=0;
			simb=' ';
			
			for(j=0 ; j<COLUMNAS ; j++)
			{
				
				f=i+1; // f corresponde a i+1 porque el for comienza en i=0 pero la matriz tablero está inicializada a partir del 1.
				c=j+1; // c corresponde a j+1 porque el for comienza en j=0 pero la matriz tablero está inicializada a partir del 1.
				
				if (tablero [f][c] != 'x' && tablero [f][c] != 'o') 
				{
					simb = ' ';
				}
				if(simb == tablero [f][c])
				{
					tablero_copia[f][c] = toupper(tablero[f][c]);
					//Almacena en tablero_copia una copia del tablero pero con los simbolos consecutivos en mayúsculas.
					length++; // Si encuentra dos elementos iguales seguidos suma 1 a length.
					
					if(length>=RAYA)
					{	//Si la longitud de la secuencia encontrada (length) es mayor que RAYA se ha encontrado un ganador.
					
						winner=1; // winner=1 significa que se ha encontrado un ganador.
						
						if(simb == ficha1)
						{
							printf("Ha ganado el jugador 1.");
							a[partidas_jugadas].ganador=1;
						}
						
						if(simb == ficha2)
						{
							printf ("Ha ganado el jugador 2.");
							a[partidas_jugadas].ganador=2;
						}
					
					i=FILAS;
					j=COLUMNAS;
					}
				}
	
				else   
				{	//Si el elemento anterior es distinto del siguiente length=1 porque ya tenemos un elemento.
					length = 1;
					
					for(k=1 ; k<=FILAS ; k++)
					{	//Si no se encuentra ganador se vuelven a poner en minúsculas las fichas.
						for(l=1 ; l<=COLUMNAS ; l++)
						{
							tablero_copia[k][l] = tablero [k][l];
						}
					}
			
				}
				
				simb=tablero[f][c];
				
				tablero_copia[f][c]=toupper(tablero[f][c]);
			
			}
		}
	}

	//Buscar en vertical.
	if (winner == 0) // Si no se ha encontrado un ganador.
	{
		for(i=0 ; i<COLUMNAS ; i++)
		{
			length=0;
			simb=' ';
		
			for(j=0 ; j<FILAS ; j++)
			{
				f=j+1; // f corresponde a f+1 porque el for empieza en j=0 pero la matriz tablero está inicializada a partir del 1.
				c=i+1; // c corresponde a i+1 porque el for empieza en i=0 pero la matriz tablero está inicializada a partir del 1.
				
				if (tablero [f][c] != 'x' && tablero [f][c] != 'o') 
					simb = ' ';
				
				if(simb == tablero [f][c])
				{
					tablero_copia[f][c] = toupper(tablero[f][c]);
					//Almacena en tablero_copia una copia del tablero pero con los simbolos consecutivos en mayúsculas.
					
					length++; //Si encuentra dos elementos iguales seguidos suma 1 a length.
					
					if(length>=RAYA)
					{	//Si la longitud de la secuencia encontrada (length) es mayor que RAYA se ha encontrado un ganador.
					
						winner=1; // winner=1 significa que se ha encontrado un ganador.
						
						if(simb == ficha1)
						{
							printf("Ha ganado el jugador 1.");
							a[partidas_jugadas].ganador=1;
						}
						if(simb == ficha2)
						{
							printf ("Ha ganado el jugador 2.");
							a[partidas_jugadas].ganador=2;
						}
				
						i=FILAS;
						j=COLUMNAS;
					}
				}
				else   
				{	//Si el elemento anterior es distinto del siguiente length=1 porque ya tenemos un elemento.
					length = 1;
					
					for(k=1 ; k<=FILAS ; k++)
					{	//Si no se encuentra ganador se vuelven a poner en minúsculas las fichas.
						for(l=1 ; l<=COLUMNAS ; l++)
						{
							tablero_copia[k][l] = tablero [k][l];
						}
					}
				}
				simb=tablero[f][c];
				
				tablero_copia[f][c] = toupper(tablero[f][c]);		
			}
		}
	}
	
	//Buscar ganador -45 grados.
	
	if(winner==0) // Si no se ha encontrado un ganador.
	{
		fila_anterior=1;
		
		for(i=0 ; i<FILAS ; i++)
		{
			length=0;
			simb=' ';
			
			for(j=0 ; j<COLUMNAS ; j++)
			{
				f= ((i+j) % FILAS)+1; 
				/* f corresponde a ((i+j) % FILAS)+1 puesto que el for comienza en 0 y la matriz tablero está inicializada a 1.
				 Esta operación nos da las coordenadas de las filas al buscar en la diagonal de -45 grados.*/
				 
				c=j+1; //c corresponde a j+1 puesto que el for comienza en 0 y la matriz tablero está inicializada a 1.
		
				if(f < fila_anterior)
				{
					simb=' ';
				} 
				
				fila_anterior = f;
				
				if(simb != 'x' && simb != 'o')
				{
					simb = ' ';
				}
				
				if( simb == tablero [f][c])
				{
					tablero_copia[f][c] = toupper(tablero[f][c]);
					//Almacena en tablero_copia una copia del tablero pero con los simbolos consecutivos en mayúsculas.
					
					length++;//Si encuentra dos elementos iguales seguidos suma 1 a length.
					
					if(length >= RAYA)
					{ //Si la longitud de la secuencia encontrada (length) es mayor que RAYA se ha encontrado un ganador.
					
						winner=1;// winner=1 significa que se ha encontrado un ganador.
						
						if (simb == ficha1)
						{
							printf("Ha ganado el jugador 1.");
							a[partidas_jugadas].ganador=1;
						}
						if(simb == ficha2)
						{
							printf("Ha ganado el jugador 2.");
							a[partidas_jugadas].ganador=2;
						}
						i=FILAS;
						j=COLUMNAS;
					}
				}
				else
				{	//Si el elemento anterior es distinto del siguiente length=1 porque ya tenemos un elemento.
					length=1;
					
					for(k=1 ; k<=FILAS ; k++)
					{	//Si no se encuentra ganador se vuelven a poner en minúsculas las fichas.
						for(l=1 ; l<=COLUMNAS ; l++)
						{
							tablero_copia[k][l] = tablero [k][l];
						}
					}
				}
				simb = tablero [f][c];
				tablero_copia[f][c] = toupper(tablero[f][c]);
			}
		}
	}
	
	//Buscar ganador 45 grados.
	
	if(winner==0) // Si no se ha encontrado un ganador.
	{
		fila_anterior=1;
		
		for(i=0 ; i<FILAS ; i++)
		{
			length=0;
			simb=' ';
			
			for(j=0 ; j<COLUMNAS ; j++)
			{
				f= ((i+j) % FILAS)+1;
				/* f corresponde a ((i+j) % FILAS)+1 puesto que el for comienza en 0 y la matriz tablero está inicializada a 1.
				 Esta operación nos da las coordenadas de las filas al buscar en la diagonal de 45 grados.*/
				 
				c=COLUMNAS-j;
				/* c corresponde a COLUMNAS-j .
					Esta operación nos da las coordenadas de las columnas al buscar en la diagonal de 45 grados.*/
	
				if(f < fila_anterior)
				{
					simb=' ';
				} 
				
				fila_anterior = f;
				
				if(simb != 'x' && simb != 'o')
				{
					simb = ' ';
				}
				
				if( simb == tablero [f][c])
				{
					tablero_copia[f][c] = toupper(tablero[f][c]);
					//Almacena en tablero_copia una copia del tablero pero con los simbolos consecutivos en mayúsculas.
					
					length++;//Si encuentra dos elementos iguales seguidos suma 1 a length.
					
					if(length >= RAYA)
					{ 	//Si la longitud de la secuencia encontrada (length) es mayor que RAYA se ha encontrado un ganador.
					
						winner=1; // winner=1 significa que se ha encontrado un ganador.
						if (simb == ficha1)
						{
							printf("Ha ganado el jugador 1.");
							a[partidas_jugadas].ganador=1;
						}
						if(simb == ficha2)
						{
							printf("Ha ganado el jugador 2.");
							a[partidas_jugadas].ganador=2;
						}
						i=FILAS;
						j=COLUMNAS;
					}
				}
				else
				{	//Si el elemento anterior es distinto del siguiente length=1 porque ya tenemos un elemento.
					length=1;
					
					for(k=1 ; k<=FILAS ; k++)
					{	//Si no se encuentra ganador se vuelven a poner en minúsculas las fichas.
						for(l=1 ; l<=COLUMNAS ; l++)
						{
							tablero_copia[k][l] = tablero [k][l];
						}
					}
				}
				simb = tablero [f][c];
				
				tablero_copia[f][c] = toupper(tablero[f][c]);
			}
		}
	}
	
	return winner; // Devuelve el valor del ganador.
}



