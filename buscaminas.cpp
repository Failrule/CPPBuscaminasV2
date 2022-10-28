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
