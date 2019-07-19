#include "iHiC_rgn.h"
using namespace std;

int main(int argc, char* args[]) {
	if( argc != 4 ){
		cout<<"Usage: iHiC_FitHiC2WashU FitHiC_prediction Bin_size Q-value\n";
		cout<<"FitHiC_prediction: Output file Fit-Hi-C with name ending with '.significances.txt'.\n";
		cout<<"Bin_size: Bin size used for generating inputs for Fit-Hi-C by iHiC_III2FitHiCInputs.\n";
		cout<<"Q-value: Q-value for significant contact retained for WashU visualization.\n";
		exit(1);
	}

	double p=atof(args[3]);
	int index = 1;
	int bin = atoi(args[2]);
	Str line;

	ifstream in(args[1]);
	ofstream out((Str(args[1])+".longrange").data());
	std::getline(in, line);
	while( !in.eof() ){
		Str chr1, chr2;
		int fragmentMid1, fragmentMid2;
		double contactCount, pvalue, qvalue;
		in>>chr1;
		if( !chr1.empty() && chr1.find("chr")==std::string::npos){
			in>>fragmentMid1>>chr2>>fragmentMid2>>contactCount>>pvalue>>qvalue;
			if( qvalue < p ){
				out<<"chr"+chr1<<"\t"<<fragmentMid1-bin/2
						<<"\t"<<fragmentMid1+bin/2
						<<"\tchr"<<chr2<<":"<<fragmentMid2-bin/2<<"-"<<fragmentMid2+bin/2
						<<","<<contactCount
						<<"\t"<<(++index)<<"\t."<<endl;
				out<<"chr"<<chr2<<"\t"<<fragmentMid2-bin/2
						<<"\t"<<fragmentMid2+bin/2
						<<"\tchr"<<chr1<<":"<<fragmentMid1-bin/2<<"-"<<fragmentMid1+bin/2
						<<","<<contactCount
						<<"\t"<<(++index)<<"\t."<<endl;
				}
		}else{
			getline(in,line);
		}
	}
	out.close();

	return 0;
}

//*/
