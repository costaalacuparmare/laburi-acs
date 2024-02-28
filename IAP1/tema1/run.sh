#!/bin/bash

# Build the Docker image
docker build -t iap-tema2 .

# Run the Docker container
docker run -p 8080:80 -it iap-tema2
