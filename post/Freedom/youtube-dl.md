

[常见用法](https://wker.com/youtube-dl/)

```bash
sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl
sudo chmod a+rx /usr/local/bin/youtube-dl

youtube-dl -f bestvideo+bestaudio URL
youtube-dl -f bestvideo+bestaudio --playlist-start 1 --playlist-end 5 URL
```

