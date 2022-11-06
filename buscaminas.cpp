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
    char char_accion;                                   //Usuario ingresa [M]arcar o [D]estapar
    char char_opc_impr;                                 //Sistema ingresa [c]laro para imprimir contenido celda, [p]osición para poder elegir, null para imprimir oscuro
    float float_dificultad;                             //Ayuda a calcular porcentaje de minas relativo a la dimensión del campo y la dificultad
    int int_area_tablero;                               //Area calculada apartir de int_lado_tablero
    int int_aleatorio;                                  //Aleatorio para minar campo
    int int_cant_descubiertas;                          //Cuenta campos descubiertos por el usuario
    int int_cant_marcas;                                //Cuenta marcas disponibles
    int int_cant_marcadas;                              //Cuenta marcas puestas por el usuario
    int int_cant_minas;                                 //Cantidad minas puestas por el sistema según dificultad
    int int_cant_pistas;                                //Cantidad de pistas para poder ver qué hay en una celda
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
    int_cont_minas = int_cant_minas; // Iguala contador y cantidad de minas calculadas para control while
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
    int_cant_marcas = int_cant_minas; // Iguala valores de minas y marcas para calcular estado del juego  
    int_cant_marcadas = 0;  
    int_cant_descubiertas = 0; // Configura a 0 descubiertas
    int_cant_pistas = (int_cant_minas/2)+1;
    while((int_cant_marcadas+int_cant_descubiertas)!=int_area_tablero) //Mientras el área del tablero no sea igual a la suma entre marcas y descubiertas, juega 
    {
        funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
        cout << "\t\bMarcas disponibles: " << int_cant_marcas << endl;
        cout << "\t\bPistas disponibles: " << int_cant_pistas << endl << endl;
        cout << "\t\b[d]escubrir, [m]arcar/desmarcar, [p]ista: ";
        cin >> char_accion;
        if(cin.fail())
        {
            cout << "\n\t\bFatal: Por favor eliga cuidadosamente las opciones\n";
            return 1;
        }
        else if(char_accion=='d' || char_accion=='D')
        {
            char_opc_impr='p';
            funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
            //Validación celda
            cout << "\t\bEscriba el número de la celda a descubrir: ";
            cin >> int_selec_celda;
            if(map_juego[int_selec_celda][0]!=9 && map_juego[int_selec_celda][1]!='>')
            {
                if(map_juego[int_selec_celda][1]=='-') // Si la celda no está descubierta o marcada como mina
                {
                    map_juego[int_selec_celda][1]=map_juego[int_selec_celda][0];
                    int_cant_descubiertas++;
                    char_opc_impr=' ';
                }
                else
                {
                    cout << "\t\bCelda "<< int_selec_celda <<" ya está descubierta y tiene valor "<< int(map_juego[int_selec_celda][0]) << endl;
                    system("sleep 3");
                    char_opc_impr=' ';
                }
            }
            else if(map_juego[int_selec_celda][1]=='>')
            {
                cout << "\t\bEsta celda está marcada, desmárquela antes de descubrirla" << endl;
                system("sleep 3");
                char_opc_impr=' ';
            }
            else if(map_juego[int_selec_celda][0]==9)
            {
                char_opc_impr='c';
                funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
                cout << "\t\b¡ Boom ! XD" << endl;
                return 1;
            }
            char_opc_impr=' ';
        }
        else if(char_accion=='m' || char_accion=='M')
        {
            char_opc_impr='p';
            funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
            //Validación celda
            cout << "\t\bEscriba el número de la celda a marcar: ";
            cin >> int_selec_celda;
            if(map_juego[int_selec_celda][1]=='-')
            {
                map_juego[int_selec_celda][1]='>';
                int_cant_marcas--;
                int_cant_marcadas++;
                char_opc_impr=' ';
            }
            else if(map_juego[int_selec_celda][1]=='>')
            {
                cout << "\t\bCelda desmarcada" << endl;
                map_juego[int_selec_celda][1]='-';
                int_cant_marcas++;
                system("sleep 3");
                char_opc_impr=' ';   
            }
            else
            {
                cout << "\t\bCelda "<< int_selec_celda <<" está descubierta y tiene valor de "<< int(map_juego[int_selec_celda][0]) << endl;
                system("sleep 3");
                char_opc_impr=' ';
            }
        }
        else if(char_accion=='p' || char_accion=='P')
        {
            char_opc_impr='p';
            funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
            //Validación celda
            cout << "\t\bEscriba el número de la celda que quiere investigar: ";
            cin >> int_selec_celda;
            if(map_juego[int_selec_celda][1]=='-' && int_cant_pistas!=0)
            {
                cout << "\t\bEsta celda tiene " << int(map_juego[int_selec_celda][0]) <<" en su interior"<< endl;
                system("sleep 3");
                char_opc_impr=' ';
                int_cant_pistas--;
            }
            else if(int_cant_pistas==0)
            {
                cout << "\t\bYa no tiene más pistas disponibles"<< endl;
                char_opc_impr=' ';
                system("sleep 3");
            }
            else
            {
                cout << "\t\bEsta celda está descubierta o está marcada"<< endl;
                char_opc_impr=' ';
                system("sleep 3");
            }
        }
    }
    char_opc_impr='c';
    funImpr(int_area_tablero, int_ite_filas, int_lado_tablero, map_juego, char_opc_impr);
    cout << "\t\b¡ Ganó !"<< endl;
    

}

//Imprime tablero
void funImpr(int int_area_tablero, int int_ite_filas, int int_lado_tablero, map<int, map<int,char>> map_juego, char char_opc_impr)
{
    system("clear");
    cout << "\n\n\n";
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
            if(char(map_juego[i][1])=='-' || char(map_juego[i][1])=='>') //Si en ese campo del map existe un '-' o '>' imprima en char de lo contrario el valor
            {
                cout << "\t\b" << char(map_juego[i][1]) <<"\t\b";//Imprime en char
            }
            else
            {
                cout << "\t\b" << int(map_juego[i][1]) <<"\t\b";//Imprime en int
            }
        }
        int_ite_filas++;
        if(int_ite_filas==int_lado_tablero)
        {
            cout << "\n\n\n";
            int_ite_filas=0;
        }
    }
}
