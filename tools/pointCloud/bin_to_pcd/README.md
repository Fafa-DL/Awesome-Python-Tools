# kitti_velodyne_bin_to_pcd

 - [Visual Odometry / SLAM Evaluation 2012](http://www.cvlibs.net/datasets/kitti/eval_odometry.php)


# Usage
```
Options
  --help : produce help message
  --b : bin file folder
  --p : pcd file folder
  --m : mode - bin2pcd, pcd2bin
```

## Example
```
./binpcd --m=bin2pcd --b=/home/docker_share/sequences/00/velodyne/ --p=/home/docker_share/sequences/00_pcd
```
