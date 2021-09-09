FROM archlinux:base

RUN pacman -Syuu --noconfirm libmicrohttpd cmake gcc clang make sudo

COPY . /backend
RUN mkdir /backend/build;
WORKDIR /backend/build
RUN cmake ..; make; sudo cmake --install .;
CMD backend