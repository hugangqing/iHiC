# iHiC
A set of C++ utilities for pre/post-processing Hi-C data for public software and for data visualization in the WashU Epigenome Browser.

Descriptions of usage of the utilities

1. <b>iHiC_BEDPE_Statistics</b>: Calculate statistics of PET alignments from a simplified BEDPE file.<br>
  <b>Usage</b>: iHiC_BEDPE_Statistics BEDPE_file MAPQ<br>
  <b>Inputs</b>:<br>
  <em>BEDPE_file</em>: a simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>
2. iHiC_PETOrientations_Stat: Calculate % of PETs in different combinations of orientations as a function of genomic distance.<br>
  <b>Usage</b>: iHiC_PETOrientations_Stat BEDPE_file MAPQ <br>
  <em>BEDPE_file</em>: a simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>
3. iHiC_ContactFreq_Distance: Calculate contact probability as a function genomic distance.<br>
  <b>Usage</b>: iHiC_ContactFreq_Distance BEDPE_file MAPQ<br>
  <em>BEDPE_file</em>: a simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>MAPQ</em>: minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <b>Outputs</b>: screen<br>
  <b>Note</b>: It is recommended to redirect the ouputs into a local file with the ">" symbol: iHiC_ContactFreq_Distance BEDPE_file MAPQ > local_file_name <br>
4. <b>iHiC_BEDPE2III</b>: Generate an intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes.<br>
<b>Usage</b>: iHiC_BEDPE2III BEDPE_file Bin_size Minimal_Distance Maximal_Distance MAPQ Output_file<br>
<b>Inputs</b>:<br>
  <em>BEDPE_file</em>: a simplified version of regular BEDPE file: only columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2” are retained.<br>
  <em>Bin_size</em>: used to partition the genome into bins of equal size.<br>
  <em>Minimal_Distance</em>: minimal distance between two PET ends considered for downstream analysis. Should be no less than Bin_size.<br>
  <em>Maximal_Distance</em>: maximal distance between two PET ends considered for downstream analysis. Simply set to 2000,0000,000 bps to include all interacting PETs longer than the Minimal_Distance. However, considering that majority of the significant contacts are less than 2,000,000 bps, one may want to set Maximal_Distance to this number to save computational time for later analysis.<br>
  <em>MAPQ</em>: minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.<br>
  <em>Output_file</em>: file name to save the III file.<br>
<b>Output file</b>:<br>
  Format for left to right columns: chromosome, genomic position of bin1, genomic position of bin2, number of PETs linking the two bins.<br>
  <b>Note</b>: only uniquely mapped PETs are considered. For multiple PETs mapped to the same position, only one copy is retained.<br>
5. iHiC_III2WashU: Convert an III file into “longrange” format (http://wiki.wubrowse.org/Long-range) accepted by the WashU browser.<br>
  <b>Usage</b>: iHiC_III2WashU III_file Bin_size Output<br>
  <b>Inputs</b>:<br>
  <em>III_file</em>: an intra-chromosomal interaction index (III) file that records the numbers of PETs for interacting genomic bins from the same chromosomes. Output from iHiC_BEDPE2III.<br>
  <em>Bin_size</em>: size of genomic bin.<br>
  <b>Outputs</b>:"longrange" format by WashU Epigenome Browser (http://wiki.wubrowse.org/Long-range).<br>
6. iHiC_BEDPE2HiCSummary: Convert a BEDPE file into “HiCsummary” format (http://homer.ucsd.edu/homer/interactions/HiCtagDirectory.html) accepted by CscoreTool.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>

7. iHiC_Cscore_Adj: Flip the sign of C-score chromosome-by- chromosome to ensure genomic regions with positive scores correspond to A compartment status.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>
8. iHiC_III2MTX4TopDom: Convert an III file into interaction matrices accepted by TopDom.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>
9. iHiC_TADBoundary_TopDom: Extract TAD boundaries from TopDom predictions.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>
10. iHiC_III2FitHiCInputs: Convert an III file into interaction matrices accepted by Fit-Hi-C.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>
11. iHiC_FitHiC2WashU: Convert the significant contacts predicted by Fit-Hi-C into a “longrange” format accepted by the WashU browser.<br>
  <b>Inputs</b>:<br>
  <em></em><br>
  <em></em><br>
  <em></em><br>
  <b>Outputs</b>:<br>
  <b>Note</b>:<br>
