import './style.css';
import { useEffect, useState } from "react";


export function Input({ setWords, vals }){
    const [hello,setHello] = useState(null);
    const [letters,setLetters] = useState("");
    
    const getHello = async () => {
      const response = await fetch("http://127.0.0.1:5000/api/home", {method: "GET"});
  
      const js = await response.json();
      console.log(js.message);
      return js.message;
    }
  
  
  const clickHandler = async () => {
    const message = await getHello();
    setHello(message);
  };
    async function handleSubmit(e){
      //disable page from reloading
      e.preventDefault();
  
    const data = [letters, vals];
      const result = await fetch("https://ahidas.pythonanywhere.com/api/letters",{method: 'POST', body: data});
      const js = await result.json();
      console.log(js);
      setWords(js);
    }


    return (<> 
        <form onSubmit={handleSubmit}> 
        <div> {hello} </div>
          <input className='lettersInput' onChange={(e) => {
      const value = e.target.value;
      const regMatch = /^[a-zA-Z]*$/.test(value);
  
      if (regMatch && e.target.value.length <= 7) {
      setLetters(e.target.value)
          }}}value={letters} type="text" placeholder='Enter your letters...'/> 
          
          <button onClick={clickHandler}> Analyze...</button>
          </form> 
    </>)
  }
  