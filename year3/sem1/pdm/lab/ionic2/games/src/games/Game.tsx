import React, {memo} from 'react'
import {IonItem, IonCard, IonLabel, IonCardTitle, IonCardSubtitle, IonCardContent} from '@ionic/react'
import { getLogger } from '../core'
import { GameProps } from './GameProps'

const log = getLogger('Game');

interface GamePropsEdit extends GameProps {
    onEdit: (_id?: string) => void;
}

const Game: React.FC<GamePropsEdit> = ({ _id, name, releaseDate, finished, rating, updatedOnServer, onEdit }) => {
    return (
        <IonCard onClick={() => onEdit(_id)}>
            <IonCardTitle>{name}</IonCardTitle>
            <IonCardSubtitle>{"Released on " + releaseDate} - {rating} / 10</IonCardSubtitle>
            <IonCardContent>{finished ? "Finished" : "Not finished"}</IonCardContent>
            <IonCardContent>{updatedOnServer ? "Sent to server" : "Not sent to server"}</IonCardContent>
        </IonCard>
    )
}

export default memo(Game)