import './style.css';
import { useEffect, useState } from "react";



export function Input({ setWords, vals, setPercent, percent }){
    const [letters,setLetters] = useState("");
    

    async function handleSubmit(e){
      //disable page from reloading
      e.preventDefault();
  
    const data = [letters, vals];
    //getting updates
    fetch("http://13.57.197.254:8000/api/updates",{method: 'POST', credentials: 'include', body: data}).then((res) => {
      const reader = res.body.getReader();

      const read = () => {
        reader.read().then(async ({done, value}) => {
          if (done) {
            console.log("end");
            const result = await fetch("http://13.57.197.254:8000/api/words",{method: 'GET', credentials: 'include'});
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
  