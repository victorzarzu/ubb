import { Redirect, Route } from 'react-router-dom';
import { IonApp, IonRouterOutlet, setupIonicReact } from '@ionic/react';
import { IonReactRouter } from '@ionic/react-router';

/* Core CSS required for Ionic components to work properly */
import '@ionic/react/css/core.css';

/* Basic CSS for apps built with Ionic */
import '@ionic/react/css/normalize.css';
import '@ionic/react/css/structure.css';
import '@ionic/react/css/typography.css';

/* Optional CSS utils that can be commented out */
import '@ionic/react/css/padding.css';
import '@ionic/react/css/float-elements.css';
import '@ionic/react/css/text-alignment.css';
import '@ionic/react/css/text-transformation.css';
import '@ionic/react/css/flex-utils.css';
import '@ionic/react/css/display.css';

/* Theme variables */
import './theme/variables.css';
import {GameProvider} from "./games/GameProvider";
import GameList from "./games/GameList";
import GameEdit from "./games/GameEdit";
import {AuthProvider, Login, PrivateRoute} from "./auth";
import React from "react";
import {NetworkProvider} from "./network/NetworkProvider";

setupIonicReact();

const App: React.FC = () => (
  <IonApp>
    <IonReactRouter>
      <IonRouterOutlet>
          <NetworkProvider>
            <AuthProvider>
              <Route path="/login" component={Login} exact={true}/>
              <GameProvider>
                    <PrivateRoute path="/games" component={GameList} exact={true}/>
                    <PrivateRoute path="/game" component={GameEdit} exact={true}/>
                    <PrivateRoute path="/game/:id" component={GameEdit} exact={true}/>
              </GameProvider>
              <Route exact path="/" render={() => <Redirect to="/games"/>}/>
            </AuthProvider>
          </NetworkProvider>
      </IonRouterOutlet>
    </IonReactRouter>
  </IonApp>
);

export default App;
