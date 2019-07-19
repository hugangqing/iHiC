#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 3 ){
		cout<<"Usage: iHiC_BEDPE2HiCSummary BEDPE_file Output_file\n";
		exit(1);
	}
	int index = 1;
	ifstream in(args[1]);
	ofstream out(args[2]);
	while( !in.eof() ){
		BED3 l, r;
		in>>l.chrom>>l.start>>l.end>>r.chrom>>r.start>>r.end>>l.info>>l.strand>>r.strand;
		if(  !l.chrom.empty() ){
			out<<(++index)<<"\t"<<l.chrom<<"\t"<<l.start<<"\t"<<l.strand
					<<"\t"<<r.chrom<<"\t"<<r.start<<"\t"<<r.strand<<endl;
		}
	}
	in.close();
	out.close();

	return 0;
}

//*/
