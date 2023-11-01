import axios from 'axios';
import { authConfig, baseUrl, getLogger, withLogs } from '../core';
import { GameProps } from './GameProps';

const gameUrl = `http://${baseUrl}/api/game`;

export const getGames: (token: string, online: boolean) => Promise<GameProps[]> = token => {
    return withLogs(axios.get(gameUrl, authConfig(token)), 'getGames');
}

export const createGame: (token: string, game: GameProps, online: boolean) => Promise<GameProps[]> = (token, game) => {
    return withLogs(axios.post(gameUrl, game, authConfig(token)), 'createGame');
}

export const updateGame: (token: string, game: GameProps, online: boolean) => Promise<GameProps[]> = (token, game) => {
    return withLogs(axios.put(`${gameUrl}/${game._id}`, game, authConfig(token)), 'updateGame');
}

interface MessageData {
    type: string;
    payload: GameProps;
}

const log = getLogger('ws');

export const newWebSocket = (token: string, onMessage: (data: MessageData) => void) => {
    const ws = new WebSocket(`ws://${baseUrl}`);
    ws.onopen = () => {
        log('web socket onopen');
        ws.send(JSON.stringify({ type: 'authorization', payload: { token } }));
    };
    ws.onclose = () => {
        log('web socket onclose');
    };
    ws.onerror = error => {
        log('web socket onerror', error);
    };
    ws.onmessage = messageEvent => {
        log('web socket onmessage');
        onMessage(JSON.parse(messageEvent.data));
    };
    return () => {
        ws.close();
    }
}
