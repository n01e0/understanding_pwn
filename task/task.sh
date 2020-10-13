#!/bin/bash
sudo systemctl start docker
sudo docker-compose up --build -d
