sudo docker build -t website/website:latest .
sudo docker run -t -p 127.0.0.1:8888:8888 website/website