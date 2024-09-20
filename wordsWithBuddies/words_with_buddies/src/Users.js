import { useEffect, useRef } from "react";



export function user_form(){
    return (<div> 
        <signUp/>
        <login/>
    </div>)
}

function signUp(){
    const Username = useRef("");
    const Password = useRef("");
    async function handleSubmit(e){
            //disable page from reloading
        e.preventDefault();
        const data = {"username": Username.current, "password": Password.current};
          //getting updates
        const result = await fetch("http://127.0.0.1:5006/api/sign_up",{method: 'POST', credentials: 'include', data: data});
        const js = await result.json();
        console.log(js);
        if(js === true){
            alert("Successfully signed up");
        }
    }
    return (<div>
        <header> Sign Up </header>
        <form className="user_form" onSubmit={handleSubmit}> 
        <input className = "user_form_input" type="text" placeholder='Username' 
        onChange={(e) => {
      const value = e.target.value;
      if (e.target.value.length <= 15) {
        Username.current = e.target.value;
          }
        }}
        />
        <input className = "user_form_input" type="text" placeholder='Password' 
                onChange={(e) => {
                    const value = e.target.value;
                    if (e.target.value.length <= 15) {
                      Password.current = e.target.value;
                        }
                      }}
                      />
        <button> Sign up</button>
        </form>
    </div>)
}

function login(){
    const Username = useRef("");
    const Password = useRef("");
    async function handleSubmit(e){
            //disable page from reloading
        e.preventDefault();
        const data = {"username": Username.current, "password": Password.current};
          //getting updates
        const result = await fetch("http://127.0.0.1:5006/api/login",{method: 'POST', credentials: 'include', data: data});
        const js = await result.json();
        console.log(js);
        if(js === true){
            alert("Successfully logged in");
        }
    }
    return (<div>
        <header> Login </header>
        <form className="user_form" onSubmit={handleSubmit}> 
        <input className = "user_form_input" type="text" placeholder='Username' 
        onChange={(e) => {
      const value = e.target.value;
      if (e.target.value.length <= 15) {
        Username.current = e.target.value;
          }
        }}
        />
        <input className = "user_form_input" type="text" placeholder='Password' 
                onChange={(e) => {
                    const value = e.target.value;
                    if (e.target.value.length <= 15) {
                      Password.current = e.target.value;
                        }
                      }}
                      />
        <button> Sign up</button>
        </form>
    </div>)
}