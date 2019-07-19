# iHiC
A set of C++ utilities for pre/post-processing Hi-C data for public software (including [CscoreTool](https://github.com/scoutzxb/CscoreTool) for A/B compartment, [TopDom](https://github.com/HenrikBengtsson/TopDom) for TAD, and [Fit-Hi-C](https://github.com/ay-lab/fithic) for significant contacts) and for data visualization with the [WashU Epigenome Browser](https://epigenomegateway.wustl.edu).

Descriptions of usage of the utilities

1. <b>iHiC_BEDPE_Statistics</b>: Calculate statistics of PET alignments from a simplified BEDPE file.<br>
  <b>Usage</b>: iHiC_BEDPE_Statistics BEDPE_file MAPQ<br>
  <b>Inputs</b>:<br>
  <em>BEDPE_file</em>: A simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: Minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>

2. <b>iHiC_PETOrientations_Stat</b>: Calculate % of PETs in different combinations of orientations as a function of genomic distance.<br>
  <b>Usage</b>: iHiC_PETOrientations_Stat BEDPE_file MAPQ <br>
  <em>BEDPE_file</em>: A simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: Minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>

3. <b>iHiC_ContactFreq_Distance</b>: Calculate contact probability as a function genomic distance.<br>
  <b>Usage</b>: iHiC_ContactFreq_Distance BEDPE_file MAPQ<br>
  <em>BEDPE_file</em>: A simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: Minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>
  <b>Note</b>: It is recommended to redirect the ouputs into a local file with the ">" symbol: iHiC_ContactFreq_Distance BEDPE_file MAPQ > local_file_name <br>

4. <b>iHiC_BEDPE2III</b>: Generate an intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes.<br>
<b>Usage</b>: iHiC_BEDPE2III BEDPE_file Bin_size Minimal_Distance Maximal_Distance MAPQ Output_file_name<br>
<b>Inputs</b>:<br>
  <em>BEDPE_file</em>: A simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>Bin_size</em>: Used to partition the genome into bins of equal size.<br>
  <em>Minimal_Distance</em>: Minimal distance between two PET ends considered for downstream analysis. Should be no less than Bin_size.<br>
  <em>Maximal_Distance</em>: Maximal distance between two PET ends considered for downstream analysis. Simply set to 2000,0000,000 bps to include all interacting PETs longer than the Minimal_Distance. However, considering that majority of the significant contacts are less than 2,000,000 bps, one may want to set Maximal_Distance to this number to save computational time for later analysis.<br>
  <em>MAPQ</em>: Minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <em>Output_file_name</em>: File name for the III file.<br>
<b>Outputs</b>: Format for left to right columns: chromosome, genomic position of bin1, genomic position of bin2, number of PETs linking the two bins.<br>
  <b>Note</b>: Only uniquely mapped PETs are considered. For multiple PETs mapped to the same position, only one copy is retained.<br>

5. <b>iHiC_III2WashU</b>: Convert an III file into [“longrange”](http://wiki.wubrowse.org/Long-range) format accepted by the [WashU Epigenome Browser](https://epigenomegateway.wustl.edu).<br>
  <b>Usage</b>: iHiC_III2WashU III_file Bin_size Output_file_name<br>
  <b>Inputs</b>:<br>
  <em>III_file</em>: An intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes. Output from iHiC_BEDPE2III.<br>
  <em>Bin_size</em>: Size of genomic bin.<br>
  <em>Output_file_name</em>: File name for the "longrange" file.<br>
  <b>Outputs</b>: A ["longrange"](http://wiki.wubrowse.org/Long-range) format by [WashU Epigenome Browser](https://epigenomegateway.wustl.edu).<br>
6. <b>iHiC_BEDPE2HiCSummary</b>: Convert a BEDPE file into [“HiCsummary”](http://homer.ucsd.edu/homer/interactions/HiCtagDirectory.html) format accepted by [CscoreTool](https://github.com/scoutzxb/CscoreTool).<br>
  <b>Usage</b>:iHiC_BEDPE2HiCSummary BEDPE Output_file_name<br>
  <b>Inputs</b>:<br>
  <em>BEDPE_file</em>: A simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>Output_file_name</em>: File name for the "HiCsummary" file.<br>
  <b>Outputs</b>:In ["HiCsummary"](http://homer.ucsd.edu/homer/interactions/HiCtagDirectory.html) format<br>

7. <b>iHiC_Cscore_Adj</b>: Flip the sign of C-score chromosome-by- chromosome to ensure genomic regions with positive scores correspond to A compartment status.<br>
  <b>Usage</b>: iHiC_Cscore_Adj Cscore_file CpG_annotation_file<br>
  <b>Inputs</b>:<br>
  <em>Cscore_file</em>: output file from Cscore_Tool with name ending with '_cscore.bedgraph'<br>
  <em>CpG_annotation_file</em>: CpG annotation downloaded from UCSC. Only the 4-5 columns corresponding to chr, start and end are used by the program. <br>
  <b>Outputs</b>: A "bedgraph" format with file name ending with "adj"<br>

8. <b>iHiC_III2MTX4TopDom</b>: Convert an III file into interaction matrices accepted by [TopDom](https://github.com/HenrikBengtsson/TopDom).<br>
  <b>Usage</b>:iHiC_III2MTX4TopDom III_file Bin_size Chr_lenth_file Output_Prefix<br>
  <b>Inputs</b>:<br>
  <em>III_file</em>: An intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes. Output from iHiC_BEDPE2III.<br>
  <em>Bin_size</em>: Size of genomic bin.<br>
  <em>Chr_lenth_file</em>: In a two column format: chr and length<br>
  <em>Output_Prefix</em>: "chr#.mtx4topdom" will be appended to the Output_Prefix to denote the file for chr#.<br>
  <b>Outputs</b>: In the format of n X (n+3) matrix format, accepted by [TopDom](https://github.com/HenrikBengtsson/TopDom) as [input](https://github.com/HenrikBengtsson/TopDom/blob/0.0.2/docs/TopDom%20Manual_v0.0.2.pdf), with first three columns for bin.chr, bin.start, and bin.end, and the next n columns for # of PETs linked to other bins.<br>
  
9. <b>iHiC_TADBoundary_TopDom</b>: Extract TAD boundaries from [TopDom](https://github.com/HenrikBengtsson/TopDom) predictions.<br>
  <b>Usage</b>:iHiC_TADBoundary_TopDom TopDom_binSignal_file Pvalue_threshold Output_file_name<br>
  <b>Inputs</b>:<br>
  <em>TopDom_binSignal_file</em>: Output file from [TopDom](https://github.com/HenrikBengtsson/TopDom) with name ending with '.binSignal'.<br>
  <em>Pvalue_threshold</em>: Pvalue used to filter bins corresponding to TAD boundaries.<br>
  <em>Output_file_name</em>: File name for the file of TAD boundaries.<br>
  <b>Outputs</b>:In bedgraph format.<br>
  
10. <b>iHiC_III2FitHiCInputs</b>: Convert an III file into interaction matrices accepted by [Fit-Hi-C](https://github.com/ay-lab/fithic).<br>
  <b>Usage</b>: iHiC_III2FitHiCInputs III Output_prefix Chr_length_file Bin_size Minimal_Distance Maximal_Distance<br>
  <b>Inputs</b>: <br>
  <em>III_file</em>: An intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes. Output from iHiC_BEDPE2III.<br>
  <em>Output_Prefix</em>: "chr#.frag" and "chr#.cnts" will be appended to the Output_Prefix to denote the files for chr#.<br>
  <em>Chr_lenth_file</em>: In a two column format: chr and length<br>
  <em>Bin_size</em>: Size of genomic bin.<br>
  <em>Minimal_Distance</em>: Minimal distance between two PET ends considered.<br>
  <em>Maximal_Distance</em>: Maximal distance between two PET ends considered<br>
  <b>Outputs</b>: "chr#.frag" and "chr#.cnts" for "fragments file" and "interactions file" accepted by [Fit-Hi-C](https://github.com/ay-lab/fithic) <br>
  
11. <b>iHiC_FitHiC2WashU</b>: Convert the significant contacts predicted by Fit-Hi-C into a “longrange” format accepted by the [WashU Epigenome Browser](https://epigenomegateway.wustl.edu).<br>
  <b>Usage</b>: iHiC_FitHiC2WashU FitHiC_prediction Bin_size Q-value<br>
  <b>Inputs</b>:<br>
  <em>FitHiC_prediction</em>: Output file Fit-Hi-C with name ending with '.significances.txt'.<br>
  <em>Bin_szie</em>: Bin size used for generating inputs for Fit-Hi-C by iHiC_III2FitHiCInputs<br>
  <em>Q-value</em>: Q-value to retain significant contacts.<br>
  <b>Outputs</b>: Output file will be ending with ["longrange"](http://wiki.wubrowse.org/Long-range) accepted by [WashU Epigenome Browser](https://epigenomegateway.wustl.edu) for data visualization. <br>
  <b>Note</b>:<br>
