#!/bin/bash

export LC_ALL=C

# Se crea la referencia al repositorio de FIWARE
echo -e "[Fiware]\nname=FIWARE repository\nbaseurl=http://repositories.testbed.fi-ware.eu/repo/rpm/x86_64/\ngpgcheck=0\nenabled=1" | sudo tee /etc/yum.repos.d/fiware.repo
# Se crea la referencia al repositorio del motor de base de datos MongoDB
echo -e "[mongodb-org-3.0]\nname=MongoDB Repository\nbaseurl=https://repo.mongodb.org/yum/redhat/\$releasever/mongodb-org/3.0/x86_64/\ngpgcheck=0\nenabled=1" | sudo tee /etc/yum.repos.d/mongodb-org-3.0.repo

# Instalación de mongodb y orion(ContextBroker)
sudo yum -y install mongodb-org
sudo yum -y install contextBroker-0.27.0-1

# Se habilita el inicio de los servicios automáticamente después de un reinicio
sudo chkconfig mongodb-org on
sudo chkconfig contextBroker on

# Se levantan el servicio de base de datos y orion (contextBroker)
sudo service mongod start
# Se utiliza la opción -corsOrigin __ALL antes de iniciar contextBroker
sudo contextBroker "-corsOrigin __ALL"
