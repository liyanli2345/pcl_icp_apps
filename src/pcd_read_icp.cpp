#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/ia_fpcs.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    typedef pcl::PointXYZ PointT;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source(new pcl::PointCloud<pcl::PointXYZ>);

    std::string dir = "/home/lyl/filebag/";
    std::string filename1 = "city_1_original_point.pcd";//target
    std::string filename2 = "city_2_original_point.pcd";//source

	//*cloud,指针的内容是文件内容，记得标明点云类型<pcl::PointXYZ>
        if (pcl::io::loadPCDFile<PointT> ((dir+filename1), *cloud_target) == -1)
	{
		//pcl有专门的报错函数PCL_ERROR
		PCL_ERROR("Couldn't read file test_pcd1.pcd\n");
		return(-1);
	}
        printf("Loaded %d data points from target PCD\n",
            cloud_target->width * cloud_target->height);

        if (pcl::io::loadPCDFile<PointT> ((dir+filename2), *cloud_source) == -1)
        {
                //pcl有专门的报错函数PCL_ERROR
                PCL_ERROR("Couldn't read file test_pcd2.pcd\n");
                return(-1);
        }
        printf("Loaded %d data points from source PCD\n",
            cloud_source->width * cloud_source->height);

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source1(new pcl::PointCloud<pcl::PointXYZ>);  
        cloud_source1 = cloud_source; 
        for (int i = 0; i < cloud_source1->points.size (); ++i){
                cloud_source1->points[i].x = cloud_source1->points[i].x + 0.7f;
                cloud_source1->points[i].y = cloud_source1->points[i].y + 0.7f;
                cloud_source1->points[i].z = cloud_source1->points[i].z + 0.7f;
        }
    //run icp
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_source);
    icp.setInputTarget(cloud_target);
    pcl::PointCloud<pcl::PointXYZ> Final;
    icp.align(Final);
   
    //run fpcs
    // pcl::registration::FPCSInitialAlignment<pcl::PointXYZ, pcl::PointXYZ> fpcs;
    // fpcs.setInputSource(cloud_source);
    // fpcs.setInputTarget(cloud_target);
    // fpcs.setNumberOfThreads (1);
    //     fpcs.setApproxOverlap (0.4f);
    //     fpcs.setDelta (1.f, true);
    //     fpcs.setNumberOfSamples (100);
    // pcl::PointCloud<pcl::PointXYZ> Final;
    // fpcs.align(Final);

//     //施加固定变换
//     Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();
//     transform_1 <<  0.983477,-0.114384,-0.140321,-0.448652,
//                     0.109203,0.993041,-0.044103,-0.739084,
//                     0.144389,0.0280508,0.989123,-1.23768,
//                     0,0,0,1;

//     // Print the transformation  打印出这个变换矩阵
//     printf ("Method #1: using a Matrix4f\n");
//     std::cout << transform_1 << std::endl;
//     pcl::PointCloud<pcl::PointXYZ>::Ptr aligened_cloud(new pcl::PointCloud<pcl::PointXYZ>);
//     pcl::transformPointCloud (*cloud_source, *aligened_cloud, transform_1);

    //类型转换pcl::PointCloud<pcl::PointXYZ>转为pcl::PointCloud<pcl::PointXYZ>::Ptr
    pcl::PointCloud<pcl::PointXYZ>::Ptr aligened_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    aligened_cloud = Final.makeShared();    

    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
    icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;

//     std::cout << "has converged:" << fpcs.hasConverged() << " score: " <<
//     fpcs.getFitnessScore() << std::endl;
//     std::cout << fpcs.getFinalTransformation() << std::endl;

// //display pointclouds in v1 viewport before icp
//     //target is white, source is green
//显示
    pcl::visualization::PCLVisualizer viewer("pcd viewer");//给显示窗口命名，CloudViewer
    viewer.setBackgroundColor(255, 255, 255);
    viewer.setCameraPosition(0,-13,6,0,0,1);
    viewer.addCoordinateSystem(0.3);

    int v1(0);
    int v2(1);
    viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);
    viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2);
    // viewer.setBackgroundColor (255, 255, 255, v1);
    // viewer.setBackgroundColor (255, 255, 255, v2);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target_white(cloud_target,255,255,0);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_source_red(cloud_source1,255,0,0);

    viewer.addPointCloud(cloud_target, cloud_target_white, "cloud_target_v1", v1);
    viewer.addPointCloud(cloud_source, cloud_source_red, "cloud_sourve_v1", v1);
//dispay aligened point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> aligened_cloud_green(aligened_cloud,0,255,0);
    viewer.addPointCloud(cloud_target, cloud_target_white, "cloud_target_v2", v2);
    viewer.addPointCloud(aligened_cloud, aligened_cloud_green, "Final_green_v2", v2);

    while(!viewer.wasStopped())
        viewer.spinOnce(100);
        return (0);
}

