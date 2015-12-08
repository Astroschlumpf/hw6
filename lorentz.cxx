#include <iostream>
#include <cmath>

using namespace std;

// ************* Funktionen fuer Ableitung F = {X', Y', Z'} ************* //
void vecDiv(double* F, double t, double* vec, double a, double b, double c){
  F[0] = a * (vec[1] - vec[0]);
  F[1] = vec[0] * (b - vec[2]) - vec[1];
  F[2] = vec[0] * vec[1] - c * vec[2];
}
// ********************************************************************* //

// ************* Vektorielles Runge-Kutta mit Butcher-Tab. ************* //
void vecRuKu(void(*vecDiv)(double*, double, double*, double, double, double),
	     double dis, double t, double* vec, double a, double b, double c){ 
  // Runge-Kutta mit nachfolgendem Tableau und als Schablone fuer jede Koordinate
  // -> Koordinate wird durch Wahl der Funktion fkt vorgegeben
  //
  // const double btRK4[5][5] = {0,  0,  0,   0, 0, // Butcher-Tableau Zeile 1
  //                            0.5, 0.5, 0,  0, 0, // Zeile 2 ...
  //                            0.5, 0,  0.5, 0, 0,
  //                            1,   0,  0,   1, 0,
  //                            0, 1/6.0, 1/3.0, 1/3.0, 1/6.0}; // letzte Zeile
  double k[3] = {0.,0.,0.};
  double tmp[3]; // Kopie der urspruenglichen Werte == NICHT ueberschreiben
  for(int i = 0; i < 3; i++){
    tmp[i] = vec[i];
  }
  
  vecDiv(k, t, tmp, a, b, c); // k1
  for(int i = 0; i < 3; i++){
    tmp[i] = tmp[i] + 0.5 * dis * k[i];
    vec[i] += dis/6.0 * k[i];
  }
  
  vecDiv(k, t, tmp, a, b, c); // k2
  for(int i = 0; i < 3; i++){
    tmp[i] = tmp[i] + 0.5 * dis * k[i];
    vec[i] += dis/3.0 * k[i];
  }
  
  vecDiv(k, t, tmp, a, b, c); // k3
  for(int i = 0; i < 3; i++){
    tmp[i] = tmp[i] + dis * k[i];
    vec[i] += dis/3.0 * k[i];
  }
  
  vecDiv(k, t, tmp, a, b, c); // k4
  for(int i = 0; i < 3; i++){
    vec[i] += dis/6.0 * k[i];
  }
}
// ********************************************************************* //

int main(void){
  const double a = 10.0;
  const double b = 28.0;
  const double c = 8/3.0;
  double t = 0.0; // Start: 0.0, Ende: 100.0
  
  int N; int ind = 0;
  cout << "Bitte Schrittanzahl eingeben:" << endl;
  cin >> N;

  const double dt = 1.0/N; // Schrittlaenge
  
  cout << dt << endl;
  
  double Yps[3];//[N]; // Yps = {[x][y][z]}
  Yps[0] = 1.; Yps[1] = 1.; Yps[2] = 1.; // initiale Werte x(0), y(0) und z(0)
  
  cout << "# t \t x \t y \t z" << endl;
  cout << t << "\t" << Yps[0] << "\t" << Yps[1] << "\t" << Yps[2] << endl;
  
  while(t < 100.0){
    vecRuKu(vecDiv, dt, t, Yps, a, b, c); // Runge-Kutta aufrufen
    cout << t << "\t" << Yps[0] << "\t" << Yps[1] << "\t" << Yps[2] << endl;
    t += dt;
    ind++;
  }

  return 0;
}