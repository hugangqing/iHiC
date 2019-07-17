//A set of functions commonly used
#ifndef OFTENUSEDOPERATLIB_H
#define OFTENUSEDOPERATLIB_H

#include<algorithm>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include<string>
#include<sstream>
#include<utility>
#include<vector>
#include"assert.h"
#include"math.h"

using std::vector;
using std::make_pair;
using std::cout;
using std::endl;
using std::setw;
using std::set;
using std::map;
using std::pair;

typedef std::pair<int, int> Pa_I_I;
typedef std::string Str;
typedef std::vector<double> Ve_D;

template <class T>
T _max(T a, T b){
	return a > b ? a:b;
}

template <class T>
T _min(T a, T b){
	return a > b ? b:a;
}

template <class T>
T _abs(T a){
	return a > 0 ? a:0-a;
}

template <class T>
int getSize(const map<Str, T >& chr_T ){
	int n = 0;
	for( typename map<Str, T >::const_iterator it = chr_T.begin();
			it != chr_T.end(); ++it)
		n += it->second.size();
	return n;
}

template<typename T>
map<Str, set<T> > vector2set( const map<Str, vector<T> >& a){
	map<Str, set<T> > b;
	for(typename map<Str, vector<T> >::const_iterator chrIt = a.begin(); chrIt != a.end(); ++chrIt ){
		for( typename vector<T>::const_iterator it = chrIt->second.begin(); it != chrIt->second.end(); ++it ){
			b[chrIt->first].insert(*it);
		}
	}
	return b;
}//*/

template<typename T>
map<Str, vector<T> > set2vector( const map<Str, set<T> >& a){
	map<Str, vector<T> > b;
	for(typename map<Str, set<T> >::const_iterator chrIt = a.begin(); chrIt != a.end(); ++chrIt ){
		for( typename set<T>::const_iterator it = chrIt->second.begin(); it != chrIt->second.end(); ++it ){
			b[chrIt->first].push_back(*it);
		}
		typedef std::string Str;
	}
	return b;
}//*/

template <class T>
std::string convert2String(const T& i)
{
	std::ostringstream os;
	os << i;
	return(os.str());
}

inline void FileNotFoundERR(Str f){
	cout<<"File "<<f<<" not found"<<endl;
	exit(0);
}

double GetAver( vector<double>& v );
double GetDerivate( vector<double>& tmp );
void strip(Str& s, char c);
map<Str, int> getChrlen(Str file);

#endif
