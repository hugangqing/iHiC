#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 4 ){
		cout<<"Usage: iHiC_TADBoundary_TopDom TopDomBinSignalFile pvalue OutputFile\n";
		return 0;
	}

	double pthreshold = atof(args[2]);
	map<Str, set<BED3> > bdrs, bdrcuts;
	Str line;
    ifstream in(args[1]);
    while( !in.eof() ){
		BED3 b;
		Str line, tag;
		in>>line;
		if( !line.empty() ){
			if(line.find("id") == std::string::npos ){
				double p = 1;
				in>>b.chrom>>b.chrom>>b.start>>b.end>>tag>>line>>p;
				strip(b.chrom,'\"');
//				if( tag == "-0.5" )
//					gaps[b.chrom].insert(b);
				if( p < pthreshold ){
					bdrs[b.chrom].insert(b);
					if( tag == "-1" ){
						bdrcuts[b.chrom].insert(b);
					}
				}
			}else{
				std::getline(in, line);
			}
		}
	}

    bdrs = self_union(bdrs);
    bdrcuts = self_union(bdrcuts);

    assignIsland2Island(bdrs, bdrcuts, "cut");

    ofstream out(args[3]);
    for( map<Str,set<BED3> >::iterator chrIt = bdrs.begin(); chrIt != bdrs.end(); ++chrIt ){
    	for( set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
    		map<Str,set<BED3> >::const_iterator cIt = bIt->islandsOn.find("cut");
    		if( cIt != bIt->islandsOn.end() ){
    			for( set<BED3>::const_iterator it = cIt->second.begin(); it != cIt->second.end(); ++it ){
    				out<<it->chrom<<"\t"<<it->start<<"\t"<<it->end<<"\t1"<<endl;
    			}
    		}
    	}
    }
    out.close();

    return 0;
}

//*/

