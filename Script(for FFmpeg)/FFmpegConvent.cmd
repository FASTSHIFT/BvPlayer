@echo off
F:
cd F:\FFmpeg
echo ����ת���ֱ���...
ffmpeg -i F:\HOP.flv -vf scale=128:64 -ss 00:00:00 -t 00:03:19 F:\HOP128x64.mkv
echo �ֱ���ת������
pause

echo ���ڴ���Ŀ¼...
md F:\HOPBmp
echo ����ת��ͼƬ...
ffmpeg -i F:\HOP128x64.mkv -vf hflip -r 51.45 -ss 00:00:00 -t 00:03:19 F:\HOPBmp\%%d.bmp
echo ͼƬת������
pause