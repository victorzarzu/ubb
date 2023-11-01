import React, { useContext } from 'react';
import { RouteComponentProps } from 'react-router';
import {
    IonButton,
    IonContent,
    IonFab,
    IonFabButton,
    IonHeader,
    IonIcon,
    IonList, IonLoading,
    IonPage,
    IonTitle,
    IonToolbar
} from '@ionic/react';
import {add, logOut} from 'ionicons/icons';
import Game from './Game';
import { getLogger } from '../core';
import { GameContext } from './GameProvider';
import {AuthContext} from "../auth";
import {NetworkContext} from "../network/NetworkProvider";

const log = getLogger('GameList');

const ItemList: React.FC<RouteComponentProps> = ({ history }) => {
    const { games, fetching, fetchingError } = useContext(GameContext);
    const {logout} = useContext(AuthContext)
    const { connected } = useContext(NetworkContext);
    log('render', fetching);
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Game inventory</IonTitle>
                    <IonTitle>{connected ? 'Online' : 'Offline'}</IonTitle>
                    <IonButton slot="end" onClick={logout}>
                        <IonIcon icon={logOut} />
                    </IonButton>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonLoading isOpen={fetching} message="Fetching games"/>
                {games && (
                    <IonList>
                        {games.map(({ _id, name, releaseDate, finished, rating, updatedOnServer }) =>
                            <Game key={_id} _id={_id} name={name} releaseDate={releaseDate} finished={finished} rating={rating} updatedOnServer={updatedOnServer} onEdit={id => history.push(`/game/${id}`)}/>)}
                    </IonList>
                )}
                {fetchingError && (
                    <div>{fetchingError.message || 'Failed to fetch games'}</div>
                )}
                <IonFab vertical="bottom" horizontal="end" slot="fixed">
                    <IonFabButton onClick={() => history.push('/game')}>
                        <IonIcon icon={add}/>
                    </IonFabButton>
                </IonFab>
            </IonContent>
        </IonPage>
    );
};

export default ItemList;
