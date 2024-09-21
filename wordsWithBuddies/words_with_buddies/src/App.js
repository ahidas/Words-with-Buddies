/*
To Do -
Make it easier to type in the words

Create Database to save old boards

keep track of your letters

*/
import './style.css';
import { useEffect, useState,useRef } from "react";
import { GameBoard } from './board.js';
import { Input } from './input.js';
import { UserForm } from './Users.js';
import { UserBoards } from './userBoards.js';
import { BestWords } from './words.js';

const emptyBoard = [
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""],
  ["","","","","","","","","","","","","","",""]
  ];

function App() {
  const [words, setWords] = useState(null);
  const [vals, setVals] = useState(emptyBoard.map(function(arr) { return arr.slice();}));
  const [percent, setPercent] = useState(0.0);
  const [loggedIn, setLoggedIn] = useState(false);
  const curr_board = useRef("");
  const prev_vals = useRef(emptyBoard);

  return (
   <div className='site'> 

    <Header vals = { vals } loggedIn = {loggedIn} setLoggedIn = { setLoggedIn } setVals ={setVals} emptyBoard={emptyBoard} curr_board={curr_board} setWords={setWords}/> 

    <div className='body'>
      <div className='boardAndInput'>
    <text> Enter your current GameBoard in the grid - then your letters - then click analyze!</text> <br/>
    <text> (Press enter to switch direction of typing) </text>
    <GameBoard vals={vals} setVals={setVals}/>
    <Input setWords ={setWords} vals={vals} setPercent = {setPercent} percent = {percent} prev_vals={prev_vals}/> 
    </div>
    <BestWords words={words} setVals={setVals} vals={vals} percent={percent} prev_vals={prev_vals}/>

   </div>
  </div>
  );
}

function Header({loggedIn, setLoggedIn, vals, setVals, emptyBoard, curr_board, setWords}){
  return( <>
  <div className='user_form_boards'> 
      <UserForm vals = { vals } loggedIn = { loggedIn } setLoggedIn = { setLoggedIn } curr_board={curr_board}/>
      {loggedIn ? <UserBoards setVals = { setVals } emptyBoard={emptyBoard} curr_board={curr_board} setWords={setWords}/> : null}
      </div>
      <header className="head"> 
        <h1> Words with Buddies!</h1>
      </header>
   </>)
}



export default App;
