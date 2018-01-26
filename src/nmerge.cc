#include <iostream>
#include "TChain.h"
#include "TString.h"
#include <TFile.h>
#include <TTree.h>
#include "TROOT.h"
using namespace std;

extern void InitGui();
VoidFuncPtr_t initfuncs[] = {InitGui, 0};
TROOT root("Rint","The ROOT Interactive Interface", initfuncs);


int main (int argc, char *argv[]) {

	if (argc < 4) {
		cout << "usage: nmerge <tree_name> -o target.root source1.root [source2.root ...]" << endl;
		return 0;
	}

	const char *n1, *n2, *f;
	for(int j=2; j<argc; j++) {
		if(strcmp(argv[j],"-o")==0){
			f  = argv[j+1];
			if(j<2){ printf("Input tree names before output file!"); return 0; }
			if(j==2){
				n1 = argv[1];
				cout << "   ntuple: " << n1 << endl;
				cout << "   filename: " << f << endl;
				cout << "   Files to be merged:  " << endl;
				TChain cha(n1);
				for (int k=j+2; k<argc; k++) {
					cha.Add(argv[k]);   cout << "       " << argv[k] << endl;
				}
				cha.Merge(f);
			}
			if(j==3){
				n1 = argv[1];
				n2 = argv[2];
				cout << "   ntuple 1: " << n1 << endl;
				cout << "   ntuple 2: " << n2 << endl;
				cout << "   filename: " << f << endl;
				cout << "   Files to be merged:  " << endl;
				TChain cha(n1);
				TChain cha2(n2);
				cha.AddFriend(n2);
				for (int k=j+2; k<argc; k++) {
					cha.Add(argv[k]);
					cha.Add(argv[k]);   cout << "       " << argv[k] << endl;
				}
				cha.Merge(f);
			}
			else{ printf("Only support for 2 trees so far"); return 0; }
		}
	}
	
  
	return 0;
}

