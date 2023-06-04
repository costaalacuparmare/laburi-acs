## IAP1 - Web Based Stenography Tool
### Constantinscu Vlad - 314CB

>Note: the run.sh script builds and runs the Docker image of the app

#### *Contents*:
```
- images: contains two options for background images for index.html
- templates: templates for each html page
- app.py: implementation of the Flask based RUST API
- Dockerfile: used to build the docker image
- requirements.txt : used by Dockefile
```

## Implementation:

My implementation is based around a website with a menu in the upper part
of the screen, which uses an LSB based stenography
encryption/decryption algorithm and is able to run in 
a Dockerimage. I used python libraries to create the routes
for the app, and the algortihms required.