```bash
sudo curl -L https://yt-dl.org/downloads/latest/youtube-dl -o /usr/local/bin/youtube-dl
sudo chmod a+rx /usr/local/bin/youtube-dl

youtube-dl -f bestvideo+bestaudio URL
youtube-dl -f bestvideo+bestaudio --playlist-start 1 URL
```

