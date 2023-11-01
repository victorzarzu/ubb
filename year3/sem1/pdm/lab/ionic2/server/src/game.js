import Router from 'koa-router';
import dataStore from 'nedb-promise';
import { broadcast } from './wss.js';

export class GameStore {
  constructor({ filename, autoload }) {
    this.store = dataStore({ filename, autoload });
  }

  async find(props) {
    return this.store.find(props);
  }

  async findOne(props) {
    return this.store.findOne(props);
  }

  async insert(game) {
    if (!game.name) { // validation
      throw new Error('Missing text property')
    }
    return this.store.insert(game);
  };

  async update(props, game) {
    return this.store.update(props, game);
  }

  async remove(props) {
    return this.store.remove(props);
  }
}

const gameStore = new GameStore({ filename: './db/games.json', autoload: true });

export const gameRouter = new Router();

gameRouter.get('/', async (ctx) => {
  const userId = ctx.state.user._id;
  ctx.response.body = await gameStore.find({ userId });
  ctx.response.status = 200; // ok
});

gameRouter.get('/:id', async (ctx) => {
  const userId = ctx.state.user._id;
  const game = await noteStore.findOne({ _id: ctx.params.id });
  const response = ctx.response;
  if (game) {
    if (game.userId === userId) {
      ctx.response.body = game;
      ctx.response.status = 200; // ok
    } else {
      ctx.response.status = 403; // forbidden
    }
  } else {
    ctx.response.status = 404; // not found
  }
});

const createGame = async (ctx, game, response) => {
  try {
    const userId = ctx.state.user._id;
    game.userId = userId;
    const newGame = await gameStore.insert(game);
    response.body = newGame;
    response.status = 201; // created
    broadcast(userId, { type: 'created', payload: newGame });
  } catch (err) {
    response.body = { message: err.message };
    response.status = 400; // bad request
  }
};

gameRouter.post('/', async ctx => await createGame(ctx, ctx.request.body, ctx.response));

gameRouter.put('/:id', async ctx => {
  const game = ctx.request.body;
  const id = ctx.params.id;
  const gameId = game._id;
  const response = ctx.response;
  if (gameId && gameId !== id) {
    response.body = { message: 'Param id and body _id should be the same' };
    response.status = 400; // bad request
    return;
  }
  if (!gameId) {
    await creategame(ctx, game, response);
  } else {
    const userId = ctx.state.user._id;
    game.userId = userId;
    const updatedCount = await gameStore.update({ _id: id }, game);
    if (updatedCount === 1) {
      response.body = game;
      response.status = 200; // ok
      broadcast(userId, { type: 'updated', payload: game });
    } else {
      response.body = { message: 'Resource no longer exists' };
      response.status = 405; // method not allowed
    }
  }
});

gameRouter.del('/:id', async (ctx) => {
  const userId = ctx.state.user._id;
  const game = await gameStore.findOne({ _id: ctx.params.id });
  if (game && userId !== game.userId) {
    ctx.response.status = 403; // forbidden
  } else {
    await gameStore.remove({ _id: ctx.params.id });
    ctx.response.status = 204; // no content
  }
});
