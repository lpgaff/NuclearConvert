//
//  mat2root.cpp
//
//
//  Created by Liam Gaffney on 21/12/2015.
//
//

#include "TFile.h"
#include "TMath.h"
#include "TH2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;


void mat2root( string matfile, short size, float binx, float biny ) {

    // test
    cout << matfile << " " << size << " " << binx << " " << biny << endl;
    
    // Somewhere to read our matrix in to!
    string filename = matfile.substr( 0, matfile.find_last_of( "." ) ) +  ".root";
    TFile *rootfile = new TFile( filename.c_str(), "RECREATE" );
    TH2D *rootmat = new TH2D( "mat", "mat", size, -0.5*binx, (size-0.5)*binx,
                             size, -0.5*biny, (size-0.5)*biny );
    
    // Read the matrix file
    ifstream infile;
    infile.open( matfile.c_str(), ios::binary );
    
    // Test that it's open!
    if( !infile.is_open() ) {
     
        cout << matfile.c_str() << " not opened...\n";
        
        return;
        
    }
    
    // Get file length
    infile.seekg ( 0, ios::end );
    const int length = infile.tellg();
    infile.seekg ( 0, ios::beg );
    
    // Read file as a block
    char *buf = new char[2*size];
    short dat[size];
    
    // Do some processing
    short counts;
    int evt = 0;
    for( int i = 0; i < size; i++ ) {
    
	infile.read( buf, 2*size );
	memcpy( dat, buf, 2*size );

        for( int j = 0; j < size; j++ ) {

            counts = (short)dat[ j ];
            
            rootmat->SetBinContent( i+1, j+1, (float)counts );
            
            evt++;
            if( evt > length/2 ) {
                
                cout << "Reading too many events... Check size\n";
                return;
                
            }
            
        }
    
    }
    
    cout << "Successfully read and processed " << matfile.c_str() << endl;
    rootmat->Write();
    rootfile->Close();

    return;
    
}


void print_usage( string progname ){
    
    cout << "-----------------------------------------------------------\n";
    cout << " mat2root : a program to convert .mat file   \n";
    cout << "            to TH2 root histrogram \n\n";
    cout << "   usage  : " << progname << " <file> <size> <binx> <biny>\n";
    cout << " where <file> is the .mat file, <size> is the number of\n";
    cout << " channels and <binx/y> are the bin widths in x/y direction\n";
    cout << "-----------------------------------------------------------\n";
    
    return;
    
}

int main( int argc, char *argv[] ) {
    
    string file;
    stringstream ss;
    int size;
    float binx, biny;
    
    if ( argc == 2 ) {
        
        file = argv[1];
        size = 4096;
        binx = 1;
        biny = 1;
        
        mat2root( file, size, binx, biny );
        
    }
    
    else if ( argc == 3 ) {
        
        file = argv[1];
	ss.clear();
        ss.str( argv[2] );
        ss >> size;
        binx = 1;
        biny = 1;
        
        mat2root( file, size, binx, biny );
        
    }
    
    else if ( argc == 4 ) {
        
        file = argv[1];
	ss.clear();
        ss.str( argv[2] );
        ss >> size;
	ss.clear();
        ss.str( argv[3] );
        ss >> binx;
        
        mat2root( file, size, binx, biny );
        
    }
    
    else if ( argc == 5 ) {
        
        file = argv[1];
	ss.clear();
        ss.str( argv[2] );
        ss >> size;
	ss.clear();
        ss.str( argv[3] );
        ss >> binx;
 	ss.clear();
        ss.str( argv[4] );
        ss >> biny;
        
        mat2root( file, size, binx, biny );
        
    }
    
    else {
        
        print_usage( argv[0] );
        
        return 0;
        
    }
    
}


