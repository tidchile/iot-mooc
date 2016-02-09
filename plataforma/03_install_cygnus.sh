#!/bin/bash

yum -y install java-1.6.0-openjdk-devel cygnus
export JAVA_HOME=/usr/lib/jvm/java-1.6.0-openjdk.x86_64

#cygnus
cd /etc/cygnus/conf
#crear agent_1.conf
sudo cat <<EOF > agent_1.conf
# Copyright 2014 Telefónica Investigación y Desarrollo, S.A.U
# 
# This file is part of fiware-cygnus (FI-WARE project).
# 
# fiware-cygnus is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
# later version.
# fiware-cygnus is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
# details.
# 
# You should have received a copy of the GNU Affero General Public License along with fiware-cygnus. If not, see
# http://www.gnu.org/licenses/.
# 
# For those usages not covered by the GNU Affero General Public License please contact with iot_support at tid dot es

#=============================================
# To be put in APACHE_FLUME_HOME/conf/agent.conf
#
# General configuration template explaining how to setup a sink of each of the available types (HDFS, CKAN, MySQL).

#=============================================
# The next tree fields set the sources, sinks and channels used by Cygnus. You could use different names than the
# ones suggested below, but in that case make sure you keep coherence in properties names along the configuration file.
# Regarding sinks, you can use multiple types at the same time; the only requirement is to provide a channel for each
# one of them (this example shows how to configure 3 sink types at the same time). Even, you can define more than one
# sink of the same type and sharing the channel in order to improve the performance (this is like having
# multi-threading).
cygnusagent.sources = http-source
cygnusagent.sinks = mysql-sink
cygnusagent.channels = mysql-channel

#=============================================
# source configuration
# channel name where to write the notification events
cygnusagent.sources.http-source.channels = mysql-channel
# source class, must not be changed
cygnusagent.sources.http-source.type = org.apache.flume.source.http.HTTPSource
# listening port the Flume source will use for receiving incoming notifications
cygnusagent.sources.http-source.port = 5050
# Flume handler that will parse the notifications, must not be changed
cygnusagent.sources.http-source.handler = com.telefonica.iot.cygnus.handlers.OrionRestHandler
# URL target
cygnusagent.sources.http-source.handler.notification_target = /notify
# Default service (service semantic depends on the persistence sink)
cygnusagent.sources.http-source.handler.default_service = project
# Default service path (service path semantic depends on the persistence sink)
cygnusagent.sources.http-source.handler.default_service_path = measures
# Number of channel re-injection retries before a Flume event is definitely discarded (-1 means infinite retries)
cygnusagent.sources.http-source.handler.events_ttl = 10
# Source interceptors, do not change
cygnusagent.sources.http-source.interceptors = ts gi
# TimestampInterceptor, do not change
cygnusagent.sources.http-source.interceptors.ts.type = timestamp
# GroupinInterceptor, do not change
cygnusagent.sources.http-source.interceptors.gi.type = com.telefonica.iot.cygnus.interceptors.GroupingInterceptor$Builder
# Grouping rules for the GroupingInterceptor, put the right absolute path to the file if necessary
# See the doc/design/interceptors document for more details
cygnusagent.sources.http-source.interceptors.gi.grouping_rules_conf_file = /usr/cygnus/conf/grouping_rules.conf

# ============================================
# OrionMySQLSink configuration
# channel name from where to read notification events
cygnusagent.sinks.mysql-sink.channel = mysql-channel
# sink class, must not be changed
cygnusagent.sinks.mysql-sink.type = com.telefonica.iot.cygnus.sinks.OrionMySQLSink
# true if the grouping feature is enabled for this sink, false otherwise
cygnusagent.sinks.mysql-sink.enable_grouping = false
# the FQDN/IP address where the MySQL server run
cygnusagent.sinks.mysql-sink.mysql_host = localhost
# the port where the MySQL server listes for incomming connections
cygnusagent.sinks.mysql-sink.mysql_port = 3306
# a valid user in the MySQL server
cygnusagent.sinks.mysql-sink.mysql_username = root
# password for the user above
cygnusagent.sinks.mysql-sink.mysql_password = student 
# how the attributes are stored, either per row either per column (row, column)
cygnusagent.sinks.mysql-sink.attr_persistence = row
# select the table type from table-by-destination and table-by-service-path
cygnusagent.sinks.mysql-sink.table_type = table-by-service-path
# number of notifications to be included within a processing batch
cygnusagent.sinks.mysql-sink.batch_size = 100
# timeout for batch accumulation
cygunsagent.sinks.mysql-sink.batch_timeout = 30

#=============================================
# mysql-channel configuration
# channel type (must not be changed)
cygnusagent.channels.mysql-channel.type = memory
# capacity of the channel
cygnusagent.channels.mysql-channel.capacity = 1000
# amount of bytes that can be sent per transaction
cygnusagent.channels.mysql-channel.transactionCapacity = 100
EOF


sudo cat <<EOF > cygnus_instance_1.conf
#####
#
# Configuration file for apache-flume
#
#####
# Copyright 2014 Telefonica Investigación y Desarrollo, S.A.U
# 
# This file is part of fiware-cygnus (FI-WARE project).
# 
# fiware-cygnus is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
# later version.
# fiware-cygnus is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
# details.
# 
# You should have received a copy of the GNU Affero General Public License along with fiware-cygnus. If not, see
# http://www.gnu.org/licenses/.
# 
# For those usages not covered by the GNU Affero General Public License please contact with iot_support at tid dot es

# Who to run cygnus as. Note that you may need to use root if you want
# to run cygnus in a privileged port (<1024)
CYGNUS_USER=cygnus

# Where is the config folder
CONFIG_FOLDER=/usr/cygnus/conf

# Which is the config file
CONFIG_FILE=/usr/cygnus/conf/agent_1.conf

# Name of the agent. The name of the agent is not trivial, since it is the base for the Flume parameters 
# naming conventions, e.g. it appears in .sources.http-source.channels=...
AGENT_NAME=cygnusagent

# Name of the logfile located at /var/log/cygnus. It is important to put the extension '.log' in order to the log rotation works properly
LOGFILE_NAME=cygnus.log

# Administration port. Must be unique per instance
ADMIN_PORT=8081

# Polling interval (seconds) for the configuration reloading
POLLING_INTERVAL=30

EOF

sudo chkconfig --level 345 cygnus on
sudo service cygnus start
