import React,{Component} from "react";
import {render} from "react-dom"
import { createRoot } from 'react-dom/client';

export default function App() {
    return (
      <div>
        cokolwiek
      </div>
    )
  }

const root = createRoot(document.getElementById('app')); // Wskazuje na element HTML, w którym chcesz umieścić aplikację
root.render(<App />);