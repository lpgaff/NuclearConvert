#include "geometry.cc"
#ifndef AnaDefs_h
#include "AnaDefs.hh"
#endif

int main(int nOfArgs, char* argz[]) {

	double theta, phi, alpha, dist_TA_MB;
	
	if( nOfArgs==1 ){ 
		printf("GeAngles: Returns the angles of each core in MINIBALL\n\n");
		printf("Usage: ./GeAngles theta phi alpha dist\n\n");
		printf("The program is run with 4 paramaters desribing the cluster position\n");
		printf("1: Theta angle of the centre of the cluster in degrees\n");
		printf("2: Phi angle of the centre of the cluster in degrees\n");
		printf("3: Alpha angle, the rotation of the cluster in degrees\n");
		printf("4: The target to cluster distance in millimetres\n");
		printf("And returns the corresponding distance, theta and phi of each core\n");
		printf("You can also read in a config file of standard format\n");
		return 0;
	}
	else if( nOfArgs==2 ){
		FILE *f = fopen(argz[1],"rb");
		if(f==NULL){ 
			printf("File %s doesn't exist\n",argz[1]);
			return 0;
		}
		for( int i=0;i<8;i++ ){
			fscanf(f,"%lf %lf %lf %lf",&theta,&phi,&alpha,&dist_TA_MB);
			get_positions_segments(theta, phi, alpha, dist_TA_MB,34.0,0.6,0,3,0);
			get_positions_segments(theta, phi, alpha, dist_TA_MB,34.0,0.6,0,4,0);
		}
		return 0;
	}
	else if( nOfArgs!=5 ){ 
		printf("Please enter theta, phi, alpha and distance to detector\n"); 
		return 0;
	}
	
	else if( nOfArgs==5 ){
		sscanf(argz[1],"%lf",&theta);
		sscanf(argz[2],"%lf",&phi);
		sscanf(argz[3],"%lf",&alpha);
		sscanf(argz[4],"%lf",&dist_TA_MB);
		get_positions_segments(theta, phi, alpha, dist_TA_MB,34.0,0.6,1,3,0);
		return 0;
	}
}
