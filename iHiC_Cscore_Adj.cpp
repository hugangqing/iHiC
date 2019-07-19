#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 3 ){
		cout<<"Usage: iHiC_Cscore_Adj Cscore_file CpG_annotation_file\n";
		cout<<"Cscore_file: output file from Cscore_Tool with name ending with '_cscore.bedgraph'\n";
		cout<<"CpG_annotation_file: CpG annotation downloaded from UCSC\n";
		exit(1);
	}

	Str abline, line;
	map<Str,set<BED3> > AB, CpG;
	ifstream cin(args[1]);
	std::getline(cin, abline);
	while( !cin.eof() ){
		BED3  b;
		cin>>b.chrom>>b.start>>b.end>>b.island_score;
		if( !b.chrom.empty() ){
			AB[b.chrom].insert(b);
		}
	}
	cin.eof();

	ifstream cpgin(args[2]);
	std::getline(cpgin, line);
	while( !cpgin.eof() ){
		BED3  b;
		cpgin>>line>>b.chrom>>b.start>>b.end;
		std::getline(cpgin, line);
		if( !b.chrom.empty() ){
			CpG[b.chrom].insert(b);
		}
	}
	cpgin.eof();

	map<Str, Ve_D> chr_cpg_csc;
	assignIsland2Island(CpG, AB, "AB");
	for( map<Str,set<BED3> >::iterator chrIt = CpG.begin(); chrIt != CpG.end(); ++chrIt ){
		for( set<BED3>::iterator cIt = chrIt->second.begin(); cIt != chrIt->second.end(); ++cIt ){
			map<Str,set<BED3> >::const_iterator abIt = cIt->islandsOn.find("AB");
			if( abIt != cIt->islandsOn.end() ){
				if( abIt->second.size() == 1 ){
					chr_cpg_csc[chrIt->first].push_back(abIt->second.begin()->island_score);
				}
			}
		}
	}

	cout<<"Chr\tAverage_Cscore_in_CpG\tCscore_flip\n";
	ofstream out((Str(args[1])+".adj").data());
	out<<abline<<endl;
	for( map<Str,set<BED3> >::iterator chrIt = AB.begin(); chrIt != AB.end(); ++chrIt ){
		map<Str, Ve_D>::iterator fIt = chr_cpg_csc.find(chrIt->first);
		if( fIt != chr_cpg_csc.end() ){
			double fct = GetAver(fIt->second)>0?1:-1;
			cout<<chrIt->first<<"\t"<<GetAver(fIt->second)<<"\t"<<(fct<0?"yes":"no")<<endl;
			for( set<BED3>::iterator cIt = chrIt->second.begin(); cIt != chrIt->second.end(); ++cIt ){
				out<<cIt->chrom<<"\t"<<cIt->start<<"\t"<<cIt->end<<"\t"<<cIt->island_score*fct<<endl;
			}
		}
	}

	return 0;
}

//*/
