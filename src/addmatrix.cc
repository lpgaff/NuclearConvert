#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){

	if(argc<4){
		cout << "usage:\naddmatrix matrix1.d2t matrix2.d2t matrixout.d2t" << endl;
		return(0);
	}
	
	fstream matrix1, matrix2, matrixo;
	matrix1.open(argv[1],ios_base::in);
	matrix2.open(argv[2],ios_base::in);
	matrixo.open(argv[3],ios_base::out);
	
	float x1,x2,y1,y2,z1,z2;
	long int count=0;
	
	if(!matrix1.is_open() || !matrix2.is_open() || !matrixo.is_open()){
		cout << "It's fucking broken... SHIT!" << endl;
		return(0);
	}
	else{
		cout << "Adding the matrix files: " << argv[1] << " and " << argv[2] << endl;
		cout << "Outputting sum to the file " << argv[3] << endl;
		while(!matrix1.eof()){
			matrix1 >> x1 >> y1 >> z1;
			matrix2 >> x2 >> y2 >> z2;
			matrixo << x1 << "\t" << y1 << "\t" << z1+z2 << endl;
			count++;
			if(count%409600==0){
				cout << count <<" lines processed...\tBin x:"<< x1+.5 <<" y:"<< y1+.5 << endl;
			}
		}
	}
	
	matrix1.close();
	matrix2.close();
	matrixo.close();
	
	return(1);
	
}