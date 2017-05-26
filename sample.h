#include<iostream>
#include<math.h>


class Object{
  
public :
  
  int reloj = 0;
  int cola;
  int TLL; //tiempo entre llegadas
  int TS; //tiempo servicio
  int TET = 0; //tiempo espera total
  int t_limite; //tiempo limite de simulación
  int t_ocio;
  int nclientes_LL; //clientes que han llegado
  int nclientes_A; //clientes atendidos
  int delta; //sive para determinar que evento sigue

  //event types
  static const int CLLEGO = 1;
  static const int CATTEND = 2;
  
 
public :

  Object(int tlimite) {

    this->t_limite = tlimite;
  }

  
  void setComingTime(int tll) {
    this->TLL = tll;
  }

  void setServiceTime(int ts) {
    this->TS = ts;
  }

  void setDelta(int delta) {
    this->delta = delta;
  }

  void updateTet() {
    this->TET += cola*delta; 
  }

  int getTET() {
    return this->TET;
  }
  
  int getDelta() {
    return this->delta;
  }

  int getLimitTime() {
    return this-> t_limite;
  }

  int getComingTime() {
    return this->TLL;
  }

  int getServiceTime() {
    return this->TS;
  }

  int getEvent() {

    int evento;
    if ((TLL - delta) == 0) {
	evento = CLLEGO;
	TLL -= delta;
    }
    
    else if((TS - delta) == 0) {
	evento = CATTEND;
	TS -= delta;
    }
      
      return evento;
  }
  
  void incrementClock() {
    this->reloj += delta;
  }

  int getClockTime() {
    return this->reloj;
  }

  bool timeFinish() {
    
    if (reloj <= t_limite)
      return true;
    else
      return false;
    
  }
  
};

// using namespace std;

// int main()
// {

//   Object objeto;

//   objeto.setComingTime(17.90);
  
//   cout << objeto.getComingTime() << endl;

//   return 0;
// }
