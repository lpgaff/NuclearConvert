/***************************************************************/
/* Convert Marabou - A C++ program that converts the marabou   */
/*  .cal files into the offl_root_med .dat file format         */
/***************************************************************/
/* Liam Gaffney - 07/07/2010                                   */
/* First workable version uploaded to pcepis41 on 19/08/2010   */
/* To do:                                                      */
/* • Add DGF paramaterisation                                  */
/* • File read errors                                          */
/* • Tab complete                                              */
/***************************************************************/

#include <stdio.h>
#include <string.h>

/* Defines for Convert procedure */
FILE *in, *out;
char line[100];
char inname[100];
char outname[100];
char gibberish[100];
char go[100];
char gain[25], offset[25];

void ConvertToMarabou(char *filename) {

	/* Open offl_root_med calibration file */
	int len = strlen(filename);
	if( (filename[len-4]=='.') &&
		(filename[len-3]=='d') &&
		(filename[len-2]=='a') &&
		(filename[len-1]=='t') ) { 
		sprintf(inname,"%s",filename);
	}
	else {
		sprintf(inname,"%s.dat",filename);
	}
	
	/* Check file exists before opening */
	in = fopen(inname, "rb");
	if(in!=NULL){
		printf("Opened %s ...\n",inname);
	}
	else if(fopen(inname,"rb")==NULL){
		fclose(in);
		return;
	}
	
	/* Open Marabou calibration file */	
	sprintf(outname,"%s",inname);
	for(unsigned int i=0; i<strlen(inname); i++){
		if(i==(strlen(inname)-4)){ outname[i]='.'; }
		if(i==(strlen(inname)-3)){ outname[i]='c'; }
		if(i==(strlen(inname)-2)){ outname[i]='a'; }
		if(i==(strlen(inname)-1)){ outname[i]='l'; }
	}
	out = fopen(outname, "wb" );
	printf("Opened %s ...\n",outname);
	
	/* Write the 3 header lines at the start of the .cal file */
	fprintf(out,"Calib.ROOTFile:\t\t/d1/miniball/cern-060712/Calib_Co60_alphaT.root\n");
	fprintf(out,"Calib.Source:\t\tWho cares? It was A/Q=4 if you must know!\n");
	fprintf(out,"Calib.NofHistograms:\t\t124\n");	
	
	/* Loop over every line and assign gain and offset appropriatley */	
	/* Write parameter to file along with (well formated) gibberish  */
	rewind(in);
	while(!feof(in)){
		for(int i=1;i<=4;i++){
			for(int j=1;j<=16;j++){
				fscanf(in,"%s%s",offset,gain);
				fprintf(out,"Calib.hEcds%if%i.Xmin:\t\t0\n",i,j);
				fprintf(out,"Calib.hEcds%if%i.Xmax:\t\t4096\n",i,j);
				fprintf(out,"Calib.hEcds%if%i.Gain:\t\t%s\n",i,j,gain);
				fprintf(out,"Calib.hEcds%if%i.Offset:\t\t%s\n",i,j,offset);
			}
			for(int k=1;k<=12;k++){
				fscanf(in,"%s%s",offset,gain);
				fprintf(out,"Calib.hEcds%ib%i.Xmin:\t\t0\n",i,k);
				fprintf(out,"Calib.hEcds%ib%i.Xmax:\t\t4096\n",i,k);
				fprintf(out,"Calib.hEcds%ib%i.Gain:\t\t%s\n",i,k,gain);
				fprintf(out,"Calib.hEcds%ib%i.Offset:\t\t%s\n",i,k,offset);
			}
			for(int l=11;l<=13;l++){
				fscanf(in,"%s%s",offset,gain);
				fprintf(out,"Calib.hdmy%i.Xmin:\t\t0\n",l);
				fprintf(out,"Calib.hdmy%i.Xmax:\t\t4096\n",l);
				fprintf(out,"Calib.hdmy%i.Gain:\t\t1\n",l);
				fprintf(out,"Calib.hdmy%i.Offset:\t\t0\n",l);
			}
				fscanf(in,"%s%s",offset,gain);
				fprintf(out,"Calib.cde%i.Xmin:\t\t0\n",i);
				fprintf(out,"Calib.cde%i.Xmax:\t\t4096\n",i);
				fprintf(out,"Calib.cde%i.Gain:\t\t1\n",i);
				fprintf(out,"Calib.cde%i.Offset:\t\t0\n",i);
		}
	}
	fclose(in);
	fclose(out);
	
	return;
}

void ConvertFromMarabou(char *filename) {
	
	/* Open marabou calibration file */
	int len = strlen(filename);
	if( (filename[len-4]=='.') &&
		(filename[len-3]=='c') &&
		(filename[len-2]=='a') &&
		(filename[len-1]=='l') ) { 
		sprintf(inname,"%s",filename);
	}
	else {
		sprintf(inname,"%s.cal",filename);
	}
	
	/* Check file exists after opening */
	in = fopen(inname, "rb");
	if(in!=NULL){
		printf("Opened %s ...\n",inname);
	}
	else if(fopen(inname,"rb")==NULL){
		fclose(in);
		return;
	}
	
	/* Open offl_root_med calibration file */	
	sprintf(outname,"%s",inname);
	for(unsigned int i=0; i<strlen(inname); i++){
		if(i==(strlen(inname)-4)){ outname[i]='.'; }
		if(i==(strlen(inname)-3)){ outname[i]='d'; }
		if(i==(strlen(inname)-2)){ outname[i]='a'; }
		if(i==(strlen(inname)-1)){ outname[i]='t'; }
	}
	out = fopen(outname, "wb" );
	printf("Opened %s ...\n",outname);

	/* Loop over every line and write parameters to out file */	
	/* Check for "Gain" or "Offset" and write appropriatley  */
	rewind(in);
	while(fscanf(in,"%s%s",gibberish,go) != EOF){
		if(strstr(gibberish,"Gain")!=NULL){
			strcpy(gain,go);
		}
		if(strstr(gibberish,"Offset")!=NULL){
			strcpy(offset,go);
			fprintf(out,"%s %s\n",offset,gain);
		}
	}
	fclose(in);
	fclose(out);
	
	return;
}

int main(){
	char userfile[100];
	int cc;
	printf("\n   #######################################################\n");
	printf("   # ConvertMarabou - Written by Liam Gaffney 19/08/2010 #\n");
	printf("   #######################################################\n");
	printf("   A code to convert Marabou ADC cal files to offl_root_med format\n");
	printf("   It also works in reverse. But not yet for the DGFs... Be patient!\n");
	printf("\n   It is a stupid program and isn't not very friendly so please\n");
	printf("   make sure you input files are free of comments et cetera.\n");
	printf("   It will also print nonsense if you give it the wrong file\n\n");
	printf("To convert TO Marabou format FROM offl_root_med: 1\n");
	printf("To convert FROM Marabou format TO offl_root_med: 2\n");
	printf("Select option, 1 or 2: ");
	scanf("%i",&cc);
	printf("File to convert: ");
	scanf("%s",userfile);
//	printf("Opening file: ",userfile);
	if(cc==1){ 
		ConvertToMarabou(userfile);
		return 0;
	}
	if(cc==2){
		ConvertFromMarabou(userfile);
		return 0;
	}
	else{
		printf("Invalid option");
		return 0;
	}
}

