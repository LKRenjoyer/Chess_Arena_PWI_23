import React,{Component} from "react";
import {render} from "react-dom"
import { createRoot } from 'react-dom/client';
import { BrowserRouter as Router, Route,Routes} from 'react-router-dom';
// import Chess from "./chess";
// import PlayRandomMoveEngine from "./game";
import Main from "./main";

export default function App() {
    return (
      <Router >
        <Routes>
          <Route exact path="/" element={<Main />} />
        </Routes>
      </Router>
    )
}

const root = createRoot(document.getElementById('app')); // Wskazuje na element HTML, w którym chcesz umieścić aplikację
root.render(<App />);