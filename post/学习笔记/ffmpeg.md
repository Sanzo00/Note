# ffmpeg的使用

[ffmpeg下载地址](http://ffmpeg.org/download.html)

[CUDA下载地址](https://developer.nvidia.com/cuda-downloads)



## 转换格式

```bash
ffmpeg -i input.mp4 output.mov
```



## 编码格式

```bash
# 查看所有支持的编码
ffmpeg -codecs
```

主流的编码格式有

- MP4（H264视频编码 + AAC音频编码）
- WebM（VP8视频编码 + Vorbis音频编码）
- OGG（Theora视频编码 + Vorbis音频编码）



### 音频编码

```bash
ffmpeg -i input.flac -acodec libmp3lame -ar 44100 -ab 320k -ac 2 out.mp3
# 可以不指定编码格式根据文件后缀自动选择
ffmpeg -i input.flac -ar 44100 -ab 320k -ac 2 out.mp3

-acodec: 音频的编码 libmp3lame(mp3编码格式)-
-ar: 采样率 (默认原视频的采样率)
-ab: 比特率 (默认128k)
-ac: 声道   (默认原音频声道数)
```





### 视频编码

```bash
ffmpeg -i input.mp4 -s 1920x1080 -pix_fmt yuv420p -vcodec libx264 -preset medium -profile:v high -level:v 4.1 -crf 23 -acodec aac -ar 44100 -ac 2 -ab 128k output.mp4

-s: 缩放尺寸
-pix_fmt: 视频颜色空间
	YUV、NV、RGB...
	网络视频一般都是yuv420p
-vcodes: 视频编码格式
libx264: h264的软件编码器
-preset: 编码器预设，改变编码算法的精度，精度越高速度越慢
	ultrafast superfast veryfast faster fast
	medium slow slower veryslow placebo
	默认值medium，一般录制视频选择veryfast，压制视频的时候选择veryslow
-prefile:v 指定编码器的配置，和压缩比有关
	实时通讯：baseline
	流媒体：main
	超清视频：high
-level:v 编码器的具体配置，压缩比和画质不可兼得
	范围：1-5.2
	一般1080视频使用4.1
-crf: 码率控制模式（恒定速率因子模式）
	范围：0-51，数字越小质量越高，0表示无损画质，一般在18-28选择
-r: 帧率
-acodec: 音频编码器
```





## 提取、合并音视频

```bash
# 只提取视频
ffmpeg -i input.mp4 -vcodec copy -an v.mp4
# 只提取音频
ffmpeg -i input.mp4 -acodec copy -vn a.m4a
# 合并音频和视频
ffmpeg -i a.m4a -i v.mp4 -c copy out.mp4

copy表示按照原视频音频的编码格式
```



## 截取音频

```bash
# 截取[1分钟，1分钟10秒]
ffmpeg -i a.mp3 -ss 00:01:00 -to 00:01:10 -acodec copy out.mp3
ffmpeg -i a.mp3 -ss 01:00 -to 01:00 -acodec copy out.mp3
ffmpeg -i a.mp3 -ss 60 -to 70 -acodec copy out.mp3
ffmpeg -i a.mp3 -ss 60 -t 10 -acodec copy out.mp3

# 截取后10s音频
ffmpeg -sseof -00:10  -i a.mp3   -acodec copy out.mp3

-ss: 开始时间
-to: 结束时间
-t: 截取时长
-sseof: 音频末尾
```

```cpp
ffmpeg -i a.mp3 -ss 01:00 -to 01:10 -c copy out.mp3
ffmpeg -ss 01:00 -i a.mp3 -to 01:10 -c copy out.mp3
ffmpeg -ss 01:00 -i a.mp3 -to 01:10 -c copy -copyts out.mp3
```

上面三种都是剪切01::00 - 01:10区间的视频，但是把-ss放到前面会采用关键帧技术，截取之后的视频，播放器的区间可能会识别错误（第二种操作），可以使用-copyts来保留时间戳。



## 截图、水印、动图

- 截图

  ```bash
  ffmpeg -i input.mp4 -ss 5 -vframes 2 img1.jpg   
  -ss: 第5秒
  -vframes: 指定帧数
  ```

- 水印

  ```bash
  ffmpeg -i input.mp4 -i JB.ico -filter_complex "overlay=10:30" out.mp4
  
  -filter_complex: 设置滤镜
  overlay=10:30: 左上角，距离左边10，距离右边30
  ```

- 动图

  ```bash
  ffmpeg -i test.mp4 -ss 5 -to 12 -s 360x360 -r 15 out.gif
  ```

- 将照片合成视频或动图

  ```bash
  cat ./*.jpg | ffmpeg -framerate 1 -f image2pipe -i - out.gif
  cat ./*.jpg | ffmpeg -framerate 1 -f image2pipe -i - out.avi
  ```

  

## 合并视频

- 使用mpeg文件进行拼接（文件大、速度慢）

  先讲mp4转为mpg格式，然后合并转换为mp4格式。

  ```bash
  ffmpeg -i 1.mp4 -qscale 4 1.mpg
  ffmpeg -i 2.mp4 -qscale 4 2.mpg
  cat 1.mpg 2.mpg | ffmpeg -f mpeg -i - -qscale 6 -vcodec mpeg4 output.mp4
  ```

- 使用ts拼接（文件小、速度快）

  先讲mp4转为ts格式，然后合并转换为mp4格式。

  ```bash
  ffmpeg -i 1.mp4 -vcodec copy -acodec copy -vbsf h264_mp4toannexb 1.ts
  ffmpeg -i 2.mp4 -vcodec copy -acodec copy -vbsf h264_mp4toannexb 2.ts
  ffmpeg -i "concat:1.ts|2.ts" -acodec copy -vcodec copy -absf aac_adtstoasc output.mp4
  
  ```



## 录屏、直播

- 录屏

  只能录制屏幕不包含音频。

  ```bash
  ffmpeg -f gdigrab -i desktop rec.mp4
  
  -f: 格式化
  gdigrab: 用来捕获视频设备
  ```

- 直播

  ```bash
  ffmpeg -re -i rec.mp4 网站视频的编码 -f flv "rtmp地址/推流码"
  ```

  

  