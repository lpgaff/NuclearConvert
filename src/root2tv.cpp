/*																			*/
/*  root2tv																	*/
/*  Designed to convert TH1 histogram to a text file readable by tv			*/
/*																			*/
/*  Created by Liam Gaffney on 04/08/2009.									*/
/*																			*/
/*	Updates:																*/
/*		04/11/2011 LPG - Added command line arguments						*/
/*		04/11/2011 LPG - Added export to grace and 2-column options			*/
/*		31/08/2012 LPG - Changed char* to string for memory purposes		*/
/*																			*/
/*	Compile with:															*/
/*	g++ $(root-config --libs --cflags) root2tv.cpp -o YOUR_BIN_PATH/root2tv	*/
 
#include "TFile.h"
#include "TH1F.h"
#include "stdio.h"
#include "string"
#include "iostream"
using namespace std;

void root2tv(TH1F *spectra, string txtfile, char opt[4]) {

	float counts;
	FILE *out;
	string specname;
	string type;
	string usrtxt;
	int usropt;
	int size_x, size_y;
	
	/* Get number of channels or the size of the spectra. And name */
	specname = spectra->GetName();
	type = spectra->ClassName();
	size_x = spectra->GetNbinsX();
	if(strncmp(type.c_str(),"TH2",3)==0) size_y = spectra->GetNbinsY();
	
	if(strncmp(type.c_str(),"TH1",3)==0 || strncmp(type.c_str(),"TH2",3)==0) ;
	else {
		printf("%s is not a TH1 or a TH2 \n",specname.c_str());
		return;
	}

	/* Open a file to write to. Simple text file */
	if(txtfile=="\0"){
		cout << "Enter txt filename: ";
		cin >> usrtxt;
		if(usrtxt=="") usrtxt = specname + ".txt";
	} 
	else{
		usrtxt = txtfile + ".txt";
	}
	
	
	out = fopen(usrtxt.c_str(),"wb");
	if(!out) return;
	cout << "Writing to " << usrtxt << " ...\n";
	
	/* Check output option */
	if(strcmp(opt,"-0")==0){
		printf("Enter output format \n");
		printf(" 1 for single column format   \n");
		printf(" 2 for two column format   \n");
		printf(" 3 for grace input format   \n");
		scanf("%d",&usropt);
	}
	else {
		printf("Output option: %c\n",opt[1]);
		sscanf(&opt[1],"%d",&usropt);
	}
	
	/* Write content of each bin followed by new line */
	for(int i=0; i<size_x; i++){
		if(strncmp(type.c_str(),"TH1",3)==0){
			counts = (float)spectra->GetBinContent(i+1);
			if(usropt==1) fprintf(out,"%f\n",counts);
			if(usropt==2) fprintf(out,"%i\t%f\n",i,counts);
			if(usropt==3) fprintf(out,"%i\t%f\n%i\t%f\n",i,counts,i+1,counts);
		}
		else if(strncmp(type.c_str(),"TH2",3)==0){
			for(int j=0; j<size_y; j++){
				counts = (float)spectra->GetBinContent(i+1,j+1);				
				if(strcmp(opt,"-1") || usropt==1) fprintf(out,"%f\n",counts);
				else{
					printf("Can only process single column matricies\n");
					break;
				}
			}
		}
	}
	
	/* Close file and print filename */
	fclose(out);
	cout << "Written " << specname << " to file " << usrtxt << endl;
	
	return;
	
};

int main(int argc, char *argv[]) {

	string file;
	string hist;
	char option[4];
	TH1F *spec;
	FILE *frap;
	TFile *file0;

	printf("--------------------------------------------------- \n");
	printf(" root2tv : a program to convert root spectrum   \n");
	printf("           to txt file readable by tv, etc. \n\n");
	printf("   usage : root2tv -${opt} rootfile.root histname   \n");
	printf("   opt = 1 for single column format   \n");
	printf("         2 for two column format   \n");
	printf("         3 for grace input format   \n");
	printf("--------------------------------------------------- \n");
	
	if(argc==1){ // root2v run on it's own

		cout << "Enter root file containing required histogram: ";
		cin >> file;

		frap = fopen(file.c_str(),"rb");
		if(frap==NULL) {
			cout << "Error opening " << file << "... Does it exist?\n";
			return(0);
		}
		fclose(frap);

		file0 = new TFile(file.c_str());	
		if(file0->IsZombie()) {
			cout << file << " is not a root file\n";
			return(0);
		}
		file0->ls();
		
		cout << "Enter histogram to convert: ";
		cin >> hist;
	}

	else { // command line version
		if(strncmp(argv[1],"-",1)==0){
			strcpy(option,argv[1]);
			file = argv[2];
			hist = argv[3];
		}
		else{
			strcpy(option,"-1");
			file = argv[1];
			hist = argv[2];
		}
	}

	file0 = new TFile(file.c_str());	
	if(file0->IsZombie()) {
		cout << file << " is not a root file\n";
		return(0);
	
	}
	spec = (TH1F*)file0->Get(hist.c_str());
	if (spec == NULL){
		cout << "Error : " << hist << " does not exist... \n";
		return(0);
	}
	
	// Final execution
	if(argc==1) root2tv(spec,"\0","-0");
	else root2tv(spec,hist,option);
	
	return 1;

}
