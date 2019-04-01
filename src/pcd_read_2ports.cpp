#include<iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>


int main(int argc, char** argv)
{
    typedef pcl::PointXYZ PointT;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source(new pcl::PointCloud<pcl::PointXYZ>);

    std::string dir = "/home/lyl/pcd_read/build/";
    std::string filename1 = "test_pcd1.pcd";
    std::string filename2 = "test_pcd2.pcd";

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


    pcl::visualization::PCLVisualizer viewer("pcd viewer");//给显示窗口命名，CloudViewer
    viewer.setBackgroundColor(0, 0, 0);
    viewer.setCameraPosition(0,-13,6,0,0,1);
    viewer.addCoordinateSystem(0.3);

    int v1(0);
    int v2(1);
    viewer.createViewPort(0.0, 0.0, 0.5, 1.0, v1);
    viewer.createViewPort(0.5, 0.0, 1.0, 1.0, v2);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_target_white(cloud_target,255,255,255);
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_source_green(cloud_source,255,0,0);
    viewer.addPointCloud(cloud_target, cloud_target_white, "cloud_target_v1", v1);
    viewer.addPointCloud(cloud_source, cloud_source_green, "cloud_sourve_v2", v2);

    while(!viewer.wasStopped())
        viewer.spinOnce(100);
        return (0);
}

