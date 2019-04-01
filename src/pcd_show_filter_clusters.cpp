
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <string>  
 
using namespace std;
/*bool next_iteration = false;
void keyboardEventOccurred (const pcl::visualization::KeyboardEvent& event,
                       void* nothing)
{  //使用空格键来增加迭代次数，并更新显示
  if (event.getKeySym()=="space"&&event.keyDown())
    next_iteration = true;
}
*/
int min_num_cluster = 40;

int main()
{
 
//***************************read PCD file*****************************************
 
	pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>());
    
    //输入点云路径
    string addr = "/home/lyl/filebag/clusters_000010/";
    string filename;
    //待处理点云个数
    int num = 106;
    
    boost::shared_ptr< pcl::visualization::PCLVisualizer > viewer(new pcl::visualization::PCLVisualizer("Viewer_filter_clusters"));
    //背景颜色
    viewer->setBackgroundColor(255,255,255);
    //创建窗口
	int vp;
	viewer->createViewPort(0.0, 0.0, 1.0, 1.0, vp);
    //显示坐标系
    //注册按键回调函数
    //viewer->registerKeyboardCallback (&keyboardEventOccurred, (void*) NULL);

    for(int i = 0;i <= num; i++)
    {
        //filename 为点云文件名
        if(i<10)
            filename = addr + "cloud_00000" + boost::chrono::to_string(i) + ".pcd";
            else if (i>=10&&i<100) {
                filename = addr + "cloud_0000" + boost::chrono::to_string(i) + ".pcd";
            }
                else
                filename = addr + "cloud_000" + boost::chrono::to_string(i) + ".pcd";
    
        //读取点云
        pcl::io::loadPCDFile(filename, *source);
        //剔除点数小于min_num_cluster
        if(source->size()>=min_num_cluster)
        {          
            //输出读取的点云个数
            printf("Loaded %d target data points from PCD %d\n",source->size(),i);

            //设置点云颜色
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_color(source, 255,0,255);

            viewer->addPointCloud<pcl::PointXYZ>(source, source_color, boost::chrono::to_string(i), vp);
        
            //改变显示点云的尺寸
            viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "source");
        }
    }
        /*while (!viewer->wasStopped()){
        viewer->spinOnce();
        //按下空格键
        if(next_iteration){
            
        next_iteration = false;
    }
    */    
    viewer->addCoordinateSystem(1.0);
    viewer->spin();
}
