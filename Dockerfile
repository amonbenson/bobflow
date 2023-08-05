FROM alpine

# install required packages
RUN apk add --no-cache git make gcc musl-dev \
    sdl2-dev
