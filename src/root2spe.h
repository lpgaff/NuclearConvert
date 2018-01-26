#ifndef FILES_H
#define FILES_H 1

#define matsize 4096
#define io_read 0
#define io_write 1


class files{
	int file_id;
	char filename[80];
	char text[100];
	int lum;
	FILE *fp;
	int fd;
public:
	char EUROGAM_NAME[80];
	files();
	files(const char*);
	struct ganil_header{
         unsigned long    num_run;          // ! numero run (a la sauvegarde)
         char   reserve_1[12];     // !
         char   nom_run[16];      // ! nom run (facultatif, 15 car utiles)
         long int    num_spectre;       // ! numero spectre
         char   type_spectre[2];   // ! type ("1D" ou "2D")
         char   reserve_2[10];    // !
         char   nom_spectre[16];  // ! nom du spectre (15 car utiles)
         char   date[12];         // ! date de creation ("jj-mmm-aaaa")
         char   heure[8];         // ! heure de creation ("hh:mn:ss")
         long int    nat_spectre;      // ! reserve ulterieure (=0)
         unsigned long    codeur_x;         // ! val max du codeur en x
         unsigned long    codeur_y;         // ! val max du codeur en y
         unsigned long    taille_canal;     // ! taille utile par canal (16 ou 32)
         char   type_canal[4];    // ! type variable ("I*4" , "I*2")
         unsigned long    dim_x;            // ! dimension du spectre en x
         unsigned long    dim_y;            // ! dimension du spectre en y
         unsigned long    min_x;            // ! numero du canal min en x
         unsigned long    min_y;            // ! numero du canal min en y
         unsigned long    max_x;            // ! numero du canal max en x
         unsigned long    max_y;            // ! numero du canal max en y
         char   commentaire[80];  // ! commentaire utilisateur
         char   nom_par_x[16];    // ! nom du parametre x (15 car utiles)
         char   nom_par_y[16];    // ! nom du parametre y (15 car utiles)
         char   unite_x[8];       // ! unite en x (8 car utiles)
         char   unite_y[8];       // ! unite en y (8 car utiles)
	}header_ganil;

	struct header_ans{
		char revision_code[2]; //0-1
		char file_name[12];  //2-13
		char spectrum_id[72]; //14-85
		char Start_Date[8];    //86-93
		char Stop_Date[8];     //94-101
		char ElapsedRT[8];    //102-109
		char ElapsedLT[8];    //110-117
		char ElapsedPass[4];  //118-121
		char DeadTime[4];      //122-125
		char Hard_Setup_AMP[42]; //126-167
		char Hard_Setup_ADC[84]; //168-251
		char Hard_Setup_Bias[30]; //252-281
		char Ener_Calib_Data[32]; //282-313
		char Shape_Calib_Data[24]; //314-337
		char Eff_Calib_Data[48]; //338-385
		char Detector[208];      //386-593
		char Hardware_spec[24];  //594-617
		char Hardware_setup_Presets[20]; // 618-637
		char Tool_Settings[28]; //638-665
		char Background[24]; // 666-689
		char Microanalysis[48]; // 690-737
		char Oxford[10]; // 738-747
		char Sample[20]; // 748-767
		char More_Tools[20]; // 768-787
		char Reserved[226]; // 788-1013
		char SpecStart[2];
		char SpecEnd[2];
		char NROIs[2];
		char AcqSysType[2];
		char AcqSysLen[2];
	}header_ans;

	struct in2p3_header{
		char nomrun[16];
		int numrun;
		char nomspe[16];
		int nuspe;
		char date[20];
		int type;
		int format;
		int nbcanx;
		int candebx;
		int nbcany;
		int candeby;
		int nbcanz;
		int candebz;
		int nbcant;
		int candebt;
		char oct[4];
		char idaplic[8];
		int hlong;
		char applic[16];
		char version[8];
	}header;

	struct header_eurogam
	{
		unsigned int magic_number;
		unsigned int version;	// expect 1 !!!
		char spectrum_name[32];		// spectrum name
		unsigned int fold;
		char creation_date[20];		//creation date
		char modification_date[20];	// modif date	

		unsigned int base_info[8];	// base info for dim 1-8

		unsigned int range[8];		// range info for dim 1-8

		unsigned int fip[32];	//  information pointer	
		int anotation_pointer[8];
		int calibration_pointer[8];
		int efficiency_pointer[8];
		unsigned int data_array_descriptor1[5];
			// 32 bits : array layout (0 for histo/matrix)
			// 32 bits : array type (5 for 32 bit signed )
			// 32 bits : reserved for future
			// 32 bits : reserved for future
			// 32 bits : pointer
		unsigned int data_array_descriptor2[5];
		int base_address_string_space;
		int string_free_space;
		unsigned int top_string_space;
		unsigned int base_address_count_space;
		unsigned int count_free_space;
		unsigned int top_count_space;
		unsigned int unused[20];	// not used ...
	}header_eurogam;

	void check_little_endian(void);
	unsigned long swap(unsigned long);
	void swap4b(char *);
	void swap2b(char *);
	int open_file(void);
	int open_file_r(void);
	int open_file_r(char *);
	int fopen_file(void);
	void get_name(const char *);
	int is_file_here(void);
	int is_file_here(char *);
	void remove(void);
	void remove(char *);
	void touch(void);
	void put_ex_mat();
	void put_ex_mat(char *);
	void put_ex_spe();	
	void put_ex_spe(char *);
	void put_ex_txt(char *);
	void put_ex_ans(char *);
	void put_ex_asc(char *);
	void put_ex_s();
	void put_ex_s(char *);
	void put_ex_mtr();
	int read_line(FILE *, char *);
	void specdump(short *, int, FILE*, FILE*);
	void specdump(int *, int, FILE*, FILE*);
	void specdump(unsigned int *, int, FILE*, FILE*);
	void specdump(float *, int, FILE*, FILE*);
	void specdump(int **, int, int, FILE*, FILE *);
	void specdump(short **, int, int, FILE*, FILE *);
// for radware .mat matrices
	int write_mat_rad(short *, FILE *, FILE *);
	int write_mat_rad(short *, char *, FILE *, FILE *);
	void write_mat_rad(int *);
	int read_mat_rad(short *, FILE *, FILE *);
	int read_mat_rad(short *, char *, FILE *, FILE *);
// for mktri matrices format 
	int read_mktri(short *, int);
	int write_mktri(short *, int);
	int check_mat(int, int*, FILE*, FILE* );
	int check_mat(int, FILE*, FILE* );
// for in2p3 format 
	int read_header_in2p3();
	void write_header_in2p3(FILE *);
	int read_sp_in2p3(unsigned int *);
	int read_sp_in2p3(unsigned int **);
	int get_type_in2p3(){return(header.type);};
	int get_nx_in2p3(){return(header.nbcanx);};
	int get_ny_in2p3(){return(header.nbcany);};
	char* get_nom_in2p3(){return(header.nomspe);};
// for gpsi format
	int get_nsp_gpsi(char *);
	int get_nx_gpsi(int, char *);
	int get_ny_gpsi(int, char *);
	void myrgspe(char *, int, float *,int , int, char *, int);
	void myrgspe(FILE *,char *, int, float *,int , int, char *, int);
// for cambda format
	int get_size_cambda(char *);
	void get_cambda(char *, float *, int);
	void get_att_mtr(void);
	int read_mtr(float **);
// for ascii format
	int get_size_ascii(char *);
	void get_ascii(char *, float *, int);
	void write_tab(float *, int);
	void write_tab(int *, int);
// for eurogam format 
	int swaping_eurogam;
	int open_eurogam(char *);
	void close_eurogam(void);
	int get_parameters_eurogam(char *, int *, int *, int *, FILE *, FILE *);
	int get_header_eurogam(char *, FILE *, FILE *);
	int get_header_eurogam(char *);
	void print_header_eurogam(void);
	int check_magicnumber_eurogam(char *, FILE *, FILE *);
	int check_magicnumber_eurogam(char *);
	void swap_header_eurogam(void);

	int get_fold_eurogam(void){return header_eurogam.fold;};
	int get_size_eurogam(void){return header_eurogam.count_free_space;};
	int get_size1_eurogam(void){return header_eurogam.range[0];};
	int get_size2_eurogam(void){return header_eurogam.range[1];};
	int get_type_eurogam(void){return
		header_eurogam.data_array_descriptor1[1];};
	int get_tab1D_eurogam(unsigned char *);
	int get_tab1D_eurogam(char *);
	int get_tab1D_eurogam(unsigned short *);
	int get_tab1D_eurogam(short *);
	int get_tab1D_eurogam(unsigned int *);
	int get_tab1D_eurogam(float *);
	int get_tab1D_eurogam(int *);
//	int get_tab2D_eurogam(short *);
	int get_tab2D_eurogam(short *, int, int);
	int get_tab2D_eurogam(short **, int, int);
//	int get_tab2D_eurogam(int *, int);
	int get_tab2D_eurogam(int *, int, int);
	int get_tab2D_eurogam(int **, int, int);
	int init_header_eg(int, int , const char *, int, FILE *, FILE *);
	int write_eg(int*, int, int , const char *, FILE *, FILE *);
	int write_eg(int*, int, int , const char *);
	int write_eg(int**, int, int , const char *, FILE *, FILE *);
	int write_eg(unsigned int*, int, int , const char *, FILE *, FILE *);
	int write_eg(short** , int, int , const char *, FILE *, FILE *);
	int write_eg(float*, int, int , const char *, FILE *, FILE *);
// for ganil format
	int get_header_ganil(char *);
	void print_header_ganil(void);
	int get_dimx_ganil(void){return swap(header_ganil.dim_x);};
	int get_ganil_integer4(unsigned long *);
// for radware monodim format 
	int write_spe(char *, float *, int, FILE *, FILE *);
	int read_spe(float *, char *, int *);
	int read_spe(char *,float *, char *, int *, FILE *, FILE *);
// for xmgr 
	int tab_to_xmgr(int, float*, float*, float*);
	void write_xmgr(int, float *, float *);
// for ans format
	int get_header_ans(char *);
	int open_ans(char *);
	void close_ans(void);
	void print_header_ans(void);
	int get_size_ans();
	int read_sp_ans(float *);
//  for asc format
	int read_header_asc(char *);
	void read_asc(float *, char *, int);
};

#endif
