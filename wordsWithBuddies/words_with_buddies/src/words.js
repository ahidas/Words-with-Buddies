


export function BestWords({ words, setVals, vals, percent, prev_vals }){
    return <>
      <div>
        {percent ? <Loading percent={percent}/> : null} 
           {words ? `Total: ${words.total}` : null} <br/>
           {words ? `Longest Word: ${words.words[0].word} for ${words.words[0].points} at position (${words.words[0].position[0]},${words.words[0].position[1]}) in the ${words.words[0].direction ? "horizontal" : "vertical"} direction using ${words.words[0].new_letters} new letters` : null}
          <br/>
          <div className='pot_words'>
          {words ? words.words.slice(1).map((w) => (<TopWord word={w} setVals={setVals} vals={vals} prev_vals={prev_vals}/>)) : null}
          </div>
      </div>
    </>
  }
  
  


function TopWord({word, setVals, vals, prev_vals}){
    
    
    
    if (word.length < 3){
      return null; 
    }
    function handleClick(word){
      let word_arr = word.word.split("");
      console.log(word_arr);
      console.log(word.direction);
      var temp = prev_vals.current.map(function(arr) { return arr.slice();});
      for(let n = 0; n < word.word.length; n++){
        console.log(word_arr[n],n);
         if(word.direction === "horizontal"){
          temp[parseInt(word.position[1])][parseInt(word.position[0]) + n] = word_arr[n];
          console.log('h');
         }else{
          console.log('v', parseInt(word.position[0]) + n - 1, n, word.position[0]);
          temp[parseInt(word.position[1]) + n][parseInt(word.position[0])] = word_arr[n];
         }
      }
      setVals([...temp]);
    }
    return <> <button className='pot' onClick={() => {handleClick(word)}}> {word.word.toUpperCase()} for {word.points} at position ({word.position[0]},{word.position[1]}) in the {word.direction} direction using {word.new_letters} new letters</button> <br/> </>
  }
  
  function Loading({percent}){
  
    return(
        <>
        <text> Finding words at square {Math.floor(percent * 225)}... </text>
        <div className="bar">
            <div className="filler" style={{width: `${percent * 100}%`}}/>
        </div>
        </>
    )
  }
  
