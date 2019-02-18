@echo off
F:
cd F:\FFmpeg
echo 正在转换分辨率...
ffmpeg -i F:\BadApple.mp4 -vf scale=128:64 -ss 00:00:00 -t 00:03:39 F:\BadApple128x64.mkv
echo 分辨率转换结束
pause

echo 正在创建目录...
md F:\BadAppleBmp
echo 正在转换图片...
ffmpeg -i F:\BadApple128x64.mkv -vf hflip -r 37.68 -ss 00:00:00 -t 00:03:39 F:\BadAppleBmp\%%d.bmp
echo 图片转换结束
pause