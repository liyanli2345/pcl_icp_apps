
#include <iostream> 
#include <string> 
#include <pcl/io/pcd_io.h> 
#include <pcl/point_types.h> 
#include <pcl/visualization/pcl_visualizer.h> 

using namespace std; 

int main (int argc, char** argv){ 
    typedef pcl::PointXYZ PointT;
    pcl::PointCloud<PointT>::Ptr cloud_target (new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr cloud_source (new pcl::PointCloud<PointT>);

        std::string dir = "/home/lyl/filebag/";
        std::string filename_target = "forest_1_all_clusters.pcd";
        std::string filename_source = "forest_2_all_clusters.pcd";

    if (pcl::io::loadPCDFile<PointT> ((dir+filename_target), *cloud_target) == -1){
		//* load the file 
		PCL_ERROR ("Couldn't read target PCD file \n"); 
		return (-1); 
	} 
	if (pcl::io::loadPCDFile<PointT> ((dir+filename_source), *cloud_source) == -1){ 
		//* load the file 
		PCL_ERROR ("Couldn't read source PCD file \n"); 
		return (-1); 
	} 

    printf("Loaded %d target data points from PCD\n",
    cloud_target->size());

    printf("Loaded %d source data points from PCD\n",
    cloud_source->size());

	pcl::visualization::PCLVisualizer viewer("Cloud viewer"); 
    viewer.setCameraPosition(0,-13,6,0,0,1);
    viewer.addCoordinateSystem(0.3);

    //源点云绿色
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> singleColor(cloud_source,0,255,0);//0-255  设置成绿色
    viewer.addPointCloud<pcl::PointXYZ>(cloud_source, singleColor, "sample");//显示点云，其中fildColor为颜色显示

    viewer.addPointCloud(cloud_target);
	while(!viewer.wasStopped()) 
	viewer.spinOnce(100); 
	return (0); 
}
