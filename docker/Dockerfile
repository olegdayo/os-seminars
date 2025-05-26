FROM golang:latest AS build
WORKDIR /app
COPY . .
RUN go mod tidy
RUN make build

FROM debian:latest
WORKDIR /app
COPY --from=builder /app/bin/echo .
ENTRYPOINT [ "/app/echo" ]
