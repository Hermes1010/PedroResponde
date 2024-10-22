#include <stdio.h>
#include <stdlib.h> //Se utiliza la funcion rand para generar numeros aleatorios
#include <unistd.h> //Se utiliza para pausar la ejecucion 
#include <windows.h> //Se utiliza para la funcion gotoxy
#include <string.h>
#include <conio.h>
#include <time.h>

#define COLOR_DEFAULT 7  //Definir color blanco
#define COLOR_SELECTED 10 //Definir color verde

//Funcion para poder usar usar la funcion gotoxy
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Funcion para poner de los colores al menu.
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Funcion para imprimir la fecha y hora actual
void buffer() {
    time_t t;
    struct tm *tm_info;
    char buffer[80];

    time(&t);  // Obtiene el tiempo actual en segundos desde el 1 de enero de 1970
    tm_info = localtime(&t);  // Convierte el tiempo en una estructura con fecha y hora locales

    // Formatea la fecha y hora en el formato "YYYY-MM-DD HH:MM:SS"
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Fecha y Hora actual: %s\n", buffer);
}

//Funcion para imprimir la parte superior de los cuadros
void parteSuperiorMatriz() {
    int width = 67;

    printf("\xC9");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCB");
   for (int i = 0; i < width; i++) {
      printf("\xCD");
   }
   printf("\xBB");
}

//Funcion para imprimir la parte media de los cuadros
void parteMediaMatriz() {
    int width = 67;
     
    printf("\xCC");
    printf("\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCA");
    for(int i = 0; i < width; i++) {
        printf("\xCD"); 
    }
    printf("\xB9");
}

//Funcion para imprimir la parte inferior de los cuadros
void parteInferiorMatriz() {
    int width = 81;

    printf("\xC8");
    for (int i = 0; i < width; i++) {
       printf("\xCD");
    }
    printf("\xBC");
}

//Funcion para imprimir espacio con dos cuadros verticales
void parteVaciaMatriz() {
    int width = 81;

    printf("\xBA");
    for(int i = 0; i < width; i++) {
        printf(" "); 
    }
    printf("\xBA");
}

//Funcion para imprimir la parte superior de los cuadros
void parteSuperior() {
   int width = 50;

   printf("\xC9");
   for (int i = 0; i < width; i++) {
      printf("\xCD");
   }
   printf("\xBB");
}

//Funcion para imprimir la parte media de los cuadros
void parteMedia() {
    int width = 50;
     
    printf("\xCC");
    for(int i = 0; i < width; i++) {
        printf("\xCD"); 
    }
    printf("\xB9");
}

//Funcion para imprimir la parte inferior de los cuadros
void parteInferior() {
    int width = 50;

    printf("\xC8");
    for (int i = 0; i < width; i++) {
       printf("\xCD");
    }
    printf("\xBC");
}

//Funcion para imprimir espacio con dos cuadros verticales
void parteVacia() {
    int width = 50;

    printf("\xBA");
    for(int i = 0; i < width; i++) {
        printf(" "); 
    }
    printf("\xBA");
}

void parteVaciaBen() {
    int width = 67;
    
    for(int i = 0; i < width; i++) {
        printf(" "); 
    }
    printf("\xBA");
}

//Funcion para poder navegar entre las opciones
int navegarOpciones(char opciones[][60], int numOpciones) {
    int opcionSeleccionada = 3; // Se inicializa en 3, es decir la primera opc del menu esta seleccionada por defecto.
    int tecla;

    while (1) {
        system("cls");
        //Si la opcion actual (i) es la seleccionada la marca en color verde y el resto en blanco.
        for (int i = 0; i < numOpciones; i++) { 
            gotoxy(40, 10 + i);
            if (i == opcionSeleccionada) {
                setColor(COLOR_SELECTED);
            } else {
                setColor(COLOR_DEFAULT);
            }
            printf("%s", opciones[i]);
        }

        tecla = getch();

        if (tecla == 224) {  
            tecla = getch();
            // si la tecla es la flecha hacia arriba ,la opc seleccionada se decrementa y si presiona la tecla hacia abajo incrementa.
            if (tecla == 72) {  
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) {
                    opcionSeleccionada = numOpciones - 1;
                }
            } else if (tecla == 80) {  
                opcionSeleccionada++;
                if (opcionSeleccionada >= numOpciones) {
                    opcionSeleccionada = 0;
                }
            }
        } else if (tecla == 13) {  
            return opcionSeleccionada;
        }
    }
}

// Función para bloquear teclas no permitidas
char validarEntrada(int tipo) {
    char c;
    do {
        c = _getch(); // Captura el caracter sin mostrarlo en pantalla y lo almacena en la variable c.
        
        // Bloquear teclas direccionales (flechas), que en la mayoría de sistemas retornan secuencias de escape.
        if (c == 0 || c == -32) { 
            _getch(); // Captura y descarta la segunda parte de la secuencia de escape para las teclas especiales.
            continue; // Ignorar esta tecla.
        }

        if (tipo == 1) {  // Para tipo 1, solo permite letras, espacios, enter y backspace.
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ' || c == '\r' || c == '\b') {
                return c; // Devuelve el caracter que ingresó el usuario.
            }
        } else if (tipo == 2) {  // Para tipo 2, solo permite números, enter y backspace.
            if ((c >= '0' && c <= '9') || c == '\r' || c == '\b') {
                return c; // Devuelve el caracter que ingresó el usuario.
            }
        } else if (tipo == 3) {  // Para tipo 3, permite letras, números, espacios, enter y backspace (para descripción).
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == '\r' || c == '\b' || c == ',' || c == '.' || c == '(' || c == ')' || c == '-' || c == '!' || c == '¡') {
                return c; // Devuelve el caracter que ingresó el usuario.
            }
        }
    } while (1);
}

// Función para ingresar solo letras y espacios
void ingresarNombre(char *nombre) {
    int i = 0; 
    char c;
    do {
        c = validarEntrada(1); // Llama a la función e indica que es de tipo 1 (solo letras y espacios).
        if (c == '\r') { 
            nombre[i] = '\0'; // Si se presiona Enter, se marca el final de la cadena.
            break;
        }
        if (c == '\b' && i > 0) { 
            // Borrar el último carácter solo si hay algo que borrar.
            printf("\b \b"); // Borra el carácter en pantalla.
            i--; // Reduce el índice para borrar el último carácter de la cadena.
        } else if (c != '\b' && i < 50) { 
            printf("%c", c); // Muestra el caracter en pantalla.
            nombre[i++] = c; // Almacena el carácter en la cadena si no es backspace.
        }
    } while (1);
}

// Función para ingresar letras, números y bloquear teclas direccionales
void ingresarProducto(char *nombre) {
    int i = 0; 
    char c;
    do {
        c = validarEntrada(3); // Llama a la función e indica que es de tipo 1 (solo letras y espacios).
        if (c == '\r') { 
            nombre[i] = '\0'; // Si se presiona Enter, se marca el final de la cadena.
            break;
        }
        if (c == '\b' && i > 0) { 
            // Borrar el último carácter solo si hay algo que borrar.
            printf("\b \b"); // Borra el carácter en pantalla.
            i--; // Reduce el índice para borrar el último carácter de la cadena.
        } else if (c != '\b' && i < 50) { 
            printf("%c", c); // Muestra el caracter en pantalla.
            nombre[i++] = c; // Almacena el carácter en la cadena si no es backspace.
        }
    } while (1);
}

// Función para ingresar letras, números y bloquear teclas direccionales
void ingresarDescripcion(char *descripcion) {
    int i = 0; 
    char c;
    do {
        c = validarEntrada(3); // Llama a la función e indica que es de tipo 3 (letras, números y espacios).
        if (c == '\r') { 
            descripcion[i] = '\0'; // Si se presiona Enter, se marca el final de la cadena.
            break;
        }
        if (c == '\b' && i > 0) { 
            // Borrar el último carácter solo si hay algo que borrar.
            printf("\b \b"); // Borra el carácter en pantalla.
            i--; // Reduce el índice para borrar el último carácter de la cadena.
        } else if (c != '\b' && i < 50) { 
            printf("%c", c); // Muestra el carácter en pantalla.
            descripcion[i++] = c; // Almacena el carácter en la cadena.
        }
    } while (1);
}

// Función para ingresar solo números y bloquear teclas direccionales
void ingresarNumeros(char *campo, int longitud) {
    int i = 0;
    char c;
    do {
        c = validarEntrada(2); // Llama a la función e indica que es de tipo 2 (solo números).
        if (c == '\r') { 
            campo[i] = '\0'; // Marca el final de la cadena cuando se presiona Enter.
            break;
        }
        if (c == '\b' && i > 0) { 
            // Borrar el último número solo si hay algo que borrar.
            printf("\b \b"); // Borra el número en pantalla.
            i--; // Reduce el índice para borrar el último número de la cadena.
        } else if (c != '\b' && i < longitud) { 
            printf("%c", c); // Muestra el número en pantalla.
            campo[i++] = c; // Almacena el número en la cadena.
        }
    } while (1);
}

//Funcion para validar la compañia telefonica
void celu(char telefono[], char *compania) {
    // Extrae los primeros 4 dígitos del número de teléfono como un entero
    char prefijo[5];
    strncpy(prefijo, telefono, 4); // Copia los primeros 4 dígitos
    prefijo[4] = '\0';  // Añade el terminador de cadena
    int prefijoInt = atoi(prefijo); // Convierte el prefijo a entero para comparar

    // Verificar rangos de Claro
    if ((prefijoInt >= 5740 && prefijoInt <= 5749) ||
        (prefijoInt >= 5780 && prefijoInt <= 5789) ||
        (prefijoInt >= 5800 && prefijoInt <= 5809) ||
        (prefijoInt >= 8330 && prefijoInt <= 8339) ||
        (prefijoInt >= 8350 && prefijoInt <= 8369) ||
        (prefijoInt >= 8400 && prefijoInt <= 8449) ||
        (prefijoInt >= 8490 && prefijoInt <= 8499) ||
        (prefijoInt >= 8500 && prefijoInt <= 8549) ||
        (prefijoInt >= 8600 && prefijoInt <= 8669) ||
        (prefijoInt >= 8690 && prefijoInt <= 8699) ||
        (prefijoInt >= 8700 && prefijoInt <= 8749) ||  
        (prefijoInt >= 8820 && prefijoInt <= 8859) ||
        (prefijoInt >= 8900 && prefijoInt <= 8949)) {
        strcpy(compania, "Claro");
    }
    // Verificar rangos de Tigo
    else if ((prefijoInt >= 7710 && prefijoInt <= 7719) ||
             (prefijoInt >= 7750 && prefijoInt <= 7759) ||
             (prefijoInt >= 7870 && prefijoInt <= 7879) ||
             (prefijoInt >= 8150 && prefijoInt <= 8159) ||
             (prefijoInt >= 8260 && prefijoInt <= 8269) ||
             (prefijoInt >= 8320 && prefijoInt <= 8329) ||
             (prefijoInt >= 8370 && prefijoInt <= 8399) ||
             (prefijoInt >= 8450 && prefijoInt <= 8489) ||
             (prefijoInt >= 8670 && prefijoInt <= 8689) ||
             (prefijoInt >= 8750 && prefijoInt <= 8779) ||
             (prefijoInt >= 8880 && prefijoInt <= 8899) ||
             (prefijoInt >= 8960 && prefijoInt <= 8969)) {
        strcpy(compania, "Tigo");
    } else {
        strcpy(compania, "Desconocido");
    }
}

// Funcion para que se muestre el logo progresivamente, int padding sirve para centrar el logo 
// y int progress para que el logo se vaya mostrando en pantalla
void printLogoProgressive(int progress, int padding) {
    printf("\033[0;34m"); 
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    const char *logoLines[] = {
      "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
      "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
       "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB       \xDB\xDB\xDB\xDB\xDB\t\t       \n",
       "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
       "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
      "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
       "\t\t\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t ",
      "\t\t\xDB\xDB\xDB\xDB\xDB       \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\t\t \n",
      "\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t\t ",
       "\t\t\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\t\t ",
    };

    int lineCount = sizeof(logoLines) / sizeof(logoLines[0]);//Calcula el total de progreso en el logo.
    int charsPerLine = strlen(logoLines[0]);// Calcula la cantidad de de caracteres en linea usando la primer linea.
    int charsToShow = (progress * charsPerLine) / 100;// Calcula la cuantos caracteres tiene que mostrar en funcion del progreso

    for (int i = 0; i < lineCount; i++) { //Imprime cada parte del logo.
        printf("%*s", padding, "");  //Imprime espacios en blancos para centrarlo.
        //Imprime los caracteres visibles de la linea de caracteres actual segun el progreso.
        for (int j = 0; j < charsToShow; j++) {
            printf("%c", logoLines[i][j]);
        }
        printf("\n");
    }

    printf("\033[0m"); 
    printf("\n\n\n");
}

//Funcion para la duracion y progreso de la barra de carga.
void loadingBarWithLogo(int duration) {
    int width = 50; //Ancho de la barra de carga
    int progress = 0; //Indica que el progreso de la barra empieza en 0
    const char *messages[] = {"Loading...", "Please wait...", "Almost done..."}; //Contiene los mensajes que se muestran en la barra de carga.
    int messageCount = sizeof(messages) / sizeof(messages[0]);
    int padding = (80 - width) / 2; // Espacio en blanco a los lados para centrar la barra.

    //El bucle asegura que hasta que no llegue a 100 se siga actualizando la barra de carga.
    while (progress <= 100) {
        int pos = (progress * width) / 100; //calcula cuántos caracteres de la barra de progreso deben estar llenos en función del porcentaje de progreso actual.
        int messageIndex = (progress / (100 / messageCount)) % messageCount; // Indica los mensajes mostrando dependiendo en que porcentaje este la barra de carga.

        system("cls");

        printLogoProgressive(progress, padding);// Llama a la función que muestra el logotipo con el progreso actual. Esta función se asegura de que el logotipo se actualice en función del progreso actual.

        //Imprime la esquina superior de la barra y la centra con padding
        printf("\r%*s\xC9", padding, ""); 
        for (int i = 0; i < width + 2; ++i) {//Imprime la linea superior de de la barra
            printf("\xCD");  
        }
        printf("\xBB\n");//Imprime la esquina superior derecha.

        printf("%*s\xBA", padding, ""); //Imprime el borde izquierdo de la barra, con padding para centrar la barra.
        // Imprime el contenido de la barra de progreso. Si i es menor a la posicion de los caracteres se imprime espacios vacios, sino imprime los cuadrados.
        for (int i = 0; i < width; ++i) {
            if (i < pos) {
                printf("\xDB");  
            } else {
                printf(" ");
            }
        }
        printf("\xBA");  //Imprime el borde derecho de la barra.
        printf(" %d%%", progress); //Muestra el porcentaje de progreso
        printf(" %s\n", messages[messageIndex]); //Muestra los mensajes segun el porcentaje.

        printf("%*s\xC8", padding, "");  //Imprime la esquina inferior izquierda de la barra de progreso.
        //Imprime la línea horizontal inferior de la barra.
        for (int i = 0; i < width + 2; ++i) {
            printf("\xCD");  
        }
        printf("\xBC\033[0m\n");//Imprime la esquina inferior derecha de la barra.  

        fflush(stdout); //Asegura que todo el texto se imprima en la pantalla antes de continuar.
        sleep(duration); //Pausa la ejecución del programa durante el número de segundos especificado
        progress += 25; //Incrementa el progreso en 25% para la siguiente iteración del bucle. Esto asegura que la barra avance en pasos de 25%.
    }
}

//Ayuda a centrar los mesajes dependiendo del tamaño de la terminal.
void printCenteredMessage(const char *message, const char *color) {
    int terminalWidth = 80; //Define el ancho total de la terminal en caracteres.
    int messageLength = strlen(message); //Calcula la longitud del mensaje que se va a centrar.
    int padding = (terminalWidth - messageLength) / 2;// Calcula el número de espacios necesarios para centrar el mensaje.

    printf("\n\n\n\n");
    printf("%s", color);

    //Imprime los espacios necesarios antes del mensaje para centrarlo.
    for (int i = 0; i < padding; ++i) {
        printf(" ");
    }
    printf("%s\n", message);
    printf("\033[0m");
}

//Funcion para mostrar la presentacion  
void presentacion(){
    system("cls");
    printf("\n\033[0;33m"); 

    gotoxy(40, 4);
    parteSuperior();
    gotoxy(40, 5);
    printf("\xBA       Proyecto de lenguajes de programacion      \xBA");
    gotoxy(40, 6);
    parteMedia();
    gotoxy(40, 7);
    printf("\xBA        Universidad Nacional De Ingenieria.       \xBA");
    gotoxy(40, 8);
    parteMedia();
    gotoxy(40, 9);
    printf("\xBA               Proyecto: UNI GYM.                 \xBA");
    gotoxy(40, 10);
    printf("\xBA      Asignatura: Lenguajes de programacion.      \xBA");
    gotoxy(40, 11);
    parteMedia();
    gotoxy(40, 12);
    printf("\xBA                  Integrantes:                    \xBA");
    gotoxy(40, 13);
    printf("\xBA     Devans Rishi Moncada Espinoza 2024-1879U     \xBA"); 
    gotoxy(40, 14);
    printf("\xBA   Mauricio Alejandros Flores Torres 2024-1890U   \xBA"); 
    gotoxy(40, 15);
    printf("\xBA      Isaac Antonio Espinoza Sanez 2024-1873U     \xBA"); 
    gotoxy(40, 16);
    parteMedia();
    gotoxy(40, 17);
    printf("\xBA          Docente: Ing. Nelson Barrios.           \xBA"); 
    gotoxy(40, 18);
    parteMedia();
    gotoxy(40, 19);
    parteVacia();
    gotoxy(45, 19);
    buffer();
    gotoxy(40, 20);
    parteInferior();

    gotoxy(40, 22);
    system("pause");

    printf("\n\033[0;0m");
}