/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/* Copyright (c) 2008-2009 Cisco Systems, Inc. All rights reserved.
 *
 * Cisco Systems, Inc. retains all right, title and interest (including all
 * intellectual property rights) in and to this computer program, which is
 * protected by applicable intellectual property laws.  Unless you have obtained
 * a separate written license from Cisco Systems, Inc., you are not authorized
 * to utilize all or a part of this computer program for any purpose (including
 * reproduction, distribution, modification, and compilation into object code),
 * and you must immediately destroy or return to Cisco Systems, Inc. all copies
 * of this computer program.  If you are licensed by Cisco Systems, Inc., your
 * rights to utilize this computer program are limited by the terms of that
 * license.  To obtain a license, please contact Cisco Systems, Inc.
 *
 * This computer program contains trade secrets owned by Cisco Systems, Inc.
 * and, unless unauthorized by Cisco Systems, Inc. in writing, you agree to
 * maintain the confidentiality of this computer program and related information
 * and to not disclose this computer program and related information to any
 * other person or entity.
 *
 * THIS COMPUTER PROGRAM IS PROVIDED AS IS WITHOUT ANY WARRANTIES, AND CISCO
 * SYSTEMS, INC. EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
 * INCLUDING THE WARRANTIES OF MERCHANTIBILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE, AND NONINFRINGEMENT.
 *
 *
 *    FileName:    pal_upnp.h
 *      Author:    Barry Wang (bowan@cisco.com)
 *        Date:    2009-05-05
 * Description:    Header file of PAL UPnP abstract interfaces
 *****************************************************************************/
/*$Id: pal_upnp.h,v 1.2 2009/05/19 07:41:12 bowan Exp $
 *
 *$Log: pal_upnp.h,v $
 *Revision 1.2  2009/05/19 07:41:12  bowan
 *change some comments and data type as per common type definition
 *
 *Revision 1.1  2009/05/13 07:56:44  bowan
 *no message
 *
 *
 **/

#ifndef __PAL_UPNP_H__
#define __PAL_UPNP_H__

#include "pal_def.h"
#include "pal_xml.h"
#include <arpa/inet.h>

#ifndef IN
	#define IN
#endif

#ifndef OUT
	#define OUT
#endif

#ifndef INOUT
	#define INOUT
#endif

#define PAL_UPNP_SID_MAX_LENGTH  256
#define PAL_UPNP_DESC_URL_SIZE   256
#define PAL_UPNP_LINE_SIZE       180
#define PAL_UPNP_NAME_SIZE       256
#define PAL_UPNP_SID_SIZE        44
#define PAL_UPNP_DEFAULT_WEB_DIR "./web"

typedef INT32 pal_upnp_device_handle;
typedef INT32 pal_upnp_cp_handle;
typedef CHAR pal_upnp_sid[PAL_UPNP_SID_SIZE];

#define PAL_UPNP_E_SUCCESS          0
#define PAL_UPNP_E_INVALID_HANDLE   -100
#define PAL_UPNP_E_INVALID_PARAM    -101
#define PAL_UPNP_E_OUTOF_HANDLE     -102
#define PAL_UPNP_E_OUTOF_CONTEXT    -103
#define PAL_UPNP_E_OUTOF_MEMORY     -104
#define PAL_UPNP_E_INIT             -105
#define PAL_UPNP_E_BUFFER_TOO_SMALL -106
#define PAL_UPNP_E_INVALID_DESC     -107
#define PAL_UPNP_E_INVALID_URL      -108
#define PAL_UPNP_E_INVALID_SID      -109
#define PAL_UPNP_E_INVALID_DEVICE   -110
#define PAL_UPNP_E_INVALID_SERVICE  -111
#define PAL_UPNP_E_BAD_RESPONSE     -113
#define PAL_UPNP_E_BAD_REQUEST      -114
#define PAL_UPNP_E_INVALID_ACTION   -115
#define PAL_UPNP_E_FINISH           -116
#define PAL_UPNP_E_INIT_FAILED      -117
#define PAL_UPNP_E_URL_TOO_BIG      -118
#define PAL_UPNP_E_BAD_HTTPMSG      -119
#define PAL_UPNP_E_ALREADY_REGISTERED -120
#define PAL_UPNP_E_NETWORK_ERROR    -200
#define PAL_UPNP_E_SOCKET_WRITE     -201
#define PAL_UPNP_E_SOCKET_READ      -202
#define PAL_UPNP_E_SOCKET_BIND      -203
#define PAL_UPNP_E_SOCKET_CONNECT   -204
#define PAL_UPNP_E_OUTOF_SOCKET     -205
#define PAL_UPNP_E_LISTEN           -206
#define PAL_UPNP_E_TIMEDOUT         -207
#define PAL_UPNP_E_SOCKET_ERROR	    -208
#define PAL_UPNP_E_FILE_WRITE_ERROR -209
#define PAL_UPNP_E_CANCELED         -210
#define PAL_UPNP_E_EVENT_PROTOCOL         -300
#define PAL_UPNP_E_SUBSCRIBE_UNACCEPTED   -301
#define PAL_UPNP_E_UNSUBSCRIBE_UNACCEPTED -302
#define PAL_UPNP_E_NOTIFY_UNACCEPTED      -303
#define PAL_UPNP_E_INVALID_ARGUMENT       -501
#define PAL_UPNP_E_FILE_NOT_FOUND         -502
#define PAL_UPNP_E_FILE_READ_ERROR        -503
#define PAL_UPNP_E_EXT_NOT_XML            -504
#define PAL_UPNP_E_NO_WEB_SERVER          -505
#define PAL_UPNP_E_OUTOF_BOUNDS	          -506
#define PAL_UPNP_E_NOT_FOUND	          -507
#define PAL_UPNP_E_INTERNAL_ERROR         -911

/* SOAP-related error codes */
#define PAL_UPNP_SOAP_E_INVALID_ACTION    401
#define PAL_UPNP_SOAP_E_INVALID_ARGS      402
#define PAL_UPNP_SOAP_E_OUT_OF_SYNC       403
#define PAL_UPNP_SOAP_E_INVALID_VAR       404
#define PAL_UPNP_SOAP_E_ACTION_FAILED     501



typedef enum _pal_upnp_etype {
  /*
   * Control callbacks
   */

  /** Received by a device when a control point issues a control
   *  request.  The {\bf Event} parameter contains a pointer to a {\bf
   *  pal_upnp_action_request} structure containing the action.  The application
   *  stores the results of the action in this structure. */

  PAL_UPNP_CONTROL_ACTION_REQUEST,

  /** A {\bf PAL_upnp_send_action} call completed. The {\bf Event}
   *  parameter contains a pointer to a {\bf pal_upnp_action_complete} structure
   *  with the results of the action.  */

  PAL_UPNP_CONTROL_ACTION_COMPLETE,

  /** Received by a device when a query for a single service variable
   *  arrives.  The {\bf Event} parameter contains a pointer to a {\bf
   *  pal_upnp_state_var_request} structure containing the name of the variable
   *  and value.  */

  PAL_UPNP_CONTROL_GET_VAR_REQUEST,

  /** A {\bf pal_upnp_get_state_var} call completed. The {\bf Event}
   *  parameter contains a pointer to a {\bf pal_upnp_state_var_Complete} structure
   *  containing the value for the variable.  */

  PAL_UPNP_CONTROL_GET_VAR_COMPLETE,

  /*
   * Discovery callbacks
   */

  /** Received by a control point when a new device or service is available.  
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  pal_upnp_discovery} structure with the information about the device
   *  or service.  */

  PAL_UPNP_DISCOVERY_ADVERTISEMENT_ALIVE,

  /** Received by a control point when a device or service shuts down. The {\bf
   *  event} parameter contains a pointer to a {\bf pal_upnp_discovery}
   *  structure containing the information about the device or
   *  service.  */

  PAL_UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE,

  /** Received by a control point when a matching device or service responds.
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  pal_upnp_discovery} structure containing the information about
   *  the reply to the search request.  */

  PAL_UPNP_DISCOVERY_SEARCH_RESULT,

  /** Received by a control point when the search timeout expires.  The
   *  SDK generates no more callbacks for this search after this 
   *  event.  The {\bf Event} parameter is {\tt NULL}.  */

  PAL_UPNP_DISCOVERY_SEARCH_TIMEOUT,

  /*
   * Eventing callbacks
   */

  /** Received by a device when a subscription arrives.
   *  The {\bf Event} parameter contains a pointer to a {\bf
   *  pal_upnp_subscription_request} structure.  At this point, the
   *  subscription has already been accepted.  {\bf pal_upnp_discovery}
   *  needs to be called to confirm the subscription and transmit the
   *  initial state table.  This can be done during this callback.  The SDK
   *  generates no events for a subscription unless the device 
   *  application calls {\bf PAL_upnp_accept_subscription}.
   */

  PAL_UPNP_EVENT_SUBSCRIPTION_REQUEST,

  /** Received by a control point when an event arrives.  The {\bf
   *  Event} parameter contains a {\bf pal_upnp_event} structure
   *  with the information about the event.  */

  PAL_UPNP_EVENT_RECEIVED,

  /** A {\bf UpnpRenewSubscriptionAsync} call completed. The status of
   *  the renewal is in the {\bf Event} parameter as a {\bf
   *  Upnp_Event_Subscription} structure.  */

  PAL_UPNP_EVENT_RENEWAL_COMPLETE,

  /** A {\bf UpnpSubscribeAsync} call completed. The status of the
   * subscription is in the {\bf Event} parameter as a {\bf
   * Upnp_Event_Subscription} structure.  */

  PAL_UPNP_EVENT_SUBSCRIBE_COMPLETE,

  /** A {\bf UpnpUnSubscribeAsync} call completed. The status of the
   *  subscription is in the {\bf Event} parameter as a {\bf
   *  Upnp_Event_Subscribe} structure.  */

  PAL_UPNP_EVENT_UNSUBSCRIBE_COMPLETE,

  /** The auto-renewal of a client subscription failed.   
   *  The {\bf Event} parameter is a {\bf Upnp_Event_Subscribe} structure 
   *  with the error code set appropriately. The subscription is no longer 
   *  valid. */

  PAL_UPNP_EVENT_AUTORENEWAL_FAILED,

  /** A client subscription has expired. This will only occur 
   *  if auto-renewal of subscriptions is disabled.
   *  The {\bf Event} parameter is a {\bf Upnp_Event_Subscribe}
   *  structure. The subscription is no longer valid. */
  
  PAL_UPNP_EVENT_SUBSCRIPTION_EXPIRED
}pal_upnp_etype;


/*for event callback function*/
typedef INT32 (*pal_upnp_func)(
    IN pal_upnp_etype event_type, 
    IN VOID *event, 
    IN VOID *cookie);

typedef struct{
    CHAR* name;
    CHAR* value;
}pal_string_pair;

typedef enum{
    PAL_UPNP_ACTION_REQUEST,
    PAL_UPNP_ACTION_RESPONSE
}pal_upnp_action_type;


typedef struct{
  /** The result of the operation. */
  INT32 error_code;
  /** The socket number of the connection to the requestor. */
  INT32 socket;
  /** The error string in case of error. */
  CHAR error_str[PAL_UPNP_LINE_SIZE];
  /** The Action Name. */
  CHAR action_name[PAL_UPNP_NAME_SIZE];
  /** The unique device ID. */
  CHAR dev_udn[PAL_UPNP_NAME_SIZE];
  /** The service ID. */
  CHAR service_id[PAL_UPNP_NAME_SIZE];
  /** The DOM document describing the action. */
  pal_xml_top *action_request;
  /** The DOM document describing the result of the action. */
  pal_xml_top *action_result;
  /** IP address of the control point requesting this action. */
  struct in_addr cp_addr;
  /** The DOM document containing the information from the
      the SOAP header. */
  pal_xml_top *soap_header;
  
}pal_upnp_action_request;

/** Represents the request for current value of a state variable in a service
 *  state table.  */

typedef struct{
  /** The result of the operation. */
  INT32 error_code;
  /** The socket number of the connection to the requestor. */
  INT32 socket;
  /** The error string in case of error. */
  CHAR err_str[PAL_UPNP_LINE_SIZE];
  /** The unique device ID. */
  CHAR dev_udn[PAL_UPNP_NAME_SIZE];
  /** The  service ID. */
  CHAR service_id[PAL_UPNP_NAME_SIZE];
  /** The name of the variable. */
  CHAR statvar_name[PAL_UPNP_NAME_SIZE];
  /** IP address of sender requesting the state variable. */
  struct in_addr cp_addr;
  /** The current value of the variable. This needs to be allocated by 
   *  the caller.  When finished with it, the SDK frees this {\bf DOMString}. */
  CHAR* CurrentVal;
}pal_upnp_state_var_request;


typedef struct{
  /** The identifier for the service being subscribed to. */
  CHAR *ServiceId; 
  /** Universal device name. */
  CHAR *UDN;       
  /** The assigned subscription ID for this subscription. */
  pal_upnp_sid Sid;
}pal_upnp_subscription_request;


/************************************************************
 * Function: PAL_upnp_init 
 *
 *  Parameters:	
 *      lo_ip: Input. Local IP Address. 
 *           If input is NULL, an appropriate IP address will be automatically selected.
 *      lo_port: Input . Local Port to listen for incoming connections.
 *           If input is NULL, a appropriate port will be automatically selected. 
 *
 *  Description:
 *      Start UPnP Stack - Initialization.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/   
INT32 PAL_upnp_init(IN const CHAR *lo_ip, IN UINT16 lo_port);


/************************************************************
 * Function: PAL_upnp_get_ipaddress 
 *
 *  Parameters:	
 *      
 *  Description:
 *      Gives back the local ipaddress.
 *
 *  Return Values: INT32
 *      return the IP address string on success else NULL of failure
 ************************************************************/ 
CHAR *PAL_upnp_get_ipaddress();

/************************************************************
 * Function: PAL_upnp_get_port 
 *
 *  Parameters:	
 *      
 *  Description:
 *      Gives back the port for listening ssdp.
 *
 *  Return Values: INT32
 *      return the port number on success else 0 of failure
 ************************************************************/
UINT16 PAL_upnp_get_port();


/************************************************************
 * Function: PAL_upnp_register_root_device
 *
 *  Parameters:	
 *      lo_path: Input. Local path for device description file. 
 *      file_name: Input. File name of device description file.
 *      func: Input. Callback functions for device events      
 *      cookie: Input. Reserved.
 *      handle: Output. Device handle.        
 * 
 *  Description:
 *     This function registers a device application with
 *	the UPnP Library.  A device application cannot make any other API
 *	calls until it registers using this function. 
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/  
INT32 PAL_upnp_register_root_device(IN const CHAR *lo_path,
                                  IN const CHAR *file_name,
                                  IN pal_upnp_func func,
                                  IN const VOID *cookie,
                                  OUT pal_upnp_device_handle *handle);


/************************************************************
 * Function: PAL_upnp_unregister_root_device 
 *
 *  Parameters:	
 *      handle: Input. Device handle.        
 * 
 *  Description:
 *     This function unregisters a root device registered with 
 *	PAL_upnp_register_root_device. After this call, the 
 *	pal_upnp_device_handle handle is no longer valid. For all advertisements that 
 *	have not yet expired, the UPnP library sends a device unavailable message 
 *	automatically. 
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_unregister_root_device(IN pal_upnp_device_handle handle);



/************************************************************
 * Function: PAL_upnp_send_advertisement 
 *
 *  Parameters:	
 *      handle: Input. Handle for device instance.    
 *      expire: Input. Timer of seconds for resending the advertisement.    
 * 
 *  Description:
 *     This function sends the device advertisement. It also schedules a
 *	job for the next advertisement after "expire" time.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_send_advertisement(IN pal_upnp_device_handle handle, IN INT32 expire);


/************************************************************
 * Function: PAL_upnp_register_cp 
 *
 *  Parameters:	
 *      func: Input. Pointer to a function for receiving 
 *		               asynchronous events.    
 *      cookie: Input. Reserved. 
 *      handle: Output. Pointer to a variable to store 
 *		               the new control point handle.  
 * 
 *  Description:
 *     This function registers a control point application with the
 *	UPnP Library.  A control point application cannot make any other API 
 *	calls until it registers using this function.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_register_cp (IN pal_upnp_func func,
                           IN const VOID *cookie,
                           OUT pal_upnp_cp_handle *handle);


/************************************************************
 * Function: PAL_upnp_unregister_cp 
 *
 *  Parameters:	
 *      handle: Input. The handle of the control point instance 
 *		               to unregister.   
 * 
 *  Description:
 *      This function unregisters a client registered with 
 *	PAL_upnp_register_cp. After this call, the 
 *	pal_upnp_cp_handle handle is no longer valid. The UPnP Library generates 
 *	no more callbacks after this function returns.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_unregister_cp(IN pal_upnp_cp_handle handle);


/************************************************************
 * Function: PAL_upnp_search_async 
 *
 *  Parameters:	
 *      handle: Input. The handle of the control point instance 
 *		  max_timeout: Input. Maximum time to wait for the search reply.
 *		  target: Input. Search target string.
 *		  cookie: Input. Reserved. 
 * 
 *  Description:
 *      This function searches for the devices for the provided maximum time.
 *	It is a asynchronous function. It schedules a search job and returns. 
 *	control point is notified about the search results after search timer.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_search_async(IN pal_upnp_cp_handle handle,
                           IN INT32 max_timeout,
                           IN const CHAR *target,
                           IN const VOID *cookie);


/************************************************************
 * Function: PAL_upnp_make_action 
 *
 *  Parameters:	
 *      action: InputOutput. Action buffer.
 *      action_name: Input. Action name.
 *      service_type: Input. Service Type.
 *      nb_params: Input. Number of pairs of parameters.
 *	params: Input. Parameter pairs array.
 *	action_type: Input. Request or response. 
 * 
 *  Description:
 *      This function creates the action(request/response) from the argument
 *      list.This function creates the action request or response if it is a first
 * argument else it will add the argument in the document.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_make_action( INOUT pal_xml_top** action,
                           IN const CHAR *action_name,
                           IN const CHAR *service_type,
                           IN INT32 nb_params,
                           IN const pal_string_pair* params,
                           IN pal_upnp_action_type action_type);


/************************************************************
 * Function: PAL_upnp_send_action 
 *
 *  Parameters:	
 *      handle: Input. Handle of control point to send action.
 *      action_url: Input. The action URL of service.
 *      service_type: Input. The type of the service.
 *      action: Input. The top structure for action.
 *      response: The top structure for the response 
 *		to the action.  The UPnP Library allocates this buffer
 *		and the caller needs to free it.     
 * 
 *  Description:
 *      This function sends a message to change a state variable in a service.
 *	This is a synchronous call that does not return until the action is
 *	complete.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/                       
 INT32 PAL_upnp_send_action( IN pal_upnp_cp_handle handle,
                           IN const CHAR *action_url,
                           IN const CHAR *service_type,
                           IN  pal_xml_top* action,
                           OUT  pal_xml_top **response);


/************************************************************
 * Function: PAL_upnp_download_xmldoc 
 *
 *  Parameters:	
 *      url: Input. Device description url for file downloading.
 *      xml_top: Output. The buffer to strore device description file.
 *               The UPnP Library allocates this buffer
 *		and the caller needs to free it  
 * 
 *  Description:
 *      This function sends a message to change a state variable in a service.
 *	This is a synchronous call that does not return until the action is
 *	complete.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/                    
 INT32 PAL_upnp_download_xmldoc(IN const CHAR *url, OUT pal_xml_top **xml_top);


/************************************************************
 * Function: PAL_upnp_resolve_url 
 *
 *  Parameters:	
 *      base_url: Input. Base URL string.
 *      rel_url: Input. Relative URL string.
 *      abs_url: Output. Absolute URL string. 
 * 
 *  Description:
 *      This functions concatinates the base URL and relative URL to generate
*	the absolute URL.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/                          
 INT32 PAL_upnp_resolve_url(IN const CHAR *base_url,
                          IN const CHAR *rel_url,
                          OUT CHAR **abs_url);


/************************************************************
 * Function: PAL_upnp_finish 
 *
 *  Parameters:	
 *     
 * 
 *  Description:
 *      Stop the UPnP library working and clean resources.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_finish();


/************************************************************
 * Function: PAL_upnp_subscribe 
 *
 *  Parameters:	
 *      handle: Input. Handle of the control point to register event.
 *      event_url: Input. The URL of the service to subscribe to.
 *      timeout: Input/Output. Pointer to a variable containing the requested 
 *		           subscription time.  Upon return, it contains the
 *		           actual subscription time returned from the service. 
 *		  sid: Output. Pointer to a variable to receive the 
 *		               subscription ID (SID)  
 * 
 *  Description:
 *      This function registers a control point to receive event
 *	notifications from another device.  This operation is synchronous
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_subscribe (IN pal_upnp_cp_handle handle,
                         IN const CHAR *event_url,
                         INOUT INT32 *timeout,
                         OUT pal_upnp_sid sid);


/************************************************************
 * Function: PAL_upnp_accept_subscription 
 *
 *  Parameters:	
 *      handle: Input. The handle of the device.
 *      device_id: Input. The device ID of the subdevice of the 
 *		                   service generating the event
 *      service_id: Input.  The unique service identifier of the 
 *		                   service generating the event. 
 *		var_names: Input. Pointer to an array of event variables.
 *      var_vals: Input. Pointer to an array of values for 
 *		                 the event variables.
 *      var_nb: Input. The number of event variables in var_names.
 *      sub_id: Input.  The subscription ID of the newly 
 *		               registered control point.
 * 
 *  Description:
 *      This function accepts a subscription request and sends
 *	out the current state of the eventable variables for a service.  
 *	The device application should call this function when it receives a 
 *	UPNP_EVENT_SUBSCRIPTION_REQUEST callback. This function is sychronous
 *	and generates no callbacks.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
INT32 PAL_upnp_accept_subscription(IN pal_upnp_device_handle handle,
                                 IN const CHAR *device_id,
                                 IN const CHAR *service_id,
                                 IN const CHAR **var_names,
                                 IN const CHAR **var_vals,
                                 IN INT32 var_nb,
                                 IN pal_upnp_sid sub_id);
                                 

/************************************************************
 * Function: PAL_upnp_notify 
 *
 *  Parameters:	
 *      handle: Input. The handle to the device sending the event.
 *      device_id: Input. The device ID of the subdevice of the 
 *		             service generating the event. 
 *		  service_name: Input. The unique identifier of the service 
 *		             generating the event.
 *		  var_name: Input. Pointer to an array of variables that 
 *		           have changed. 
 *		  new_value: Input. Pointer to an array of new values for 
 *		           those variables.  
 *		  var_number: Input. The count of variables included in this 
 *		           notification.
 * 
 *  Description:
 *      This function sends out an event change notification to all
 *	control points subscribed to a particular service.  This function is
 *	synchronous and generates no callbacks.
 *
 *  Return Values: INT32
 *      0 if successful else error code. 
 ************************************************************/
 INT32 PAL_upnp_notify (IN pal_upnp_device_handle handle,
                      IN const CHAR *device_id,
                      IN const CHAR *service_name,
                      IN const CHAR **var_name,
                      IN const CHAR **new_value,
                      IN INT32 var_number);

/************************************************************
 * Function: PAL_upnp_get_error_message 
 *
 *  Parameters:	
 *     errno: Input, error code.
 * 
 *  Description:
 *     This functions returns the error string mapped to the error code.
 *
 *  Return Values: const CHAR *
 *      return either the right string or "Unknown Error"
 ************************************************************/
 const CHAR *PAL_upnp_get_error_message(IN INT32 errno);

#endif //__PAL_UPNP_H__

