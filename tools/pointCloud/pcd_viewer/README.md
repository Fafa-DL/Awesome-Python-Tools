# 在Rviz中显示PCD点云

<div align="center">

[![BILIBILI](https://raw.githubusercontent.com/Fafa-DL/readme-data/main/Bilibili.png)](https://space.bilibili.com/46880349)


![Visitors](https://visitor-badge.glitch.me/badge?page_id=Fafa-DL.Awesome-Python-Tools/tools/PointCloud/pcd_viewer&right_color=yellow)

</div>

```
mkdir pcdViewer && cd pcdViewer
mkdir src && cd src
git clone # 将pcd_viewer文件夹放在src中，修改pcd文件路径
catkin_make -j8
source devel/setup.bash
rosrun pcd_viewer pcd_viewer
```