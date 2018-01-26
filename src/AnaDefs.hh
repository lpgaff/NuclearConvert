#ifndef AnaDefs_h
#define AnaDefs_h 0

#define PURE_SI_EVENT           1    /* only ONE SI event in built event */
#define PURE_GE_EVENT           2    /* only GE events in built event (how much: -> GEmul) */
#define SI_GE_EVENT             3    /* coincidence event: ONE SI and at least ONE GE event */

#define NUMBER_OF_CLUSTER      8     /* Number of Miniball clusters */
#define NUMBER_OF_CORE         (NUMBER_OF_CLUSTER*3)
#define NUMBER_OF_EXTRA_DGF    6     /* Number of extra DGFs: Q1, Q2, Q3, Q4, (EBIS, T1, SS), Beam Dump */
#define NUMBER_OF_DGF          (NUMBER_OF_CORE*2+NUMBER_OF_EXTRA_DGF)
#define NUMBER_OF_CHAN         ((NUMBER_OF_DGF-2)*NUMBEROFCHANNELS) /* Why -2? */
#define NUMBER_OF_XIA_CHAN     (NUMBER_OF_DGF*NUMBEROFCHANNELS)
#define CHANNELS_PER_CLUSTER   NUMBEROFCHANNELS*2*3

#define NUMBER_OF_CAEN_V785_ADC_CHANNELS      32
#define NUMBER_OF_CAEN_V775_TDC_CHANNELS      32

#define NUMBER_OF_CAEN_V7X5_CHECK_CHANNELS    NUMBER_OF_CAEN_V785_ADC_CHANNELS
#define FIRST_TIMESTAMP_MODULE 48 /* DGF for Q1 timestamp */

#define MAX_NUM_OF_EVENTS      100 /* Recommended: 100 for coulex run, 400 for 152Eu run */

#define DEFAULT_FILENAME       "out"
#define DEFAULT_COINC_WINDOW     "4" /* in us */
#define DEFAULT_REF_POINT       ".5"
#define DEFAULT_STOP_EVENT      "-1"

#define SI_NTUPLE_ANNULAR         16
#define SI_NTUPLE_SECTOR          32 
#define SI_NTUPLE_CDE              4
#define GE_NTUPLE                 100
#define CORE_NTUPLE               20 
#define SI_MAX_NUM_OF_REC_EVENTS  10
#define MAX_NR_OF_REC_EV_PER_SECTOR  8 
#define MAX_ANNULAR_ENERGY       180000.
#define CORE_MAX_SEGMENT_PERCENTAGE 0.1
#define GE_ADDBACK_THRESHHOLD_KEV          100  // in 'MB_Addback()': only core gammas with 'E[keV] >= GE_ADDBACK_THRESHHOLD_KEV' are considered for ADDBACK
#define ADDBACK_NTUPLE                     10 /* Recommended: 10 for coulex runs, 20 for 152Eu runs */

#define ANNULAR_FIRST              0
#define ANNULAR_LAST               15

#define SECTOR_FIRST               16
#define SECTOR_LAST                27 

#define CAEN_TDC_FIRST           0
#define CAEN_TDC_LAST            32

//#define LASER_CONTROL
#define SI_MAXIMUM_ADC_VALUE    3840
#define SI_GENERAL_THRESHOLD       0
#define SI_THRESHOLD             100

#define NUM_OF_CD_SECTORS         4
#define NUM_OF_CDE_SECTORS         4

#define ANNULAR_STRIPS_PER_SECTOR    16
#define SECTOR_STRIPS_PER_SECTOR     24

#define PI                       (TMath::Pi())
#define SL                       34
#define SL2                      29.4
#define DISTANCE_TARGET_MB       125
#define DISTANCE_TARGET_DET_MEAN 160
#define RATIO                    0.6
#define DETECTOR_LENGTH          78
#define TILT_ANGLE               (1/13.)
#define THICKNESS_TRIPLE_CAP     1
#define THICKNESS_DET_CAP        0.7
#define AIRGAP_TRIPLE_DET_CAP    1

#define PSA_R_GAIN           0.094
#define PSA_R_OFFSET         1.213
#define PSA_T_SLOPE_OFFSET     -50
#define PSA_PHI_GAIN        13.812
#define PSA_PHI_OFFSET       2.560
#define PSA_T_MINIMUM            0
#define PSA_T_MAXIMUM         1000

#define BUFFER_SIZE          512

#define DEFAULT_TIME_DIFF -10000  /* in ns: max.coinc.window:~10us-> set to -10000 */


#define GGCOINC

//#define FILL_GTREE         /* classes: EventData, SiData, GeData   */  
#define FILL_RTREE         /* classes: SiData, SiEvtData. RealData */     
//#define FILL_PTREE         /* classes: AuxData                     */
//#define FILL_TESTTREE      /* classes: TestData                    */
#define PART_OUTPUT          /*output info on particle handling - JVdW 9jan2004*/

//#define EVENTBUILDING_TEST       /* define to test eventbuilding AFTER it was done */
//#define REAL_DATA_TEST     /* define to test RealData class */
//#define ReadEich_TEST                 /* test of ReadEich() */
//#define ReadConfigFile_TEST           /* test of ReadConfigFile()         */
//#define GetMINIBALLGeometry_TEST      /* test of GetMINIBALLGeometry()    */
//#define CD_EventReconstruction_TEST   /* test of CD_EventReconstruction() */
//#define PSA_MB_Pos_Rec_TEST           /* test of PSA_MB_Pos_Rec()         */

//#define TRACE_READOUT 1  /* define if timestamping is done _WITH_ a trace */
#define TRACE_READOUT 0  /* define if timestamping is done _WITHOUT_ a trace */

#define TIMESTAMP_CHANNEL  0  /* channel number of VME gate in TIMESTAMP_MODULE */

/* coincidence window for ADDBACK in MINIBALL clusters */
#define MINIBALL_ADDBACK_COINC_WINDOW_LOW_NS   -200
#define MINIBALL_ADDBACK_COINC_WINDOW_HIGH_NS   200

#define NUMBER_OF_INFO_MARKERS 10

#define ROOT_FILE_COMPRESSION_LEVEL 1

#define DGF_INIT_DELAY 65556

#endif
