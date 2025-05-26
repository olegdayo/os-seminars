package main

import (
	"fmt"
	"log/slog"
	"net/http"
	"os"

	"gopkg.in/yaml.v3"
)

func pingpong(w http.ResponseWriter, r *http.Request) {
	slog.Info("Got request", r)
	w.Write([]byte("pong"))
}

type Config struct {
	Port uint16 `yaml:"port"`
}

func parse(path string) (Config, error) {
	bytes, err := os.ReadFile(path) // nolint:gosec
	if err != nil {
		return Config{}, err
	}

	config := Config{}
	err = yaml.Unmarshal(bytes, &config)
	if err != nil {
		return Config{}, err
	}

	return config, nil
}

func main() {
	slog.Info("I am an echo server")
	http.HandleFunc("/ping", pingpong)

	conf, err := parse(os.Args[1])
	if err != nil {
		panic(err)
	}
	http.ListenAndServe(fmt.Sprintf(":%d", conf.Port), nil)
}
