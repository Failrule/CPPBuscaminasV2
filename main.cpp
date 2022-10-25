#include <iostream>
#include <iterator>
#include <map>
using namespace std;
  
int main()
{
    bool bool_juego;
    char char_accion;
    int int_cant_minas;
    int int_cont_minas;
    int int_coor_x;
    int int_coor_y;
    int int_dificultad;
    int int_tablero;
    int int_resultado;
    map<int, map<int,string>> map_juego;
    map<int, map<int,string>>::iterator itr_map_juego;
    map<int, string>::iterator ptr_map_juego;
    
    cout << "Hello world" << endl;
}

/*
Configurar entorno para hacer pruebas y debugs con CMake -- OK

Definir variables
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
        int_tablero
    Para el área del tablero
        int_tablero*int_tablero
    Para las coordenadas
        int_coor_x
        int_coor_y
    Para las acciones
        char_accion
    Para el resultado del juego
        int_resultado
    
Ingresar dimensión del tablero
    Ingrese la dimensión EJ: 5 será un tablero de 5x5

Ingresar dificultad del tablero
    Ingrese dificultad 1-3 siendo 3 nivel más difícil
        int_dificultad = 1 → area_tablero*0,1 = int_cant_minas
        int_dificultad = 2 → area_tablero*0,5 = int_cant_minas
        int_dificultad = 3 → area_tablero*0,9 = int_cant_minas
        Redondear al siguiente en todos los casos

Asignar minas a posiciones
    int_tmp_cant_minas=int_cant_minas
    mientras(int_temp_cant_minas > 0)
        entonces 
            for Recorre map_juego(n)
                Si map_juego(n)!=9
                    map_juego→second=random(0 y 9)
                    int_temp_cant_minas--

Sumar minas vecinas y llenar map_juego ¿ITR termina siendo la dimensión del campo? parece que todo el campo
    ej:
    0 1 9 
    0 1 1
    0 0 0
    respecto a la posición central [5] del campo (celda que contiene un 1), map_juego[4].ptr->first[1] ptr-> [·]
    tiene una mina (9) en la posición superior derecha
    int_cont_mina=0 hasta cuando valida (superior derecha) int_cont_mina++
    si (-(int_tablero)+1) == 9; entonces int_cont_mina++;
    Así con todas las relaciones:
        relación de una posición respecto su alrededor
            -(int_tablero)   (superior)
            -(int_tablero)+1 (superior derecha)
            +1                     (derecha)
            +(int_tablero)+1 (inferior derecha)
            +(int_tablero)   (inferior)
            +(int_tablero)-1 (inferior izquierda)
            -1                     (izquierda)
            -(int_tablero)-1 (superior izquierda)
        restricciones:
            si comprobación celda != error;
    luego asigna el valor int_cont_mina a map_juego[4].ptr->first[1] mediante
         map_juego[itr].insert(make_pair(int_cont_mina, "·"));

Pintar campo oscuro
    funcPintarCampoOscuro(){
        for(hasta que se acaben las celdas del map) ¿anidado?
                cout << map_juego.ptr->second; //Imprimirá · o M según el caso
        }

Pintar campo claro
    funcPintarCampoClaro(){
        for(hasta que se acaben las celdas del map) ¿anidado?
                cout << map_juego.ptr->first; //Imprimirá el valor de la celda
        }


Validar celda
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
*/
