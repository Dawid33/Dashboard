#FROM archlinux:base
FROM ubuntu

#RUN pacman -Syuu --noconfirm libmicrohttpd cmake gcc clang make sudo
RUN DEBIAN_FRONTEND=noninteractive apt-get update -y --no-install-recommends && DEBIAN_FRONTEND=noninteractive apt-get upgrade -y --no-install-recommends
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends cmake clang make sudo sqlite3 git

COPY . /backend
RUN mkdir /backend/build;
WORKDIR /backend/build
RUN cmake ..; make;
CMD ./backend