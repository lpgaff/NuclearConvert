#include <cmath>
#include <iostream>

using namespace std;

// Program to calulate angle of cd detector strips
// Liam Gaffney 12/01/09

int main() {
  const double PI = 4*atan(1);

  // Set distances
  double cd_target_dist_mm = 32.5;
  cout << "Enter CD to target distance [in mm]: ";
  cin >> cd_target_dist_mm;
  double cd_target_dist = cd_target_dist_mm * 1e-3;
  double radius_hole = 0.0090;
  double strip_seperation = 0.0020;
  double active_region = 0.0019;

  // Calculate angle
  cout << "Strip Number" << "\t\t" << " Angle\t" << "Lower\tUpper" << endl;
  for(int i=1;i<=16;i++) {
    double startangle = atan((radius_hole+((strip_seperation-active_region)/2)+(16-i)*strip_seperation)/ cd_target_dist);
	double endangle = atan((radius_hole+((strip_seperation+active_region)/2)+(16-i)*strip_seperation)/ cd_target_dist);
	cout << "Strip " << i-1 << ": \t" << "Average: " << (startangle+endangle)*(180/PI)/2. << "  \t" << startangle*(180/PI) << "\t to   " << endangle*(180/PI) << endl;
	}
  for(int i=16;i>=1;i--) {
	double startangle = atan((radius_hole+((strip_seperation-active_region)/2)+(16-i)*strip_seperation)/ cd_target_dist);
	double endangle = atan((radius_hole+((strip_seperation+active_region)/2)+(16-i)*strip_seperation)/ cd_target_dist);
	if(i>1){
		cout << (startangle+endangle)*(180/PI)/2. << ",";
		}
	if(i==1){
		cout << (startangle+endangle)*(180/PI)/2. << endl;
		}
	}

  return 0;
}
