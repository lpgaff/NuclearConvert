/*																			*/
/*  root2rw																	*/
/*  Designed to convert TH2 matrix to a text file readable by radware	*/
/*																			*/
/*  Created by Liam Gaffney on 01/09/2012.									*/
/*																			*/
/*	Updates:																*/
/*																			*/
/*																			*/
/*	Compile with:															*/
/*	g++ $(root-config --libs --cflags) root2rw.cpp -o YOUR_BIN_PATH/root2rw	*/
 
#include "TFile.h"
#include "TH2F.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

#define MATSIZE 4096

void root2rw(TH2F *spectra, string matfile) {

	ofstream out;
	string specname;
	string type;
	string usrmat;
	int size_x, size_y;
	short int* matrix = new short int[MATSIZE*MATSIZE];
	
	/* Get number of channels or the size of the spectra. And name */
	specname = spectra->GetName();
	type = spectra->ClassName();
	size_x = spectra->GetNbinsX();
	size_y = spectra->GetNbinsY();
	
	if(strncmp(type.c_str(),"TH2",3)==0) ;
	else {
		printf("%s is not a TH2 and therfore not a ROOT matrix\n",specname.c_str());
		return;
	}

	/* Open a file to write to. Simple text file */
	if(matfile=="\0"){
		cout << "Enter mat filename: ";
		cin >> usrmat;
		if(usrmat=="") usrmat = specname + ".mat";
	} 
	else{
		usrmat = matfile + ".mat";
	}
	
	if (size_x>MATSIZE || size_y>MATSIZE) {
		cout << "Matrix is too big. Must be <= "<< MATSIZE << " x " << MATSIZE << " channels\n";
		return;
	}
	
	/* The matrix! */
	for (int i=0; i<MATSIZE; i++) {
		for (int j=0; j<MATSIZE; j++) {
			matrix[j*MATSIZE+i] = 0;	// initialise
			if (i<size_x && j<size_y) // fill
				matrix[j*MATSIZE+i] = (short int)spectra->GetBinContent(i+1,j+1);
		}
	}

	/* Open and write to file */
	out.open(usrmat.c_str(),ios::out | ios::binary);
	if(!out.is_open()) return;
	cout << "Writing " << specname << " to " << usrmat << " ...\n";
	for (int i=0; i<MATSIZE; i++) {
		for (int j=0; j<MATSIZE; j++)
			out.write((char*)&matrix[j*MATSIZE+i],sizeof(short int));
	}
	out.close();

	delete [] matrix;
	
	return;
	
};

void print_usage(){

	printf("--------------------------------------------------- \n");
	printf(" root2rw : a program to convert root matrix   \n");
	printf("           to .mat file readable by radware, etc. \n\n");
	printf("   usage : root2rw rootfile.root histname   \n");
	printf("--------------------------------------------------- \n");
	
	return;

}

int main(int argc, char *argv[]) {

	string file;
	string hist;
	TH2F *spec;
	FILE *frap;
	TFile *file0;

	print_usage();
	
	if(argc==1){ // root2rw run on it's own

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

	else if (argc==3) { // command line version
		file = argv[1];
		hist = argv[2];
	}
	
	else {
		print_usage();
		return(0);
	}


	file0 = new TFile(file.c_str());	
	if(file0->IsZombie()) {
		cout << file << " is not a root file\n";
		return(0);
	
	}
	spec = (TH2F*)file0->Get(hist.c_str());
	if (spec == NULL){
		cout << "Error : " << hist << " does not exist... \n";
		return(0);
	}
	
	// Final execution
	if(argc==1) root2rw(spec,"\0");
	else root2rw(spec,hist);
		
	return 1;

}
