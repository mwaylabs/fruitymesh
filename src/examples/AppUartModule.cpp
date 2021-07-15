////////////////////////////////////////////////////////////////////////////////
// /****************************************************************************
// **
// ** Copyright (C) 2015-2021 M-Way Solutions GmbH
// ** Contact: https://www.blureange.io/licensing
// **
// ** This file is part of the Bluerange/FruityMesh implementation
// **
// ** $BR_BEGIN_LICENSE:GPL-EXCEPT$
// ** Commercial License Usage
// ** Licensees holding valid commercial Bluerange licenses may use this file in
// ** accordance with the commercial license agreement provided with the
// ** Software or, alternatively, in accordance with the terms contained in
// ** a written agreement between them and M-Way Solutions GmbH.
// ** For licensing terms and conditions see https://www.bluerange.io/terms-conditions. For further
// ** information use the contact form at https://www.bluerange.io/contact.
// **
// ** GNU General Public License Usage
// ** Alternatively, this file may be used under the terms of the GNU
// ** General Public License version 3 as published by the Free Software
// ** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
// ** included in the packaging of this file. Please review the following
// ** information to ensure the GNU General Public License requirements will
// ** be met: https://www.gnu.org/licenses/gpl-3.0.html.
// **
// ** $BR_END_LICENSE$
// **
// ****************************************************************************/
////////////////////////////////////////////////////////////////////////////////

#include <AppUartModule.h>
#include <GlobalState.h>
#include <Logger.h>
#include <Node.h>
#include <Utility.h>
#include <mini-printf.h>

AppUartModule::AppUartModule()
    : Module(APP_UART_MODULE_ID, "appuart")
    , logQueue(logBuffer, APP_UART_LOG_BUFFER_SIZE)
{
    // Register callbacks n' stuff

    // Enable the logtag for our vendor module template
    GS->logger.EnableTag("APPUART");
    // If MACONN is active, the log will be output on the packet transmission itself, so the application log will be
    // sent forever.
#if IS_ACTIVE(APP_UART)
    GS->logger.DisableTag("MACONN");
#endif

    // Save configuration to base class variables
    // sizeof configuration must be a multiple of 4 bytes
    vendorConfigurationPointer = &configuration;
    configurationLength = sizeof(AppUartModuleConfiguration);

    // Set defaults
    ResetToDefaultConfiguration();
}

void AppUartModule::ResetToDefaultConfiguration()
{
    // Set default configuration values
    configuration.moduleId = vendorModuleId;
    configuration.moduleActive = true;
    configuration.moduleVersion = APP_UART_MODULE_CONFIG_VERSION;

    // Set additional config values...

    // This line allows us to have different configurations of this module depending on the featureset
    SET_FEATURESET_CONFIGURATION_VENDOR(&configuration, this);
}

void AppUartModule::ConfigurationLoadedHandler(u8* migratableConfig, u16 migratableConfigLength)
{
    VendorModuleConfiguration* newConfig = (VendorModuleConfiguration*)migratableConfig;

    // Version migration can be added here, e.g. if module has version 2 and config is version 1
    if (newConfig != nullptr && newConfig->moduleVersion == 1) { /* ... */
    };

    // Do additional initialization upon loading the config

    // Start the Module...
}

void AppUartModule::TimerEventHandler(u16 passedTimeDs)
{
    if (SHOULD_IV_TRIGGER(GS->appTimerDs, passedTimeDs, LOG_SENT_INTERVAL_DS)) {
        if (IsConnectSmartPhone()) {
            SendAppLogQueue();
        }
    }
}

#ifdef TERMINAL_ENABLED
TerminalCommandHandlerReturnType AppUartModule::TerminalCommandHandler(const char* commandArgs[], u8 commandArgsSize)
{
    if (commandArgsSize >= 3 && TERMARGS(2, moduleName)) {
        if (TERMARGS(0, "action")) {
            if (!TERMARGS(2, moduleName))
                return TerminalCommandHandlerReturnType::UNKNOWN;
            if (TERMARGS(3, "start")) {
                char command[] = "action 0 status get";
                size_t commandLen = strlen(command);
                AppUartModuleTerminalCommandMessage data;
                data.splitHeader = MessageType::SPLIT_WRITE_CMD;
                data.splitCount = 0;
                data.partLen = commandLen;
                CheckedMemcpy(data.data, command, commandLen);
                SendModuleActionMessage(MessageType::MODULE_TRIGGER_ACTION, NODE_ID_BROADCAST,
                    (u8)AppUartModuleTriggerActionMessages::TERMINAL_COMMAND, 0, (u8*)&data,
                    SIZEOF_APP_UART_MODULE_TERMINAL_COMMAND_MESSAGE_STATIC + commandLen, true);
                return TerminalCommandHandlerReturnType::SUCCESS;
            }
            if (TERMARGS(3, "end")) {
                char command[] = "_status";
                size_t commandLen = strlen(command);
                AppUartModuleTerminalCommandMessage data;
                data.splitHeader = MessageType::SPLIT_WRITE_CMD_END;
                data.splitCount = 1;
                data.partLen = commandLen;
                CheckedMemcpy(data.data, command, commandLen);
                SendModuleActionMessage(MessageType::MODULE_TRIGGER_ACTION, NODE_ID_BROADCAST,
                    (u8)AppUartModuleTriggerActionMessages::TERMINAL_COMMAND, 0, (u8*)&data,
                    SIZEOF_APP_UART_MODULE_TERMINAL_COMMAND_MESSAGE_STATIC + commandLen, true);
                return TerminalCommandHandlerReturnType::SUCCESS;
            }
            if (TERMARGS(3, "log")) {
                logt("APPUART", "sample log from terminal command");
                return TerminalCommandHandlerReturnType::SUCCESS;
            }
        }
    }
    // Must be called to allow the module to get and set the config
    return Module::TerminalCommandHandler(commandArgs, commandArgsSize);
}
#endif

void AppUartModule::MeshMessageReceivedHandler(
    BaseConnection* connection, BaseConnectionSendData* sendData, ConnPacketHeader const* packetHeader)
{
    // Must call superclass for handling
    Module::MeshMessageReceivedHandler(connection, sendData, packetHeader);

    if (packetHeader->messageType == MessageType::MODULE_TRIGGER_ACTION
        && sendData->dataLength >= SIZEOF_CONN_PACKET_MODULE_VENDOR) {
        ConnPacketModuleVendor const* packet = (ConnPacketModuleVendor const*)packetHeader;

        // Check if our module is meant and we should trigger an action
        if (packet->moduleId != vendorModuleId)
            return;

        if (packet->actionType == AppUartModuleTriggerActionMessages::TERMINAL_COMMAND) {
            const AppUartModuleTerminalCommandMessage* data = (const AppUartModuleTerminalCommandMessage*)packet->data;
            // invalid buffer state
            if (readBufferOffset == 0 && data->splitCount > 0) {
                readBufferOffset = 0;
                AppUartModuleTerminalResponseMessage message = { .commandSuccess = 0 };
                SendModuleActionMessage(MessageType::MODULE_ACTION_RESPONSE, packet->header.sender,
                    AppUartModuleActionResponseMessages::TERMINAL_RETURN_TYPE, 0, reinterpret_cast<u8*>(&message),
                    SIZEOF_APP_UART_MODULE_TERMINAL_RESPONSE_MESSAGE, false);
                return;
            }
            // If there is not enough buffer, clear it
            if (TERMINAL_READ_BUFFER_LENGTH - readBufferOffset - 1 < data->partLen) {
                logt("APPUART", "Too large command.");
                readBufferOffset = 0;
                AppUartModuleTerminalResponseMessage message = { .commandSuccess = 0 };
                SendModuleActionMessage(MessageType::MODULE_ACTION_RESPONSE, packet->header.sender,
                    AppUartModuleActionResponseMessages::TERMINAL_RETURN_TYPE, 0, reinterpret_cast<u8*>(&message),
                    SIZEOF_APP_UART_MODULE_TERMINAL_RESPONSE_MESSAGE, false);
                return;
            }
            if ((readBufferOffset == 0 && data->splitCount == 0) || (readBufferOffset > 0 && data->splitCount > 0)) {
                CheckedMemcpy(&(readBuffer[readBufferOffset]), data->data, data->partLen);
                readBufferOffset += data->partLen;

                AppUartModuleTerminalResponseMessage message = { .commandSuccess = 1 };
                SendModuleActionMessage(MessageType::MODULE_ACTION_RESPONSE, packet->header.sender,
                    AppUartModuleActionResponseMessages::TERMINAL_RETURN_TYPE, 0, reinterpret_cast<u8*>(&message),
                    SIZEOF_APP_UART_MODULE_TERMINAL_RESPONSE_MESSAGE, false);

                if (data->splitHeader != MessageType::SPLIT_WRITE_CMD_END)
                    return;
#if IS_ACTIVE(LOGGING)
                char temp[data->partLen + 1];
                CheckedMemcpy(temp, data->data, data->partLen);
                temp[data->partLen] = '\0';
                logt("APPUART", "Got command one message with %s", temp);
#endif
                lineToReadAvailable = true;
                GS->terminal.CheckAndProcessLine();
                lineToReadAvailable = false;
                readBufferOffset = 0;
            }
        }
    }
}

NodeId AppUartModule::GetMeshAccessConnectionInNodeId(bool isVirtual) const
{
    MeshAccessConnections connIn = GS->cm.GetMeshAccessConnections(ConnectionDirection::DIRECTION_IN);
    if (connIn.count < 1)
        return NODE_ID_INVALID;
    return isVirtual ? connIn.handles[0].GetVirtualPartnerId() : connIn.handles[0].GetPartnerId();
}

bool AppUartModule::IsConnectSmartPhone()
{
    const NodeId partnerId = GetMeshAccessConnectionInNodeId();
    return partnerId >= NODE_ID_APP_BASE && partnerId < NODE_ID_GLOBAL_DEVICE_BASE;
}

void AppUartModule::SendAppLogQueue()
{
    if (logQueue._numElements < 2 || !IsConnectSmartPhone())
        return;

    AppUartLogRemain* logRemain = reinterpret_cast<AppUartLogRemain*>(logQueue.PeekNext().data);
    char* log = reinterpret_cast<char*>(logQueue.PeekNext(1).data);
    const u16 logLen = logRemain->logLen;
    AppUartModuleTerminalLogMessage message;
    if (logLen <= DATA_MAX_LEN) {
        message.splitHeader = MessageType::SPLIT_WRITE_CMD_END;
        message.splitCount = 0;
        message.partLen = logLen;
        CheckedMemcpy(message.data, log, logLen);
    }
    const u16 remainLogLen = logLen - logRemain->sentLength;
    if (logLen > DATA_MAX_LEN) {
        message.splitHeader
            = remainLogLen > DATA_MAX_LEN ? MessageType::SPLIT_WRITE_CMD : MessageType::SPLIT_WRITE_CMD_END;
        message.splitCount = (u8)(logRemain->sentLength / DATA_MAX_LEN);
        message.partLen = remainLogLen > DATA_MAX_LEN ? DATA_MAX_LEN : remainLogLen;
        CheckedMemcpy(message.data, &log[logRemain->sentLength], message.partLen);
    }

    const NodeId virtualPartnerId = GetMeshAccessConnectionInNodeId(true);
    SendModuleActionMessage(MessageType::MODULE_ACTION_RESPONSE, virtualPartnerId,
        AppUartModuleActionResponseMessages::RECEIVE_LOG, 0, reinterpret_cast<u8*>(&message),
        SIZEOF_APP_UART_MODULE_TERMINAL_COMMAND_MESSAGE_STATIC + message.partLen, false);
    if (remainLogLen > DATA_MAX_LEN) {
        logRemain->sentLength += DATA_MAX_LEN;
        return;
    }
    // send log completely
    DiscardLogQueue();
}

bool AppUartModule::PutAppLogQueue(const char* log, u16 length)
{
    if (log == NULL || length == 0 || !IsConnectSmartPhone())
        return false;

    AppUartLogRemain remain = { .sentLength = 0, .logLen = length };
    if (!logQueue.Put(reinterpret_cast<u8*>(&remain), sizeof(AppUartLogRemain)))
        return false;
    if (!logQueue.Put(reinterpret_cast<u8*>(const_cast<char*>(log)), length)) {
        logQueue.DiscardLast();
        return false;
    }
    return true;
}

void AppUartModule::DiscardLogQueue()
{
    logQueue.DiscardNext();
    logQueue.DiscardNext();
}
