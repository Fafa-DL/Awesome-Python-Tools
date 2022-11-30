# 将rosbag中img topic数据逐帧保存

<div align="center">

[![BILIBILI](https://raw.githubusercontent.com/Fafa-DL/readme-data/main/Bilibili.png)](https://space.bilibili.com/46880349)


![Visitors](https://visitor-badge.glitch.me/badge?page_id=Fafa-DL.Awesome-Python-Tools/tools/PointCloud/bag_to_img&right_color=yellow)

</div>

```
mkdir bagToImg && cd bagToImg
mkdir src && cd src
git clone # 将bag_to_img文件夹放在src中，修改img_topic, save_path, bag_path文件路径 
catkin_make -j8
source devel/setup.bash
rosrun bag_to_img bag_to_img
```