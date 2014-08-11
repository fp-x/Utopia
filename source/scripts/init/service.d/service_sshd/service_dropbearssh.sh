#!/bin/sh

#------------------------------------------------------------------
# Copyright (c) 2009 by Cisco Systems, Inc. All Rights Reserved.
#
# This work is subject to U.S. and international copyright laws and
# treaties. No part of this work may be used, practiced, performed,
# copied, distributed, revised, modified, translated, abridged, condensed,
# expanded, collected, compiled, linked, recast, transformed or adapted
# without the prior written consent of Cisco Systems, Inc. Any use or
# exploitation of this work without authorization could subject the
# perpetrator to criminal and civil liability.
#------------------------------------------------------------------

#------------------------------------------------------------------
# This script is used to start ssh daemon
# $1 is the calling event (sshd-restart, lan-status, wan-status, etc)
#------------------------------------------------------------------

source /etc/utopia/service.d/ulog_functions.sh

SERVICE_NAME="sshd"
SELF_NAME="`basename $0`"

PID_FILE=/var/run/dropbear.pid
PMON=/etc/utopia/service.d/pmon.sh

do_start() {
   DIR_NAME=/tmp/home/admin
   if [ ! -d $DIR_NAME ] ; then
      # in order to use user admin for ssh we need to give it a home directory
      # echo "[utopia] Creating ssh user admin" > /dev/console
      mkdir -p $DIR_NAME
      chown admin $DIR_NAME
      chgrp admin $DIR_NAME
      chmod 755 $DIR_NAME
   fi

   # start a ssh daemon
   # echo "[utopia] Starting SSH daemon" > /dev/console
#   dropbear -d /etc/dropbear_dss_host_key  -r /etc/dropbear_rsa_host_key
#   /etc/init.d/dropbear start
   dropbear -r /etc/rsa_key.priv
   sysevent set ssh_daemon_state up
}

do_stop() {
   # echo "[utopia] Stopping SSH daemon" > /dev/console
   sysevent set ssh_daemon_state down
#   kill -9 dropbear
   kill -9 `cat $PID_FILE`
   rm -f $PID_FILE
#    /etc/init.d/dropbear stop
}

service_start() {
   ulog ${SERVICE_NAME} status "starting ${SERVICE_NAME} service" 

   SSH_ENABLE=`syscfg get mgmt_wan_sshaccess`

   if [ "$SSH_ENABLE" = "1" ]; then

      if [ ! -f "$PID_FILE" ] ; then
         do_start
      fi
      $PMON setproc ssh dropbear $PID_FILE "/etc/utopia/service.d/service_sshd.sh sshd-restart"

      sysevent set ${SERVICE_NAME}-errinfo
      sysevent set ${SERVICE_NAME}-status "started"

   fi
}

service_stop () {
   ulog ${SERVICE_NAME} status "stopping ${SERVICE_NAME} service" 

   if [ -f "$PID_FILE" ] ; then
      do_stop
   fi
   $PMON unsetproc ssh 

   sysevent set ${SERVICE_NAME}-errinfo
   sysevent set ${SERVICE_NAME}-status "stopped"
}

service_lanwan_status ()
{
      CURRENT_LAN_STATE=`sysevent get lan-status`
      CURRENT_WAN_STATE=`sysevent get wan-status`
      if [ "stopped" = "$CURRENT_LAN_STATE" ] && [ "stopped" == "$CURRENT_WAN_STATE" ] ; then
         service_stop
      else
         service_start
      fi
}

service_bridge_status ()
{
      CURRENT_BRIDGE_STATE=`sysevent get bridge-status`
      if [ "stopped" = "$CURRENT_BRIDGE_STATE" ] ; then
         service_stop
      elif [ "started" = "$CURRENT_BRIDGE_STATE" ] ; then
         service_start
      fi
}

# Entry

case "$1" in
  ${SERVICE_NAME}-start)
      service_start
      ;;
  ${SERVICE_NAME}-stop)
      service_stop
      ;;
  ${SERVICE_NAME}-restart)
      service_stop
      service_start
      ;;
  lan-status)
      service_lanwan_status
      ;;
  wan-status)
      service_lanwan_status
      ;;
  bridge-status)
      service_bridge_status
      ;;
  *)
        echo "Usage: $SELF_NAME [${SERVICE_NAME}-start|${SERVICE_NAME}-stop|${SERVICE_NAME}-restart|ssh_server_restart|lan-status|wan-status]" >&2
        exit 3
        ;;
esac
