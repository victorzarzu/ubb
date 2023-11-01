import React, { useEffect, useState } from "react";
import { Network, ConnectionStatus } from '@capacitor/network'
import { PluginListenerHandle } from "@capacitor/core";
import PropTypes from "prop-types";

const initialState : ConnectionStatus = {
    connected: false,
    connectionType: 'unknown',
}

export const NetworkContext = React.createContext<ConnectionStatus>(initialState);

interface NetworkProviderProps {
    children: PropTypes.ReactNodeLike;
}

export const NetworkProvider: React.FC<NetworkProviderProps> = ({children}) =>  {
    const [networkStatus, setNetworkStatus] = useState(initialState);
    const value = networkStatus;
    useEffect(() => {
        let handler: PluginListenerHandle;
        registerNetworkStatusChange();
        Network.getStatus().then(handleNetworkStatusChange);
        let canceled = false;
        return () => {
            canceled = true;
            handler?.remove();
        }

        async function registerNetworkStatusChange() {
            handler = await Network.addListener('networkStatusChange', handleNetworkStatusChange);
        }

        async function handleNetworkStatusChange(status: ConnectionStatus) {
            console.log('useNetwork - status change', status);
            if (!canceled) {
                setNetworkStatus(status);
            }
        }
    }, [])
    return (
        <NetworkContext.Provider value = {value}>
            {children}
        </NetworkContext.Provider>
    )
}
export const useNetwork = () => {
    const [networkStatus, setNetworkStatus] = useState(initialState);
    useEffect(() => {
        let handler: PluginListenerHandle;
        registerNetworkStatusChange();
        Network.getStatus().then(handleNetworkStatusChange);
        let canceled = false;
        return () => {
            canceled = true;
            handler?.remove();
        }

        async function registerNetworkStatusChange() {
            handler = await Network.addListener('networkStatusChange', handleNetworkStatusChange);
        }

        async function handleNetworkStatusChange(status: ConnectionStatus) {
            console.log('useNetwork - status change', status);
            if (!canceled) {
                setNetworkStatus(status);
            }
        }
    }, [])

    return { networkStatus };
}