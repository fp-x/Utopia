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
#                     ulog_functions.sh 
#
# Helper routines for logging to system logger
#------------------------------------------------------------------


# $1 - Component (system | wan | fw | ...)
# $2 - Sub component (syscfg | sysevent | pktdrop | ...)
# $3 - descriptive message

ulog () {
    COMP=$1
    SUBCOMP=$2
    MESG=$3

    UL_MESG="$COMP.$SUBCOMP $MESG"
    /usr/bin/logger -p local7.notice -t UTOPIA $UL_MESG
}

ulog_error () {
    COMP=$1
    SUBCOMP=$2
    MESG=$3

    UL_MESG="$COMP.$SUBCOMP $MESG"
    /usr/bin/logger -p local7.error -t UTOPIA $UL_MESG
}

ulog_debug () {
    COMP=$1
    SUBCOMP=$2
    MESG=$3

    UL_MESG="$COMP.$SUBCOMP $MESG"
    /usr/bin/logger -p local7.debug -t UTOPIA $UL_MESG
}

