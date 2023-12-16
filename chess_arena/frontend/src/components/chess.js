import { Chessboard } from "react-chessboard";
import React from 'react';

export default function Chess() {
    return (
        <div className="boardVIS">
            <Chessboard
              position="start"
              onPieceClick={(square) => console.log('Clicked square:', square)}
              boardWidth={500}
            />        
        </div>
    );
}