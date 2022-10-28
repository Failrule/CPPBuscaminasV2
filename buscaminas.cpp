#include <iostream>
#include <iterator>
#include <map>
#include <time.h>
#include <cstdlib>

using namespace std;
  

//Declaración de funcion imprimir tablero
void funImpr(int, int, int, map<int, map<int,char>>, char);

//Buscaminas
int main(int argc, char** argv)
{
    //Declaración de variables
    bool bool_juego;                                    //Mientras sea true se jugará
    char char_accion;                                   //Usuario ingresa [M]arcar o [D]estapar
    char char_opc_impr;                                 //Sistema ingresa [c]laro para imprimir contenido celda, [p]osición para poder elegir, null para imprimir oscuro
    float float_dificultad;                             //Ayuda a calcular porcentaje de minas relativo a la dimensión del campo y la dificultad
    int int_area_tablero;                               //Area calculada apartir de int_lado_tablero
    int int_aleatorio;                                  //Aleatorio para minar campo
    int int_cant_descubiertas;                          //Cuenta campos descubiertos por el usuario
    int int_cant_marcas;                                //Cuenta marcas puestas por el usuario
    int int_cant_minas;                                 //Cantidad minas puestas por el sistema según dificultad
    int int_cont_minas;                                 //Cuenta minas puestas por el sistema para validar que se pongan todas
    int int_selec_celda;                                //Número correspondiente al número ID de la celda
    int int_dificultad;                                 //Nivel de dificultad ingresada por el usuario de 1 a 3
    int int_ite_filas=0;;                               //Contador para darle forma de cuadrado al sistema
    int int_lado_tablero;                               //Dimension de largo o alto ingresada para cálculo de int_area_tablero
    int int_resultado;                                  //Ayuda a calcular estado del juego en relación a int_cant_minas, int_cant_marcas, map_juego.max_size()
    map<int, map<int,char>> map_juego;                  //Map para almacenar posiciones estados y valores de las minas

    //Validación de parámetros de entrada
    if(argc!=3 || !isdigit(argv[1][0]) || !isdigit(argv[2][0]) || int(argv[2][0]-48)>3 || int(argv[2][0]-48)<1) //Se resta 48 a argv[2][0] para convertir char a valor int
    {
        cout<<"Uso: ./buscaminas 5 3 | es un tablero 5x5 con dificultad máxima [1-3]"<<endl;
        return 1;
    }
    cout <<"Tablero de "<<argv[1]<<"x"<<argv[1]<<" dificultad "<<argv[2][0]<<"\n\n";

    //Instanciación de tablero
    int_lado_tablero = int(argv[1][0]-48);
    int_area_tablero = int_lado_tablero*int_lado_tablero;
    //Instanciación de cantidad de minas según dificultad
    int_dificultad = int(argv[2][0]-48);
    if(int_dificultad==1)
    {
        float_dificultad = 0.3; //30% del tablero con minas
    }
    else if(int_dificultad==2)
    {
        float_dificultad = 0.5; //50% del tablero con minas
    }
    else
    {
        float_dificultad = 0.7; //70% del tablero con minas
    }
    int_cant_minas = int((int_area_tablero)*float_dificultad);
    int_cant_marcadas = 0;
    //Inflar tablero y asignar minas
    int_cont_minas = int_cant_minas;
    while(int_cont_minas!=0)//Solo saldrá de aquí si todas las minas son puestas
    {
        srand(time(0));
        for(int i=0;i!=(int_area_tablero);i++) //Pasa por cada una de las celdas del tablero
        {
            map_juego[i][1]='-';
            int_aleatorio = rand()%4;
            if(map_juego[i][0]!=9 && int_aleatorio==1 && int_cont_minas>0)//Si el arreglo no tiene una mina y el aleatorio es 0 y las minas aún no son 0
            {
                map_juego[i][0]=9;
                int_cont_minas--;
            }
        }
    }

    //Calcular campo de minas
    for(int i=0;i!=int_area_tablero;i++)
    {
        //Todas las de la derecha, no entrar si col = int_lado_tablero
        if(map_juego[i][0]!=9 && int_ite_filas != int_lado_tablero-1)
        {
            if(map_juego[i+1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de la izquierda, no entrar si col=0
        if(map_juego[i][0]!=9 && int_ite_filas!=0)
        {
            if(map_juego[i-1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de arriba
        if(map_juego[i][0]!=9)
        {
            if(map_juego[i-int_lado_tablero][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de abajo
        if(map_juego[i][0]!=9)
        {
            if(map_juego[i+int_lado_tablero][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de arriba derecha, no entrar si col=int_lado_tablero
        if(map_juego[i][0]!=9 && int_ite_filas != int_lado_tablero-1)
        {
            if(map_juego[(i-int_lado_tablero)+1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de arriba izquierda, no entrar si col=0
        if(map_juego[i][0]!=9 && int_ite_filas !=0)
        {
            if(map_juego[(i-int_lado_tablero)-1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de abajo derecha, no entrar si col=int_lado_tablero
        if(map_juego[i][0]!=9 && int_ite_filas != int_lado_tablero-1)
        {
            if(map_juego[(i+int_lado_tablero)+1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        //Todas las de abajo izquierda, no entrar si col=0
        if(map_juego[i][0]!=9 && int_ite_filas != 0)
        {
            if(map_juego[(i+int_lado_tablero)-1][0]==9)
            {
                map_juego[i][0]++;
            }
        }
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            int_ite_filas=0;
        }
    }

    //Flujo de juego
    while(int_resultado!=0)//Siempre que sea 0 jugará hasta que gane int_resultado == 1 o pierda return 1;
    {
        
    }

    funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
    cout << "\t\bSeleccione celda\n\n\n";
    char_opc_impr = 'o';
    funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
    cout << "\t\bSeleccione celda ";
    

    //Validación celda
    cin >> int_selec_celda;
    if(map_juego[int_selec_celda][0]!=9)
    {
        map_juego[int_selec_celda][1]=map_juego[int_selec_celda][0];
    }
    else
    {
        cout << "\t\b¡ Boom ! XD" << endl;
    }
}

//Imprime tablero
void funImpr(int int_area_tablero, int int_ite_filas, int int_lado_tablero, map<int, map<int,char>> map_juego, char char_opc_impr)
{
    for(int i=0;i!=int_area_tablero;i++)
    {
        if (char_opc_impr == 'c') // Opción Claro
        {
            cout << "\t\b" << int(map_juego[i][0]) << "\t\b";//Imprime map en su posición 0 que son los valores y las minas
        }
        else if (char_opc_impr == 'p')
        {
            cout << "\t\b" << i << "\t\b";//Imprime posiciones de los campos que son números para seleccionar
        }
        else // Opción Oscuro
        {
            cout << "\t\b" << int(map_juego[i][1]) <<"\t\b";//Imprime 45 por algo de la tabla Ascii
        }
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << "\n\n\n";
            int_ite_filas=0;
        }
    }
}


/*
Configurar entorno para hacer pruebas y debugs con CMake -- OK

Definir variables -- OK
    Para las posiciones, contenido y estado de las casillas 
        map_juego 
            map<int, map<int,String>> 
            map<int_posicion,map<int_contenido,str_estado>>
            donde
                int_posicion es el id de la celda
                int_contenido es el valor: 
                    0 es cero minas alrededor
                    1 - 8 minas alrededor
                    9 es mina
                str_estado es el estado [·]Sin descubrir y [M]Marcada
        https://www.geeksforgeeks.org/implementing-multidimensional-map-in-c/
    Para el juego mientras true juega
        bool_juego
    Para la cantidad de minas y contador
        int_cant_minas
        int_cont_minas
    Para la dificultad del juego
        int_dificultad
    Para dimensión del tablero
        int_lado_tablero
    Para el área del tablero
        int_lado_tablero*int_lado_tablero
    Para las coordenadas
        int_coor_x
        int_coor_y
    Para las acciones
        char_accion
    Para el resultado del juego
        int_resultado
    
Ingresar dimensión del tablero -- OK
    Ingrese la dimensión EJ: 5 será un tablero de 5x5

Ingresar dificultad del tablero -- OK
    Ingrese dificultad 1-3 siendo 3 nivel más difícil
        int_dificultad = 1 → area_tablero*0,1 = int_cant_minas
        int_dificultad = 2 → area_tablero*0,5 = int_cant_minas
        int_dificultad = 3 → area_tablero*0,9 = int_cant_minas
        Redondear al siguiente en todos los casos

Asignar minas a posiciones -- OK
    int_tmp_cant_minas=int_cant_minas
    mientras(int_temp_cant_minas > 0)
        entonces 
            for Recorre map_juego(n)
                Si map_juego(n)!=9
                    map_juego→second=random(0 y 9)
                    int_temp_cant_minas--

Sumar minas vecinas y llenar el campo -- OK
    ej:
    0 1 1 1
    0 1 9 1
    0 1 1 1
    0 0 0 0

    0 0 0
    1 2 2
    9 9 2
    respecto a la posición central [5] del campo (celda que contiene un 1), map_juego[4].ptr->first[1] ptr-> [·]
    tiene una mina (9) en la posición superior derecha
    int_cont_mina=0 hasta cuando valida (superior derecha) int_cont_mina++
    si (-(int_lado_tablero)+1) == 9; entonces int_cont_mina++;
    Así con todas las relaciones:
        relación de una posición respecto su alrededor
            -(int_lado_tablero)   (superior)
            -(int_lado_tablero)+1 (superior derecha)
            +1                     (derecha)
            +(int_lado_tablero)+1 (inferior derecha)
            +(int_lado_tablero)   (inferior)
            +(int_lado_tablero)-1 (inferior izquierda)
            -1                     (izquierda)
            -(int_lado_tablero)-1 (superior izquierda)
        restricciones:
            si comprobación celda != error;
    luego asigna el valor int_cont_mina a map_juego[4].ptr->first[1] mediante
         map_juego[itr].insert(make_pair(int_cont_mina, "·"));

    
Pintar campo oscuro -- OK
    funcPintarCampoOscuro(){
        for(hasta que se acaben las celdas del map) ¿anidado?
                cout << map_juego.ptr->second; //Imprimirá · o M según el caso
        }

Pintar campo claro -- OK
    funcPintarCampoClaro(){
        for(hasta que se acaben las celdas del map) ¿anidado?
                cout << map_juego.ptr->first; //Imprimirá el valor de la celda
        }


Validar celda -- OK
    int funcValidarCelda()
        cin << int_coor_x << int_coor_y << char_accion[[M]arcar, [D]estapar]; 
        if (char_accion=='M')
            find int_coor_x*int_corr_y: map_juego[itr].insert(second "M")
            if (descubiertas+marca=celdas)
                return 0; //Ganó
            else
                return 1; //Juega
            
        else if char_accion=='D'
            if (map_juego<map->first==9)
                funcPintarCampoClaro
                bool_juego=false;
                return 2; //Muere
            else
                if (descubiertas+marca=celdas)
                return 0; //Ganó
                else
                return 1; //Juega

Hacer impresión de tablero como función
    funImprOscuro
        Imprime persiana
    funImprClaro
        Imprime valor celda
    funImprId
        Imprime posiciones




Flujo de juego
        bool_juego=true;
        limpiaPantalla()
        asignarMinas()
        sumarMinas()

    mientras bool_juego==true
        pintarOscuro();
        minar();
        si es mina
            fin
        else
            destapa()
            valida()
            si(gano())
                fin

Mejorar controles con ←↑↓→ [espacio] [M]

BLOC DE NOTAS
    Cada celda tiene
        posición && valor(mina||cuenta, estado)

        valor   
         0-8    suma vecinas
         9      mina
    Resuelto con Map dentro de Map

    Para que gane
        si (cantidad_celdas-cant_minas)!=
        
        1 1     · ·     1 1
        9 1     · ·     M 1

        4 celdas, 1 mina, 1 marca, 3 descubiertas

        ¿necesito una variable int_descubierto?

        Para: descubiertas+marca=celdas
        ganó

    Flujo de juego
    selecciona una celda
    la marca o destapa
    si es bomba y la destapó
        boom
    si es bomba y la marcó
        ok
    si no es bomba y la destapó
        ok
        Ganó
    vuelve a selecciona

    Mientras descubiertas+marca=celdas sea falso

*/
