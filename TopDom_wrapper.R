args = commandArgs(TRUE);
source(args[1])
mtx<-args[2]
dom<-paste(mtx,".domain",sep="")
sig<-paste(mtx,".binSignal",sep="")
tad_w10<-TopDom(matrix.file=mtx,window.size=10)
write.table(tad_w10$binSignal,sig)
write.table(tad_w10$domain,dom)
