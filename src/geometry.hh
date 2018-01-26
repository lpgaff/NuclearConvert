#ifndef GEOMETRY_H
#define GEOMETRY_H 0
int get_positions_segments(double theta, double phi, double alpha, double dist_CORE_CORNER, double dist_TA_MB, double ratio, int drawopt, int outopt, TVector3* vdirec = 0);
int get_cluster_coordinate_systems(double theta, double phi, double alpha, double dist_TA_MB, double dist_CORE_CORNER, double dist_CORE_LINE, double dist_FRONT_BACK, double tilt_angle, double tri_cap_thick, double det_cap_thick, double airgap_tri_det_cap, int outopt, TVector3* coordv = 0);
int shift_position(double r, double phi, double z, TVector3* coordv, TVector3* outv);
double maxtiefe(double energy);
#endif
