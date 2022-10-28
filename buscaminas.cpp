#include <iostream>
#include <iterator>
#include <map>
#include <time.h>
#include <cstdlib>
using namespace std;
  
int main(int argc, char** argv)
{
    //Validación de parámetros de entrada
    //Se resta 48 a argv[2][0] para convertir debido a la tabla Ascii
    if(argc!=3 || !isdigit(argv[1][0]) || !isdigit(argv[2][0]) || int(argv[2][0]-48)>3 || int(argv[2][0]-48)<1)
    {
        cout<<"Uso: ./buscaminas 5 3 | es un tablero 5x5 con dificultad máxima [1-3]"<<endl;
        return 1;
    }
    cout <<"Tablero de "<<argv[1]<<"x"<<argv[1]<<" dificultad "<<argv[2][0]<<endl;
    //Instanciación de variables
    bool bool_juego;
    char char_accion;
    float float_dificultad;
    int int_area_tablero;
    int int_aleatorio;
    int int_cant_descubiertas;
    int int_cant_marcadas;
    int int_cant_minas;
    int int_cont_minas;
    int int_coor_x;
    int int_coor_y;
    int int_dificultad;
    int int_ite_filas=0;;    
    int int_lado_tablero;
    int int_resultado;
    map<int, map<int,char>> map_juego;
    map<int, map<int,char>>::iterator itr_map_juego;
    map<int, char>::iterator ptr_map_juego;
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
    //Map de 5x5 para test
    /*map_juego[0][1]='-';
    map_juego[1][1]='-';
    map_juego[2][1]='-';
    map_juego[3][1]='-';
    map_juego[4][1]='-';
    map_juego[5][1]='-';
    map_juego[6][1]='-';
    map_juego[7][1]='-';
    map_juego[8][1]='-';
    map_juego[9][1]='-';
    map_juego[10][1]='-';
    map_juego[11][1]='-';
    map_juego[12][1]='-';
    map_juego[13][1]='-';
    map_juego[14][1]='-';
    map_juego[15][1]='-';
    map_juego[16][1]='-';
    map_juego[17][1]='-';
    map_juego[18][1]='-';
    map_juego[19][1]='-';
    map_juego[20][1]='-';
    map_juego[21][1]='-';
    map_juego[22][1]='-';
    map_juego[23][1]='-';
    map_juego[24][1]='-';

    map_juego[0][0]=9;
    map_juego[1][0]=0;
    map_juego[2][0]=0;
    map_juego[3][0]=9;
    map_juego[4][0]=0;
    map_juego[5][0]=9;
    map_juego[6][0]=0;
    map_juego[7][0]=0;
    map_juego[8][0]=9;
    map_juego[9][0]=0;
    map_juego[10][0]=9;
    map_juego[11][0]=9;
    map_juego[12][0]=0;
    map_juego[13][0]=0;
    map_juego[14][0]=0;
    map_juego[15][0]=9;
    map_juego[16][0]=9;
    map_juego[17][0]=0;
    map_juego[18][0]=9;
    map_juego[19][0]=0;
    map_juego[20][0]=0;
    map_juego[21][0]=0;
    map_juego[22][0]=0;
    map_juego[23][0]=0;
    map_juego[24][0]=0;*/
    
    //Pintar tablero Claro
    for(int i=0;i!=int_area_tablero;i++)
    {
        cout << int(map_juego[i][0]) << " ";
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << endl;
            int_ite_filas=0;
        }
    }
    cout << endl;
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
    //Pintar tablero claro
    for(int i=0;i!=int_area_tablero;i++)
    {
        cout << int(map_juego[i][0]) << " ";//pinta claro
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << endl;
            int_ite_filas=0;;
        }
    }
    cout << endl;
    //Pintar oscuro
    for(int i=0;i!=int_area_tablero;i++)
    {
        cout << "\t\b" <<int(map_juego[i][1]) <<"\t\b";//Imprime oscuro
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << "\n\n\n";
            int_ite_filas=0;;
        }
    }
    //Pinta posiciones
        for(int i=0;i!=int_area_tablero;i++)
    {
        cout << "\t\b" << i <<"\t\b";//Imprime id de celdas
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << "\n\n\n";
            int_ite_filas=0;;
        }
    }
    cout << "\t\bSeleccione celda ";
    cin >> int_coor_x; //Debo cambiar esto y la Y
    if(map_juego[int_coor_x][0]!=9)
    {
        map_juego[int_coor_x][1]=map_juego[int_coor_x][0];
        //Pintar oscuro
        for(int i=0;i!=int_area_tablero;i++)
        {
        cout << "\t\b" <<int(map_juego[i][1]) <<"\t\b";//Imprime oscuro
        int_ite_filas++;
            if(int_ite_filas==int_lado_tablero)
            {
                cout << "\n\n\n";
                int_ite_filas=0;;
            }
        }
    }
    else
    {
        cout << "\t\b¡ Boom ! XD" << endl;
    }
    

    return 1;
    int_aleatorio = rand()%2;
    map_juego[0][0]=int_aleatorio;
    map_juego[0][1]='-';
    int_aleatorio = rand()%2;
    map_juego[1][0]=int_aleatorio;
    map_juego[1][1]='-';
    int_aleatorio = rand()%2;
    map_juego[2][0]=int_aleatorio;
    map_juego[2][1]='-';
    int_aleatorio = rand()%2;
    map_juego[3][0]=int_aleatorio;
    map_juego[3][1]='-';
    while(!((int_cant_descubiertas+int_cant_marcadas)==int_lado_tablero))
    {
        for(int i=0;i<int_lado_tablero; i++)
        {
            for(int j=0;j<int_lado_tablero;j++)
            {
                cout << map_juego[i][1];
            }
            cout << endl;
        }
        cin >> int_coor_x >> int_coor_y >> char_accion;
        if(char_accion=='d' || char_accion=='D')
        {
            if (map_juego[0][0]!=1)//1 es igual a bomba 9
            {
                map_juego[0][1]==map_juego[0][0];
                cout << "OK" << endl;
                int_cant_descubiertas++;
            }
            else
            {
                cout << "BOOM!" << endl;
                return 1;
            }
        }
        else if(char_accion=='m' || char_accion=='M')
        {

        }
    }
    /* 
    map_juego[0][0]=3;
    map_juego[0][1]='M';
    map_juego[1][0]=1;
    map_juego[1][1]='-';
    map_juego[2][0]=4;
    map_juego[2][1]=map_juego[2][0];
    cout << int_aleatorio << endl;
    cout << int(map_juego[0][0]) <<" "<< map_juego[0][1] << endl;
    cout << int(map_juego[1][0]) <<" "<< map_juego[1][1] << endl;
    cout << int(map_juego[2][0]) <<" "<< int(map_juego[2][0]) << endl;
     */
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
