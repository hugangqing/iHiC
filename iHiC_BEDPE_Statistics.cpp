#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 3 ){
		cout<<"Usage: iHiC_BEDPE_Statistics BEDPE_file MAPQ\n";
		cout<<"MAPQ: the minimal MAPQ score for uniquely mapped PETs: 10 recommended.\n";
		return 0;
	}
	long int N = 0, N_lowQ = 0, N_highQnr = 0, n = 0;
	map<Str,long int> intra_n;

	long int nrD0_1k = 0;
	long int nrD1k20k = 0;
	long int nrD20k = 0;

	int MAPQ = atoi(args[2]);
	cout<<"BEDPE file: "<<args[1]<<endl;
	cout<<"Read PETs "<<endl;
	map<Str, set<Str> > chrchr_rds;
	ifstream in(args[1]);
	while( !in.eof() ){
		BED3 l, r;
		in>>l.chrom>>l.start>>l.end>>r.chrom>>r.start>>r.end>>l.info>>l.strand>>r.strand;
		if( ++n % 1000000 == 0 )
			cout<<".";
		if( !l.chrom.empty() ){
			++N;
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
				int dis = _abs(r5-l5);
				if( !exist )//remove redundancy
				{
					++N_highQnr;
					if( l.chrom == r.chrom ){
						++intra_n["intra"];
						if( dis < 1000 )
							++nrD0_1k;
						else if(dis < 20000 )
							++nrD1k20k;
						else
							++nrD20k;
					}else{
						++intra_n["inter"];
					}
					chrchr_rds[chrchr].insert(pos);
				}
			}else{
				++N_lowQ;
			}
		}
	}
	in.close();
	cout<<endl;
	cout<<"Mapped PETs: "<<N<<endl;
	cout<<"	| Uniquely mapped PETs (MAPQ>"<<MAPQ<<"): "<<N-N_lowQ<<" ("<<(N-N_lowQ)/double(N)*100<<"%)"<<endl;
	cout<<"		| Non-redundant PETs: "<<N_highQnr<<" ("<<N_highQnr/double(N-N_lowQ)*100<<"%)"<<endl;
	cout<<"			| Intra-chromosomal PETs: "<<intra_n["intra"]<<" ("<<intra_n["intra"]/double(N_highQnr)*100<<"%)"<<endl;
	cout<<"				| <1K: "<<nrD0_1k<<" ("<<nrD0_1k/double(intra_n["intra"])*100<<"%)"<<endl;
	cout<<"				| >=1K, < 20K:"<<nrD1k20k<<" ("<<nrD1k20k/double(intra_n["intra"])*100<<"%)"<<endl;
	cout<<"				| >= 20K (long-range cis):"<<nrD20k<<" ("<<nrD20k/double(intra_n["intra"])*100<<"%)"<<endl;
	cout<<"			| Inter-chromosomal PETs: "<<N_highQnr-intra_n["intra"]<<endl;
	cout<<"Cis/Trans ratio (4DN): "<<100*nrD20k/double(nrD20k+N_highQnr-intra_n["intra"])<<"%"<<endl;
	cout<<"%Long-range cis reads (4DN): "<<100*nrD20k/double(N_highQnr)<<"%"<<endl;

	return 0;
}

//*/
