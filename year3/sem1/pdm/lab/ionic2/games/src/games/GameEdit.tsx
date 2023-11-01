import React, { useCallback, useContext, useEffect, useState } from "react";
import {
    IonButton, IonButtons, IonCheckbox,
    IonContent, IonDatetime,
    IonHeader,
    IonInput, IonItem, IonLabel,
    IonLoading,
    IonPage,
    IonTitle,
    IonToolbar
} from "@ionic/react";
import { getLogger} from "../core";
import { GameContext } from "./GameProvider";
import { GameProps } from './GameProps';
import { RouteComponentProps } from "react-router";

const log = getLogger('GameEdit');

interface GameEditProps extends RouteComponentProps<{
    id?: string;
}> {}

const GameEdit: React.FC<GameEditProps> = ({ history, match }) => {
    const { games, saving, savingError, saveGame } = useContext(GameContext);
    const [name, setName] = useState('');
    const [releaseDate, setReleaseDate] = useState(new Date());
    const [finished, setFinished] = useState(false);
    const [rating, setRating] = useState(0);
    const [game, setGame] = useState<GameProps>();
    useEffect(() => {
        log('useEffect');
        const routeId = match.params.id || '';
        const game = games?.find(it => it._id === routeId);
        setGame(game);
        if (game) {
            setName(game.name);
            setReleaseDate(game.releaseDate);
            setFinished(game.finished);
            setRating(game.rating);
        }
    }, [match.params.id, games]);
    const handleSave = () => {
        const editedGame = game ? { ...game, name, releaseDate, finished, rating, updatedOnServer: false } : { name, releaseDate, finished, rating, updatedOnServer: false };
        saveGame && saveGame(editedGame).then(() => history.goBack());
    };
    log('render');
    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonTitle>Edit game</IonTitle>
                    <IonButtons slot="end">
                        <IonButton onClick={handleSave}>
                            Save
                        </IonButton>
                    </IonButtons>
                </IonToolbar>
            </IonHeader>
            <IonContent>
                <IonItem>
                    <IonLabel position="floating">Name</IonLabel>
                    <IonInput value={name} onIonInput={e => setName(e.detail.value || '')}></IonInput>
                </IonItem>
                <IonItem>
                    <IonLabel position="floating">Release Date</IonLabel>
                    <IonDatetime
                        value={releaseDate.toLocaleString()}
                        presentation="date"
                        max={new Date().toLocaleDateString()}
                        onIonChange={(e) => {
                            const selectedDate = new Date(e.detail.value as string); // Explicitly cast to string
                            setReleaseDate(selectedDate);
                        }}
                    ></IonDatetime>
                </IonItem>
                <IonItem>
                    <IonLabel>Finished</IonLabel>
                    <IonCheckbox checked={finished} onIonChange={e => setFinished(e.detail.checked)}></IonCheckbox>
                </IonItem>
                <IonItem>
                    <IonLabel position="floating">Rating</IonLabel>
                    <IonInput
                        type="number"
                        inputmode="numeric"
                        min="1"
                        max="10"
                        step="0.1"
                        value={rating}
                        onIonChange={e => {
                            const inputValue = parseFloat(e.detail.value || '1');
                            const newValue = Math.min(10, Math.max(1, inputValue));
                            console.log(newValue)
                            setRating(newValue);
                        }}
                    ></IonInput>
                </IonItem>
                <IonLoading isOpen={saving} />
                {savingError && (
                    <div>{savingError.message || 'Failed to save the game'}</div>
                )}
            </IonContent>
        </IonPage>
    )
}

export default GameEdit;