import { useState } from "react";

export function GameBoard({vals, setVals}){
  const board = [];
  for (let i = 0; i < 15; i++){
    board.push(<BuildRow vals={vals} index={i} setVals={setVals}/>);
  }
  return (<div className="board">
  {board}

   </div>)
}
let boxKey = 1;

function BuildRow({ vals, index, setVals }){
  const rows = [];
  let type;
  function changeHandler(i,lett){
    vals[index][i] = lett; 
    console.log(vals);  
    setVals([...vals]);
  }
  for ( let i = 0; i < 15; i++){
    //tripple letter
    if(((index == 0 || index == 14) && (i == 6 || i == 8)) || ((index == 3 || index == 11) && (i == 3  || i == 11)) || ((index==5 || index == 9) && (i == 5 || i == 9)) || ((index == 6 || index == 8) && (i == 0 || i == 14))){
      type =  'box tripleLetter';
  }
  //tripple word
  else if(((index == 0 || index == 14) && (i == 3 || i == 11)) || ((index == 3 || index == 11) && (i == 0  || i == 14))){
      type = 'box tripleWord';
  }
  //Double Letter
  else if(((index == 1 || index == 13) && (i == 2 || i == 12)) || ((index == 2 || index == 12) && (i == 1  || i == 4 || i == 13 || i == 10)) || ((index==4 || index == 10) && (i == 2 || i == 6 || i == 12 || i == 8)) || ((index == 6 || index == 8) && (i == 4 || i == 10))){
      type = 'box doubleLetter';
  }
  ///double word
  else if(((index == 1 || index == 13) && (i == 5 || i == 9)) || ((index == 3 || index == 11) && (i == 7)) || ((index==5 || index == 9) && (i == 1 || i == 13)) || ((index == 7) && (i == 3 || i == 11))){
      type = 'box doubleWord';
  } else if ( index == 7 && i == 7){
        type = "box center"
    }
    else {
        type = "box letter";
    }
   // console.log(type);
    const newCol = <input onChange={(e) => changeHandler(i,e.target.value)} className={type} key={boxKey} value={vals[index][i]} />
    boxKey++;
    rows.push(newCol);
  }

  return (<div className='row'> 
    {rows}
  </div>)
}