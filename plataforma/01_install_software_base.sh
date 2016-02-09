#!/bin/bash

TMP="/home/student/tmp"
HOME="/home/student"

sudo yum -y groupinstall "Development Tools"
sudo yum -y install vim git nano gedit firefox wget curl

# Instalación de node
mkdir $TMP
cd $TMP
wget "http://nodejs.org/dist/v4.2.3/node-v4.2.3-linux-x64.tar.gz"
tar --strip-components 1 -xzf "node-v4.2.3-linux-x64.tar.gz" -C "/usr/local"

# Instalación de RabbitMQ y módulo MQTT
cd $TMP
wget "http://packages.erlang-solutions.com/erlang-solutions-1.0-1.noarch.rpm"
sudo rpm -Uvh erlang-solutions-1.0-1.noarch.rpm
sudo yum -y install erlang

sudo rpm --import "https://www.rabbitmq.com/rabbitmq-signing-key-public.asc"
wget "https://www.rabbitmq.com/releases/rabbitmq-server/v3.6.0/rabbitmq-server-3.6.0-1.noarch.rpm"
sudo yum -y install rabbitmq-server-3.6.0-1.noarch.rpm

sudo rabbitmq-plugins enable rabbitmq_mqtt

# Instalación del iotagent-mqtt
cd $HOME
git clone "https://github.com/telefonicaid/iotagent-mqtt.git"
cd "$HOME/iotagent-mqtt"
npm install;

#instalar google chrome en centos (para usar postman)
cd $TMP
wget http://chrome.richardlloyd.org.uk/install_chrome.sh
chmod u+x install_chrome.sh
yes | sudo ./install_chrome.sh
#luego instalar postman como una app de chrome

#sublime text
wget https://download.sublimetext.com/Sublime%20Text%202.0.2%20x64.tar.bz2
tar vxjf Sublime\ Text\ 2.0.2\ x64.tar.bz2
sudo mv Sublime\ Text\ 2 /opt/
sudo ln -s /opt/Sublime\ Text\ 2/sublime_text /usr/bin/sublime
cat <<EOF > ~/.local/share/applications/sublime-text.desktop
#!/usr/bin/env xdg-open

[Desktop Entry]
Version=1.0
Type=Application
Terminal=false
Encoding=UTF-8
Categories=Utility;TextEditor;
Icon[es_ES]=/opt/Sublime Text 2/Icon/128x128/sublime_text.png
Name[es_ES]=Sublime Text 2
Exec=/usr/bin/sublime
Name=Sublime Text 2
Icon=/opt/Sublime Text 2/Icon/128x128/sublime_text.png

EOF

cp ~/.local/share/applications/sublime-text.desktop ~/Escritorio/sublime-text.desktop
chmod 755 ~/Escritorio/sublime-text.desktop

#mysql
sudo yum -y install mysql mysql-server mysql-devel
sudo service mysqld start # iniciar el servicio mysql 
sudo chkconfig --level 345 mysqld on
sudo mysqladmin -u root password 'student'
echo "create database project" | mysql -u root -p'student' 

#rvm, ruby y el proyecto 
sudo curl -sSL https://rvm.io/mpapis.asc | sudo gpg2 --import -
sudo curl -sSL https://get.rvm.io | sudo bash -s stable
source /etc/profile.d/rvm.sh
rvm reload
sudo /usr/local/rvm/bin/rvm install 2.3.0

#  1. Abrir gnome-terminal
#  2. Menu superior: Editar
#  3. Preferencias del Perfil
#  4. Título y comando
#  5. Marcar el "Ejecutar el comando como un intérprete de conexión"
#  6. Reiniciar la consola
#  7. rvm use 2.3.0
#  8. irb             ( si se abre la consola interactiva de ruby estamos redi )

rvmsudo gem install bundle
cd /home/student/course/
git clone https://github.com/tidchile/iot-mooc
cd iot-mooc/final-project
bundle install
#así tendremos todas las gemas pre instaladas cuando el estudiante corra su proyecto

cd $HOME
# Download freeboard from repo to /home/student/freeboard
git clone https://github.com/Freeboard/freeboard.git
