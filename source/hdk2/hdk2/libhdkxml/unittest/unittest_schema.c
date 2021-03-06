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

#include "unittest_schema.h"


/* Namespace table */
HDK_XML_Namespace g_schema_namespaces[] =
{
    /* 0 */ "",
    /* 1 */ "http://cisco.com/",
    /* 2 */ "http://cisco.com/HNAPExt/",
    HDK_XML_Schema_NamespacesEnd
};

/* Elements table */
HDK_XML_ElementNode g_schema_elements[] =
{
    /* Element_NoNamespace */ { 0, "NoNamespace" },
    /* Element_a */ { 1, "a" },
    /* Element_b */ { 1, "b" },
    /* Element_c */ { 1, "c" },
    /* Element_d */ { 1, "d" },
    /* Element_e */ { 1, "e" },
    /* Element_f */ { 1, "f" },
    /* Element_g */ { 1, "g" },
    /* Element_h */ { 1, "h" },
    /* Element_i */ { 1, "i" },
    /* Element_j */ { 1, "j" },
    /* Element_k */ { 1, "k" },
    /* Element_Cisco_Bar */ { 2, "Bar" },
    /* Element_Cisco_Foo */ { 2, "Foo" },
    HDK_XML_Schema_ElementsEnd
};
