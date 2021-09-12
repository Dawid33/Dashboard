sudo docker build -t website/website:latest .
sudo docker run -it -p 127.0.0.1:c8888:8888 website/website