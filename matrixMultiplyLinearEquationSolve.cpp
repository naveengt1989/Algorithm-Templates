#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAXD = 30;
const int MAXK = 30;

void mul(int a[MAXD][MAXD], int b[MAXD][MAXD], int c[MAXD][MAXD], int d) {
  for (int i = 0; i < d; ++i)
    for (int j = 0; j < d; ++j) {
      c[i][j] = 0;
      for (int k = 0; k < d; ++k) 
	c[i][j] += a[i][k]*b[k][j];
      c[i][j] &= 1;
    }
}

void fpowmod(int a[MAXD][MAXD], int d, int b) {
  int x[MAXD][MAXD], tmp[MAXD][MAXD];
  for (int i = 0; i < d; ++i)
    for (int j = 0; j < d; ++j)
      x[i][j] = (i==j?1:0);

  while (b) {
    if (b&1) {
      mul(a,x,tmp,d);
      memcpy(x,tmp,sizeof(x));
    }
    b >>= 1;
    mul(a,a,tmp,d);
    memcpy(a,tmp,sizeof(tmp));
  }
  memcpy(a,x,sizeof(x));
}

int solve(int m[MAXK][MAXD+1], int r, int c, int x[MAXD]) {
  int row = 0;
  for (int col = 0; col < c; ++col) {
    int piv = row;
    while (piv < r && !m[piv][col]) ++piv;
    if (piv == r) continue;

    for (int i = col; i < c; ++i)
      swap(m[row][i], m[piv][i]);

    for (int i = row+1; i < r; ++i)
      if (m[i][col])
	for (int j = c-1; j >= col; --j)
	  m[i][j] = (m[i][j]+m[row][j])&1;

    ++row;
  }

  for (int i = r-1; i >= 0; --i)
    for (int j = 0; j < c; ++j)
      if (m[i][j]) {
	if (j == c-1) return 0;
	else if (i < c-2) return 2;
	i = 0;
	break;
      }

  for (int i = c-2; i >= 0; --i) {
    x[i] = m[i][c-1];
    for (int j = c-2; j > i; --j)
      x[i] += m[i][j]*x[j];
    x[i] &= 1;
  }

  return 1;
}

int main() {
  int t, a[MAXD], id[MAXK], x[MAXK], r[MAXD][MAXD], m[MAXK][MAXD+1], seed[MAXD];
  cin >> t;
  while (t--) {
    int d, k, tmp;
    cin >> d >> k;
    for (int i = 0; i < d; ++i) cin >> a[i];//a values
    for (int i = 0; i < k; ++i) cin >> id[i] >> x[i];//
//xi(j)
    for (int i = 0; i < k; ++i) {
      memset(r, false, sizeof(r));
      for (int j = 0; j < d; ++j) r[0][j] = a[d-j-1];
      for (int j = 1; j < d; ++j) r[j][j-1] = 1;//A matrix 

      fpowmod(r,d,id[i]);// r = A^k = A^ id[i]
      for (int j = 0; j < d; ++j) m[i][j] = r[d-1][d-j-1];
      m[i][d] = x[i];
    }


    int num = solve(m,k,d+1,seed);
    if (num == 0) cout << "no solution" << endl;
    else if (num > 1) cout << "multiple solutions" << endl;
    else for (int i = 0; i < d; ++i) cout << seed[i] << (i+1==d?'\n':' ');
  }
}
