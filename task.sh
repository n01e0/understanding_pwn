#!/bin/bash
sudo dnf install -y nc
cd task && sudo docker-compose up --build -d

