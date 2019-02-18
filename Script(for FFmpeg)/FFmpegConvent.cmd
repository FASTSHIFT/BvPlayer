@echo off
F:
cd F:\FFmpeg
echo 正在转换分辨率...
ffmpeg -i F:\HOP.flv -vf scale=128:64 -ss 00:00:00 -t 00:03:19 F:\HOP128x64.mkv
echo 分辨率转换结束
pause

echo 正在创建目录...
md F:\HOPBmp
echo 正在转换图片...
ffmpeg -i F:\HOP128x64.mkv -vf hflip -r 51.45 -ss 00:00:00 -t 00:03:19 F:\HOPBmp\%%d.bmp
echo 图片转换结束
pause