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

// actual_client_dom.cpp - [Generated by hdkcli_cpp]

// Local header.
#include "actual_client_dom.h"

using namespace HDK;

Cisco::CiscoStructStruct::CiscoStructStruct() throw() :
    Struct(ACTUAL_CLIENT_DOM_MOD_Element_Cisco_CiscoStruct)
{
}

Cisco::CiscoStructStruct::CiscoStructStruct(HDK_XML_Struct* phdkstruct) throw() :
    Struct(phdkstruct)
{
}

HDK_XML_Int Cisco::CiscoStructStruct::get_a() const throw()
{
    return HDK_XML_GetEx_Int(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_a, 0);
}

void Cisco::CiscoStructStruct::set_a(HDK_XML_Int value) throw()
{
    (void)HDK_XML_Set_Int(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_a, value);
}

const char* Cisco::CiscoStructStruct::get_b() const throw()
{
    return HDK_XML_GetEx_String(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_b, 0);
}

void Cisco::CiscoStructStruct::set_b(const char* value) throw()
{
    (void)HDK_XML_Set_String(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_b, value);
}

HDK_XML_Long Cisco::CiscoStructStruct::get_c() const throw()
{
    return HDK_XML_GetEx_Long(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_c, 0);
}

void Cisco::CiscoStructStruct::set_c(HDK_XML_Long value) throw()
{
    (void)HDK_XML_Set_Long(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_c, value);
}

bool Cisco::CiscoStructStruct::FromFile(const char* pszFile) throw()
{
    return HDK::Struct::DeserializeFromFile(ACTUAL_CLIENT_DOM_MOD_Schema_Cisco_CiscoStruct(), pszFile);
}

bool Cisco::CiscoStructStruct::ToFile(const char* pszFile) const throw()
{
    return HDK::Struct::SerializeToFile(ACTUAL_CLIENT_DOM_MOD_Schema_Cisco_CiscoStruct(), pszFile, 0);
}

Cisco::CiscoStructTooStruct::CiscoStructTooStruct() throw() :
    Struct(ACTUAL_CLIENT_DOM_MOD_Element_Cisco_CiscoStructToo)
{
}

Cisco::CiscoStructTooStruct::CiscoStructTooStruct(HDK_XML_Struct* phdkstruct) throw() :
    Struct(phdkstruct)
{
}

Cisco::CiscoStructStruct Cisco::CiscoStructTooStruct::get_s() const throw()
{
    return HDK_XML_Get_Struct(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_s);
}

void Cisco::CiscoStructTooStruct::set_s(const Cisco::CiscoStructStruct& value) throw()
{
    (void)HDK_XML_SetEx_Struct(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_s, value);
}

HDK_XML_Int Cisco::CiscoStructTooStruct::get_d() const throw()
{
    return HDK_XML_GetEx_Int(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_d, 0);
}

void Cisco::CiscoStructTooStruct::set_d(HDK_XML_Int value) throw()
{
    (void)HDK_XML_Set_Int(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_d, value);
}

const char* Cisco::CiscoStructTooStruct::get_e() const throw()
{
    return HDK_XML_GetEx_String(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_e, 0);
}

void Cisco::CiscoStructTooStruct::set_e(const char* value) throw()
{
    (void)HDK_XML_Set_String(GetStruct(), ACTUAL_CLIENT_DOM_MOD_Element_Cisco_e, value);
}

bool Cisco::CiscoStructTooStruct::FromFile(const char* pszFile) throw()
{
    return HDK::Struct::DeserializeFromFile(ACTUAL_CLIENT_DOM_MOD_Schema_Cisco_CiscoStructToo(), pszFile);
}

bool Cisco::CiscoStructTooStruct::ToFile(const char* pszFile) const throw()
{
    return HDK::Struct::SerializeToFile(ACTUAL_CLIENT_DOM_MOD_Schema_Cisco_CiscoStructToo(), pszFile, 0);
}