#include "iHiC_rgn.h"

bool isOverlap(Pa_I_I region, Str chrom, map<Str, set<BED3> >& islands){
	for( set<BED3>::const_iterator it = islands[chrom].begin(); it != islands[chrom].end(); ++it ){
		if( _max(region.first, it->start) < _min(region.second, it->end) )
			return true;
	}
	return false;
}

map<Str, set<BED3> > self_union( map<Str, set<BED3> > beds ){
	map<Str, set<BED3> > unions;
	for(map<Str, set<BED3> >::iterator chrIt = beds.begin(); chrIt != beds.end(); ++chrIt ){
		set<BED3>::iterator bIt = chrIt->second.begin();
		set<BED3>::iterator bIt1 = bIt;
		for( ; bIt != chrIt->second.end(); bIt = bIt1){
			int rightmst = bIt->end;
			for( ++bIt1; bIt1 != chrIt->second.end() && bIt1->start <= rightmst ; ++bIt1 ){
				if( bIt1->end > rightmst){
					rightmst = bIt1->end;
				}
			}
			BED3 b;
			b.start = bIt->start;
			b.end = rightmst;
			b.chrom = bIt->chrom;
			unions[b.chrom].insert(b);
		}
	}
	return unions;
}

/*
map<Str, set<BED3> > get_complement_set(map<Str, set<BED3> > bed, Str file ){
	map<Str, set<BED3> > pro = self_union(bed);
	map<Str, int> chr_len = getChrlen(file);
	map<Str, set<BED3> > nonpro;
	for( map<Str, set<BED3> >::iterator chrIt = bed.begin(); chrIt != bed.end(); ++chrIt ){
		set<BED3>::iterator bIt1 = chrIt->second.begin();
		set<BED3>::iterator bIt2 = bIt1;
		int lftmst = bIt1->strand == "+" ? bIt1->start - PROMOTERUPLEN: bIt1->start;
		if( lftmst > 0 ){
			BED3 b;
			b.start = 1;
			b.end = lftmst;
			b.chrom = bIt1->chrom;
			if( b.end - b.start > 3)
				nonpro[b.chrom].insert(b);
		}
		for( ++bIt2; bIt2 != chrIt->second.end(); ++bIt1, ++bIt2 ){
			if( bIt2->start > bIt1->end ){
				BED3 b;
				b.start = bIt1->end;
				b.end = bIt2->start;
				b.chrom = bIt1->chrom;
				if( b.end - b.start > 3)
					nonpro[b.chrom].insert(b);
			}else{
				cout<<bIt1->chrom<<'\t'<<bIt1->end<<'\t'<<bIt2->start<<endl;
			}
		}
		map<Str, int>::iterator lIt = chr_len.find(chrIt->first);
		if( lIt != chr_len.end() ){
			--bIt2;
			int rgtmst = bIt2->strand == "+" ? bIt2->end: bIt2->end + PROMOTERUPLEN;
			if( rgtmst < lIt->second){
				BED3 b;
				b.start = rgtmst;
				b.end = lIt->second;
				b.chrom = bIt2->chrom;
				if( b.end - b.start > 3)
					nonpro[b.chrom].insert(b);
			}
		}else{
		//	cout<<chrIt->first<<"ERR 22"<<endl;
		}
	}
	return nonpro;
}//*/

map<Str, set<BED3> > merge(map<Str, set<BED3> > bed1, map<Str, set<BED3> > bed2){
	for( map<Str, set<BED3> >::iterator chrIt = bed1.begin(); chrIt != bed1.end(); ++chrIt ){
		for( set<BED3>::iterator bIt = chrIt->second.begin(); bIt != chrIt->second.end(); ++bIt ){
			bed2[bIt->chrom].insert(*bIt);
		}
	}
	return self_union(bed2);
}

BED3 parsStr2Bed3(Str s){
	BED3 b;
	for( int i = 0; i < s.size(); ++i ){
		if( s[i] == ':' || s[i] =='-' || s[i] == '>')
			s[i] = '\t';
	}
	std::istringstream buf(s);//ensure one line per gene
	buf>>b.chrom>>b.start>>b.end;
	std::getline(buf, b.info);
	buf.clear();//*/
	return b;
}

map<Str, set<BED3> > PartitionGenomeIntoBins(Str chrlen_fn, int binsz){
	map<Str, set<BED3> > bins;
	map<Str,int> chrlen = getChrlen(chrlen_fn);
	for( map<Str,int>::iterator cIt = chrlen.begin(); cIt != chrlen.end(); ++cIt ){
		for( int i = 0; i < cIt->second - binsz; i += binsz ){
			BED3 b;
			b.chrom = cIt->first;
			b.start = i;
			b.end = i + binsz;
			bins[b.chrom].insert(b);
		}
	}
	return bins;
}


void assignIsland2Island(map<Str, set<BED3> >& target_island,
		const map<Str, set<BED3> >& source_island, Str source_island_label){
	map<Str, vector<BED3> > target_islands = set2vector(target_island);
	map<Str, vector<BED3> > source_islands = set2vector(source_island);
	for( map<Str, vector<BED3> >::iterator chrIt = target_islands.begin(); chrIt != target_islands.end(); ++chrIt ){
		if( !source_islands[chrIt->first].empty() ){
			vector<BED3>::const_iterator sIt = source_islands[chrIt->first].begin();
			for( vector<BED3>::iterator tIt = chrIt->second.begin(); tIt != chrIt->second.end(); ++tIt ){
//				if( tIt->start > 123962000 && tIt->end < 123993820 && tIt->chrom == "chr9" ){
//					cout<<tIt->start<<'\t'<<tIt->end<<endl;
//				}
				while( (sIt->end > tIt->start && sIt != source_islands[chrIt->first].begin())
						|| sIt == source_islands[chrIt->first].end() ){
					--sIt;
				}
				for( ; sIt != source_islands[chrIt->first].end() && (sIt->start < tIt->end); ++sIt){
					if( _min(tIt->end, sIt->end) > _max(tIt->start, sIt->start)){
						tIt->islandsOn[source_island_label].insert(*sIt);
					}
				}
			}
		}
	}
	target_island = vector2set(target_islands);//*/
}
