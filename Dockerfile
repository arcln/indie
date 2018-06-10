FROM ubuntu

USER root

RUN apt update && apt install -y libirrlicht1.8 libirrlicht1.8-dbg libirrlicht-dev

COPY worms-server /srv
COPY assets /assets
