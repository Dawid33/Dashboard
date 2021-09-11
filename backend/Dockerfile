#FROM archlinux:base
FROM ubuntu

#RUN pacman -Syuu --noconfirm libmicrohttpd cmake gcc clang make sudo
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install --yes cmake clang make sudo sqlite3

COPY . /backend
RUN mkdir /backend/build;
WORKDIR /backend/build
RUN cmake ..; make;
CMD ./backend