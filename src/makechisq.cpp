// Read in gosia2 input files and do a loop over a range of matrix elements,
// extracting and plotting the chisq as we go

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

double GetChiSq(string cmd) {
	
	string data, tmp;
	stringstream gosia_chisq (stringstream::in | stringstream::out);
    double chisq;
    FILE* gosiaout;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
	
    gosiaout = popen(cmd.c_str(), "r");
    if (gosiaout) {
		while (!feof(gosiaout))
			if (fgets(buffer, max_buffer, gosiaout) != NULL) data.assign(buffer);
		pclose(gosiaout);
    }
	
	gosia_chisq << data;
	gosia_chisq >> tmp >> tmp >> chisq;
	
    return chisq;
}


void PrintUsage( char* progname ) {

	cout << "\nUsage: \n" << progname << " <inputfile> ";
	cout << "<lineNo=41> <low_lim=0.1> <upp_lim=2.5> <Nsteps=51>\n\n";
	cout << " where <lineNo> is the line number in the input file that\n";
	cout << "contains the transitional matrix elemtent\n\n";
	cout << "Only <inputfile> is required, the rest have default values\n";
	cout << "as indicated in the usage.\n";

	return;
	
}

int main( int argc, char* argv[] ) {
	
	// If the number of arguments are wrong, exit with usage
	if( argc < 2 || argc > 6 ) {
		
		PrintUsage(argv[0]);
		return 0;
	
	}
	
	// Get/Set arguments
	stringstream arg (stringstream::in | stringstream::out);

	string inputfile;
	int lineNo = 41;
	double low_lim = 0.1;
	double upp_lim = 2.5;
	int Nsteps = 51;
	
	if( argc >= 2 ) {
		arg.clear();
		arg << argv[1];
		arg >> inputfile;
	}
	if( argc >= 3 ) {
		arg.clear();
		arg << argv[2];
		arg >> lineNo;
	}
	if( argc >= 4 ) {
		arg.clear();
		arg << argv[3];
		arg >> low_lim;
	}
	if( argc >= 5 ) {
		arg.clear();
		arg << argv[4];
		arg >> upp_lim;
	}
	if( argc == 6 ) {
		arg.clear();
		arg << argv[5];
		arg >> Nsteps;
	}
	
	
	// Open input file and store
	ifstream in;
	in.open(inputfile.c_str(),ios::in);
	if( !in.is_open() ) {
	
		cout << "Unable to open " << inputfile << endl;
		return 1;

	}
		
	int maxlinesize = 2048;
	char line[maxlinesize];
	stringstream input1 (stringstream::in | stringstream::out);
	stringstream input2 (stringstream::in | stringstream::out);
	
	int lineNo_ptr = 1;
	cout << "\nReading input file... ";
	while (!in.eof()) {

		in.getline(line,maxlinesize);
		if( lineNo_ptr < lineNo ) input1 << line << endl;
		else if( lineNo_ptr > lineNo ) input2 << line << endl;

		lineNo_ptr++;
		
	}
	cout << "Complete\n\n";
	
	// Declare "gosia2.inp"
	ofstream gosia2inp;
	
	// Open output file
	string outname = inputfile.substr(0, inputfile.find_last_of("."));
	outname += ".chisq";
	ofstream out;
	out.open(outname.c_str(),ios::out);	
	
	// Get chisq values and write to file
	double tme;
	double chisq = 999.;
	double stepSize = ( upp_lim - low_lim ) / (double)(Nsteps-1);
	
	cout << "TME\tChisq\n";
	for ( int i=0; i<Nsteps; i++ ) {
		
		tme = low_lim + i*stepSize;
	
		// Make input file
		gosia2inp.open("gosia2.inp",ios::out);
		gosia2inp << input1.str();
		gosia2inp << " 1 2 " << tme << " 1 1" << endl;
		gosia2inp << input2.str();
		gosia2inp.close();
		
		chisq = GetChiSq("gosia2 < gosia2.inp");
	
		cout << tme << "\t" << chisq << endl;
		out << tme << "\t" << chisq << endl;
				
	}
	
	out.close();
	

	return 0;
	
}