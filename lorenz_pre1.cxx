#include <iostream>
#include <cmath>

using namespace std;

int main(void){
  double* Yps = new double[6]; // Yps = {[x, x'][y, y'][z, z']}
  Yps[0] = 1; Yps[2] = 1; Yps[4] = 1; // initiale Werte x(0), y(0) und z(0)
  
  const double btRK4[5][5] = {0, 0, 0, 0, 0, // Butcher-Tableau Zeile 1
                              0.5, 0.5, 0, 0, 0, // Zeile 2 ...
                              0.5, 0, 0.5, 0, 0,
                              1, 0, 0, 1, 0,
                              0, 1/6.0, 1/3.0, 1/3.0, 1/6.0}; // letzte Zeile
  const double b = 28.0;
  const double c = 8/3.0;
  double t = 0.0; // Start: 0.0, Ende: 100.0
  
  int N;
  cout << "Bitte Schrittanzahl eingeben:" << endl;
  cin >> N;

  const double dt = 100.0/N; // Schrittlaenge
  
  while(t < 100.0){
    cout << t << "\t" << endl;
    t += dt;
  }

  return 0;
}