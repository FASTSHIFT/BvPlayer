@echo off
F:
cd F:\FFmpeg
echo ����ת���ֱ���...
ffmpeg -i F:\BadApple.mp4 -vf scale=128:64 -ss 00:00:00 -t 00:03:39 F:\BadApple128x64.mkv
echo �ֱ���ת������
pause

echo ���ڴ���Ŀ¼...
md F:\BadAppleBmp
echo ����ת��ͼƬ...
ffmpeg -i F:\BadApple128x64.mkv -vf hflip -r 37.68 -ss 00:00:00 -t 00:03:39 F:\BadAppleBmp\%%d.bmp
echo ͼƬת������
pause