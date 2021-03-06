#!/bin/sh

#######################################################################
#   Copyright [2014] [Cisco Systems, Inc.]
# 
#   Licensed under the Apache License, Version 2.0 (the \"License\");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an \"AS IS\" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#######################################################################


#------------------------------------------------------------------
# Copyright (c) 2008 by Cisco Systems, Inc. All Rights Reserved.
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
# This script is used to monitor process that are suppose to be
# running and, if not they are restarted
# 
# There are many ways to use this script
#
# 1) without any arg, it checks the processes to be monitored
#
# 2) register/unregister a feature to be monitored,
#    Usage: pmon.sh [register | unregister] <feature-name> 
#    Eg: pmon.sh register httpd 
#    Eg: pmon.sh unregister ssh 
#
# 2) Set (or unset) process details of a feature to be monitored,
#    Usage: pmon.sh setproc <feature-name> <process-name> <pidfile|none> <restart-cmd>
#    Usage: pmon.sh unsetproc <feature-name>
#    Eg: pmon.sh setproc httpd /var/run/mini_httpd.pid "/etc/utopia/service.d/service_httpd.sh httpd-restart"
#    Eg: pmon.sh unsetproc httpd
#
# When the feature is enabled AND started, appropriate <feature>.sh script need to
# add this pmon sysevent entry with more details about itself
#    pmon_proc_<feature> 
#
# WARNING: sysevent isn't locked down, so we are not thread-safe
#          to aleviate this, register & enable are seperated into
#          two different operations.
#
#------------------------------------------------------------------
# Sysevent namespace
#   pmon_feature_count - current maximum 'number' of pmon_proc_X entries
#        always monetonically increases. register can fill holes caused
#        by unregister
#   pmon_feature_<x> - list of features to be monitered by process-monitor
#   pmon_proc_<feature> - process details (feature_name process_name pid/none restart-cmd)
#        Could be empty or "" string due to an unregister
#        such entries are silently ignored
#------------------------------------------------------------------

CONF_FILE=/tmp/pmon.conf
BIN=pmon

#
# Config file format
#   <process-name> <pid-file | none> <restart-cmd>
# For eg:
#   "mini_httpd /var/run/mini_httpd.pid /etc/init.d/httpd.sh restart"
#   "samba      none                    /etc/init.d/samba restart

do_check_process() {
    # echo "[utopia] Running process monitor" > /dev/console
    LOCAL_CONF_FILE=/tmp/pmon.conf$$
    rm -f $LOCAL_CONF_FILE

    # Add static pmon entries
    echo "syseventd    /var/run/syseventd.pid    /etc/utopia/service.d/syseventd_restart.sh" >> $LOCAL_CONF_FILE

    # Add dynamic pmon entries stashed in sysevent
    # by various modules
    COUNT=`sysevent get pmon_feature_count`
    if [ "" = "$COUNT" ] ; then
        COUNT=0
    fi

    for ct in `seq 1 $COUNT`
    do
        feature=`sysevent get pmon_feature_$ct`
        if [ "" != "$feature" ] ; then
            PROC_ENTRY=`sysevent get pmon_proc_$feature`
            if [ "" != "$PROC_ENTRY" ] ; then
                process_name=`echo $PROC_ENTRY | cut -d' ' -f1`
                pid=`echo $PROC_ENTRY | cut -d' ' -f2`
                restartcmd=`echo $PROC_ENTRY | cut -d' ' -f3-`
                if [ "" != "$process_name" ] && [ "" != "$pid" ] && [ "" != "$restartcmd" ] ; then
                    echo "$process_name $pid $restartcmd" >> $LOCAL_CONF_FILE
                fi
            fi
        fi
   done
   
   cat $LOCAL_CONF_FILE > $CONF_FILE
   rm -f $LOCAL_CONF_FILE
   $BIN $CONF_FILE
}

do_register()
{
    if [ "" = "$1" ] ; then
        echo "pmon-register: invalid parameter [$1]" > /dev/console
        return 1
    fi

    # echo "[utopia] process monitor register feature [$1]" > /dev/console

    COUNT=`sysevent get pmon_feature_count`
    if [ "" = "$COUNT" ] ; then
        COUNT=0
    fi

    FREE_SLOT=0

    for ct in `seq 1 $COUNT`
    do
        FEATURE=`sysevent get pmon_feature_$ct`
        if [ "" = "$FEATURE" ] ; then
            FREE_SLOT=$ct
        else
            if [ "$FEATURE" = "$1" ] ; then
                # echo "pmon-register: already monitoring $FEATURE, nothing to do" > /dev/console
                return
            fi
        fi
    done

    if [ "0" != "$FREE_SLOT" ]; then
        SLOT=$FREE_SLOT
    else
        COUNT=`expr $COUNT + 1`
        SLOT=$COUNT
        sysevent set pmon_feature_count $COUNT
    fi

    sysevent set pmon_feature_$SLOT "$1"
}

do_unregister()
{

    if [ "" = "$1" ] ; then
        # echo "pmon-unregister: invalid parameter [$1]" > /dev/console
        return 1
    fi

    # echo "[utopia] process monitor unregister feature [$1]" > /dev/console

    COUNT=`sysevent get pmon_feature_count`
    if [ "" = "$COUNT" ] ; then
        COUNT=0
    fi

    for ct in `seq 1 $COUNT`
    do
        FEATURE=`sysevent get pmon_feature_$ct`
        if [ "" != "$FEATURE" ] && [ "$1" = "$FEATURE" ] ; then
            sysevent set pmon_feature_$ct 
            sysevent set pmon_proc_$feature 
            return
        fi
    done
    # echo "pmon-unregister: entry for $1 not found" > /dev/console
}

do_setproc ()
{
    if [ "" = "$1" ] || [ "" = "$2" ] || [ "" = "$3" ] || [ "" = "$4" ] ; then
        echo "pmon-setproc: invalid parameter(s) " > /dev/console
        return 1
    fi

    sysevent set pmon_proc_$1 "$2 $3 $4"
}

do_unsetproc ()
{
    if [ "" = "$1" ]; then
        echo "pmon-unsetproc: invalid parameter " > /dev/console
        return 1
    fi

    sysevent set pmon_proc_$1 
}

# Entry

case "$1" in
    register)
      do_register $2 $3 "$4"
      ;;
    unregister)
      do_unregister $2
      ;;
    setproc)
      do_setproc $2 $3 $4 "$5"
      ;;
    unsetproc)
      do_unsetproc $2
      ;;
    *)
      do_check_process
      ;;
esac

