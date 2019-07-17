/*
 * BED.h
 *
 *  Created on: Sep 9, 2009
 *      Author: hugq
 */

#ifndef BED_H_
#define BED_H_

#include "iHiC_base.h"

//Class for bed lines with 3 values: chrom, start and end
class BED3{
public:
	BED3(){}
	bool isOverlap(BED3 r){
		return ((end > r.start) && (start <r.end) );
	}//*/
	bool operator <( const BED3 & rhs )const{
		return make_pair(make_pair(chrom,start), make_pair(end, info)) < make_pair(make_pair(rhs.chrom, rhs.start), make_pair(rhs.end,rhs.info));
	}//*/
	bool operator == ( const BED3 & rhs )const{
		return start == rhs.start && chrom == rhs.chrom;
	}//*/
	void initFromLineOfFile(std::istream &stream){
		stream>>chrom>>start>>end;
		Str line;
		std::getline( stream, info);
	}
	Str chrom, info, strand;
	int start;
	int end;
	double island_score;
	map<Str, set<BED3> > islandsOn;
};

bool isOverlap(Pa_I_I region, Str chrom, map<Str, set<BED3> >& islands);
//map<Str, set<BED3> > get_complement_set(map<Str, set<BED3> > pro, Str file );
map<Str, set<BED3> > self_union( map<Str, set<BED3> > beds );
map<Str, set<BED3> > merge(map<Str, set<BED3> > bed1, map<Str, set<BED3> > bed2);
BED3 parsStr2Bed3(Str s); //Str like "chr1:22333-44434";
map<Str, set<BED3> > PartitionGenomeIntoBins(Str chrlen, int binsz);
void assignIsland2Island(map<Str, set<BED3> >& target_islands, const map<Str, set<BED3> >& source_islands, Str source_island_label);


#endif /* BED_H_ */
