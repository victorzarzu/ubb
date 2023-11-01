export interface GameProps {
    _id?: string;
    name: string;
    releaseDate: Date;
    finished: boolean;
    rating: number;
}

export interface InternalGameProps {
    game: GameProps;
    updatedOnServer: boolean;
}