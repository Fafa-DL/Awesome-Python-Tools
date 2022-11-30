// #include <sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ros/ros.h>
#include <opencv/cv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <rosbag/bag.h>
#include <rosbag/view.h>

using namespace std;

ros::Publisher pubPC;
ros::Subscriber sub_img;
string img_topic = "";
string save_path = "";
string bag_path = "";

void check_path(string path)
{
    if (access(path.c_str(), 0) != -1)
    {
        rmdir(path.c_str());
    } 
    else
    {
        mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
		
}

void img_callback(const sensor_msgs::CompressedImageConstPtr &msg)
{
    cv::Mat image_get;
    double  img_rec_time;
    std::vector<int> compression_params;
    // compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    // compression_params.push_back(6);
    try
    {
        cv_bridge::CvImagePtr cv_ptr_compressed = cv_bridge::toCvCopy( msg, sensor_msgs::image_encodings::BGR8 );
        img_rec_time = msg->header.stamp.toSec();
        image_get = cv_ptr_compressed->image;
        cv_ptr_compressed->image.release();
    }
    catch ( cv_bridge::Exception &e )
    {
        printf( "Could not convert from '%s' to 'bgr8' !!! ", msg->format.c_str() );
    }
    cv::Rect rect(0, 0, 2880, 1430);
    image_get = image_get(rect);
    ROS_INFO( "Convert '%s' ", std::to_string(img_rec_time).c_str() );
    string filename = save_path + std::to_string(img_rec_time) + ".jpg";
    cv::imwrite(filename, image_get);
}


int main(int argc, char **argv) {
    // ros::init(argc, argv, "bag_to_img");
    // ros::NodeHandle nh;
    // ROS_INFO("Listening from %s", img_topic.c_str());
    // sub_img = nh.subscribe(img_topic, 1000000, img_callback);
    
    // ros::spin();

    check_path(save_path);
    rosbag::Bag bag;
    bag.open(bag_path);
    std::vector<std::string> topics;
    topics.push_back(img_topic);
    rosbag::View view(bag, rosbag::TopicQuery(topics));
    for (auto m : view) 
    {
        sensor_msgs::CompressedImageConstPtr msg = m.instantiate<sensor_msgs::CompressedImage>();
        if (msg != nullptr)
        {
            img_callback(msg);
        }
        else{
            ROS_INFO("Topic is null");
        }
        
    }

    return 0;
}
