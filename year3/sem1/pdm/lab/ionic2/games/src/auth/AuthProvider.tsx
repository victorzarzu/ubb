import React, { useCallback, useEffect, useState } from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { login as loginApi } from './authApi';
import { Preferences } from "@capacitor/preferences";
import {Simulate} from "react-dom/test-utils";
import cancel = Simulate.cancel;

const log = getLogger('AuthProvider');

type LoginFn = (username?: string, password?: string) => void;
type LogoutFn = () => void;

export interface AuthState {
    authenticationError: Error | null;
    isAuthenticated: boolean;
    isAuthenticating: boolean;
    login?: LoginFn;
    logout?: LogoutFn;
    pendingAuthentication?: boolean;
    pendingLogout?: boolean;
    username?: string;
    password?: string;
    token: string;
}

const initialState: AuthState = {
    isAuthenticated: false,
    isAuthenticating: false,
    authenticationError: null,
    pendingAuthentication: false,
    pendingLogout: false,
    token: '',
};

export const AuthContext = React.createContext<AuthState>(initialState);

interface AuthProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const AuthProvider: React.FC<AuthProviderProps> = ({ children }) => {
    const [state, setState] = useState<AuthState>(initialState);
    const { isAuthenticated, isAuthenticating, authenticationError, pendingAuthentication, token } = state;
    const login = useCallback<LoginFn>(loginCallback, []);
    const logout = useCallback<LogoutFn>(logoutCallback, []);
    useEffect(authenticationEffect, [pendingAuthentication]);
    useEffect(checkAuthenticateEffect, []);
    const value = { isAuthenticated, login, logout, isAuthenticating, authenticationError, token };
    log('render');
    return (
        <AuthContext.Provider value={value}>
            {children}
        </AuthContext.Provider>
    );

    function loginCallback(username?: string, password?: string): void {
        log('login');
        setState({
            ...state,
            pendingAuthentication: true,
            username,
            password
        });
    }

    function logoutCallback(): void {
        log('login');
        setState({
            ...state,
            pendingLogout: true
        });
    }

    function authenticationEffect() {
        let canceled = false;
        authenticate();
        return () => {
            canceled = true;
        }

        async function authenticate() {
            if (!pendingAuthentication) {
                log('authenticate, !pendingAuthentication, return');
                return;
            }
            try {
                const res1 = await Preferences.get({key: 'token'});
                if(res1.value) {
                    console.log('Token found', res1.value);
                }
                log('authenticate...');
                setState({
                    ...state,
                    isAuthenticating: true,
                });
                const { username, password } = state;
                const { token } = await loginApi(username, password);
                if (canceled) {
                    return;
                }
                log('authenticate succeeded');
                await Preferences.set({
                    key: 'token',
                    value: token
                });
                const res = await Preferences.get({key: 'token'});
                if(res.value) {
                    console.log('Token found', res.value);
                }
                setState({
                    ...state,
                    token,
                    pendingAuthentication: false,
                    isAuthenticated: true,
                    isAuthenticating: false,
                });
            } catch (error) {
                if (canceled) {
                    return;
                }
                log('authenticate failed');
                setState({
                    ...state,
                    authenticationError: error as Error,
                    pendingAuthentication: false,
                    isAuthenticating: false,
                });
            }
        }
    }

    function checkAuthenticateEffect() {
        let canceled = false;
        checkAuthenticate();
        return () => {
            canceled = true;
        }

        async function checkAuthenticate() {
            try {
                const res = await Preferences.get({key: 'token'});
                const token = res.value;
                if(token) {
                    setState({
                        ...state,
                        token,
                        pendingAuthentication: false,
                        isAuthenticated: true,
                        isAuthenticating: false,
                    });
                }
            } catch (error) {
                if (canceled) {
                    return;
                }
                log('authenticate failed');
                setState({
                    ...state,
                    authenticationError: error as Error,
                    pendingAuthentication: false,
                    isAuthenticating: false,
                });
            }
        }
    }

    function logoutEffect() {
        let canceled = false;
        logout();
        return () => {
            canceled = true;
        }

        async function logout() {
            await Preferences.remove({ key: 'token '});
            setState({
                ...state,
                token: '',
                pendingLogout: false,
            });
        }
    }
};
