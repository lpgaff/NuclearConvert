#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH2F.h"
#include "TChain.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TRandom.h"
#include "TVector3.h"
#include "TRotation.h"
#include "TLorentzVector.h"
#include "TGenPhaseSpace.h"
#include "TMath.h"
#include "TRint.h"
#include "TString.h"
#include "TKey.h"  
#include "root2spe.h"
#include <fstream>
#include <iostream>
using namespace std;

/*              root2spe spectrum converter root->spe
                1D histograms only
                Ch. Theisen
                First Version :  Feb 2005
		
		compile with :
		
g++ root2spe.C -o root2spe `$ROOTSYS/bin/root-config --libs` `$ROOTSYS/bin/root-config --cflags`
*/
                                                

class files File;

files::files(){

	strcpy(EUROGAM_NAME,"Eurogam spectrum");

}

files::files(const char *fname){

	strcpy(EUROGAM_NAME,fname);

}
int files::is_file_here(char *file){
FILE *fpa;

	fpa = fopen(file,"r");
	if (fpa == NULL) return(0);
	fclose(fpa);
	return(1);
}

void files::swap4b(char *buf){
char c;

  c = buf[3]; buf[3] = buf[0]; buf[0] = c;
  c = buf[2]; buf[2] = buf[1]; buf[1] = c;

}

int files::write_spe(char *file, float *spectre, int size, FILE *stream1, FILE *stream2) {
	
	FILE *fprad;
	int dum;
	int j = 24;
	int toto;
	int tab[4] = {0,1,1,1};
	int i;
	float *newspec;
	int newsize;


	newsize = size;
	if (size > 32768){
		newsize = 32768;
		printf("Initial size = %d; resizing to %d \n",size,newsize);
	}

	tab[0] = newsize;
	toto = newsize * sizeof(float);

	fprad = fopen(file,"w");
	if (fprad == NULL){
		fprintf(stream1,"Cannot write %s \n",file);
		if (stream2)
			fprintf(stream2,"Cannot write %s \n",file);
		fclose(fprad);
		return(0);
	}
	if (LITTLE_ENDIAN == 1){
		swap4b((char*)&j);
		for(i=0; i<4; i++)
			swap4b((char*)&(tab[i]));
		swap4b((char*)&toto);
		newspec = new float[newsize];
		for(i=0; i<newsize; i++){
			newspec[i] = spectre[i];
			swap4b((char*)&(newspec[i]));
		}
	}

	dum = fwrite(&j, sizeof(int), 1, fprad);
	dum = fwrite(filename, 8, 1, fprad);
	dum = fwrite(tab, sizeof(int), 4, fprad);
	dum = fwrite(&j, sizeof(int), 1, fprad);

	dum = fwrite(&toto, sizeof(int), 1, fprad);
	if (LITTLE_ENDIAN == 1){
		dum = fwrite(newspec, sizeof(float), newsize, fprad);
		delete [] newspec;
	}
	else
		dum = fwrite(spectre, sizeof(float), newsize, fprad);

  	dum = fwrite(&toto,sizeof(int),1,fprad);
	if (fprad == NULL){
		fprintf(stream1,"Cannot write %s \n",file);
		if (stream2)
			fprintf(stream2,"Cannot write %s \n",file);

		fclose(fprad);
		return(0);
	}
	fclose(fprad);

	return(1);
}


void files::put_ex_spe(char *name){

	int len;
	len = strlen(name);
	if ( ( name[len-1] == 'e' ) &&
	     ( name[len-2] == 'p' ) &&
	     ( name[len-3] == 's' ) &&
		 ( name[len-4] == '.' ) ) return;

	sprintf(name,"%s.spe",name);
	
}

int process(TH1F *histo, int option) {
	
	char name[80];
	char radname[80];
	char type[80];
	int nx,ny;
	int binning,range,start;
	float *spec;
	float ch,st;
	int i,j;

	sprintf(name,histo->GetName());
	printf("processing %s ...\n",name);
	sprintf(type,histo->ClassName());
	if (strncmp(type,"TH1",3) != 0){
		printf("	%s is not a TH1 \n",name);
		 return(1);
	}

	nx = histo->GetNbinsX();
	ny = histo->GetNbinsY();
	printf("	Nombre de bins X : %d \n",nx);
	printf("	Nombre de bins Y : %d \n",ny);
	printf("	First bin : %f \n",histo->GetBinLowEdge(1));
	printf("	Last bin : %f \n",histo->GetBinLowEdge(nx));
	
	spec = new float[nx];
	for(i=1; i<=nx; i++){
		ch = histo->GetBinLowEdge(i);
		st = histo->GetBinContent(i);
		//printf("%d %f %f \n",i,ch,st);
		spec[i-1] = histo->GetBinContent(i);
	}
	


	switch(option){
		case 1:
			sprintf(radname,name);
	        	File.put_ex_spe(radname);
			printf("	writing %s \n",radname);
		break;
		case 2:
        		printf("Enter output .spe filename : ");
        		scanf("%s",radname);
	        	File.put_ex_spe(radname);
			break;
	}
        
	File.write_spe(radname, spec, nx, stdout, NULL);
        delete [] spec;
	return(1);
}

int main(int argc, char *argv[]){
	
	int mode;       // 1 for only one    2 for all
	int dum;
	char file[80];
	char specname[80];
	TH1F *histo;

	printf("--------------------------------------------------- \n");
	printf(" root2spe : a program to convert root spectrum   \n");
	printf("          to Radford spectrum format \n");
	printf("  use root2spe -all to convert all histos           \n");
	printf("--------------------------------------------------- \n");
	
	if (argc == 1){
		mode = 1;
	}
	else{
		dum = strcmp(argv[1],"-all");
		if (dum != 0){
			printf("unvalid option %s \n",argv[1]);
			exit(0);
		}
		mode = 2;
	}
	
	printf("root file : ");
	scanf("%s",file);

        if (!File.is_file_here(file)){
		printf("This file does not exists ...\n");
		exit(0);
	}
	

	TFile *file1 = new TFile(file);
	if (file1->IsZombie()){
		printf("%s is not a root file ... \n",file);
		exit(0);
	}

	switch(mode){
	    case 1:
		file1->ls();
		printf("histogram name : ");
		scanf("%s",specname);

		histo = (TH1F*)file1->Get(specname);
		if (histo == NULL){
			printf("Error : %s does not exist... \n",specname);
			exit(0);
		}
		process(histo,2);
		break;
	    case 2:
		TIter nextkey(file1->GetListOfKeys());
		TKey *key;
		while(key = (TKey*)nextkey()){
			TH1F *histo = (TH1F*)key->ReadObj();
			process(histo,1);
		}
		break;	
	}
	
	file1->Close();

}
