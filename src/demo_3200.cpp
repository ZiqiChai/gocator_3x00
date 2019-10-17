//C++
#include <stdio.h>
#include <stdlib.h>

//OpenCV
#include <opencv2/opencv.hpp>

//boost
#include <boost/thread/thread.hpp>

//PCL
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/transforms.h>
//Customed
#include "gocator3200.h"

//main
int main(int argc, char **argv)
{
	Gocator3200::Device device("192.168.1.10");
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	device.getSingleSnapshot(*cloud);
	std::cout<<"point cloud size:"<<cloud->points.size()<<std::endl;

	//可视化
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("Cloud"));
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color (cloud, 0, 255, 0);
	viewer->addPointCloud(cloud, "cloud");
	viewer->addCoordinateSystem(10);
	while(!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100));
	}
	viewer->updatePointCloud(cloud, "cloud");
	viewer->removePointCloud("cloud");
	viewer->removeAllPointClouds();
	viewer->close();
	device.stop();

	return 0;
}