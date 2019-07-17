#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 5 ){
		cout<<"Usage: iHiC_III2TopDomInputs III_file Bin_size Chr_Lenth Output_prefix\n";
		exit(1);
	}
	int bin = atoi(args[2]);
	map<Str, int> chrlen = getChrlen(args[3]);
	Str prefix(args[4]);

	map<Str,map<pair<int,int>, int > > chr_bin1bin2_n;
	ifstream iii(args[1]);
	while( !iii.eof() ){
		Str chr;
		int pos1, pos2, cnt;
		iii>>chr>>pos1>>pos2>>cnt;
		if( !chr.empty() ){
			chr_bin1bin2_n[chr][make_pair(pos1/bin,pos2/bin)] += cnt;
		}
	}
	iii.close();

	for( map<Str, int>::iterator chrIt = chrlen.begin(); chrIt != chrlen.end(); ++chrIt ){
		int start = 1/bin;
		int end = chrIt->second/bin;
		if( end > 0 ){
			std::vector<vector<int> > matrix;
			for( int i = start; i < end; ++i ){
				matrix.push_back(vector<int>(end-start,0));
			}

			Str chr = chrIt->first;
			map<Str,map<pair<int,int>, int > >::const_iterator it = chr_bin1bin2_n.find(chr);
			if( it != chr_bin1bin2_n.end() ){
				for( map<pair<int,int>, int >::const_iterator cIt = it->second.begin(); cIt != it->second.end(); ++cIt ){
					int i = cIt->first.first;
					int j = cIt->first.second;
					if( i >= start && i < end && j >=start && j < end ){
						matrix[i-start][j-start] = cIt->second;
						matrix[j-start][i-start] = cIt->second;
					}
				}
			}

			Str fn = prefix+ "."+chr+".mtx4topdom";
			ofstream out(fn.data());
			for( unsigned int i = 0; i < matrix.size(); ++i ){
				out<<chrIt->first<<"\t"<<(start+i)*bin<<"\t"<<(start+i+1)*bin;
				for( unsigned int j = 0; j < matrix[i].size(); ++j ){
					out<<"\t"<<matrix[i][j];
				}
				out<<endl;
			}
			out.close();
		}
	}

	return 0;
}

//*/

