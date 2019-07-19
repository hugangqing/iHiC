# iHiC
A set of C++ utilities for pre/post-processing Hi-C data for public software and for data visualization in the WashU Epigenome Browser.

Descriptions of the utilities

1. iHiC_BEDPE_Statistics: Calculate statistics of PET alignments from a simplified BEDPE file.


2. iHiC_PETOrientations_Stat: Calculate % of PETs in different combinations of orientations as a function of genomic distance.
3. iHiC_ContactFreq_Distance: Calculate contact probability as a function genomic distance.
4. iHiC_BEDPE2III: Generate an intra-chromosomal interaction index (III) file for the number of PETs of interacting genomic bins from the same chromosomes.
Usage: iHiC_BEDPE2III BEDPE_file Bin_size Minimal_Distance Maximal_Distance MAPQ Output_file
Inputs:
  BEDPE_file: a simplified version of regular BEDPE file: only retain columns for “chrom1”, “start1”, “end1”, “chrom2”, “start2”, “end2”, “score”, “strand1”, and “strand 2”.
  Bin_size: used to partition the genome into bins of equal size.
  Minimal_Distance: minimal distance between two PET ends considered for downstream analysis. Should be no less than Bin_size.
  Maximal_Distance: maximal distance between two PET ends considered for downstream analysis. Simply set to 2000,0000,000 bps to include all interacting PETs longer than the Minimal_Distance. However, considering that majority of the significant contacts are less than 2,000,000 bps, one may want to set Maximal_Distance to this number to save computational time for later analysis.
  MAPQ: minimal mapping quality score used to filter out PETs mapped to multiple positions. 10 recommended.
  Output_file: file name to save the III file.
Output file:
  Format for left to right columns: chromosome, genomic position of bin1, genomic position of bin2, number of PETs linking the two bins.
  Note: only uniquely mapped PETs are considered. For multiple PETs mapped to the same position, only one copy is retained.

5. iHiC_III2WashU: Convert an III file into “longrange” format (http://wiki.wubrowse.org/Long-range) accepted by the WashU browser.
6. iHiC_BEDPE2HiCSummary: Convert a BEDPE file into “HiCsummary” format (http://homer.ucsd.edu/homer/interactions/HiCtagDirectory.html) accepted by CscoreTool.
7. iHiC_Cscore_Adj: Flip the sign of C-score chromosome-by- chromosome to ensure genomic regions with positive scores correspond to A compartment status.
8. iHiC_III2MTX4TopDom: Convert an III file into interaction matrices accepted by TopDom.
9. iHiC_TADBoundary_TopDom: Extract TAD boundaries from TopDom predictions.
10. iHiC_III2FitHiCInputs: Convert an III file into interaction matrices accepted by Fit-Hi-C.
11. iHiC_FitHiC2WashU: Convert the significant contacts predicted by Fit-Hi-C into a “longrange” format accepted by the WashU browser.
