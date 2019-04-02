#pragma once

#include "AuthSocket.h"
#include "WorldSocket.h"

#include "RealmInfo.h"

class CWoWClient : public std::enable_shared_from_this<CWoWClient>
{
public:
	CWoWClient(const std::string& AuthServerHost, uint16 AuthServerPort = 3724);

    // CWoWClient
	void BeginConnect(const std::string& Username, const std::string& Password);
	void OnSuccessConnect(BigNumber Key);

    //
	void AddRealm(RealmInfo& _realm);

	// Getters
    
  
    const uint32 getClientBuild() const { return 5875; }


	const std::string& getHost() const { return m_Host; }
    port_t getPort() const { return m_Port; }
	const std::string& getUsername() const { return m_Username; }
	const std::string& getPassword() const { return m_Password; }

	BigNumber* getKey() { return &m_Key; }

private:
	std::string                     m_Host;
	port_t                          m_Port;
	std::string                     m_Username;
	std::string                     m_Password;

	BigNumber                       m_Key;

	std::vector<RealmInfo>          m_Realms;

    // Sockets controller
    StdoutLog                       m_SocketLog;
    std::shared_ptr<SocketHandler>  m_SocketsHandler;

    // Sockets
	std::shared_ptr<CAuthSocket>    m_AuthSocket;
    std::shared_ptr<CWorldSocket>   m_WorldSocket;

};