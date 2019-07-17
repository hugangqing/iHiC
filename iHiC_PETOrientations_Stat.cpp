#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 3 ){
		cout<<"Usage: iHiC_PETOrientations_Stat BEDPE_file MAPQ\n";
		cout<<"MAPQ: the minimal MAPQ score for uniquely mapped PETs: 10 recommended.\n";
		cout<<"Statistics are based on uniquely mapped cis PETs after remove redundancy and distance >= 100.\n";
		return 0;
	}
	map<int,map<Str,int> > dis_orn_n;
	int logbase = 2;

	int MAPQ = atoi(args[2]);
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
				int dis = _abs(r5-l5);

				if( dis >= 100 ){
					dis = log(dis)/log(logbase);
					if( dis >= log(1000000)/log(logbase) )
						dis = log(1000000)/log(logbase);
					if( !exist )//remove redundancy
					{
						if( l.chrom == r.chrom ){
							++dis_orn_n[dis][l.strand+r.strand];
						}
						chrchr_rds[chrchr].insert(pos);
					}
				}
			}
		}
	}
	in.close();
	set<Str> orns;
	orns.insert("++");
	orns.insert("+-");
	orns.insert("-+");
	orns.insert("--");

	cout<<"Distance";
	for( set<Str>::iterator it = orns.begin(); it != orns.end(); ++it )
		cout<<"\t"<<*it;
	cout<<"\tstdev\tSubtotal"<<endl;

	for( map<int,map<Str,int> >::iterator dIt = dis_orn_n.begin(); dIt != dis_orn_n.end(); ++dIt ){
		double sum = 0;
		for( map<Str,int>::iterator i = dIt->second.begin(); i != dIt->second.end(); ++i ){
			sum += i->second;
		}
		Ve_D  ps;
		cout<<pow(logbase, dIt->first);
		for( set<Str>::iterator it = orns.begin(); it != orns.end(); ++it ){
			map<Str,int>::iterator i = dIt->second.find(*it);
			double p = i != dIt->second.end() ? i->second/sum : 0;
			ps.push_back(p);
			cout<<"\t"<<p;
		}
		cout<<"\t"<<GetDerivate(ps)<<"\t"<<sum<<endl;
	}

	return 0;
}

//*/
