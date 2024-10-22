#include <stdio.h>
#include <stdlib.h> // Se utiliza la función rand para generar números aleatorios
#include <conio.h>
#include <windows.h> // Se utiliza para la función gotoxy
#include <time.h>
#include <string.h>
#include <basicthings.h> // Para usar gotoxy y set Color

#define COLOR_DEFAULT 7  // Definir color blanco
#define COLOR_SELECTED 10  // Definir color verde
#define MAX_PREGUNTAS 100  // Define el máximo de preguntas que se pueden hacer
#define TAM_RESPUESTA 100  // Define el tamaño de las respuestas
#define MAX_JUEGOS 10   // Define el máximo de veces que podemos jugar 
#define PREGUNTAS_POR_PAGINA 5  // Define el máximo de preguntas por página
#define MAX_CARACTERES_PETICION 55 // Límite de caracteres para peticiones
#define MAX_CARACTERES_PREGUNTA 55 // Límite de caracteres para preguntas

// Función para poder usar el cuadro tipo matriz
void cuadroMatriz() {
    int y; // Inicializa la cadena

    gotoxy(1, 1);
    parteSuperiorMatriz();
    gotoxy(1, 2);
    printf("\xBA             \xBA");
    parteVaciaBen();
    gotoxy(1, 3);
    printf("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9");
    parteVaciaBen();
    gotoxy(1, 4);
    printf("\xBA             \xBA");
    parteVaciaBen();
    gotoxy(1, 5);
    printf("\xBA             \xBA");
    parteVaciaBen();
    gotoxy(1, 6);
    printf("\xCC\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xB9");
    parteVaciaBen();
    for (y = 7; y < 30; y++) {
        gotoxy(1, y);
        printf("\xBA             \xBA");
        parteVaciaBen();
    }
    gotoxy(1, 30);
    parteMediaMatriz();
    for (y = 31; y < 35; y++) {
        gotoxy(1, y);
        parteVaciaMatriz();
    }

    gotoxy(1, 35);
    parteInferiorMatriz();
}

// Función para generar respuestas aleatorias
void generarRespuestaAleatoria(char *respuesta) {
    const char *respuestas[] = {  // Un puntero con arreglos donde están todas las respuestas aleatorias
        "Ni un brillo XDXDXDXD", 
        "Si no le sabes, no le sabes", 
        "Casi, pero ni le atinalstes tilin", 
        "HOOGGG RRIIIDDEERRRRRRRRRRR!!!!!", 
        "Salite de aqui mae, no estoy de humor", 
        "Hoy dicen que le atinaras a la loto", 
        "Talvez algun dia BV, o posiblemente no ;V", 
        "EVERYBODY IS KUNG FU FIGHTING", 
        "Ayy que asco loco, sos chancho", 
        "Ambos sabemos que necesitas ayuda ;V"
    };
    int totalRespuestas = sizeof(respuestas) / sizeof(respuestas[0]); // Para calcular el número de respuestas aleatorias
    srand(time(NULL));  
    int indiceAleatorio = rand() % totalRespuestas; // Escoger aleatoriamente una respuesta
    strcpy(respuesta, respuestas[indiceAleatorio]); // La copia la respuesta aleatoria en la variable respuesta
}

// Función para poder mostrar el historial de preguntas y respuestas de todos los juegos en páginas
void mostrarHistorial(char historialPreguntas[MAX_JUEGOS][MAX_PREGUNTAS][TAM_RESPUESTA], char historialRespuestas[MAX_JUEGOS][MAX_PREGUNTAS][TAM_RESPUESTA], int numPreguntasPorJuego[MAX_JUEGOS], int totalJuegos) {
    // Validación para preguntarle al usuario si quiere salir o no
    system("cls");
    cuadroMatriz();
    gotoxy(30, 2);
    printf("  ---------------PEDRITOTO--------------  ");
    gotoxy(2, 2);
    printf(" ---Menu--- ");
    gotoxy(2, 4);
    printf(" Escoge una ");
    gotoxy(2, 5);
    printf("   opcion   ");
    gotoxy(2, 7);
    printf("1. Jugar");
    gotoxy(2, 8);
    printf("2. Historial");
    gotoxy(2, 9);
    printf("3. Salir");
    gotoxy(30, 16);
    printf("Quiere ver el historial del juego? ");
    gotoxy(30, 17);
    printf("Presiona 'n' o 'N' para regresar. ");
    gotoxy(30, 18);
    printf("Para continuar, presione 's' o 'S'. ");

    // Validando el teclado para que continue o regrese
    int continuarJuego = 1;
    while (continuarJuego) {
        char tecla = getch();
        if (tecla == 'n' || tecla == 'N') {
            continuarJuego = 0;  
        } else if (tecla == 's' || tecla == 'S') {
            break;  
        } else {
            gotoxy(40, 31);
            printf("Tecla invalida. ");
            gotoxy(27, 32);
            printf("Presione 's' o 'S' para continuar ");
            gotoxy(32, 33);
            printf("o 'n' o 'N' para regresar.");
        }
    }

    system("cls");
    cuadroMatriz();
    gotoxy(30, 2);
    printf(" ---------------PEDRITO-------------- ");
    gotoxy(2, 2);
    printf(" ---Menu--- ");
    gotoxy(2, 4);
    printf(" Escoge una ");
    gotoxy(2, 5);
    printf("   opcion   ");
    gotoxy(2, 7);
    printf("1. Jugar");
    gotoxy(2, 8);
    printf("2. Historial");
    gotoxy(2, 9);
    printf("3. Salir");

    int y; // Inicializa la cadena
    
    // Validación si no hay ningún juego hecho
    if (totalJuegos == 0) {
        gotoxy(25, 11);
        printf("No hay preguntas ni respuestas registradas aun.");
        gotoxy(25, 12);
        system("pause");
        return;
    }

    int totalPreguntas = 0; 
    for (int i = 0; i < totalJuegos; i++) {
        totalPreguntas += numPreguntasPorJuego[i];
    }
    
    // Función para mostrar el número de páginas
    int totalPaginas = (totalPreguntas + PREGUNTAS_POR_PAGINA - 1) / PREGUNTAS_POR_PAGINA;
    int paginaActual = 0;

    int tecla;
    
    // Validación para poder mostrar el historial
    do {
        system("cls");
        cuadroMatriz();
        gotoxy(28, 2);
        printf("--- Historial de Preguntas y Respuestas ---");
        gotoxy(2, 2);
        printf(" ---Menu--- ");
        gotoxy(2, 4);
        printf(" Escoge una ");
        gotoxy(2, 5);
        printf("   opcion   ");
        
        // Función para colorear la opción seleccionada y dejar en blanco las otras
        for (int i = 1; i <= 3; i++) {
            if (i == 1) {
                setColor(COLOR_SELECTED);  
            } else {
                setColor(COLOR_DEFAULT);  
            }
            
            // Función para navegar en el menú
            switch (i) {
                case 1:
                    gotoxy(2, 7);
                    printf("1. Jugar");
                    break;
                case 2:
                    gotoxy(2, 8);
                    printf("2. Historial");
                    break;
                case 3:
                    gotoxy(2, 9);
                    printf("3. Salir");
                    break;
            }
        }
        setColor(COLOR_DEFAULT);  
        
        int preguntasEnPagina = 0;
        int preguntaActual = 0;  
        y= 4;

        for (int juego = 0; juego < totalJuegos; juego++) {  // For anidado en otro para imprimir el historial
            for (int p = 0; p < numPreguntasPorJuego[juego]; p++) {
                if (preguntaActual >= paginaActual * PREGUNTAS_POR_PAGINA && preguntasEnPagina < PREGUNTAS_POR_PAGINA) {
                    gotoxy(18, y );
                    printf("Juego %d, Pregunta %d: ", juego + 1, p + 1);
                    y++;

                    gotoxy(18, y);
                    printf("%s", historialPreguntas[juego][p]);
                    y++;

                    gotoxy(18, y);
                    printf("Respuesta %d: ", p + 1);
                    y++;

                    gotoxy(18, y);
                    printf("%s", historialRespuestas[juego][p]);

                    y +=2;
                    preguntasEnPagina++;
                }
                preguntaActual++;
                if (preguntaActual >= (paginaActual + 1) * PREGUNTAS_POR_PAGINA) {
                    break;
                }
            }
        }
        
        // Muestra el número de página en que estamos y las instrucciones para moverse
        gotoxy(32, 31);
        printf("Pagina %d de %d", paginaActual + 1, totalPaginas);
        gotoxy(24, 32);
        printf("Usa las flechas izquierda y derecha para navegar.");
        gotoxy(30, 33);
        printf("Presiona Enter para volver al menú.");
        
        // Validación de las teclas izquierda y derecha
        tecla = _getch();  
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            if (tecla == 75) {  
                if (paginaActual > 0) {
                    paginaActual--;
                }
            } else if (tecla == 77) {  
                if (paginaActual < totalPaginas - 1) {
                    paginaActual++;
                }
            }
        } else if (tecla == '\r') {  
            break;
        }

    } while (1);
}

// Función del menú principal
void mostrarMenu(int opcionSeleccionada) {
    system("cls"); 
    cuadroMatriz();
    gotoxy(30, 2);
    printf("  ---------------PEDRITO--------------  ");
    gotoxy(2, 2);
    printf(" ---Menu--- ");
    gotoxy(2, 4);
    printf(" Escoge una ");
    gotoxy(2, 5);
    printf("   opcion   ");
    
    // Función para colorear la opción seleccionada y dejar en blanco las otras
    for (int i = 1; i <= 3; i++) {
        if (i == opcionSeleccionada) {
            setColor(COLOR_SELECTED);  
        } else {
            setColor(COLOR_DEFAULT);  
        }
        
        // Función para navegar en el menú
        switch (i) {
            case 1:
                gotoxy(2, 7);
                printf("1. Jugar");
                break;
            case 2:
                gotoxy(2, 8);
                printf("2. Historial");
                break;
            case 3:
                gotoxy(2, 9);
                printf("3. Salir");
                break;
        }
    }
    setColor(COLOR_DEFAULT);  
}

// Función para ejecutar el código
int main() {

    //Logo
    int duration;
    duration = 1;
    loadingBarWithLogo(1);
    
    // Declaración de variables
    char *respuestaSecreta = NULL; 
    char *peticionVisible = NULL;   
    char pregunta[TAM_RESPUESTA];
    char historialPreguntas[MAX_JUEGOS][MAX_PREGUNTAS][TAM_RESPUESTA];  
    char historialRespuestas[MAX_JUEGOS][MAX_PREGUNTAS][TAM_RESPUESTA]; 
    const char *mensajeVisible = "Pedro por favor respondeme esta pregunta muy importante";
    char ch;
    int modoSecreto = 0;
    int totalJuegos = 0;  
    int numPreguntasPorJuego[MAX_JUEGOS] = {0};  
    int opcionSeleccionada = 1;  
    int salir = 0;
    
    // Ejecuta todo lo principal
    do {
        mostrarMenu(opcionSeleccionada);

        ch = _getch();  
        
        // Captura la opción seleccionada usando un switch
        switch (ch) {
            case 72:  
                opcionSeleccionada--;
                if (opcionSeleccionada < 1) opcionSeleccionada = 3;
                break;
            case 80:  
                opcionSeleccionada++;
                if (opcionSeleccionada > 3) opcionSeleccionada = 1;
                break;
            case '\r':  
                switch (opcionSeleccionada) {
                    case 1: {
                            // Validación para preguntarle al usuario si quiere jugar o no
                            system("cls");
                            cuadroMatriz();
                            gotoxy(30, 2);
                            printf("  ---------------PEDRITO--------------  ");
                            gotoxy(2, 2);
                            printf(" ---Menu--- ");
                            gotoxy(2, 4);
                            printf(" Escoge una ");
                            gotoxy(2, 5);
                            printf("   opcion   ");
                            gotoxy(2, 7);
                            printf("1. Jugar");
                            gotoxy(2, 8);
                            printf("2. Historial");
                            gotoxy(2, 9);
                            printf("3. Salir");
                            gotoxy(30, 16);
                            printf("Quiere continuar con el juego? ");
                            gotoxy(28, 17);
                            printf("Presiona 'n' o 'N' para regresar. ");
                            gotoxy(26, 18);
                            printf("Para continuar, presione 's' o 'S'. ");

                             
                            // Validando el teclado para que continue o regrese
                            int continuarJuego = 1;
                            while (continuarJuego) {
                                char tecla = getch();
                                if (tecla == 'n' || tecla == 'N') {
                                continuarJuego = 0;  
                                } else if (tecla == 's' || tecla == 'S') {
                                    break;  
                                } else {
                                    gotoxy(40, 31);
                                    printf("Tecla invalida. ");
                                    gotoxy(27, 32);
                                    printf("Presione 's' o 'S' para continuar ");
                                    gotoxy(32, 33);
                                    printf("o 'n' o 'N' para regresar.");
                                }
                            }
                            
                            system("cls");
                            // Imprime la función de jugar junto con la matriz
                            cuadroMatriz();
                            gotoxy(30, 2);
                            printf("  ---------------PEDRITO--------------  ");
                            gotoxy(2, 2);
                            printf(" ---Menu--- ");
                            gotoxy(2, 4);
                            printf(" Escoge una ");
                            gotoxy(2, 5);
                            printf("   opcion   ");
                            gotoxy(2, 7);
                            printf("1. Jugar");
                            gotoxy(2, 8);
                            printf("2. Historial");
                            gotoxy(2, 9);
                            printf("3. Salir");

                            int i = 0, j = 0, continuar = 1;
                            size_t tamSecreto = 1, tamVisible = 1;
                            
                            // Asigna memoria dinámica
                            respuestaSecreta = (char*)malloc(TAM_RESPUESTA);  
                            peticionVisible = (char*)malloc(TAM_RESPUESTA);  
                            if (!respuestaSecreta || !peticionVisible) {  // Error de memoria
                                gotoxy(38, 11);
                                printf("Error de memoria");
                                gotoxy(38, 12);
                                system("pause");
                                return 1;
                            }

                            respuestaSecreta[0] = '\0'; // Terminación de cadenas para ambas memorias para que finalicen
                            peticionVisible[0] = '\0';

                            system("cls");  

                            cuadroMatriz();
                            gotoxy(30, 2);
                            printf("  ---------------PEDRITO--------------  ");
                            gotoxy(2, 2);
                            printf(" ---Menu--- ");
                            gotoxy(2, 4);
                            printf(" Escoge una ");
                            gotoxy(2, 5);
                            printf("   opcion   ");
                            gotoxy(2, 7);
                            printf("1. Jugar");
                            gotoxy(2, 8);
                            printf("2. Historial");
                            gotoxy(2, 9);
                            printf("3. Salir");
                            
                            gotoxy(18, 11);
                            printf("Peticion: ");
                            
                            // Validación de todo el modo secreto
                            while (continuar) {
                                if (_kbhit()) {
                                    ch = _getch();
                                    
                                    if (ch == '.') {
                                        modoSecreto = !modoSecreto;
                                        continue;
                                    }

                                    if (ch ==  8) { 
                                        if (modoSecreto && i > 0) {
                                            i--;
                                            printf("\b \b"); 
                                            j = 0;
                                            tamSecreto = 1;
                                            respuestaSecreta = (char*)realloc(respuestaSecreta, tamSecreto);
                                        } else if (!modoSecreto && j > 0) {
                                            j--;
                                            printf("\b \b"); 
                                        }
                                        continue;
                                    }
                                    
                                    if (modoSecreto) {
                                       respuestaSecreta[i++] = ch;
                                       printf("%c", mensajeVisible[j++]);
                                       tamSecreto++;
                                       respuestaSecreta = (char*)realloc(respuestaSecreta, tamSecreto); 
                                    }else{
                                       peticionVisible[j++] = ch;
                                       printf("%c", ch);
                                       tamVisible++;
                                       peticionVisible = (char*)realloc(peticionVisible, tamVisible);
                                    }
                                    

                                    if (ch == 13) {
                                        continuar = 0;
                                    }
                                    if (i >= MAX_CARACTERES_PETICION || j >= MAX_CARACTERES_PETICION) {
                                        gotoxy(30, 27);
                                        printf("Limite de caracteres alcanzado.");
                                        gotoxy(31, 28);
                                        printf("Presione Enter para continuar.");
                                        _getch();
                                        continuar = 0;
                                    }
                                }
                            }
                            
                            // Terminación de cadenas
                            respuestaSecreta[i] = '\0';  
                            peticionVisible[j] = '\0';
                            
                            gotoxy(18, 13);
                            printf("Peticion registrada. Presiona Enter para continuar...");
                            _getch();  
                            
                            // Validación de la pregunta
                            int longitudPregunta = 0; // Variable para controlar la longitud actual de la pregunta
                            do {
                                gotoxy(18, 15);
                                printf("Pregunta: ");
                                longitudPregunta = 0; // Reiniciar la longitud para cada nueva entrada
                                char ch;

                                while (1) {
                                    ch = _getch(); // Captura el carácter ingresado

                                    if (ch == 13) { // Si se presiona Enter
                                        break; // Salir del bucle
                                    } else if (ch == 8) { // Si se presiona Backspace
                                        if (longitudPregunta > 0) {
                                            longitudPregunta--; // Disminuir la longitud
                                            printf("\b \b"); // Borrar el carácter en la consola
                                        }
                                    } else if (longitudPregunta < MAX_CARACTERES_PREGUNTA) {
                                        printf("%c", ch); // Mostrar el carácter ingresado
                                        pregunta[longitudPregunta++] = ch; // Agregar el carácter a la pregunta
                                    }
                                }

                                pregunta[longitudPregunta] = '\0'; // Terminar la cadena
                                if (longitudPregunta >= MAX_CARACTERES_PREGUNTA) {
                                    gotoxy(30, 31);
                                    printf("Limite de caracteres alcanzado.");
                                    gotoxy(31, 32);
                                    printf("Presione Enter para continuar.");
                                    _getch();
                                }
                            } while (longitudPregunta > MAX_CARACTERES_PREGUNTA);
                            
                            gotoxy(18, 17);
                            printf("Tu pregunta es: ");
                            gotoxy(18, 18);
                            printf("%s", pregunta);

                            strcpy(historialPreguntas[totalJuegos][numPreguntasPorJuego[totalJuegos]], pregunta); 
                            
                            // Imprimir respuesta secreta o aleatoria
                            if (strlen(respuestaSecreta) > 0) {
                                gotoxy(18, 20);
                                printf("Respuesta secreta: ");
                                gotoxy(18, 21);
                                printf("%s", respuestaSecreta);
                                strcpy(historialRespuestas[totalJuegos][numPreguntasPorJuego[totalJuegos]], respuestaSecreta); 
                            } else {
                                char respuestaAleatoria[TAM_RESPUESTA];
                                generarRespuestaAleatoria(respuestaAleatoria);
                                gotoxy(18, 20);
                                printf("Respuesta aleatoria: ");
                                gotoxy(18, 21);
                                printf("%s", respuestaAleatoria);
                                strcpy(historialRespuestas[totalJuegos][numPreguntasPorJuego[totalJuegos]], respuestaAleatoria); 
                            }

                            numPreguntasPorJuego[totalJuegos]++;
                            totalJuegos++;
                            
                            gotoxy(22, 24);
                            printf("Presiona cualquier tecla para volver al menu...");
                            _getch();  

                            free(respuestaSecreta);  // Libera las memorias dinámicas
                            free(peticionVisible);  

                            system("cls");
                        }
                        break;

                    case 2:
                        // Imprime el historial
                        mostrarHistorial(historialPreguntas, historialRespuestas, numPreguntasPorJuego, totalJuegos);
                        break;

                    case 3:
                        // Validación para preguntarle al usuario si quiere salir o no
                        system("cls");
                        cuadroMatriz();
                        gotoxy(30, 2);
                        printf("  ---------------PEDRITO--------------  ");
                        gotoxy(2, 2);
                        printf(" ---Menu--- ");
                        gotoxy(2, 4);
                        printf(" Escoge una ");
                        gotoxy(2, 5);
                        printf("   opcion   ");
                        gotoxy(2, 7);
                        printf("1. Jugar");
                        gotoxy(2, 8);
                        printf("2. Historial");
                        gotoxy(2, 9);
                        printf("3. Salir");
                        gotoxy(30, 16);
                        printf("Quiere salir del juego? ");
                        gotoxy(25, 17);
                        printf("Presiona 'n' o 'N' para regresar. ");
                        gotoxy(23, 18);
                        printf("Para continuar, presione 's' o 'S'. ");

                        // Validando el teclado para que continue o regrese
                        int continuarJuego = 1;
                        while (continuarJuego) {
                            char tecla = getch();
                            if (tecla == 'n' || tecla == 'N') {
                                continuarJuego = 0;  
                            } else if (tecla == 's' || tecla == 'S') {
                                break;  
                            } else {
                                gotoxy(40, 31);
                                printf("Tecla invalida. ");
                                gotoxy(27, 32);
                                printf("Presione 's' o 'S' para continuar ");
                                gotoxy(32, 33);
                                printf("o 'n' o 'N' para regresar.");
                            }
                        }

                        salir = 1;
                        system("cls");
                        break;
                }
                break;
        }
    } while (!salir);

    return 0;
}
