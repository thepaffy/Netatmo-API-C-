FROM debian:stable

LABEL Description="Gluon builder with Debain Stable"
MAINTAINER Christian Paffhausen <mail@thepaffy.de>

# set environment
ENV LANG=en_US.UTF-8

RUN echo 'Debug::pkgProblemResolver "true";' > /etc/apt/apt.conf.d/Debug
RUN apt update && apt upgrade -y && apt-get install -y \
  build-essential \
  clang \
  cmake \
  doxygen \
  nlohmann-json-dev \
  googletest \
  locales

RUN locale-gen en_US.UTF-8

RUN apt-get autoremove -y
