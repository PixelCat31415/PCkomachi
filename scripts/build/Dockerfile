FROM ubuntu:22.04

ENV LANG C.UTF-8
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y texlive-full
RUN apt-get install -y python-is-python3
RUN apt-get install -y wget
RUN apt-get install -y fonts-noto-cjk
RUN apt-get install -y cabextract

COPY install_consolas.sh install_consolas.sh
RUN ./install_consolas.sh && rm install_consolas.sh

RUN apt-get install -y git
RUN apt-get install -y g++
