

[常见用法](https://wker.com/youtube-dl/)



- 安装

  ```bash
  sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl
  
  sudo chmod a+rx /usr/local/bin/youtube-dl
  ```

- 下载视频

  ```bash
  youtube-dl -f bestvideo+bestaudio URL
  
  youtube-dl -f bestvideo+bestaudio --playlist-start 1 --playlist-end 5 URL
  ```

- 下载音频

  ```bash
  youtube-dl -x --audio-format mp3 URL
  
  youtube-dl -x --embed-thumbnail --audio-format mp3 URL
  ```

- 文件下载

  ```bash
  for i in $(<videos.txt); do youtube-dl -x --audio-format mp3 $i; done
  ```

  

