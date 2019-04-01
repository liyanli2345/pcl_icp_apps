cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(pcd_read)

find_package(PCL 1.9.1 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(Eigen3)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable (pcd_read_1port src/pcd_read_1port.cpp)
target_link_libraries (pcd_read_1port ${PCL_LIBRARIES})

add_executable (pcd_read_2ports src/pcd_read_2ports.cpp)
target_link_libraries (pcd_read_2ports ${PCL_LIBRARIES})

add_executable (pcd_read_icp src/pcd_read_icp.cpp)
target_link_libraries (pcd_read_icp ${PCL_LIBRARIES})

add_executable (pcd_show_all_clusters src/pcd_show_all_clusters.cpp)
target_link_libraries (pcd_show_all_clusters ${PCL_LIBRARIES})

add_executable (pcd_show_filter_clusters src/pcd_show_filter_clusters.cpp)
target_link_libraries (pcd_show_filter_clusters ${PCL_LIBRARIES})

add_executable (pcd_read_original src/pcd_read_original.cpp)
target_link_libraries (pcd_read_original ${PCL_LIBRARIES})

add_executable (pcd_show_ground_points src/pcd_show_ground_points.cpp)
target_link_libraries (pcd_show_ground_points ${PCL_LIBRARIES})

add_executable (pcd_save_all_filter_clusters_pcd src/pcd_save_all_filter_clusters_pcd.cpp)
target_link_libraries (pcd_save_all_filter_clusters_pcd ${PCL_LIBRARIES})

add_executable (pcd2ply src/pcd2ply.cpp)
target_link_libraries (pcd2ply ${PCL_LIBRARIES})




