#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 6 ){
		cout<<"Usage: iHiC_III2WashU III_file Bin_size Output_file_name\n";
		cout<<"Convert the numbers of PETs connecting two intra-chromosomal bins into the \"Long Range\" format acceptable to WashU Epigenome Browser for visualization\n";
		cout<<"The number of interacting PETs are normalized by library size and bin size\n";
		cout<<"III_file: the intra-chromosomal interaction index file output by MiMB_HiC_BEDPE2III\n";
		exit(1);
	}

	int binsz = atoi(args[2]);

	int totalPETs = 0;
	map<Str,map<pair<int,int>, int > > chr_bin1bin2_n;
        ifstream iii(args[1]);
        while( !iii.eof() ){
                Str chr;
                int pos1, pos2, cnt;
                iii>>chr>>pos1>>pos2>>cnt;
                if( !chr.empty() ){
                        chr_bin1bin2_n[chr][make_pair(pos1/binsz,pos2/binsz)] += cnt;
			totalPETs += cnt;
                }
        }
        iii.close();

    int index = 1;
    ofstream out(args[3]);
    for( map<Str,map<pair<int,int>, int > >::const_iterator chrIt = chr_bin1bin2_n.begin();
    		chrIt != chr_bin1bin2_n.end(); ++chrIt ){
    	for( map<pair<int,int>, int >::const_iterator pIt = chrIt->second.begin();
    			pIt != chrIt->second.end(); ++pIt ){
    		out<<chrIt->first<<"\t"<<pIt->first.first*binsz
    				<<"\t"<<(pIt->first.first+1)*binsz
    				<<"\t"<<chrIt->first<<":"<<pIt->first.second*binsz
    				<<"-"<<(pIt->first.second+1)*binsz
    				<<","<<pIt->second/double(totalPETs)*100000000./binsz*100
    				<<"\t"<<(++index)<<"\t."<<endl;
    		out<<chrIt->first<<"\t"<<pIt->first.second*binsz
    				<<"\t"<<(pIt->first.second+1)*binsz
    				<<"\t"<<chrIt->first<<":"<<pIt->first.first*binsz
    				<<"-"<<(pIt->first.first+1)*binsz
    				<<","<<(pIt->second/double(totalPETs)*100000000./binsz*100)
    				<<"\t"<<(++index)<<"\t."<<endl;
    	}
    }

    return 0;
}

//*/
