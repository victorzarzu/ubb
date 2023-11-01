import React, { useCallback, useContext, useEffect, useReducer } from 'react';
import PropTypes from 'prop-types';
import { getLogger } from '../core';
import { GameProps } from './GameProps';
import { createGame, getGames, newWebSocket, updateGame } from './GameApi';
import { AuthContext } from '../auth';
import {NetworkContext} from "../network/NetworkProvider";

const log = getLogger('GameProvider');

type SaveGameFn = (game: GameProps) => Promise<any>;

export interface GamesState {
    games?: GameProps[],
    fetching: boolean,
    fetchingError?: Error | null,
    saving: boolean,
    savingError?: Error | null,
    saveGame?: SaveGameFn,
}

interface ActionProps {
    type: string,
    payload?: any,
}

const initialState: GamesState = {
    fetching: false,
    saving: false,
};

const FETCH_GAMES_STARTED = 'FETCH_GAMES_STARTED';
const FETCH_GAMES_SUCCEEDED = 'FETCH_GAMES_SUCCEEDED';
const FETCH_GAMES_FAILED = 'FETCH_GAMES_FAILED';
const SAVE_GAME_STARTED = 'SAVE_GAME_STARTED';
const SAVE_GAME_SUCCEEDED = 'SAVE_GAME_SUCCEEDED';
const SAVE_GAME_FAILED = 'SAVE_GAME_FAILED';

const reducer: (state: GamesState, action: ActionProps) => GamesState =
    (state, { type, payload }) => {
        switch (type) {
            case FETCH_GAMES_STARTED:
                return { ...state, fetching: true, fetchingError: null };
            case FETCH_GAMES_SUCCEEDED:
                return { ...state, games: payload.games, fetching: false };
            case FETCH_GAMES_FAILED:
                return { ...state, fetchingError: payload.error, fetching: false };
            case SAVE_GAME_STARTED:
                return { ...state, savingError: null, saving: true };
            case SAVE_GAME_SUCCEEDED:
                const games = [...(state.games || [])];
                const game = payload.game;
                if(!game._id) {
                    return state;
                }
                const index = games.findIndex(it => it._id === game._id);
                if (index === -1) {
                    games.splice(0, 0, game);
                } else {
                    games[index] = game;
                }
                return { ...state, games, saving: false };
            case SAVE_GAME_FAILED:
                return { ...state, savingError: payload.error, saving: false };
            default:
                return state;
        }
    };

export const GameContext = React.createContext<GamesState>(initialState);

interface GameProviderProps {
    children: PropTypes.ReactNodeLike,
}

export const GameProvider: React.FC<GameProviderProps> = ({ children }) => {
    const { token } = useContext(AuthContext);
    const { connected } = useContext(NetworkContext);
    const [state, dispatch] = useReducer(reducer, initialState);
    const { games, fetching, fetchingError, saving, savingError } = state;
    useEffect(getGamesEffect, [token]);
    useEffect(wsEffect, [token]);
    const saveGame = useCallback<SaveGameFn>(saveGameCallback, [token]);
    const value = { games, fetching, fetchingError, saving, savingError, saveGame };
    log('returns');
    return (
        <GameContext.Provider value={value}>
            {children}
        </GameContext.Provider>
    );

    function getGamesEffect() {
        let canceled = false;
        if (token) {
            fetchGames();
        }
        return () => {
            canceled = true;
        }

        async function fetchGames() {
            try {
                log('fetchGames started');
                dispatch({ type: FETCH_GAMES_STARTED });
                const games = await getGames(token, connected);
                log('fetchGames succeeded');
                if (!canceled) {
                    dispatch({ type: FETCH_GAMES_SUCCEEDED, payload: { games } });
                }
            } catch (error) {
                log('fetchGames failed', error);
                dispatch({ type: FETCH_GAMES_FAILED, payload: { error } });
            }
        }
    }

    async function saveGameCallback(game: GameProps) {
        try {
            log('saveGame started');
            dispatch({ type: SAVE_GAME_STARTED });
            const savedGame = await (game._id ? updateGame(token, game, connected) : createGame(token, game, connected));
            log('saveGame succeeded');
            dispatch({ type: SAVE_GAME_SUCCEEDED, payload: { game: savedGame } });
        } catch (error) {
            log('saveGame failed');
            dispatch({ type: SAVE_GAME_FAILED, payload: { error } });
        }
    }

    function wsEffect() {
        let canceled = false;
        log('wsEffect - connecting');
        let closeWebSocket: () => void;
        if (token?.trim()) {
            closeWebSocket = newWebSocket(token, message => {
                if (canceled) {
                    return;
                }
                const { type, payload: game } = message;
                log(`ws message, game ${type}`);
                if (type === 'created' || type === 'updated') {
                    dispatch({ type: SAVE_GAME_SUCCEEDED, payload: { game } });
                }
            });
        }
        return () => {
            log('wsEffect - disconnecting');
            canceled = true;
            closeWebSocket?.();
        }
    }
};
