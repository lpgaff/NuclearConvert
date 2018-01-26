// Collate matrix elements and errors in to one file readable by gnuplot

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

void printusage(){

	cout << "\nusage: collategosiaoutput <filename>\n";
	cout << "<filename> is the name of the .bst and .err files without the extension\n\n";
	return;
	
}

int process(char *file){

	ifstream f_err, f_bst;
	ofstream f_out; // output file *.me
	string filename;
	
	// Read-in values for me ± err
	double me, erm, erp;
	
	// Open matrix element gosia output file first
	filename.assign(file);
	filename.append(".bst");
	f_bst.open(filename.c_str());
	if(!f_bst.is_open()) {
		cerr << "Error opening " << filename << endl;
		return 1;
	}

	// Open error gosia output file
	filename.assign(file);
	filename.append(".err");
	f_err.open(filename.c_str());
	if(!f_err.is_open()) {
		cerr << "Error opening " << filename << endl;
		return 2;
	}
	
	// Write to output file.. Open it first
	filename.assign(file);
	filename.append(".me",ios::trunc);
	f_out.open(filename.c_str());
	if(!f_out.is_open()) {
		cerr << "Error opening " << filename << endl;
		return 3;
	}

	while(!f_bst.eof()){
		f_bst >> me;
		f_err >> erm >> erp;
		f_out << me << "\t" << erm << "\t" << erp << endl;
	}
	f_bst.close();
	f_err.close();
	f_out.close();
	
	cout << "Wrote matrix elements and errors to \"" << filename << "\"\n";
	
	return 0; // success!!
	
}

int main(int argc, char *argv[]){

	if(argc==1) {
		cout << endl;
		cout << argv[0] << ": A program to collate matrix elements in to \n";
		cout << "a single file so that they can be plotted by gnuplot for example\n";
		printusage();
	}
	else if(argc==2) {
		if(process(argv[1])>0){
			cerr << "Error: Something went wrong...\n";
			printusage();
		}
	}
	else {
		cout << "\n";
		printusage();
	}
	
	return 0;
	
}