#!/bin/sh

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

RESOLV_CONF=/etc/resolv.conf

#-----------------------------------------------------------------
# set the resolv.conf file
#-----------------------------------------------------------------

overwrite_wandomain () {
   WAN_STATIC_DOMAIN=`syscfg get wan_domain`
    
   #delete old static domain if exists
   `sed -i '/#overwrite domain name start/,/#overwrite domain name end/d' $RESOLV_CONF`

   #append wan_domain to resolv.conf
   #The search keywords are mutually exclusive. If more than one instance of these keywords is present, the last instance wins
   if [ "" != "$WAN_STATIC_DOMAIN " ]; then
       echo "#overwrite domain name start" >> $RESOLV_CONF
       echo "search $WAN_STATIC_DOMAIN" >> $RESOLV_CONF
       echo "#overwrite domain name end" >> $RESOLV_CONF
       sysevent set dhcp_domain $WAN_STATIC_DOMAIN
       sysevent set dhcp_server-restart
   fi
}

overwrite_wandomain 