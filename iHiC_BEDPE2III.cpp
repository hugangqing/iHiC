#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 7 ){
		cout<<"Usage: iHiC_BEDPE2III BEDPE_file Bin_size Minimal_Distance Maximal_Distance MAPQ Output_file_name\n";
		cout<<"Only uniquely mapped intra-chromosomal PETs, after removing redundancy, are considered.\n";
		exit(1);
	}
	int bin = atoi(args[2]);
	int minDis = atoi(args[3]);
	int maxDis = atoi(args[4]);
	int MAPQ = atoi(args[5]);

	map<Str, set<Str> > chrchr_rds;
	map<Str,map<pair<int,int>, int > > _chr_bin1bin2_n;

	ifstream in(args[1]);
	int rd = 0;
	while( !in.eof() ){
		BED3 l, r;
		in>>l.chrom>>l.start>>l.end>>r.chrom>>r.start>>r.end>>l.info>>l.strand>>r.strand;
		if( ++rd % 10000000 == 0 )
			cout<<++rd<<endl;
		if( !l.chrom.empty() && l.chrom == r.chrom ){
			int beg = _min(l.start, r.start);
			int end = _max(l.end, r.end);
			if( atoi(l.info.data()) > MAPQ //only reads mapped to 1 position
					&& end - beg > minDis
					&& end - beg < maxDis)//distance restriction
			{
				Str pos = convert2String(l.start)+"_"+convert2String(r.start);
				map<Str, set<Str> >::iterator chrIt = chrchr_rds.find(l.chrom+r.chrom);
				bool exist = false;
				if( chrIt != chrchr_rds.end()){
					if( chrIt->second.find(pos) != chrIt->second.end() )
						exist = true;
				}
				if( !exist )//remove redundancy
				{
					++_chr_bin1bin2_n[l.chrom][make_pair(beg/bin,end/bin)];
					chrchr_rds[l.chrom+r.chrom].insert(pos);
				}
			}
		}
	}
	in.close();

	ofstream out(args[6]);
	for( map<Str,map<pair<int,int>, int > >::iterator chrIt = _chr_bin1bin2_n.begin(); chrIt != _chr_bin1bin2_n.end(); ++chrIt ){
		for( map<pair<int,int>, int >::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			out<<chrIt->first<<"\t"<<bIt->first.first*bin<<"\t"<<bIt->first.second*bin<<"\t"<<bIt->second<<endl;
		}
	}
	out.close();

	return 0;
}

//*/
