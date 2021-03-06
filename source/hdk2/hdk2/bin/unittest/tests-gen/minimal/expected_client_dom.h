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

/*
 * Copyright (c) 2008-2010 Cisco Systems, Inc. All rights reserved.
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
 */

#pragma once

// actual_client_dom.h - [Generated by hdkcli_cpp]

// Non-generated client code.
#include "hdk_cli_cpp.h"

// Underlying schema module.
#include "actual_client_dom_mod.h"


namespace HDK
{
    ///
    /// \fn InitializeClient
    ///      Initialize the HDK client library.  This should be called once per application instance.
    ///      Each call to InitializeClient should be matched by a call to UninitializeClient.
    ///      \retval true if initialization was successful, false if not.
    ///
    bool InitializeClient() throw();

    ///
    /// \fn UninitializeClient
    ///      Cleanup the HDK client library.  This should be called if true was returned from InitializeClient
    ///      When the caller is done using the HDK client library.
    ///
    void UninitializeClient() throw();


    namespace Cisco
    {
        ///
        /// \enum CiscoActionResult
        ///      <a>http://cisco.com/HNAPExt/CiscoActionResult</a>
        ///
        enum CiscoActionResult
        {
            CiscoActionResult_Unknown = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_CiscoActionResult__UNKNOWN__ /*<! Unknown value */,
            CiscoActionResult_OK = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_CiscoActionResult_OK /*!< OK */,
            CiscoActionResult_ERROR = ACTUAL_CLIENT_DOM_MOD_Enum_Cisco_CiscoActionResult_ERROR /*!< ERROR */
        }; // enum CiscoActionResult

        ///
        /// \brief CiscoAction
        ///      <a>http://cisco.com/HNAPExt/CiscoAction</a>
        ///
        class CiscoActionStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionStruct() throw();

        }; // class CiscoActionStruct : public Struct

        ///
        /// \brief CiscoActionResponse
        ///      <a>http://cisco.com/HNAPExt/CiscoActionResponse</a>
        ///
        class CiscoActionResponseStruct : public Struct
        {
        public:
            //
            // Constructors/Destructor.
            //
            CiscoActionResponseStruct() throw();

            ///
            /// \brief Get the CiscoActionResult value.
            ///
            enum CiscoActionResult get_CiscoActionResult() const throw();

        }; // class CiscoActionResponseStruct : public Struct

        ///
        /// \brief SOAP method URI for action CiscoAction
        ///
#define Cisco_CiscoAction_URI (HDK_MOD_GetMethod(ACTUAL_CLIENT_DOM_MOD_Module(), ACTUAL_CLIENT_DOM_MOD_MethodEnum_Cisco_CiscoAction)->pszSOAPAction)

        ///
        /// \brief Call the CiscoAction method on a given device.
        ///     <a>http://cisco.com/HNAPExt/CiscoAction</a>
        ///     This method uses HTTP method POST and location '/HNAP1'
        ///
        ///     Possible result values:
        ///          - #CiscoActionResult_OK
        ///          - #CiscoActionResult_ERROR
        ///     \arg pTarget The target on which to call this method.
        ///     \arg[optional] result The HNAP result of the CiscoAction HNAP method.
        ///     \arg timeoutSecs An optional timeout, in seconds, to use for the HNAP call.
        ///     \retval The result of the HNAP method call.
        ///
        HDK::ClientError CiscoAction
        (
            HDK::ITarget* pTarget,
            enum CiscoActionResult* presult = NULL,
            unsigned int timeoutSecs = 0
        ) throw();

    } // namespace Cisco
} // namespace HDK
