import { useState } from "react";
import { useRef } from 'react';
import { useEffect } from 'react'





export function GameBoard({vals, setVals}){
  const board = [];
  const [currCor,setCurrCor] = useState([-1,-1]);
  const inputRefs = useRef(Array(15));
  const direction = useRef(true); //1 == horizontal, 0 = vertical

  for (var i = 0; i < 15; i++){
    inputRefs.current[i] = [];
    for(var ix = 0; ix < 15; ix++){
      inputRefs.current[i].push(i * 15 + ix);
     // console.log(inputRefs.current[i][ix]);
    }
  }
  for (let i = 0; i < 15; i++){
    board.push(<BuildRow direction = { direction } vals={vals} index={i} setVals={setVals} inputRefs = {inputRefs} setCurrCor={setCurrCor} />);
  }
  useEffect(() => {
    if(currCor[0] === -1){
      return;
    }
    let x = currCor[0];
    let y = currCor[1];
      if(direction.current){
        while(true){
        if(y === 14){
          return;
        }
        if(vals[x][y+1] === ""){
          inputRefs.current[x][y+1].focus();
          return;
        } else {
          y = y+1;
        }
      }
      } else {
        while(true){
          if(x === 14){
            return;
          }
          if(vals[x+1][y] === ""){
            inputRefs.current[x+1][y].focus();
            return;
          } else {
            x = x+1;
          }
        }
      }

    }
  ,[currCor]);



  return (<div className="board">
  {board}
  
   </div>)
}
let boxKey = 1;

function BuildRow({ vals, index, setVals,inputRefs,setCurrCor, direction }){
  const rows = [];
  let type;
  function changeHandler(i,lett){  //need to figure out how to make it only one let, maybe check lett to see if it is a string larger than 1, or just take the last letter of the string
      vals[index][i] = lett.slice(-1); 
      setVals([...vals]);
      setCurrCor([index,i]);
  }


  for ( let i = 0; i < 15; i++){
    //tripple letter
    if(((index === 0 || index === 14) && (i ===  6 || i ===  8)) || ((index === 3 || index === 11) && (i ===  3  || i ===  11)) || ((index ===5 || index === 9) && (i ===  5 || i ===  9)) || ((index === 6 || index === 8) && (i ===  0 || i ===  14))){
      type =  'box tripleLetter';
  }
  //tripple word
  else if(((index === 0 || index === 14) && (i ===  3 || i ===  11)) || ((index === 3 || index === 11) && (i ===  0  || i ===  14))){
      type = 'box tripleWord';
  }
  //Double Letter
  else if(((index === 1 || index === 13) && (i ===  2 || i ===  12)) || ((index === 2 || index === 12) && (i ===  1  || i ===  4 || i ===  13 || i ===  10)) || ((index === 4 || index === 10) && (i ===  2 || i ===  6 || i ===  12 || i ===  8)) || ((index === 6 || index === 8) && (i ===  4 || i ===  10))){
      type = 'box doubleLetter';
  }
  ///double word
  else if(((index === 1 || index === 13) && (i ===  5 || i ===  9)) || ((index === 3 || index === 11) && (i ===  7)) || ((index ===5 || index === 9) && (i ===  1 || i ===  13)) || ((index === 7) && (i ===  3 || i ===  11))){
      type = 'box doubleWord';
  } else if ( index === 7 && i ===  7){
        type = "box center"
    }
    else {
        type = "box letter";
    }
   // console.log(type);
    const newCol = <input onKeyDown={(e) => {if(e.key === 'Enter'){ direction.current = !direction.current; }}} onChange={(e) => changeHandler(i,e.target.value)} className={type} key={boxKey}  ref={(el) => (inputRefs.current[index][i] = el)} value={vals[index][i]} x = {i} y={index}  />
    boxKey++;
    rows.push(newCol);
    //console.log(inputRefs.current[index][i]);
  }

  return (<div className='row'> 
    {rows}
  </div>)
}