#include <iostream>
#include <string>
 // opencv library
#include <opencv2/opencv.hpp>
 // PCL library
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
 

 
 // Define the point cloud type
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;
 
 // camera internal reference
const double camera_factor=5000;
const double camera_cx=319.5;
const double camera_cy=239.5;
const double camera_fx=481.20;
const double camera_fy=-480;
 
 // main function
int main(int argc,char** argv)
{
	 // Read rgb image and depth image, and converted to point cloud
	 // Image matrix
	cv::Mat rgb, depth;
	rgb = cv::imread("rgbd_dataset_freiburg1_xyz/rgb/1305031102.211214.png");
    depth = cv::imread("rgbd_dataset_freiburg1_xyz/depth/1305031102.194330.png", -1);
	 //Point cloud variable
	 //Create a null cloud using smart pointers. This kind of pointer will be automatically released when it is used up.
	PointCloud::Ptr cloud(new PointCloud);
	
	 // traverse the depth map
	for(int m = 0; m<depth.rows; m++) {
		for(int n = 0; n<depth.cols; n++) {
		 // Get the value at (m, n) in the depth map
		ushort d = depth.ptr<ushort>(m)[n];
		 
		// if(d == 0)
		// 	continue;
		//  //d has a value, then add a point to the point cloud
		PointT p;//p is a PointXYZRGBA structure variable
		//  // Calculate the space coordinates of this point
		p.z = double(d)/camera_factor;
		p.x = (n-camera_cx)*p.z/camera_fx;
		p.y = (m-camera_cy)*p.z/camera_fy;
		//  // Get its color from the rgb image
		//  //rgb is a three-channel BGR format, so get the colors in the following order.
		std::cout<<rgb.ptr<uchar>(m)[n*3]<<std::endl;
		p.b = rgb.ptr<uchar>(m)[n*3];
		p.g = rgb.ptr<uchar>(m)[n*3+1];
		p.r = rgb.ptr<uchar>(m)[n*3+2];
		//  //Add p to the point cloud
		cloud->points.push_back(p);
		}
	}
	 //Set and save point cloud
	cloud->height = 1;
	cloud->width = cloud->points.size();
	std::cout<< "point cloud size=" << cloud->points.size() << std::endl;
	cloud->is_dense = false;
	//pcl::io::savePCDFile("./pointcloud2.pcd", *cloud);
	pcl::io::savePLYFile("./pointcloud.ply", *cloud);
	cloud->points.clear();
	std::cout<< "Point cloud saved." << std::endl;
	
	return 0;
}