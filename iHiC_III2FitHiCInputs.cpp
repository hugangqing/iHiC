#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 7 ){
		cout<<"Usage: iHiC_III2FitHiCInputs III output_prefix Chr_Length_File Bin_size Minimal_Distance Maximal_Distance\n";
		exit(1);
	}
	int bin = atoi(args[4]);
	map<Str, int> chrlen = getChrlen(args[3]);
	int minD = atoi(args[5])/bin;
	int maxD = atoi(args[6])/bin;
	Str prefix(args[2]);

	map<Str,map<pair<int,int>, int > > chr_bin1bin2_n;
	ifstream iii(args[1]);
	while( !iii.eof() ){
		Str chr;
		int pos1, pos2, cnt;
		iii>>chr>>pos1>>pos2>>cnt;
		map<Str, int>::iterator chrIt = chrlen.find(chr);
		if( !chr.empty() && chrIt != chrlen.end()){
			chr_bin1bin2_n[chr][make_pair(pos1/bin,pos2/bin)] += cnt;
		}
	}
	iii.close();

	for( map<Str, int>::iterator chrIt = chrlen.begin(); chrIt != chrlen.end(); ++chrIt ){
		int start = 1/bin;
		int end = chrIt->second/bin;
		if( end > start ){
			std::vector<vector<int> > matrix;
			for( int i = start; i < end; ++i ){
				matrix.push_back(vector<int>(end-start,0));
			}
			Str chr = chrIt->first;
			cout<<chrIt->first<<"\t"<<start*bin<<"\t"<<end*bin<<endl;
			cout<<"\tmatrix size: "<<matrix.size()<<"\t"<<matrix[0].size()<<endl;

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

			Str _chr = chr.substr(3);
			Str fn1 = prefix+ "."+chr+".frag";
			ofstream out1(fn1.data());
			Str fn2 = prefix+ "."+chr+".cnts";
			ofstream out2(fn2.data());
			for( unsigned int i = 0; i < matrix.size(); ++i ){
				double midrang = 0;
				bool mappable = false;
				for( unsigned int j = i - maxD; j < i + maxD; ++j ){
					if( j >= 0 && j < matrix[i].size() ){
						if( _abs(i-j) > minD ){
							midrang += matrix[i][j];
							if( i < j && matrix[i][j] > 0 )
								out2<<_chr<<"\t"<<(i*bin+bin/2)<<"\t"<<_chr<<"\t"<<(j*bin+bin/2)<<"\t"<<matrix[i][j]<<endl;
						}
						if( matrix[i][j] > 0 )
							mappable = true;
					}
				}
				out1<<_chr<<"\t0\t"<<i*bin+bin/2<<"\t"<<midrang<<"\t"<<mappable<<endl;
			}
			system(("gzip "+fn1+"&").data());
			system(("gzip "+fn2+"&").data());
			out1.close();
			out2.close();
		}
	}

	return 0;
}

//*/
