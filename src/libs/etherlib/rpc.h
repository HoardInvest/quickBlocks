#pragma once
/*-------------------------------------------------------------------------------------------
 * QuickBlocks - Decentralized, useful, and detailed data from Ethereum blockchains
 * Copyright (c) 2018 Great Hill Corporation (http://quickblocks.io)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include "etherlib.h"

namespace qblocks {

//-----------------------------------------------------
class IPCSocket
{
public:
    IPCSocket   ( const string_q& _path );
    ~IPCSocket   ( );
    string_q        sendRequest ( const string_q& _req);

    const string_q& path        ( void ) const;

private:
    FILE *m_fp;
    string_q m_path;
    int m_socket;
};

//-----------------------------------------------------
IPCSocket::~IPCSocket(void)
{
    close(m_socket);
    fclose(m_fp);
}

//-----------------------------------------------------
const string_q& IPCSocket::path( void ) const
{
    return m_path;
}

//-----------------------------------------------------
class RPCSession
{
public:
    CReceipt           eth_getTransactionReceipt ( const string_q& _transactionHash );
    string_q           eth_getCode               ( const string_q& _address, const string_q& _blockNumber );
    string_q           eth_getBalanc e            ( const string_q& _address, const string_q& _blockNumber );
    string_q           eth_getSt orageRoot        ( const string_q& _address, const string_q& _blockNumber );
    string_q           rpcCall                   (const string_q& _methodName, const string_q& _args);

private:
    RPCSession               (const string_q& _path);

    IPCSocket m_ipcSocket;
    size_t m_rpcSequence = 1;
};
}
