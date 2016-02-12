#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <complex>
#pragma comment(linker, "/STACK:266777216")
using namespace std;

#define assert(f) { if(!(f)) { fprintf(stderr,"Assertion failed: "); fprintf(stderr,#f); fprintf(stderr,"\n"); exit(1); } }

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<double> VD;
typedef pair<double,double> PDD;

const int inf=1000000000;
const LL INF=LL(inf)*inf;
const double eps=1e-9;
const double PI=2*acos(0.0);
#define bit(n) (1<<(n))
#define bit64(n) ((LL(1))<<(n))
#define pb push_back
#define sz size()
#define mp make_pair
#define cl clear()
#define all(a) (a).begin(),(a).end()
#define fill(ar,val) memset((ar),(val),sizeof (ar))
#define MIN(a,b) {if((a)>(b)) (a)=(b);}
#define MAX(a,b) {if((a)<(b)) (a)=(b);}
#define sqr(x) ((x)*(x))
#define X first
#define Y second
#define PI 3.14159265
//clock_t start=clock();
//fprintf(stderr,"time=%.3lfsec\n",0.001*(clock()-start));

#define MOD 1000000007

#define N 101010

struct Point
{
	int x;
	int y;
	Point(int a, int b)
	{
		x=a;
		y=b;
	}
};

double dotProduct(Point a, Point b)
{
	return (a.x*b.x + a.y*b.y);
}

double crossProduct(Point a, Point b)
{
	return abs(a.x*b.y - a.y*b.x);
}

double distancePoints(Point a, Point b)
{
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrt(dx*dx + dy*dy);
}


double getCosineAngle(double dot_product, double a_norm, double b_norm)
{
	return acos(dot_product/(a_norm*b_norm))* 180.0 / PI;
}

double getDistanceOfPointToLineSegment(Point A, Point B, Point P)
{
	
	Point vector_AP(P.x-A.x, P.y-A.y);
	Point vector_AB(B.x-A.x, B.y-A.y);
	Point vector_BA(A.x-B.x, A.y-B.y);
	Point vector_BP(P.x-B.x, P.y-B.y);

	if (dotProduct(vector_AB, vector_AP) < 0)
		return distancePoints(A, P);
	else if(dotProduct(vector_BA, vector_BP) < 0)
		return distancePoints(B, P);
	else
	return crossProduct(vector_AB, vector_AP)/distancePoints(A, B);
}



double getTangentAngle(double dot_product, double a_norm, double b_norm)
{
	//return atan(dot_product/(a_norm*b_norm))* 180.0 / PI;
	return atan(dot_product/(a_norm*b_norm))* 180.0 / PI;
}

double getArcTangentAngle(double x, double y)
{
	//return atan(dot_product/(a_norm*b_norm))* 180.0 / PI;
	cout<<atan2(y,x)* 180.0 / PI<<" degrees\n";
	cout<<atan2(y,x)/ PI<<" radiants\n";
}

int main()
{
	Point one(4,0);
	Point two(5,1);
	Point origin(0,0);	

	Point vectorA(one.x-origin.x, one.y-origin.y);
	Point vectorB(two.x-origin.x, two.y-origin.y);

	double dot_product = dotProduct(vectorA, vectorB);
	double a_norm = sqrt(vectorA.x*vectorA.x + vectorA.y*vectorA.y);
	double b_norm = sqrt(vectorB.x*vectorB.x + vectorB.y*vectorB.y);

	//cout<<getCosineAngle(dot_product, a_norm, b_norm)<<" degrees";

	//cout<<getTangentAngle(dot_product, a_norm, b_norm)<<" degrees";
	//getArcTangentAngle(1000,-1);
	cout<<getDistanceOfPointToLineSegment(one, origin, two);
}
