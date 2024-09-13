import './style.css';
import { useEffect, useState } from "react";



export function Input({ setWords, vals, setPercent, percent }){
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
    //getting updates
    fetch("http://127.0.0.1:5006/api/updates").then((res) => {
      const reader = res.body.getReader();

      const read = () => {
        reader.read().then(async ({done, value}) => {
          if (done) {
            console.log("end");
            const result = await fetch("http://127.0.0.1:5006/api/words",{method: 'POST', body: data});
            const js = await result.json();
            console.log(js);
            setWords(js);
            setPercent(0);
            return;
          }

          const decoder = new TextDecoder();

          
          const split_value = decoder.decode(value).split("-");
          console.log(Number(split_value[split_value.length - 2])/2.25);
          setPercent(Number(split_value[split_value.length - 2])/225);
          read();
        });
      };
      read();
    })
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
          
          <button> Analyze...</button>
          </form> 
    </>)
  }
  