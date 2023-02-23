/*
Nom: Jordi Torrella Lopez
S'ha d'optimitzar aquest codi tot el que pugueu.
Fer un document PDF on s'explica detalladament com estava el codi i quina millora heu fet.
Podeu modificar el codi tot el que vulgueu, però ha de mantenir les mateixes funcionalitats, no pot tenir noves ni tenir menys, el programa ha de fer el mateix.
*/

#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>

using namespace std;

struct carta // declaro structura carta

{
  int numero; // integral numero
  string palo;
};
/* HAY QUE HACER PUNTEROS EL BOOLEANO Y NUMERO CARTAS MANO Y PUNTOS*/
/* PARA OBTIMIZAR CODIGO PUEDES HACER DOS FUNCIONES BASICAS QUE TE AYUDARAN A QUITAR 200 LINEAS. FUNCION DE COUTS Y FUNCION DE COUTS DE GANAR PERDER Y EMPATAR. RECUERDALO */
void robarcarta(carta mano[], int contadorAs, int *puntos, int *num_cartas_mano, bool *repetir, int *contadorMano);
void resultado(int *puntos, bool *repetir);

int main()
{

  struct carta baraja[52];                                       // Creamos estructura carta con el mazo casi completo (es decir, sin jokers)
  time_t t;                                                      // la variable time la declaramos para que no se repita en ningún caso la extraccion de una carta con un numero y palo iguales
  srand((unsigned)time(&t));                                     // creamos con el srand y obligamos con el time a que no sean iguales
  int numeros[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // array de posiciones de carta A,J,Q,K...

  const string palos[4] = {"Corazones", "Diamantes", "Picas", "Treboles"}; // variable como el int pero que no cambia

  int contador = 0; // contador igualamos a 0

  for (int i = 0; i < 13; i++)
  { // generamos valor carta
    for (int j = 0; j < 4; j++)
    {                                       // generamos valor palo
      baraja[contador].numero = numeros[i]; // juntas las dos, generan la baraja entera
      baraja[contador].palo = palos[j];
      contador++; // elevamos el contador a 52, genera todo el mazo
    }
  }

  int opcion;                                                                            // variable de menu
  bool repetir = true;                                                                   // repetir que te de carta siempre y cuando esté en true
  struct carta mano[52], manoMaquina[52];                                                // 1era structura nuestra mano 2da la de la maquina
  int num_cartas_mano, carta_mano_maquina, puntos, contadorAs, puntosMaquina, turno = 0; // declara las variables que va a utilizar a 0 (contadores)

  // Repartir cartas
  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++)
  {
    mano[contadorBaraja] = baraja[rand() % 52]; // generamos dos cartas random del mazo
  }

  do
  { // hace do while para que primera haga 6 couts y luego condiciones. Saca lo que puedes hacer como switch case ejem ejem
    cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
    cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
    cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
    cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
    cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
    cout << "\033[1;32m 0. SALIR \033[0m" << endl;

    if (turno == 0) // en el caso de que turno sea igual a 0...
    {
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      puntos = 0;
      contadorAs = 0;
      for (int contadorMano = 0; contadorMano < 52; contadorMano++)
      {
        robarcarta(mano, contadorAs, &puntos, &num_cartas_mano, &repetir, &contadorMano);
      }
    }
    resultado(&puntos, &repetir);
    cout << "\nIngrese una opcion: "; // ingresa la opción que quieres realizar en el menu...
    cin >> opcion;
    turno++; // y por lo tanto se suma 1 turno

    switch (opcion)
    { // abrimos el switch case para que elija opcion
    case 1:
      // system("cls");                                   // limpiamos
      mano[num_cartas_mano + 1] = baraja[rand() % 52]; // te saca carta
      cout << "\033[1;32mTu carta es: \033[0m" << endl;

      if (mano[num_cartas_mano + 1].numero == 1)
      { // lo del AS
        cout << "\033[1;32m A de " << mano[num_cartas_mano + 1].palo << "\033[0m" << endl;
        contadorAs++;
        if (contadorAs >= 1 && puntos + 11 > 21)
        {
          puntos = puntos + 1;
        }
        else
        {
          puntos = puntos + 11;
        }
        num_cartas_mano++;
      }
      else if (mano[num_cartas_mano + 1].numero == 11)
      { // lo de la Sota
        cout << "\033[1;32m Sota de " << mano[num_cartas_mano + 1].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
      }
      else if (mano[num_cartas_mano + 1].numero == 12)
      { // lo del caballo
        cout << "\033[1;32m Caballo de " << mano[num_cartas_mano + 1].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
      }
      else if (mano[num_cartas_mano + 1].numero == 13)
      { // lo del rey
        cout << "\033[1;32m Rey de " << mano[num_cartas_mano + 1].palo << "\033[0m" << endl;
        puntos = puntos + 10;
        num_cartas_mano++;
      }
      else
      { // si no es una figura...
        cout << "\033[1;32m " << mano[num_cartas_mano + 1].numero << " de " << mano[num_cartas_mano + 1].palo << "\033[0m" << endl;
        puntos = puntos + mano[num_cartas_mano + 1].numero;
        num_cartas_mano++;
      }

      resultado(&puntos, &repetir);
      break;

    case 2:
      // system("cls");
      cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
      puntos = 0;
      contadorAs = 0;
      for (int contadorMano = 0; contadorMano < 52; contadorMano++)
      {
        robarcarta(mano, contadorAs, &puntos, &num_cartas_mano, &repetir, &contadorMano);
      }
      cout << "\033[1;32mTienes " << puntos << " puntos \033[0m" << endl;
      break;

    case 3:
      // system("cls");
      cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << endl;
      cout << "\033[1;36mAhora juega la máquina\033[0m" << endl;
      while (puntosMaquina < puntos)
      {
        cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        manoMaquina[carta_mano_maquina] = baraja[rand() % 52];
        if (manoMaquina[carta_mano_maquina].numero == 1)
        {
          cout << "\033[1;33m A de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
        }
        else if (manoMaquina[carta_mano_maquina].numero == 11)
        {
          cout << "\033[1;33m Sota de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
        }
        else if (manoMaquina[carta_mano_maquina].numero == 12)
        {
          cout << "\033[1;33m Caballo de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
        }
        else if (manoMaquina[carta_mano_maquina].numero == 13)
        {
          cout << "\033[1;33m Rey de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
        }
        else
        {
          cout << "\033[1;33m " << manoMaquina[carta_mano_maquina].numero << " de " << manoMaquina[carta_mano_maquina].palo << "\033[0m" << endl;
        }
        puntosMaquina = puntosMaquina + manoMaquina[carta_mano_maquina].numero;
        cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
        carta_mano_maquina++;
      }
      if (puntosMaquina > 21)
      {
        cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
        cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
      }
      else if (puntosMaquina == puntos)
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;33mEmpate\033[0m" << endl;
      }
      else
      {
        cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
        cout << "\033[1;31mHas perdido...\033[0m" << endl;
      }
      cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
      repetir = false;
      break;
    case 4: // muestra toda la baraja
      for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++)
      {
        if (baraja[contadorBaraja].numero == 1)
        {
          cout << "A de " << baraja[contadorBaraja].palo << endl;
        }
        else if (baraja[contadorBaraja].numero == 11)
        {
          cout << "Sota de " << baraja[contadorBaraja].palo << endl;
        }
        else if (baraja[contadorBaraja].numero == 12)
        {
          cout << "Caballo de " << baraja[contadorBaraja].palo << endl;
        }
        else if (baraja[contadorBaraja].numero == 13)
        {
          cout << "Rey de " << baraja[contadorBaraja].palo << endl;
        }
        else
        {
          cout << baraja[contadorBaraja].numero << " de " << baraja[contadorBaraja].palo << endl;
        }
      }

      break;

    case 0: // sale
      repetir = false;
      break;
    }
  } while (repetir);

  return 0;
}

void robarcarta(carta mano[], int contadorAs, int *puntos, int *num_cartas_mano, bool *repetir, int *contadorMano)
{
  // si tienes 0 cartas o menos de 52 ejecuta el for
  if (mano[*contadorMano].palo != "")
  {
    if (mano[*contadorMano].numero == 1)
    {
      cout << "\033[1;33m A de " << mano[*contadorMano].palo << "\033[0m" << endl;
      contadorAs++;
      if (contadorAs >= 1 && *puntos + 11 > 21)
      {                        // si tienes un as o mas de un as y tus puntos mas 11 son mas que 21
        *puntos = *puntos + 1; // el valor sera 1
      }
      else
      {
        *puntos = *puntos + 11; // el valor sera 11
      }
      *num_cartas_mano++; // y añadimos una carta a la mano
    }
    else if (mano[*contadorMano].numero == 11)
    {                                                                                 // si el numero es 11
      cout << "\033[1;33m Sota de " << mano[*contadorMano].palo << "\033[0m" << endl; // cout de sota
      *puntos = *puntos + 10;                                                         // representa +10 de valor de la jugada
      *num_cartas_mano++;                                                             // aumentamos 1 carta a la mano
    }
    else if (mano[*contadorMano].numero == 12)
    { // si es el 12... ( caballo)
      cout << "\033[1;33m Caballo de " << mano[*contadorMano].palo << "\033[0m" << endl;
      *puntos = *puntos + 10;
      *num_cartas_mano++; // aumentamos 1 carta a la mano
    }
    else if (mano[*contadorMano].numero == 13)
    { // si es el 13... ( caballo)
      cout << "\033[1;33m Rey de " << mano[*contadorMano].palo << "\033[0m" << endl;
      *puntos = *puntos + 10;
      *num_cartas_mano++; // aumentamos 1 carta a la mano
    }
    else
    { // TODAS LAS DEMAS CARTAS QUE NO SEAN FIGURAS...
      cout << "\033[1;33m " << mano[*contadorMano].numero << " de " << mano[*contadorMano].palo << "\033[0m" << endl;
      *puntos = *puntos + mano[*contadorMano].numero;
      *num_cartas_mano++; // aumentamos 1 carta a la mano
    }
  }
}

void resultado(int *puntos, bool *repetir)
{
  if (*puntos > 21)
  { // si puntos es mas grande que 21..
    cout << "\033[1;31mTe has pasado... puntos: " << *puntos << "\033[0m" << endl;
    cout << "\033[1;31mHas perdido\033[0m" << endl;
    *repetir = false; // el bool para y por tanto se acaba juego
  }
  else if (*puntos == 21)
  { // si clavas 21...
    cout << "\033[1;33mFELICIDADES tienes " << *puntos << " puntos!(Blackjack)\033[0m" << endl;
    *repetir = false; // se para porque has ganado
  }
  else
  { // te muestra los puntos si no haces estas dos jugadas de arriba
    cout << "\033[1;32mTienes " << *puntos << " puntos \033[0m" << endl;
  }
}
