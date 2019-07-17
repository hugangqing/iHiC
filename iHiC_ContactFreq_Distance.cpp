#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 3 ){
		cout<<"Usage: iHiC_ContactFreq_Distance BEDPE_file MAPQ\n";
		cout<<"MAPQ: the minimal MAPQ score for uniquely mapped PETs: 10 recommended.\n";
		cout<<"Statistics are based on uniquely mapped cis PETs after remove redundancy.\n";
		return 0;
	}
	map<int,int> dis_n;
	double totalN = 0;

	int MAPQ = atoi(args[2]);
	int MinDistance = 1000;
	int binsz = 1000;
	cout<<"BEDPE file: "<<args[1]<<endl;
	map<Str, set<Str> > chrchr_rds;
	ifstream in(args[1]);
	while( !in.eof() ){
		BED3 l, r;
		in>>l.chrom>>l.start>>l.end>>r.chrom>>r.start>>r.end>>l.info>>l.strand>>r.strand;
		if( !l.chrom.empty() ){
			if( atoi(l.info.data()) > MAPQ )//only reads mapped to 1 position
			{
				Str pos = l.start<r.start?convert2String(l.start)+"_"+convert2String(r.start):convert2String(r.start)+"_"+convert2String(l.start);
				Str chrchr = l.start<r.start ? l.chrom+r.chrom:r.chrom+l.chrom;
				map<Str, set<Str> >::iterator chrIt = chrchr_rds.find(chrchr);
				bool exist = false;
				if( chrIt != chrchr_rds.end()){
					if( chrIt->second.find(pos) != chrIt->second.end() )
						exist = true;
				}
				int l5 = l.strand == "+" ? l.start : l.end;
				int r5 = r.strand == "+" ? r.start : r.end;

				if( !exist )//remove redundancy
				{
					if( l.chrom == r.chrom ){
						int dis = _abs(r5-l5);
						if( dis >= MinDistance ){
							++dis_n[dis/binsz];
							++totalN;
						}
					}
 					chrchr_rds[chrchr].insert(pos);
				}
			}
		}
	}
	in.close();

	cout<<"Distance(log10)\tn\tContactProb(log10)\n";
	for( map<int,int>::iterator dIt = dis_n.begin(); dIt != dis_n.end(); ++dIt ){
		cout<<log(dIt->first*binsz)/log(10)<<"\t"<<dIt->second<<"\t"<<log(dIt->second/totalN/binsz)/log(10)<<endl;
	}
	return 0;
}

//*/
