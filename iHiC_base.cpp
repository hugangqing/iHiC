#include "iHiC_base.h"

double GetAver( vector<double>& v )
{
	double aver = 0;
	int i = 0;
	for( ; i < v.size(); ++i )
		aver += v[i];
	return (aver / v.size());
}

double GetDerivate( vector<double>& tmp )
{
	vector<double> v = tmp;
	double aver = GetAver( v );
	double der = 0;
	int i = 0;
	for( ; i < v.size(); ++i )
		der += ( v[i] - aver ) * ( v[i] - aver );
	return sqrt( der / v.size() );
}

map<Str, int> getChrlen(Str fileName){
	std::ifstream in(fileName.data());
	if( !in.good() )
		FileNotFoundERR(fileName);
	map<Str, int> chr_len;
	while( !in.eof() ){
		Str chr;
		int len;
		in>>chr>>len;
		if( !chr.empty() ){
			chr_len[chr] = len;
		}
	}
	return chr_len;
}

void strip(Str& s, char c){
	Str tmp;
	for( unsigned int i = 0; i < s.size(); ++i){
		if(s[i] != c)
			tmp.push_back(s[i]);
	}
	s = tmp;
}

