#include "TVector3.h"
#include "TRotation.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include "TH3.h"
#include "TMath.h"

#ifndef PI
#define PI                  (TMath::Pi())
#endif

/*****************************************************************************/
/* Get positions  of the segments                                            */
int get_positions_segments(double theta, double phi, double alpha,
			   double dist_TA_MB, double dist_CORE_CORNER, 
			   double ratio, int drawopt, int outopt,
			   TVector3* vdirec = 0) {
  
   /* *************************************** START of main POSITIONING code ************************************* */
   
   /* pos_...[]: 0:center, 1:A, 2:B, 3:C */
   double pos_x[4], pos_y[4], pos_z[4];
   
   /* 18 segments of cluster */ 
   double x[24], y[24], z[24];
   double r[24], th[24], ph[24];
  int i;
   TVector3 v2[24];
   
   /* center of cluster */
   pos_x[0] =                                  0; 
   pos_y[0] =                                  0; 
   pos_z[0] =                         dist_TA_MB; 
   
   /* core A */
   pos_x[1] =                   dist_CORE_CORNER;
   pos_y[1] =                                  0;
   pos_z[1] =                         dist_TA_MB;
   
   /* core B */
   pos_x[2] = -dist_CORE_CORNER*sin(30/180.0*PI);
   pos_y[2] = -dist_CORE_CORNER*cos(30/180.0*PI);
   pos_z[2] =                         dist_TA_MB;
   
   /* core C */
   pos_x[3] = -dist_CORE_CORNER*sin(30/180.0*PI);
   pos_y[3] =  dist_CORE_CORNER*cos(30/180.0*PI);
   pos_z[3] =                         dist_TA_MB;
   
   /* R: distance from core to wanted point in segment middle (0<=ratio<=1) */
   double R;
   R = ratio * dist_CORE_CORNER;
   
   /* SA(=standard angle): 30deg (half of one segment=60deg) */
   double ang;
   double SA = 30;
   ang = SA / 180.0 * PI;
   
   /* x_A[], y_A[] (x and y pos. of 6 segments relative to core) */
   double x_A[6], y_A[6];
   x_A[0]  =   R*sin(ang);         // A1 
   y_A[0]  = (-R*cos(ang));
   x_A[1]  = (-R*sin(ang));        // A2
   y_A[1]  = (-R*cos(ang));
   x_A[2]  =   R;                  // A3
   y_A[2]  =   0;
   x_A[3]  =   R*sin(ang);         // A4
   y_A[3]  =   R*cos(ang);
   x_A[4]  = (-R);                 // A5
   y_A[4]  =   0;
   x_A[5]  = (-R*sin(ang));        // A6
   y_A[5]  =   R*cos(ang);
   
   /* Segments and core and empty 4th channel of slave module of det A */
   x[0]  = pos_x[1];               // A0 (core) 
   y[0]  = pos_y[1];
   z[0]  = pos_z[1];
   x[1]  = pos_x[1] +   x_A[0];    // A1 
   y[1]  = pos_y[1] +   y_A[0];
   z[1]  = pos_z[1];
   x[2]  = pos_x[1] +   x_A[1];    // A2
   y[2]  = pos_y[1] +   y_A[1];
   z[2]  = pos_z[1];
   x[3]  = 0;                      // empty DGF channel
   y[3]  = 0;
   z[3]  = 0;
   x[4]  = pos_x[1] +   x_A[2];    // A3
   y[4]  = pos_y[1] +   y_A[2];
   z[4]  = pos_z[1];
   x[5]  = pos_x[1] +   x_A[3];    // A4
   y[5]  = pos_y[1] +   y_A[3];
   z[5]  = pos_z[1];
   x[6]  = pos_x[1] +   x_A[4];    // A5
   y[6]  = pos_y[1] +   y_A[4];
   z[6]  = pos_z[1];
   x[7]  = pos_x[1] +   x_A[5];    // A6
   y[7]  = pos_y[1] +   y_A[5];
   z[7]  = pos_z[1];
   
   /* Segments and core and empty 4th channel of slave module of det B */
   x[8]  = pos_x[2];               // B0 (core)
   y[8]  = pos_y[2];
   z[8]  = pos_z[2];
   x[9]  = pos_x[2] +   x_A[4];    // B1 (=A5)
   y[9]  = pos_y[2] +   y_A[4];
   z[9]  = pos_z[2];
   x[10] = pos_x[2] +   x_A[5];    // B2 (=A6)
   y[10] = pos_y[2] +   y_A[5];
   z[10] = pos_z[2];
   x[11] = 0;                      // empty DGF channel
   y[11] = 0;
   z[11] = 0;
   x[12] = pos_x[2] +   x_A[1];    // B3 (=A2)
   y[12] = pos_y[2] +   y_A[1];
   z[12] = pos_z[2];
   x[13] = pos_x[2] +   x_A[0];    // B4 (=A1)
   y[13] = pos_y[2] +   y_A[0];
   z[13] = pos_z[2];
   x[14] = pos_x[2] +   x_A[3];    // B5 (=A4)
   y[14] = pos_y[2] +   y_A[3];
   z[14] = pos_z[2];
   x[15] = pos_x[2] +   x_A[2];    // B6 (=A3)
   y[15] = pos_y[2] +   y_A[2];
   z[15] = pos_z[2];
   
   /* Segments and core and empty 4th channel of slave module of det C */
   x[16] = pos_x[3];               // C0 (core)
   y[16] = pos_y[3];
   z[16] = pos_z[3];
   x[17] = pos_x[3] +   x_A[3];    // C1 (=A4)
   y[17] = pos_y[3] +   y_A[3];
   z[17] = pos_z[3];
   x[18] = pos_x[3] +   x_A[2];    // C2 (=A3)
   y[18] = pos_y[3] +   y_A[2];
   z[18] = pos_z[3];
   x[19] = 0;                      // empty DGF channel
   y[19] = 0;
   z[19] = 0;
   x[20] = pos_x[3] +   x_A[5];    // C3 (=A6)
   y[20] = pos_y[3] +   y_A[5];
   z[20] = pos_z[3];
   x[21] = pos_x[3] +   x_A[4];    // C4 (=A5)
   y[21] = pos_y[3] +   y_A[4];
   z[21] = pos_z[3];
   x[22] = pos_x[3] +   x_A[0];    // C5 (=A1)
   y[22] = pos_y[3] +   y_A[0];
   z[22] = pos_z[3];
   x[23] = pos_x[3] +   x_A[1];    // C6 (=A2)
   y[23] = pos_y[3] +   y_A[1];
   z[23] = pos_z[3];
   
   /* Angles in radians */
   alpha = alpha/180.0*PI;  
   phi   = phi/180.0*PI;
   theta = theta/180.0*PI;
   
   /* ********* */
   /* IMPORTANT */
   /* ********* */
   /* Update theta and phi to be angles in the standard MINIBALL frame of
    * reference. Theta and phi passed to this routine are values read from the
    * MINIBALL frame (HARDWARE), which correspond to value in a system with
    * the z-axis pointing upward, i.e. the x-direction of the MINIBALL frame
    * of reference (FoR).  The following lines transform the theta and phi
    * values. */

   /* Check if phi > PI -> rotation angles change */
   if(phi>PI) {
      phi = 2*PI - phi;
      theta = -theta;
   }
   
   TVector3 trans;
   trans.SetXYZ(1,0,0);
   trans.RotateY(-phi);
   trans.RotateX(-theta);
   
   theta=trans.Theta();
   phi=trans.Phi();
   
   
   /* Done transforming theta and phi */

   /* Find alpha offset */
   
   TVector3 vd,va,vn;
   const TVector3 ex(1,0,0);
   
   vd.SetXYZ(0,0,1);
   va.SetXYZ(1,0,0);
   
   vd.RotateY(theta);
   vd.RotateZ(phi);
   va.RotateY(theta);
   va.RotateZ(phi);
   
   vn=ex-vd*(ex*vd);
   vn.SetMag(1.);
   
   double spat=vn*(va.Cross(vd));
   double alpha_offset=va.Angle(vn);  //*spat;
   if (spat<0) alpha_offset*=-1;
   
#if 0
   printf("vn %f %f %f\n",vn.X(),vn.Y(),vn.Z());
   printf("va %f %f %f\n",va.X(),va.Y(),va.Z());
   printf("angle %f\n",alpha_offset*180./PI);
   printf("spat %f\n",spat);
#endif
   
   /* Rotation of all segments */
   for(i=0;i<24;i++) {
      
      v2[i].SetXYZ(x[i],y[i],z[i]);
      v2[i].RotateZ(-alpha-alpha_offset);
      v2[i].RotateY(theta);
      v2[i].RotateZ(phi);
      

      /* If TVector3 vdirec is given: write v2[] values to vdirec[] */  
      if(vdirec!=0) {
	 vdirec[i]=v2[i];
      }
      
      //    r[i]  = dist_TA_MB;
      r[i]  = v2[i].Mag();
      th[i] = v2[i].Theta();
      ph[i] = v2[i].Phi();    
      
      if(ph[i]<0) {
	 ph[i] = 2*PI+ph[i];
      }
      else {
	 ph[i] = ph[i];
    }
      
      ph[i] = ph[i]/PI*180.0;
      th[i] = th[i]/PI*180.0;
      
   }
   
   /* *************************************** END of main POSITIONING code ************************************* */
   
   
   /* Output options: 1: print values in file; 2: print values on terminal */
   if(outopt==1) {
      FILE* ofp;
      ofp=fopen("cluster_xyz.dat","wb");
      if(ofp!=NULL) {
	 for(i=0; i<24; i++) {
	    if (i==0) {
	       fprintf(ofp,"%15e %15e %15e\n", v2[i].X()+10., v2[i].Y(), v2[i].Z());
	    }
	    if (i%8!=3) {
	       fprintf(ofp,"%15e %15e %15e\n", v2[i].X(), v2[i].Y(), v2[i].Z());
	    }
	    if (i%8==7) {
	       fprintf(ofp,"\n");
	    }
	 }
	 printf("\n\nWrote values to file cluster_xyz.dat\n\n");
	 fclose(ofp);
      }
   }
   
   if(outopt==2) {
      for(i=0;i<24;i++) {
	 printf("x[%2d]: %5.1f, y[%2d]: %5.1f, z[%2d]: %5.1f -> x[%2d]: %5.1f, y[%2d]: %5.1f, z[%2d]: %5.1f -> r[%2d]: %5.1f, th[%2d]: %5.1f, ph[%2d]: %5.1f\n", 
		i, x[i], i, y[i], i, z[i],i,v2[i].X(),i,v2[i].Y(),i,v2[i].Z(),i,r[i],i,th[i],i,ph[i]);
      }
   }

	if(outopt==3) {
		char corename[4]="abc";
		printf("Core\tTheta\tPhi\tTarget Dist\n");
		for(i=0;i<24;i++){
			if(i%8==0){
				printf("%c\t%5.1f\t%5.1f\t%5.1f\n",corename[i/8],th[i],ph[i],r[i]);
			}
			else printf("\t%5.1f\t%5.1f\t%5.1f\n",i,th[i],ph[i],r[i]);

		}
	}
	
	if(outopt==4) {
		FILE *ofp, *ofth, *ofph;
		char corename[4]="abc";
		ofp=fopen("cluster_xyz.dat","a+b");
		ofph=fopen("phi.dat","a+b");
		ofth=fopen("theta.dat","a+b");
		if(ofp!=NULL) {
			for(i=0;i<24;i++){
				if(i%8==0){
					fprintf(ofp,"%3.3i%3.3i%c\t%5.1f\t%5.1f\t%5.1f\n",(int)TMath::Abs(theta*TMath::RadToDeg()),(int)TMath::Abs(phi*TMath::RadToDeg()),corename[i/8],th[i],ph[i],r[i]);
					fprintf(ofth,"%5.1f,",th[i]);
					fprintf(ofph,"%5.1f,",ph[i]);
				}
			}
		}
		printf("Updated values on file cluster_xyz.dat, theta.dat and phi.dat\n");
		fclose(ofp); fclose(ofth), fclose(ofph);
	}
   
   /* Draw option */
   if(drawopt==1) {
      
 	  TH3F* h = new TH3F("h","Position of cluster in MB system",200,-110,110,200,-110,110,200,-110,110);
	  TFile* rf = new TFile("geometry.root","RECREATE");
      
      for(i=0;i<24;i++) {
	 if((i+5)%8!=0) {
	    if(i<8) {
	       h->SetMarkerColor(4);
	    }
	    else if(i<16) {
	       h->SetMarkerColor(3);
	    }
	    else {
	       h->SetMarkerColor(2);
	    }
	    h->Fill(v2[i].X(),v2[i].Y(),v2[i].Z());
	 }
    }
      h->SetMarkerStyle(20);
      h->SetMarkerSize(2);
      h->SetXTitle("x");
      h->SetYTitle("y");
      h->SetZTitle("z (beam direction)");
      h->Draw();
	  h->Write();
	  rf->Close();
   }
   
   return 0;
   
}

/*****************************************************************************/
/* Get cluster coordinate systems                                            */

int get_cluster_coordinate_systems(double theta, double phi, double alpha,
				   double dist_TA_MB, double dist_CORE_CORNER,
				   double dist_CORE_LINE,
				   double dist_FRONT_BACK, double tilt_angle,
				   double tri_cap_thick, double det_cap_thick,
				   double airgap_tri_det_cap, int outopt,
				   TVector3* coordv = 0) {

   /* dist_TA_MB = distance target-MB = 115               */
   /* dist_CORE_CORNER = SL = 34                          */
   /* dist_CORE_LINE = SL2 = 29.5                         */
   /* dist_FRONT_BACK = DETECTOR_LENGTH = 78              */
   /* tilt_angle = TILT_ANGLE = 1/13.                     */
   /* tri_cap_thick = THICKNESS_TRIPLE_CAP = 1            */
   /* det_cap_thick = THICKNESS_DET_CAP = 0.7             */
   /* airgap_tri_det_cap = AIRGAP_TRIPLE_DET_CAP = 1      */
   /* dist_TA_det_mean   = DISTANCE_TARGET_DET_MEAN = 160 */
   /* positions of points 0, 1, 2 and 3 in PRELIMINARY tilted coord.sys. of detector A */
   /* 0: core position */
   /* 1: corner of segment a3 */
   /* 2: position between segments a1 and a2 */
   /* 3: core position on backside of detector */
   int i;
   double pos_A_xp[4], pos_A_yp[4], pos_A_zp[4]; 
   
   /* Position 0 */
   pos_A_xp[0] = dist_CORE_CORNER   * cos(tilt_angle);
   pos_A_yp[0] =                                  0;
   pos_A_zp[0] = dist_CORE_CORNER   * sin(tilt_angle);
   
   /* Position 1 */
   pos_A_xp[1] = dist_CORE_CORNER*2 * cos(tilt_angle);
   pos_A_yp[1] =                                    0;
   pos_A_zp[1] =                                    0;
   
   /* Position 2 */
   pos_A_xp[2] =                                       pos_A_xp[0];
   pos_A_yp[2] =                                   -dist_CORE_LINE;
   pos_A_zp[2] =                                       pos_A_zp[0];
   
   /* Position 3 */
   pos_A_xp[3] = dist_FRONT_BACK   * sin(tilt_angle) + pos_A_xp[0];
   pos_A_yp[3] =                                               0;
   pos_A_zp[3] = dist_FRONT_BACK   * cos(tilt_angle) + pos_A_zp[0];
   
   
   /* Shift coordinate system to standard MINIBALL system */
   double pos_A_x_shift, pos_A_y_shift, pos_A_z_shift;
   /* x shift */
   pos_A_x_shift = det_cap_thick;
   /* y shift */
   pos_A_y_shift =             0;
   /* z shift */
   pos_A_z_shift = - (tri_cap_thick + airgap_tri_det_cap
		      + det_cap_thick * sin(tilt_angle) 
		      + det_cap_thick / cos(tilt_angle) ) + dist_TA_MB;
   
   /* Apply shift to all 4 positions */
   double pos_A_xf[4], pos_A_yf[4], pos_A_zf[4];
   for(i=0; i<4; i++) {
      pos_A_xf[i] = pos_A_xp[i] + pos_A_x_shift;
      pos_A_yf[i] = pos_A_yp[i] + pos_A_y_shift;
      pos_A_zf[i] = pos_A_zp[i] + pos_A_z_shift;
   }
   
   /* Assign positions for detector A (4 for each detector -> 12) */
   double cluster_x[12], cluster_y[12], cluster_z[12];
   for(i=0; i<4; i++) {
      cluster_x[i] = pos_A_xf[i];
      cluster_y[i] = pos_A_yf[i];
      cluster_z[i] = pos_A_zf[i];
   }
   
   
   /* Rotate 4 positions of det A to get det B */
   double rot_angle_B;
   TVector3 detB_v[4];
   /* Rotation angle of detector B */
   rot_angle_B = 2 * PI / 3;
   
   for(i=0; i<4; i++) {
      detB_v[i].SetXYZ(cluster_x[i], cluster_y[i], cluster_z[i]);
      detB_v[i].RotateZ(-rot_angle_B);
      cluster_x[i+4] = detB_v[i].X();
      cluster_y[i+4] = detB_v[i].Y();
      cluster_z[i+4] = detB_v[i].Z();
   }
   
   /* Rotate 4 positions of det A to get det C */
   double rot_angle_C;
   TVector3 detC_v[4];
   /* Rotation angle of detector B */
   rot_angle_C = 4 * PI / 3;
   
   for(i=0; i<4; i++) {
      detC_v[i].SetXYZ(cluster_x[i], cluster_y[i], cluster_z[i]);
      detC_v[i].RotateZ(-rot_angle_C);
      cluster_x[i+8] = detC_v[i].X();
      cluster_y[i+8] = detC_v[i].Y();
      cluster_z[i+8] = detC_v[i].Z();
   }
   
   /* If outopt==3 */
  if(outopt==3) {
     /* Write values on terminal... */
     printf("rot_angle_B: %f, rot_angle_C: %f\n", rot_angle_B, rot_angle_C);
     for(i=0; i<4; i++) {
	printf("cluster_x[%2d]: %6.1f, -> cluster_x[%2d]: %6.1f, -> cluster_x[%2d]: %6.1f\n",i,cluster_x[i],i+4,cluster_x[i+4],i+8,cluster_x[i+8]);
	printf("cluster_y[%2d]: %6.1f, -> cluster_y[%2d]: %6.1f, -> cluster_y[%2d]: %6.1f\n",i,cluster_y[i],i+4,cluster_y[i+4],i+8,cluster_y[i+8]);
	printf("cluster_z[%2d]: %6.1f, -> cluster_z[%2d]: %6.1f, -> cluster_z[%2d]: %6.1f\n",i,cluster_z[i],i+4,cluster_z[i+4],i+8,cluster_z[i+8]);
     }   
     /* ... and in file */
     FILE* ofp;
     ofp=fopen("cluster_positions_xyz_NOT_rotated.dat","w");
     if(ofp!=NULL) {
	for(i=0; i<12; i++) {
	   if(i%4==0) {
	      fprintf(ofp,"%15e %15e %15e\n", cluster_x[i], cluster_y[i]+10., cluster_z[i]);
	   }
	   fprintf(ofp,"%15e %15e %15e\n", cluster_x[i], cluster_y[i], cluster_z[i]);
	   if (i%4==3) {
	      fprintf(ofp,"\n");
	   }
	}
	printf("\n\nWrote values to file cluster_positions_xyz_NOT_rotated.dat\n\n");
	fclose(ofp);
     }
     
     return 0;
  }
   
   /* Angles in rad */
   alpha = alpha/180.0*PI;  
   phi   = phi/180.0*PI;
   theta = theta/180.0*PI;
   
   /* ********* */
   /* IMPORTANT */
   /* ********* */
   /* Update theta and phi to be angles in the standard MINIBALL frame of
    * reference. Theta and phi passed to this routine are values read from the
    * MINIBALL frame (HARDWARE), which correspond to value in a system with
    * the z-axis pointing upward, i.e. the x-direction of the MINIBALL frame
    * of reference (FoR). The following lines transform the theta and phi
    * values. */
   
   /* Check if phi > PI -> rotation angles change */
   if(phi>PI) {
      phi = 2*PI - phi;
      theta = -theta;
   }
   
   TVector3 trans;
   trans.SetXYZ(1,0,0);
   trans.RotateY(-phi);
   trans.RotateX(-theta);
   
   theta=trans.Theta();
   phi=trans.Phi();
   
   
   /* Done transforming theta and phi */

   /* Find alpha offset */
   
   TVector3 vd,va,vn;
   const TVector3 ex(1,0,0);
   
   vd.SetXYZ(0,0,1);
   va.SetXYZ(1,0,0);
   
   vd.RotateY(theta);
   vd.RotateZ(phi);
   va.RotateY(theta);
   va.RotateZ(phi);
   
   vn=ex-vd*(ex*vd);
   vn.SetMag(1.);
   
   double spat=vn*(va.Cross(vd));
   double alpha_offset=va.Angle(vn);  //*spat;
   if (spat<0) alpha_offset*=-1;
   
#if 0
   printf("vn %f %f %f\n",vn.X(),vn.Y(),vn.Z());
   printf("va %f %f %f\n",va.X(),va.Y(),va.Z());
   printf("angle %f\n",alpha_offset*180./PI);
   printf("spat %f\n",spat);
#endif
   
   /* Rotation of all positions */
   TVector3 v2[12];
   for(i=0;i<12;i++) {
      
      v2[i].SetXYZ(cluster_x[i],cluster_y[i],cluster_z[i]);
      v2[i].RotateZ(-alpha-alpha_offset);
      v2[i].RotateY(theta);
      v2[i].RotateZ(phi);
      
   }
   
   /* Get unity vectors in Joerg's coord. system */
   int v_off = 0;
   
   for(i=0; i<3; i++) {
      
      TVector3 ex, ey, ez;
      ex = v2[(1+v_off)] - v2[(0+v_off)];
      ex = ex.Unit();
      ey = v2[(2+v_off)] - v2[(0+v_off)];
      ey = ey.Unit();
      ez = v2[(3+v_off)] - v2[(0+v_off)];
      ez = ez.Unit();
      
      /* Write values to coordv[] */  
      if(coordv!=0) {
	 coordv[0+v_off] = v2[(0+v_off)];
	 coordv[1+v_off] = ex;
	 coordv[2+v_off] = ey;
	 coordv[3+v_off] = ez;
      }
      
      /* Increment v2 offset */
      v_off+=4;
      
   }
   
   
   /* Output options: 1: print values in file; 2: print values on terminal */
   if(outopt==1) {
      FILE* ofp;
      ofp=fopen("cluster_positions_xyz.dat","w");
      if(ofp!=NULL) {
	 for(i=0; i<12; i++) {
	    fprintf(ofp,"%15e %15e %15e\n", v2[i].X(), v2[i].Y(), v2[i].Z());
	    if (i%4==3) {
	       fprintf(ofp,"\n");
	    }
	 }
	 printf("\n\nWrote values to file cluster_positions_xyz.dat\n\n");
      fclose(ofp);
      }
   }
   
   if(outopt==2) {
      for(i=0;i<12;i++) {
	 printf("x[%2d]: %5.1f, y[%2d]: %5.1f, z[%2d]: %5.1f -> x[%2d]: %5.1f, y[%2d]: %5.1f, z[%2d]: %5.1f\n", 
		i, cluster_x[i], i, cluster_y[i], i, cluster_z[i],i,v2[i].X(),i,v2[i].Y(),i,v2[i].Z());
	 if(coordv != 0) {
	    printf("coordv[%d].Mag(): %f, coordv[%d].X(): %f\n", i, coordv[i].Mag(), i, coordv[i].X());
	 }
      }
   }
   
  return 0;
   
}

/*****************************************************************************/
/* Shift position                                                            */
int shift_position(double r, double phi, double z, TVector3* coordv,
		   TVector3* outv) {

   /* Calculate x and y from r and phi */
   double x, y;
   
   /* Transform phi to rad */
   phi = phi/180.0*PI;
   
   x = r * cos(phi);
   y = r * sin(phi);
   
   /* x shift */
   *outv = coordv[0] + x*coordv[1];
   /* y shift */
   *outv = *outv + y*coordv[2];
   /* z shift */
   *outv = *outv + z*coordv[3];
   
   return 0;
}

/*****************************************************************************/
/* Calculate maximum depth for a given gamma-ray energy based on the         */
/* simulations of Christoph Gund                                             */
double maxtiefe(double energy) {
   
   static double depth[12]={0., 0.39, 0.91, 1.59, 2.25, 2.51, 2.61, 2.69,
	2.74, 2.80, 2.81, 2.82};
   static double ener[12]={0., 100., 150., 225., 350., 500., 700., 1000.,
	1300., 1800., 2500., 10000.};
   double wert;
   int index = 0;
   
   while(energy>ener[index]) index++;
   /* Wert=0.; */
   
   /* 25/06/2003: check index number (ON) */
   /* ATTENTION: function only works till energies of 10000keV = 10MeV */
   if (index > 11) return(-1);
   
   
   wert=(depth[index]*(energy-ener[index-1]) +
	 depth[index-1]*(ener[index]-energy)) / (ener[index]-ener[index-1]);
   return(wert);
}
