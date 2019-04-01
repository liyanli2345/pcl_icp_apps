
#include <iostream> 
#include <string> 
#include <pcl/io/pcd_io.h> 
#include <pcl/point_types.h> 
#include <pcl/visualization/pcl_visualizer.h> 

using namespace std; 

int main()
{
 
//***************************read PCD file*****************************************
 
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_target(new pcl::PointCloud<pcl::PointXYZ>());
    
    std::string dir = "/home/lyl/filebag/points_ground/";
    std::string filename_target = "1553504186.026767000.pcd";
    
    boost::shared_ptr< pcl::visualization::PCLVisualizer > viewer(new pcl::visualization::PCLVisualizer("Viewer_points_ground"));
    //背景颜色
    viewer->setBackgroundColor(255,255,255);
    //创建窗口
    int vp;
    viewer->createViewPort(0.0, 0.0, 1.0, 1.0, vp);
     
    if (pcl::io::loadPCDFile<pcl::PointXYZ> ((dir+filename_target), *cloud_target) == -1){
		//* load the file 
		PCL_ERROR ("Couldn't read target PCD file \n"); 
		return (-1); 
	} 

    printf("Loaded %d data points from original PCD\n",
    cloud_target->size());
    //原始点云绿色
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> singleColor(cloud_target,255,0,0);//0-255  设置成 色
    viewer->addPointCloud<pcl::PointXYZ>(cloud_target, singleColor, "sample");//显示点云，其中fildColor为颜色显示
    
	while(!viewer->wasStopped()) 
	viewer->spinOnce(100); 
	return (0); 
}
