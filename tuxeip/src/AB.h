/***************************************************************************
 *   Copyright (C) 2006 by TuxPLC					                                 *
 *   Author Stephane JEANNE s.jeanne@tuxplc.net                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
#ifndef _AB_H
#define _AB_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "CIP_Types.h"
#include "Ethernet_IP.h"

#define UNUSED(expr) do { (void)(expr); } while (0)
	
typedef enum _Plc_Type{Unknow,PLC5,SLC500,LGX} Plc_Type;
typedef enum _DHP_Channel{Channel_A=0x01,Channel_B} DHP_Channel;
typedef enum _Data_Type{UNKNOW,BIT,SINT,TUXINT,DINT,REAL,TIMER,COUNTER} Data_Type; // pvbrowser modification INT already defined in MINGW
//typedef enum _Data_Type{UNKNOW,BIT,SINT,INT,DINT,REAL,TIMER,COUNTER} Data_Type;
typedef enum _PLC_Data_Type{PLC_BIT=1, PLC_BIT_STRING, PLC_BYTE_STRING, \
                            PLC_INTEGER, PLC_TIMER, PLC_COUNTER, PLC_CONTROL, \
                            PLC_FLOATING, PLC_ARRAY, PLC_ADRESS=15, PLC_BCD, \
                            PLC_QUEUE_STATUS, PLC_QUEUE_DATA } PLC_Data_Type;
typedef enum _LGX_Data_Type{LGX_BOOL=0xC1,LGX_BITARRAY=0xD3,LGX_SINT=0xC2,LGX_INT=0xC3,LGX_DINT=0xC4,LGX_REAL=0xCA} LGX_Data_Type;
typedef enum _Data_Req_Type{DATA_REQ=1, QUEUE_STATUS_REQ, QUEUE_DATA_REQ} Data_Req_Type;

#define CNET_Connexion_Parameters 0x4320 //f8
#define DHP_Connexion_Parameters 0x4302

Eip_Connection *_ConnectPLCOverCNET(
		Eip_Session *session,
		Plc_Type Plc,
		BYTE Priority,
		CIP_USINT TimeOut_Ticks,//used to calculate request timeout information
		CIP_UDINT TO_ConnID, //originator's CIP consumed session ID
		CIP_UINT ConnSerialNumber,// session serial number
		CIP_UINT OriginatorVendorID,
		CIP_UDINT OriginatorSerialNumber,
		CIP_USINT TimeOutMultiplier,
		CIP_UDINT RPI,// originator to target packet rate in msec
		CIP_USINT Transport,
		BYTE *path,CIP_USINT pathsize);	
#define ConnectPLCOverCNET(session,Plc,TO_ConnID,ConnSerialNumber,RPI,path,pathsize)\
		_ConnectPLCOverCNET(session,Plc,_Priority,_TimeOut_Ticks,TO_ConnID,ConnSerialNumber,\
		_OriginatorVendorID,_OriginatorSerialNumber,_TimeOutMultiplier,RPI,\
		_Transport,path,pathsize)

Eip_Connection *_ConnectPLCOverDHP(		
		Eip_Session *session,
		Plc_Type Plc,
		BYTE Priority,
		CIP_USINT TimeOut_Ticks,//used to calculate request timeout information
		CIP_UDINT TO_ConnID, //originator's CIP consumed session ID
		CIP_UINT ConnSerialNumber,// session serial number
		CIP_UINT OriginatorVendorID,
		CIP_UDINT OriginatorSerialNumber,
		CIP_USINT TimeOutMultiplier,
		CIP_UDINT RPI,// originator to target packet rate in msec
		CIP_USINT Transport,
		DHP_Channel channel,
		BYTE *path,CIP_USINT pathsize);	
#define ConnectPLCOverDHP(session,Plc,TO_ConnID,ConnSerialNumber,RPI,channel,path,pathsize)\
		_ConnectPLCOverDHP(session,Plc,_Priority,_TimeOut_Ticks,TO_ConnID,ConnSerialNumber,\
		_OriginatorVendorID,_OriginatorSerialNumber,_TimeOutMultiplier,RPI,\
		_Transport,channel,path,pathsize)

#ifdef __cplusplus
}
#endif

#endif /* _AB_H */
