#include <ros/ros.h>
#include <iostream>
#include <sensor_msgs/PointCloud2.h>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>


// 备用，接收其余格式点云
struct MyPointXYZRGB {
    PCL_ADD_POINT4D;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
} EIGEN_ALIGN16;
POINT_CLOUD_REGISTER_POINT_STRUCT(MyPointXYZRGB,
                                  (float, x, x)(float, y, y)(float, z, z)(uint8_t, r, r)
                                          (uint8_t, g, g)(uint8_t, b, b))                                       

using PointType = MyPointXYZRGB;
ros::Publisher pubPC;


int main(int argc, char **argv) {
    ros::init(argc, argv, "pcd_viewer");
    ros::NodeHandle nh;
    
    pubPC = nh.advertise<sensor_msgs::PointCloud2>("/lidar_points", 1);
    pcl::PointCloud<pcl::PointXYZRGB> inputCloud;
    sensor_msgs::PointCloud2 outputMsg;

    pcl::io::loadPCDFile ("color_map.pcd", inputCloud); // your pcd path

    // pcl::PointCloud<MyPointXYZRGB> processedCloud;
    // for(int i = 0; i < inputCloud.points.size(); ++i)
    // {
    //     RsPointXYZRGB tempPoint;
    //     tempPoint.x = inputCloud.points[i].x;
    //     tempPoint.y = inputCloud.points[i].y;
    //     tempPoint.z = inputCloud.points[i].z;
    //     tempPoint.r = (inputCloud.points[i].rgba >> 16) & 0x0000ff;
    //     tempPoint.g = (inputCloud.points[i].rgba >> 8)  & 0x0000ff;
    //     tempPoint.b = inputCloud.points[i].rgba & 0x0000ff;
    //     processedCloud.points.push_back(tempPoint);

    // }

    pcl::toROSMsg(inputCloud, outputMsg);
    outputMsg.header.frame_id = "map";//this has been done in order to be able to visualize our PointCloud2 message on the RViz visualizer
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pubPC.publish(outputMsg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    ros::spin();
    return 0;
}
