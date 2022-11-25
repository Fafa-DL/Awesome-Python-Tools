import os
import cv2

def to_ts(init_video_path, ts_video_path):
    """将原视频格式转为ts

    Args:
        init_video_path (str): 原视频文件夹
        ts_video_path (str): 转换后的ts文件夹
    """
    for i in os.listdir(init_video_path):
        init_video_file = os.path.join(init_video_path, i)
        ts_video_file = os.path.join(ts_video_path, i.split('.')[0] + '.ts')
        command = f'ffmpeg -i {init_video_file} -vcodec copy -acodec copy -vbsf h264_mp4toannexb {ts_video_file}'
        # command = f'ffmpeg -i {init_video_file} -c:v copy {ts_video_file}'
        os.system(command)

def make_batch_file(ts_video_path):
    """制作批量合并ts所需的txt文件

    Args:
        ts_video_path (str): 转换后的ts文件夹
    """
    files = os.listdir(ts_video_path)
    files.sort()
    with open('ts_filename.txt', 'w') as f:
        for item in files:
            tmp = item.strip()
            file_path = os.path.join(ts_video_path, item)
            f.write(f'file \'{file_path}\'\n')

def get_video_duration(filename):
    """获取视频时长

    Args:
        filename (str): 视频文件路径

    Returns:
        float: 视频时长
    """
    cap = cv2.VideoCapture(filename)
    if cap.isOpened():
        rate = cap.get(5)
        frame_num =cap.get(7)
        duration = frame_num/rate
        return duration
    return -1

def make_timestamp(ts_video_path):
    """制作各视频结点时间戳，默认保存在程序运行文件夹下timestamp.txt

    Args:
        ts_video_path (ts): 视频文件夹
    """
    filelist = os.listdir(ts_video_path)
    filelist.sort()
    f = open('timestamp.txt', 'w')
    total_seconds = 0
    for file in filelist:
        t = get_video_duration(os.path.join(ts_video_path, file))
        m, s = divmod(total_seconds, 60)
        h, m = divmod(m, 60)
        total_seconds += t
        file = file.split('.')[0]
        if not h:
            f.write("%02d:%02d " % (m, s) + file + '\n')
        else:
            f.write("%02d:%02d:%02d " % (h, m, s) + file + '\n')
        # print ("%02d:%02d:%02d " % (h, m, s) + os.path.join(ts_video_path, file))
    f.close()

def merge_video():
    """根据ts_filename.txt合并视频
    """
    command = 'ffmpeg -f concat -safe 0 -i ts_filename.txt -acodec copy -vcodec copy -absf aac_adtstoasc output.mp4'
    # command = 'ffmpeg -f concat -safe 0 -i ts_filename.txt -c copy output.mp4'
    os.system(command)
    
def del_ts(ts_video_path):
    """删除转换中转文件，如ts视频，txt文件

    Args:
        ts_video_path (str): ts文件夹路径
    """
    for i in os.listdir(ts_video_path):
        temp = os.path.join(ts_video_path, i)
        command = f'del {temp}'
        os.system(command)
        command = f'del ts_filename.txt'
        os.system(command)

def main():
    init_video_path = 'init'
    ts_video_path = 'ts'
    del_ts_flag = False

    to_ts(init_video_path, ts_video_path)
    make_batch_file(ts_video_path)
    # make_timestamp(ts_video_path) # Optional
    merge_video()
    if del_ts_flag:
        del_ts(ts_video_path)


if __name__ == '__main__':
    main()