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

/fss/gw/usr/sbin/GenFWLog -c
/fss/gw/usr/sbin/firewall $*
/fss/gw/usr/sbin/GenFWLog -gc

CONN_F=`sysevent get firewall_flush_conntrack`
WANIP=`sysevent get current_wan_ipaddr`
if [ "$CONN_F" == "1" ] && [ "$WANIP" != "0.0.0.0" ]
then
    conntrack_flush
    sysevent set firewall_flush_conntrack 0
fi



