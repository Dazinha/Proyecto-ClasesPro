#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "list.h"
#include "treemap.h"
//===================================================================================
//Estructura principal del codigo "Estudiante"
//===================================================================================
typedef struct Estudiante{
  char nombre[100];
  char rut[11];
  int edad;
  List *ListaDeRamos;
  List *HojaDeVida;
  TreeMap* MapaAsistencia;
  TreeMap* MapaRamos;
  float *Calificaciones;
  int NumCalificaciones;
  float Promedio;
} Estudiante;
//===================================================================================
//Funciones adicionales 
//===================================================================================
void mostrarOpciones(int opcionMostrar){
  if(opcionMostrar==1){
    printf("           ╔══╗╔╗  ╔══╗╔══╗╔═══╗╔══╗ ╔═══╗╔═══╗╔══╗\n");
    printf("           ║╔═╝║║  ║╔╗║║╔═╝║╔══╝║╔═╝ ║╔═╗║║╔═╗║║╔╗║\n");
    printf("           ║║  ║║  ║╚╝║║╚═╗║╚══╗║╚═╗ ║╚═╝║║╚═╝║║║║║\n");
    printf("           ║║  ║║  ║╔╗║╚═╗║║╔══╝╚═╗║ ║╔══╝║╔╗╔╝║║║║\n");
    printf("           ║╚═╗║╚═╗║║║║╔═╝║║╚══╗╔═╝║ ║║   ║║║║ ║╚╝║\n");
    printf("           ╚══╝╚══╝╚╝╚╝╚══╝╚═══╝╚══╝ ╚╝   ╚╝╚╝ ╚══╝\n");
      
    printf("\n╔═════════════════════════════════════════════════════════════╗\n");
    printf("║                       MENÚ PRINCIPAL                        ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n");
    printf("╔═════════════════════════════════════════════════════════════╗\n");
    printf("║ 1. Menú de Registros                                        ║\n");
    printf("║ 2. Menú de Día a Día                                        ║\n");
    printf("║ 0. Salir                                                    ║\n");
    printf("╚═════════════════════════════════════════════════════════════╝\n");
    printf("Seleccione una opción: ");
  }
  else{
    if(opcionMostrar==2){
      printf("\n╔═════════════════════════════════════════════════════════════╗\n");
      printf("║                      MENÚ DE REGISTROS                      ║\n");
      printf("╚═════════════════════════════════════════════════════════════╝\n");
      printf("╔═════════════════════════════════════════════════════════════╗\n");
      printf("║ 1. Registrar Estudiantes                                    ║\n");
      printf("║ 2. Registrar Asignaturas                                    ║\n");
      printf("║ 0. Salir al menú principal                                  ║\n");
      printf("╚═════════════════════════════════════════════════════════════╝\n");
      printf("Seleccione una opción: ");
      
    }
    else{
      printf("\n╔═════════════════════════════════════════════════════════════╗\n");
      printf("║                      MENÚ DE DÍA A DÍA                      ║\n");
      printf("╚═════════════════════════════════════════════════════════════╝\n");
      printf("╔═════════════════════════════════════════════════════════════╗\n");
      printf("║ 1. Registro de Asistencia                                   ║\n");
      printf("║ 2. Registro de Calificaciones                               ║\n");
      printf("║ 3. Registro de Anotaciones                                  ║\n");
      printf("║ 4. Estudiantes Sobresalientes                               ║\n");
      printf("║ 5. Estadisticas generales del curso                         ║\n");
      printf("║ 0. Salir al menú principal                                  ║\n");
      printf("╚═════════════════════════════════════════════════════════════╝\n");
      printf("Seleccione una opción: ");     
    }
  }
}
/*
La función contains verifica si un elemento dado está presente en una lista. Recibe como entrada una lista y un elemento a buscar. Itera a través de la lista y compara cada elemento con el elemento objetivo. Si encuentra una coincidencia, devuelve 1, indicando que el elemento está contenido en la lista; de lo contrario, devuelve 0, indicando que el elemento no se encuentra en la lista.
*/
int contains(List *lista, const char *elemento) {
    void *dato = firstList(lista);
    while (dato != NULL) {   
        if (strcmp((char *)dato, elemento) == 0) {
            return 1;  
        }
        dato = nextList(lista);
    }
    return 0;
}
/*
La función imprimirMapaAsistencia recibe un TreeMap que representa el registro de asistencia de un estudiante. Primero, verifica si el tamaño del TreeMap es cero, en cuyo caso imprime un mensaje indicando que el mapa de asistencia está vacío. En caso contrario, itera sobre los elementos del TreeMap, imprimiendo la fecha y la asistencia correspondiente para cada par clave-valor. La función proporciona una visión estructurada del registro de asistencia, mostrando la información de manera legible.
*/
void imprimirMapaAsistencia(TreeMap *mapaAsistencia) {
    if (tamanoTreeMap(mapaAsistencia) == 0) {
        printf("Mapa de Asistencia vacío.\n");
        return;
    }

    Pair *asistenciaPair = firstTreeMap(mapaAsistencia);

    printf("Mapa de Asistencia:\n");

    while (asistenciaPair != NULL) {
        char asistencia = *((char *)asistenciaPair->value);
        printf("Fecha: %s | Asistencia: %c\n", (char *)asistenciaPair->key, asistencia);
        asistenciaPair = nextTreeMap(mapaAsistencia);
    }
}
/*
La función imprimirCalificaciones recibe un objeto de tipo Estudiante y se encarga de mostrar por pantalla las calificaciones asociadas a dicho estudiante. Primero imprime la etiqueta "Calificaciones:", seguido de las notas almacenadas en el arreglo. Luego, calcula e imprime el promedio de las calificaciones, o indica si no hay calificaciones registradas. La función proporciona una visión general de las calificaciones de un estudiante de manera estructurada.
*/
void imprimirCalificaciones(Estudiante *estudiante) {
    printf("Calificaciones:\n");

    // Imprimimos las notas almacenadas en el arreglo
    for (int i = 0; i < estudiante->NumCalificaciones; i++) {
        printf("%.2f ", estudiante->Calificaciones[i]);
    }

    // Calculamos e imprimimos el promedio
    if (estudiante->NumCalificaciones > 0) {
        float suma = 0.0;
        for (int i = 0; i < estudiante->NumCalificaciones; i++) {
            suma += estudiante->Calificaciones[i];
        }
        printf("\nPromedio: %.2f\n", suma / estudiante->NumCalificaciones);
    } else {
        printf("\nNo hay calificaciones registradas.\n");
    }
}
//===================================================================================
//Menú de Registros 
//===================================================================================
/*
La función registrarEstudiantes opera en un bucle continuo, solicitando al usuario información sobre estudiantes, como nombre, rut y edad. Luego, crea estructuras de datos para almacenar información adicional sobre cada estudiante, como listas de ramos, hoja de vida, mapas de asistencia y ramos, vinculándolas al estudiante correspondiente. Estos datos se insertan en el MapaCurso utilizando el nombre del estudiante como clave. El bucle continúa hasta que el usuario decide no agregar más estudiantes, proporcionando así una forma eficiente de registrar información detallada sobre varios estudiantes en el sistema.
*/
void registrarEstudiantes(TreeMap* MapaCurso){
  char respuesta[3];
  while (1){
    Estudiante *auxEstudiante=malloc(sizeof(Estudiante));
    
    printf("Ingrese el nombre del estudiante: ");
    scanf("%99[^\n]", auxEstudiante->nombre);
    printf("Ingrese el rut del estudiante: ");
    scanf("%11s", auxEstudiante->rut);
    printf("Ingrese la edad del estudiante: ");
    scanf("%d", &auxEstudiante->edad); 
    getchar();

    auxEstudiante->ListaDeRamos = createList();
    auxEstudiante->HojaDeVida = createList();
    auxEstudiante->MapaAsistencia = createTreeMap(lower_than_str);
    auxEstudiante->MapaRamos = createTreeMap(lower_than_str);

    
    insertTreeMap(MapaCurso, auxEstudiante->nombre ,auxEstudiante);
    printf("\nSe ha registrado exitosamente!!\n");
    
    printf("¿Desea agregar más estudiantes? (si/no): ");
    scanf("%s", respuesta);
    getchar();
    if(strcmp(respuesta, "no") == 0){
      break;
    }
  }
}
/*
La función registrarAsignaturas solicita al usuario el nombre de un estudiante y busca al estudiante correspondiente en el MapaCurso. Si encuentra al estudiante, solicita el nombre de una asignatura y crea una lista vacía para almacenar las calificaciones asociadas a esa asignatura. Luego, actualiza el mapa de ramos del estudiante con la nueva asignatura y agrega la asignatura a la lista de ramos del estudiante. Además, mantiene una lista global de todas las asignaturas registradas. Esta función proporciona una manera de estructurar y organizar las asignaturas de los estudiantes en el sistema, permitiendo un seguimiento eficiente de las calificaciones y la hoja de vida académica.
  */
void registrarAsignaturas(TreeMap *MapaCurso) {
  char nombreEstudiante[100];
  printf("Ingrese el nombre del estudiante: ");
  scanf(" %99[^\n]", nombreEstudiante);

  Pair *estudianteDestino = searchTreeMap(MapaCurso, nombreEstudiante);

  if (estudianteDestino != NULL) {
    Estudiante *estudiante = (Estudiante *)estudianteDestino->value;

    char *asignatura = malloc(100);
    if (asignatura == NULL) {
      printf("Error: No se pudo asignar memoria para el nombre de la asignatura.\n");
      return;
    }

    printf("Ingrese el nombre de la asignatura a agregar para %s: ", nombreEstudiante);
    scanf(" %99[^\n]", asignatura);

    List *listaNotas = createList();
    insertTreeMap(estudiante->MapaRamos, asignatura, listaNotas);

    pushBack(estudiante->ListaDeRamos, asignatura);

    List *listaAsignaturas = (List *)searchTreeMap(estudiante->MapaRamos, "asignaturas");
    if (listaAsignaturas == NULL) {
      listaAsignaturas = createList();
      insertTreeMap(estudiante->MapaRamos, "asignaturas", listaAsignaturas);
    }

    pushBack(listaAsignaturas, asignatura);

    printf("Asignatura registrada exitosamente para %s.\n", nombreEstudiante);
  } 
  else {
    printf("Estudiante %s no encontrado en el MapaCurso.\n", nombreEstudiante);
  }
}
/*
La función mostrarMenuRegistro presenta un menú interactivo que permite al usuario elegir entre registrar estudiantes, asignaturas, o salir al menú principal. Dependiendo de la opción seleccionada, invoca las funciones correspondientes para llevar a cabo las operaciones. La función utiliza la entrada del usuario para determinar la acción a realizar y proporciona mensajes informativos.
  */
void mostrarMenuRegistro(TreeMap* MapaCurso){  
  unsigned short opciones;
  while(1){
      char opcion[2]; 
      mostrarOpciones(2);
      scanf("%1s", opcion);
      getchar();

      if (isdigit(opcion[0])){
          opciones = atoi(opcion);

          switch(opciones){
              case 1:
                registrarEstudiantes(MapaCurso);
                break;

              case 2:
                registrarAsignaturas(MapaCurso);
                break;

            case 0: 
                printf("Regresando al Menú Principal de la aplicación...\n\n");
                return;

              default:
                printf("Opción no valida ingrese nuevamente\n");
          }
      }
      else{
          printf("\nOpción no válida. Ingrese un número.\n");
      }
  }
}
//===================================================================================
//Menú de Día Día 
//===================================================================================
/* La función de registro de asistencia busca un estudiante en el mapa curso y si lo encuentra permite dejar registrado según la fecha si estuvo presente o ausente, quedando registrado en un mapa de asistencias.
*/
void asistencia(TreeMap* MapaCurso) {
    char fecha[11];
    char nombreEstudiante[100];

    printf("Ingrese el nombre del estudiante: ");
    scanf("%99[^\n]%*c", nombreEstudiante);

    Pair* estudiantePair = searchTreeMap(MapaCurso, nombreEstudiante);

    if (estudiantePair != NULL) {
        printf("Ingrese la fecha (DD/MM/AAAA): ");
        scanf("%10s", fecha);

        Estudiante* estudiante = (Estudiante*)estudiantePair->value;

        char asistencia;
        printf("Ingrese la asistencia (P=Presente, A=Ausente): ");
        scanf(" %c", &asistencia);

        TreeMap* mapaAsistencia = (TreeMap*)estudiante->MapaAsistencia;

        char *fechaDuplicada = strdup(fecha);

        char *asistenciaCopia = malloc(sizeof(char));
        *asistenciaCopia = asistencia;

        insertTreeMap(mapaAsistencia, fechaDuplicada, asistenciaCopia);

        printf("Asistencia registrada exitosamente para %s en la fecha %s.\n", nombreEstudiante, fecha);
    } 
    else {
        printf("Estudiante %s no encontrado en el MapaCurso.\n", nombreEstudiante);
    }
}
/* La función de registro de calificaciones busca un estudiante en el mapa curso y si lo encuentra permite agregar las notas al estudiante almacenándolas en un arreglo.
*/
void calificaciones(TreeMap *MapaCurso) {
    char nombreEstudiante[100];

    printf("Ingrese el nombre del estudiante: ");
    scanf(" %99[^\n]%*c", nombreEstudiante);

    Pair *estudiantePair = searchTreeMap(MapaCurso, nombreEstudiante);

    if (estudiantePair == NULL) {
        printf("Estudiante %s no encontrado en el MapaCurso.\n", nombreEstudiante);
    } else {
        Estudiante *estudiante = (Estudiante *)estudiantePair->value;

        float nota;
        int calificacionValida = 0; 

        do {
            printf("Ingrese la calificación para %s (entre 10 y 70): ", nombreEstudiante);
            scanf("%f", &nota);

            if (nota >= 10 && nota <= 70) {
                calificacionValida = 1; 

                estudiante->Calificaciones = realloc(estudiante->Calificaciones, (estudiante->NumCalificaciones + 1) * sizeof(float));
                estudiante->Calificaciones[estudiante->NumCalificaciones++] = nota;

                printf("Calificación registrada exitosamente para %s.\n", nombreEstudiante);
            } else {
                printf("Error: La calificación debe estar en el rango de 10 a 70.\n");
            }
        } while (!calificacionValida); 
    }
}
/* La función de registro de anotaciones busca un estudiante en el mapa curso y si lo encuentra ocupa una lista para registrar las anotaciones como string para el estudiante.
*/  
void anotaciones(TreeMap *MapaCurso) {
    char nombreEstudiante[100];
    char anotacion[256];

    printf("Ingrese el nombre del estudiante: ");
    scanf(" %99[^\n]%*c", nombreEstudiante);

    Pair *estudiantePair = searchTreeMap(MapaCurso, nombreEstudiante);

    if (estudiantePair != NULL) {
        Estudiante *estudiante = (Estudiante *)estudiantePair->value;

        printf("Ingrese la anotación para %s: ", nombreEstudiante);
        fgets(anotacion, sizeof(anotacion), stdin);

        size_t len = strlen(anotacion);
        if (len > 0 && anotacion[len - 1] == '\n') {
            anotacion[len - 1] = '\0';
        }

        pushBack(estudiante->HojaDeVida, strdup(anotacion));

        printf("Anotación registrada exitosamente para %s.\n", nombreEstudiante);
    } else {
        printf("Estudiante %s no encontrado en el MapaCurso.\n", nombreEstudiante);
    }
}
/* La función calcular promedio permite conocer el promedio del estudiante según el arreglo de calificaciones y lo almacena para el estudiante en su estructura.
*/
void calcularPromedio(Estudiante *estudiante) {
    float sumaNotas = 0.0;

    if (estudiante->NumCalificaciones > 0) {
        for (int i = 0; i < estudiante->NumCalificaciones; ++i) {
            sumaNotas += estudiante->Calificaciones[i];
        }
        estudiante->Promedio = sumaNotas / estudiante->NumCalificaciones;
    } else {
        estudiante->Promedio = 0.0;
    }
}
/* La función mejores Estudiantes permite conocer todos los estudiantes que tengan promedio mayor o igual que 60 y se muestran por pantalla como los estudiantes sobresalientes dentro del mapa curso.
*/  
void mejoresEstudiantes(TreeMap *MapaCurso) {
    Pair *estudiantePair = firstTreeMap(MapaCurso);

    if (estudiantePair == NULL) {
        printf("No existen estudiantes registrados.\n");
        return;
    }

    while (estudiantePair != NULL) {
        Estudiante *estudiante = (Estudiante *)estudiantePair->value;

        // Calcular el promedio antes de mostrar
        calcularPromedio(estudiante);

        if (estudiante->Promedio >= 60.0) {
            printf("Estudiante: %s, Promedio: %.2f\n", estudiante->nombre, estudiante->Promedio);
        }

        estudiantePair = nextTreeMap(MapaCurso);
    }
}
/*
La función mostrarTodo solicita al usuario el nombre de un estudiante, busca al estudiante en el TreeMap llamado MapaCurso y, si se encuentra, imprime información detallada sobre ese estudiante. Muestra el nombre, el rut, la edad, la lista de ramos, la hoja de vida y las calificaciones del estudiante. Además, imprime el mapa de asistencia del estudiante. Si el estudiante no se encuentra en el MapaCurso, emite un mensaje indicando que el estudiante no fue encontrado.
  */
void mostrarTodo(TreeMap* MapaCurso){
  char nombreEstudiante[100];
  printf("Ingrese el nombre del estudiante: ");
  scanf(" %99[^\n]%*c", nombreEstudiante);
  Pair *estudiantePair = searchTreeMap(MapaCurso, nombreEstudiante);
  
  if(estudiantePair != NULL){
    Estudiante *estudiante = (Estudiante *)estudiantePair->value;
    printf("Nombre: %s\n", estudiante->nombre);
    printf("Rut: %s\n", estudiante->rut);
    printf("Edad: %d\n", estudiante->edad);

    printf("Lista de ramos: ");
    imprimirListaString(estudiante->ListaDeRamos);

    printf("Hoja de vida: ");
    imprimirListaString(estudiante->HojaDeVida);

    imprimirCalificaciones(estudiante);
    
    TreeMap *mapaAsistencia=(TreeMap *)estudiante->MapaAsistencia;
    imprimirMapaAsistencia(estudiante->MapaAsistencia);
    

  } else {
    printf("Estudiante no encontrado en el MapaCurso.\n");
  }
}
/*
La función mostrarMenuDiaDia presenta al usuario un menú con varias opciones relacionadas con las actividades diarias de los estudiantes. Se le pide al usuario que seleccione una opción, y según la opción elegida, se ejecutan diferentes funciones. Las opciones incluyen registrar asistencia, calificaciones, anotaciones, visualizar estudiantes sobresalientes, y mostrar toda la información detallada de un estudiante. 
  */
void mostrarMenuDiaDia(TreeMap* MapaCurso){  
  unsigned short opciones;
  while(1){
      char opcion[2]; 
      mostrarOpciones(3);
      scanf("%1s", opcion);
      getchar();

      if (isdigit(opcion[0])){
          opciones = atoi(opcion);

          switch(opciones){
              case 1:
                asistencia(MapaCurso);
                break;

              case 2:
                calificaciones(MapaCurso);
                break;
            
              case 3:
                anotaciones(MapaCurso);
                break;
            
              case 4:
                mejoresEstudiantes(MapaCurso);
                break;
            
              case 5:
                mostrarTodo(MapaCurso);
                break;

            case 0: 
                printf("Regresando al Menú Principal de la aplicación...\n\n");
                return;

              default:
                printf("Opción no valida ingrese nuevamente\n");
          }
      }
      else{
          printf("\nopción no válida. Ingrese un número.\n");
      }
  }
}
//===================================================================================
//Menú principal 
//===================================================================================
void mostrarMenuPrincipal(TreeMap* MapaCurso){  
  unsigned short opciones;
  while(1){
      char opcion[2]; 
      mostrarOpciones(1);
      scanf("%1s", opcion);
      getchar();

      if (isdigit(opcion[0])){
          opciones = atoi(opcion);

          switch(opciones){
              case 1:
                mostrarMenuRegistro(MapaCurso);
                break;

              case 2:
                mostrarMenuDiaDia(MapaCurso);
                break;

            case 0: 
                printf("Saliendo de la aplicación...\n");
                return;

              default:
                printf("Opción no valida ingrese nuevamente\n");
          }
      }
      else{
          printf("\nopción no válida. Ingrese un número.\n");
      }
  }
}
//===================================================================================
//Main 
//===================================================================================
int main() {
  TreeMap* MapaCurso = createTreeMap(lower_than_str);
  mostrarMenuPrincipal(MapaCurso);
  return 0;
}